#include <window/context.hpp>

#include <format>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace engine::window {
    Context::Context() {
        if (glfwInit() != GLFW_TRUE) {
            const char* error = nullptr;

            glfwGetError(&error);

            std::string message = std::format("failed to initialise window subsystem:\n\n{}", error);

            throw std::runtime_error(message);
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

    bool Context::supportsVulkan() const {
        return glfwVulkanSupported();
    }

    const char** Context::getRequiredInstanceExtensions(std::uint32_t* count) const {
        return glfwGetRequiredInstanceExtensions(count);
    }
}