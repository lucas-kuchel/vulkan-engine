#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/swapchain.hpp>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanSwapchainBackend : public Swapchain::Backend {
    public:
        VulkanSwapchainBackend(const Swapchain::BackendCreateInfo& createInfo);
        ~VulkanSwapchainBackend();

        VkSwapchainKHR swapchain;
    };
}

#endif