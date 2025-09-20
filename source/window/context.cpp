#include <window/context.hpp>

#include <format>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace engine::window
{
    Context::Context() {
        if (glfwInit() != GLFW_TRUE) {
            const char* message = nullptr;

            glfwGetError(&message);

            throw std::runtime_error(std::format("failed to initialise window subsystem:\n\n{}", message));
        }

        // stop GLFW from creating windows with OpenGL contexts
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    Context::~Context() {
        glfwTerminate();
    }

    void Context::pollEvents() {
        glfwPollEvents();
    }

    void Context::awaitEvents() {
        glfwWaitEvents();
    }

    void Context::awaitEventsTimeout(double timeout) {
        glfwWaitEventsTimeout(timeout);
    }
}