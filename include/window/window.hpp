#pragma once

#include <window/events.hpp>

#include <queue>
#include <string>

#include <GLFW/glfw3.h>

namespace engine::window
{
    enum class Visibility {
        FULLSCREEN,
        WINDOWED,
        MINIMISED,
    };

    class Context;

    struct CreateInfo {
        std::size_t width;
        std::size_t height;

        std::string title;

        Visibility visibility;

        Context& context;

        bool resizable;
    };

    class Window {
    public:
        Window();
        ~Window();

        Window(const Window& other) = delete;
        Window(Window&& other) noexcept = default;

        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) noexcept = default;

        void create(const CreateInfo& createInfo);

        [[nodiscard]] std::queue<Event>& queryEvents() noexcept;

        void setSize(std::size_t width, std::size_t height);

        [[nodiscard]] const std::size_t& getWidth() const noexcept;
        [[nodiscard]] const std::size_t& getHeight() const noexcept;

        void setPosition(std::size_t x, std::size_t y);

        [[nodiscard]] const std::size_t& getX() const noexcept;
        [[nodiscard]] const std::size_t& getY() const noexcept;

        void setTitle(const std::string& title);

        [[nodiscard]] const std::string& getTitle() const noexcept;

        void setVisibility(Visibility visibility);

        [[nodiscard]] const Visibility& getVisibility() const noexcept;

    private:
        std::queue<Event> events_;

        std::size_t width_;
        std::size_t height_;
        std::size_t x_;
        std::size_t y_;
        std::string title_;

        Visibility visibility_;

        GLFWwindow* handle_;

        static void resizeCallback(GLFWwindow* window, int width, int height);
        static void moveCallback(GLFWwindow* window, int x, int y);
        static void closeCallback(GLFWwindow* window);
        static void focusCallback(GLFWwindow* window, int focused);
        static void iconifyCallback(GLFWwindow* window, int iconified);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void mousePositionCallback(GLFWwindow* window, double x, double y);
        static void mouseScrollCallback(GLFWwindow* window, double x, double y);

        [[nodiscard]] static Key mapKey(int key);
        [[nodiscard]] static MouseButton mapMouseButton(int button);
    };
}