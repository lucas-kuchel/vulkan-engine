#if !defined(PLATFORM_APPLE)

#include <renderer/instance/vulkan.hpp>
#include <renderer/surface/vulkan.hpp>

#include <window/window.hpp>

namespace engine::renderer {
    VulkanSurfaceBackend::VulkanSurfaceBackend(const Surface::Backend::CreateInfo& createInfo) : Surface::Backend(createInfo), surface(nullptr) {
        auto& vulkanInstanceBackend = static_cast<VulkanInstanceBackend&>(instance.getBackend());

        if (window.createWindowSurface(vulkanInstanceBackend.instance, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create VkSurfaceKHR");
        }

        std::uint32_t queueFamilyCount = 0;

        vkGetPhysicalDeviceQueueFamilyProperties(vulkanInstanceBackend.physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

        vkGetPhysicalDeviceQueueFamilyProperties(vulkanInstanceBackend.physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (std::uint32_t i = 0; i < queueFamilies.size(); i++) {
            VkBool32 presentSupported = VK_FALSE;

            vkGetPhysicalDeviceSurfaceSupportKHR(vulkanInstanceBackend.physicalDevice, i, surface, &presentSupported);

            if (presentSupported) {
                presentQueueSelection = i;
                break;
            }
        }

        if (presentQueueSelection < 0) {
            throw std::runtime_error("failed to find a present-capable queue family");
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