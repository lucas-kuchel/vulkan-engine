#include <window/window.hpp>

#include <format>
#include <stdexcept>

namespace engine::window
{
    Window::Window()
        : width_(0), height_(0), x_(0), y_(0), title_(), visibility_(Visibility::WINDOWED), handle_(nullptr) {
    }

    void Window::create(const CreateInfo& createInfo) {
        if (handle_) {
            throw std::runtime_error("window already created");
        }

        width_ = createInfo.width;
        height_ = createInfo.height;
        title_ = createInfo.title;
        visibility_ = createInfo.visibility;

        // determine if window is resizeable
        glfwWindowHint(GLFW_RESIZABLE, createInfo.resizable);

        handle_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);

        if (!handle_) {
            const char* message = nullptr;

            glfwGetError(&message);

            throw std::runtime_error(std::format("error creating window:\n\n{}", message));
        }

        switch (visibility_) {
            case Visibility::WINDOWED:
                glfwRestoreWindow(handle_);
                break;

            case Visibility::MINIMISED:
                glfwIconifyWindow(handle_);
                break;

            case Visibility::FULLSCREEN: {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                glfwSetWindowMonitor(
                    handle_,
                    monitor,
                    0, 0,
                    mode->width, mode->height,
                    mode->refreshRate);
                break;
            }
        }

        // store this window in the GLFW user pointer
        // this allows callbacks to load our window data
        glfwSetWindowUserPointer(handle_, this);

        // set all the window callbacks
        glfwSetWindowSizeCallback(handle_, resizeCallback);
        glfwSetWindowPosCallback(handle_, moveCallback);
        glfwSetWindowCloseCallback(handle_, closeCallback);
        glfwSetWindowFocusCallback(handle_, focusCallback);
        glfwSetWindowIconifyCallback(handle_, iconifyCallback);
        glfwSetKeyCallback(handle_, keyCallback);
        glfwSetMouseButtonCallback(handle_, mouseButtonCallback);
        glfwSetCursorPosCallback(handle_, mousePositionCallback);
        glfwSetScrollCallback(handle_, mouseScrollCallback);
    }

    Window::~Window() {
        if (handle_) {
            glfwDestroyWindow(handle_);

            handle_ = nullptr;
        }
    }

    std::queue<Event>& Window::queryEvents() noexcept {
        return events_;
    }

    void Window::setSize(std::size_t width, std::size_t height) {
        if (!handle_) {
            throw std::runtime_error("window not created");
        }

        width_ = width;
        height_ = height;

        glfwSetWindowSize(handle_, width_, height_);
    }

    const std::size_t& Window::getWidth() const noexcept {
        return width_;
    }

    const std::size_t& Window::getHeight() const noexcept {
        return height_;
    }

    void Window::setPosition(std::size_t x, std::size_t y) {
        if (!handle_) {
            throw std::runtime_error("window not created");
        }

        x_ = x;
        y_ = y;

        glfwSetWindowPos(handle_, x_, y_);
    }

    const std::size_t& Window::getX() const noexcept {
        return x_;
    }

    const std::size_t& Window::getY() const noexcept {
        return y_;
    }

    void Window::setTitle(const std::string& title) {
        if (!handle_) {
            throw std::runtime_error("window not created");
        }

        title_ = title;

        glfwSetWindowTitle(handle_, title_.c_str());
    }

    const std::string& Window::getTitle() const noexcept {
        return title_;
    }

    void Window::setVisibility(Visibility visibility) {
        if (!handle_) {
            throw std::runtime_error("window not created");
        }

        visibility_ = visibility;

        switch (visibility_) {
            case Visibility::WINDOWED:
                glfwRestoreWindow(handle_);
                break;

            case Visibility::MINIMISED:
                glfwIconifyWindow(handle_);
                break;

            case Visibility::FULLSCREEN: {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                glfwSetWindowMonitor(
                    handle_,
                    monitor,
                    0, 0,
                    mode->width, mode->height,
                    mode->refreshRate);
                break;
            }
        }
    }

    const Visibility& Window::getVisibility() const noexcept {
        return visibility_;
    }
}
