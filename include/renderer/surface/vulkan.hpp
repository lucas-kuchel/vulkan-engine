#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/surface.hpp>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanSurfaceBackend : public Surface::Backend {
    public:
        VulkanSurfaceBackend(const Surface::BackendCreateInfo& createInfo);
        ~VulkanSurfaceBackend();

        VkSurfaceKHR surface;
    };
}

#endif