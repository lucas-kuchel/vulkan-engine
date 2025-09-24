#if !defined(PLATFORM_APPLE)

#include <renderer/device/vulkan.hpp>
#include <renderer/queue/vulkan.hpp>
#include <renderer/surface/vulkan.hpp>
#include <renderer/swapchain/vulkan.hpp>

namespace engine::renderer {
    VulkanSwapchainBackend::VulkanSwapchainBackend(const Swapchain::BackendCreateInfo& createInfo)
        : Swapchain::Backend(createInfo) {

        // TODO: get supported surface formats, extent & present modes

        VkSwapchainCreateInfoKHR swapchainCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            .pNext = nullptr,
            .flags = 0,
            .oldSwapchain = VK_NULL_HANDLE,
        };
    }

    VulkanSwapchainBackend::~VulkanSwapchainBackend() {
    }
}

#endif