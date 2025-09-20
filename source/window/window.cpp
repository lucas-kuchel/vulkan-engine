#include <window/window.hpp>

#include <format>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace engine::window
{
    class Window::Backend {
    public:
        static Key mapKey(std::int32_t key) {
            switch (key) {
                case GLFW_KEY_A:
                    return Key::A;

                case GLFW_KEY_B:
                    return Key::B;

                case GLFW_KEY_C:
                    return Key::C;

                case GLFW_KEY_D:
                    return Key::D;

                case GLFW_KEY_E:
                    return Key::E;

                case GLFW_KEY_F:
                    return Key::F;

                case GLFW_KEY_G:
                    return Key::G;

                case GLFW_KEY_H:
                    return Key::H;

                case GLFW_KEY_I:
                    return Key::I;

                case GLFW_KEY_J:
                    return Key::J;

                case GLFW_KEY_K:
                    return Key::K;

                case GLFW_KEY_L:
                    return Key::L;

                case GLFW_KEY_M:
                    return Key::M;

                case GLFW_KEY_N:
                    return Key::N;

                case GLFW_KEY_O:
                    return Key::O;

                case GLFW_KEY_P:
                    return Key::P;

                case GLFW_KEY_Q:
                    return Key::Q;

                case GLFW_KEY_R:
                    return Key::R;

                case GLFW_KEY_S:
                    return Key::S;

                case GLFW_KEY_T:
                    return Key::T;

                case GLFW_KEY_U:
                    return Key::U;

                case GLFW_KEY_V:
                    return Key::V;

                case GLFW_KEY_W:
                    return Key::W;

                case GLFW_KEY_X:
                    return Key::X;

                case GLFW_KEY_Y:
                    return Key::Y;

                case GLFW_KEY_Z:
                    return Key::Z;

                case GLFW_KEY_F1:
                    return Key::F1;

                case GLFW_KEY_F2:
                    return Key::F2;

                case GLFW_KEY_F3:
                    return Key::F3;

                case GLFW_KEY_F4:
                    return Key::F4;

                case GLFW_KEY_F5:
                    return Key::F5;

                case GLFW_KEY_F6:
                    return Key::F6;

                case GLFW_KEY_F7:
                    return Key::F7;

                case GLFW_KEY_F8:
                    return Key::F8;

                case GLFW_KEY_F9:
                    return Key::F9;

                case GLFW_KEY_F10:
                    return Key::F10;

                case GLFW_KEY_F11:
                    return Key::F11;

                case GLFW_KEY_F12:
                    return Key::F12;

                case GLFW_KEY_SPACE:
                    return Key::SPACE;

                case GLFW_KEY_LEFT_CONTROL:
                    return Key::LCTRL;

                case GLFW_KEY_RIGHT_CONTROL:
                    return Key::RCTRL;

                case GLFW_KEY_LEFT_SUPER:
                    return Key::LSUPER;

                case GLFW_KEY_RIGHT_SUPER:
                    return Key::RSUPER;

                case GLFW_KEY_LEFT_ALT:
                    return Key::LALT;

                case GLFW_KEY_RIGHT_ALT:
                    return Key::RALT;

                case GLFW_KEY_CAPS_LOCK:
                    return Key::CAPSLOCK;

                case GLFW_KEY_TAB:
                    return Key::TAB;

                case GLFW_KEY_ESCAPE:
                    return Key::ESCAPE;

                case GLFW_KEY_LEFT_SHIFT:
                    return Key::LSHIFT;

                case GLFW_KEY_RIGHT_SHIFT:
                    return Key::RSHIFT;

                case GLFW_KEY_HOME:
                    return Key::HOME;

                case GLFW_KEY_END:
                    return Key::END;

                case GLFW_KEY_PAGE_UP:
                    return Key::PGUP;

                case GLFW_KEY_PAGE_DOWN:
                    return Key::PGDN;

                case GLFW_KEY_INSERT:
                    return Key::INSERT;

                case GLFW_KEY_DELETE:
                    return Key::DELETE;

                case GLFW_KEY_ENTER:
                    return Key::ENTER;

                case GLFW_KEY_BACKSPACE:
                    return Key::BACKSPACE;

                case GLFW_KEY_GRAVE_ACCENT:
                    return Key::GRAVE_ACCENT;

                case GLFW_KEY_EQUAL:
                    return Key::EQUAL;

                case GLFW_KEY_MINUS:
                    return Key::MINUS;

                case GLFW_KEY_SLASH:
                    return Key::SLASH;

                case GLFW_KEY_BACKSLASH:
                    return Key::BACKSLASH;

                case GLFW_KEY_SEMICOLON:
                    return Key::SEMICOLON;

                case GLFW_KEY_APOSTROPHE:
                    return Key::APOSTROPHE;

                case GLFW_KEY_COMMA:
                    return Key::COMMA;

                case GLFW_KEY_PERIOD:
                    return Key::PERIOD;

                case GLFW_KEY_0:
                    return Key::ROW_0;

                case GLFW_KEY_1:
                    return Key::ROW_1;

                case GLFW_KEY_2:
                    return Key::ROW_2;

                case GLFW_KEY_3:
                    return Key::ROW_3;

                case GLFW_KEY_4:
                    return Key::ROW_4;

                case GLFW_KEY_5:
                    return Key::ROW_5;

                case GLFW_KEY_6:
                    return Key::ROW_6;

                case GLFW_KEY_7:
                    return Key::ROW_7;

                case GLFW_KEY_8:
                    return Key::ROW_8;

                case GLFW_KEY_9:
                    return Key::ROW_9;

                case GLFW_KEY_KP_ADD:
                    return Key::KEYPAD_PLUS;

                case GLFW_KEY_KP_SUBTRACT:
                    return Key::KEYPAD_MINUS;

                case GLFW_KEY_KP_0:
                    return Key::KEYPAD_0;

                case GLFW_KEY_KP_1:
                    return Key::KEYPAD_1;

                case GLFW_KEY_KP_2:
                    return Key::KEYPAD_2;

                case GLFW_KEY_KP_3:
                    return Key::KEYPAD_3;

                case GLFW_KEY_KP_4:
                    return Key::KEYPAD_4;

                case GLFW_KEY_KP_5:
                    return Key::KEYPAD_5;

                case GLFW_KEY_KP_6:
                    return Key::KEYPAD_6;

                case GLFW_KEY_KP_7:
                    return Key::KEYPAD_7;

                case GLFW_KEY_KP_8:
                    return Key::KEYPAD_8;

                case GLFW_KEY_KP_9:
                    return Key::KEYPAD_9;

                case GLFW_KEY_UP:
                    return Key::UP;

                case GLFW_KEY_DOWN:
                    return Key::DOWN;

                case GLFW_KEY_LEFT:
                    return Key::LEFT;

                case GLFW_KEY_RIGHT:
                    return Key::RIGHT;
            }

            throw;
        }

        static MouseButton mapMouseButton(std::int32_t button) {
            switch (button) {
                case GLFW_MOUSE_BUTTON_LEFT:
                    return MouseButton::LEFT;

                case GLFW_MOUSE_BUTTON_RIGHT:
                    return MouseButton::RIGHT;

                case GLFW_MOUSE_BUTTON_MIDDLE:
                    return MouseButton::MIDDLE;
            }

            throw;
        }

        static void resizeCallback(GLFWwindow* window, int width, int height) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            self->size_ = {width, height};

            ResizeEventInfo info = {
                .size = self->size_,
            };

            self->events_.push(Event{EventType::RESIZED, info});
        }

        static void moveCallback(GLFWwindow* window, int x, int y) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            self->position_ = {x, y};

            MoveEventInfo info = {
                .position = self->position_,
            };

            self->events_.push(Event{EventType::MOVED, info});
        }

        static void closeCallback(GLFWwindow* window) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            self->events_.push(Event{EventType::CLOSED, std::monostate()});
        }

        static void focusCallback(GLFWwindow* window, int focused) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            self->events_.push(Event{focused ? EventType::FOCUSED : EventType::UNFOCUSED, std::monostate()});
        }

        static void iconifyCallback(GLFWwindow* window, int iconified) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            self->events_.push(Event{iconified ? EventType::MINIMIZED : EventType::RESTORED, std::monostate()});
        }

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            Key mappedKey = mapKey(key);

            if (action == GLFW_PRESS) {
                KeyPressedEventInfo pressedInfo;

                pressedInfo.key = mappedKey;
                pressedInfo.scancode = scancode;

                self->events_.push(Event{EventType::KEY_PRESSED, pressedInfo});
            }
            else if (action == GLFW_RELEASE) {
                KeyReleasedEventInfo releasedInfo;

                releasedInfo.key = mappedKey;
                releasedInfo.scancode = scancode;

                self->events_.push(Event{EventType::KEY_RELEASED, releasedInfo});
            }
        }

        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            MouseButton mappedButton = mapMouseButton(button);

            if (action == GLFW_PRESS) {
                MouseButtonPressedEventInfo pressedInfo;

                pressedInfo.button = mappedButton;

                self->events_.push(Event{EventType::MOUSE_BUTTON_PRESSED, pressedInfo});
            }
            else if (action == GLFW_RELEASE) {
                MouseButtonReleasedEventInfo releasedInfo;

                releasedInfo.button = mappedButton;

                self->events_.push(Event{EventType::MOUSE_BUTTON_RELEASED, releasedInfo});
            }
        }

        static void mousePositionCallback(GLFWwindow* window, double x, double y) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            MouseMovedEventInfo info = {
                .position = {x, y},
            };

            self->events_.push(Event{EventType::MOUSE_MOVED, info});
        }

        static void mouseScrollCallback(GLFWwindow* window, double x, double y) {
            Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (!self) {
                return;
            }

            MouseScrolledEventInfo info = {
                .offsets = {x, y},
            };

            self->events_.push(Event{EventType::MOUSE_SCROLLED, info});
        }

        GLFWwindow* window;
    };

    Window::Window()
        : backend_(std::make_unique<Backend>()), size_(0, 0), position_(0, 0), title_(), visibility_(Visibility::WINDOWED) {
    }

    void Window::create(const CreateInfo& createInfo) {
        if (backend_->window) {
            throw std::runtime_error("window already created");
        }

        size_ = createInfo.size;
        title_ = createInfo.title;
        visibility_ = createInfo.visibility;

        // determine if window is resizeable
        glfwWindowHint(GLFW_RESIZABLE, createInfo.resizable);

        backend_->window = glfwCreateWindow(size_.x, size_.y, title_.c_str(), nullptr, nullptr);

        if (!backend_->window) {
            const char* message = nullptr;

            glfwGetError(&message);

            throw std::runtime_error(std::format("error creating window:\n\n{}", message));
        }

        switch (visibility_) {
            case Visibility::WINDOWED:
                glfwRestoreWindow(backend_->window);
                break;

            case Visibility::MINIMISED:
                glfwIconifyWindow(backend_->window);
                break;

            case Visibility::FULLSCREEN: {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                glfwSetWindowMonitor(
                    backend_->window,
                    monitor,
                    0, 0,
                    mode->width, mode->height,
                    mode->refreshRate);
                break;
            }
        }

        // store this window in the GLFW user pointer
        // this allows callbacks to load our window data
        glfwSetWindowUserPointer(backend_->window, this);

        // set all the window callbacks
        glfwSetWindowSizeCallback(backend_->window, Backend::resizeCallback);
        glfwSetWindowPosCallback(backend_->window, Backend::moveCallback);
        glfwSetWindowCloseCallback(backend_->window, Backend::closeCallback);
        glfwSetWindowFocusCallback(backend_->window, Backend::focusCallback);
        glfwSetWindowIconifyCallback(backend_->window, Backend::iconifyCallback);
        glfwSetKeyCallback(backend_->window, Backend::keyCallback);
        glfwSetMouseButtonCallback(backend_->window, Backend::mouseButtonCallback);
        glfwSetCursorPosCallback(backend_->window, Backend::mousePositionCallback);
        glfwSetScrollCallback(backend_->window, Backend::mouseScrollCallback);
    }

    Window::~Window() {
        if (backend_->window) {
            glfwDestroyWindow(backend_->window);

            backend_->window = nullptr;
        }
    }

    std::queue<Event>& Window::queryEvents() noexcept {
        return events_;
    }

    void Window::setSize(glm::uvec2 size) {
        if (!backend_->window) {
            throw std::runtime_error("window not created");
        }

        size_ = size;

        glfwSetWindowSize(backend_->window, size_.x, size_.y);
    }

    const glm::uvec2& Window::getSize() const noexcept {
        return size_;
    }

    void Window::setPosition(glm::uvec2 position) {
        if (!backend_->window) {
            throw std::runtime_error("window not created");
        }

        position_ = position;

        glfwSetWindowPos(backend_->window, position_.x, position_.y);
    }

    const glm::uvec2& Window::getPosition() const noexcept {
        return position_;
    }

    void Window::setTitle(const std::string& title) {
        if (!backend_->window) {
            throw std::runtime_error("window not created");
        }

        title_ = title;

        glfwSetWindowTitle(backend_->window, title_.c_str());
    }

    const std::string& Window::getTitle() const noexcept {
        return title_;
    }

    void Window::setVisibility(Visibility visibility) {
        if (!backend_->window) {
            throw std::runtime_error("window not created");
        }

        visibility_ = visibility;

        switch (visibility_) {
            case Visibility::WINDOWED:
                glfwRestoreWindow(backend_->window);
                break;

            case Visibility::MINIMISED:
                glfwIconifyWindow(backend_->window);
                break;

            case Visibility::FULLSCREEN: {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                glfwSetWindowMonitor(
                    backend_->window,
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
