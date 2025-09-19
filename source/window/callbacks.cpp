#include <window/window.hpp>

namespace engine::window
{
    void Window::resizeCallback(GLFWwindow* window, int width, int height) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        self->width_ = width;
        self->height_ = height;

        ResizeEventInfo info = {
            .width = self->width_,
            .height = self->height_,
        };

        self->events_.push(Event{EventType::RESIZED, info});
    }

    void Window::moveCallback(GLFWwindow* window, int x, int y) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        self->x_ = x;
        self->y_ = y;

        MoveEventInfo info = {
            .x = self->x_,
            .y = self->y_,
        };

        self->events_.push(Event{EventType::MOVED, info});
    }

    void Window::closeCallback(GLFWwindow* window) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        self->events_.push(Event{EventType::CLOSED, std::monostate()});
    }

    void Window::focusCallback(GLFWwindow* window, int focused) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        self->events_.push(Event{focused ? EventType::FOCUSED : EventType::UNFOCUSED, std::monostate()});
    }

    void Window::iconifyCallback(GLFWwindow* window, int iconified) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        self->events_.push(Event{iconified ? EventType::MINIMIZED : EventType::RESTORED, std::monostate()});
    }

    void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        Key mappedKey = Window::mapKey(key);

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

    void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        MouseButton mappedButton = Window::mapMouseButton(button);

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

    void Window::mousePositionCallback(GLFWwindow* window, double x, double y) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        MouseMovedEventInfo info = {
            .x = x,
            .y = y,
        };

        self->events_.push(Event{EventType::MOUSE_MOVED, info});
    }

    void Window::mouseScrollCallback(GLFWwindow* window, double x, double y) {
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) {
            return;
        }

        MouseScrolledEventInfo info = {
            .x = x,
            .y = y,
        };

        self->events_.push(Event{EventType::MOUSE_SCROLLED, info});
    }
}