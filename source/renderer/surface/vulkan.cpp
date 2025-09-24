#if !defined(PLATFORM_APPLE)

#include <renderer/instance/vulkan.hpp>
#include <renderer/surface/vulkan.hpp>

#include <window/window.hpp>

namespace engine::renderer {
    VulkanSurfaceBackend::VulkanSurfaceBackend(const Surface::BackendCreateInfo& createInfo)
        : Surface::Backend(createInfo), surface(nullptr) {
        auto& vulkanInstanceBackend = static_cast<VulkanInstanceBackend&>(instance.getBackend());

        if (window.createWindowSurface(vulkanInstanceBackend.instance, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create surface");
        }
    }

    VulkanSurfaceBackend::~VulkanSurfaceBackend() {
        if (surface) {
            auto& vulkanInstanceBackend = static_cast<VulkanInstanceBackend&>(instance.getBackend());

            vkDestroySurfaceKHR(vulkanInstanceBackend.instance, surface, nullptr);
        }
    }
}

#endif