#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/instance/vulkan.hpp>
#include <renderer/surface.hpp>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanSurfaceBackend : public Surface::Backend {
    public:
        VulkanSurfaceBackend(const Surface::Backend::CreateInfo& createInfo);
        ~VulkanSurfaceBackend();

        VkSurfaceKHR surface;

        std::int32_t presentQueueSelection = -1;
    };
}

#endif