#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/instance.hpp>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanInstanceBackend : public Instance::Backend {
    public:
        VulkanInstanceBackend(const Instance::Backend::CreateInfo& createInfo);
        ~VulkanInstanceBackend();

        VkInstance instance;
        VkPhysicalDevice physicalDevice;

        std::int32_t graphicsQueueSelection = -1;
        std::int32_t computeQueueSelection = -1;
        std::int32_t transferQueueSelection = -1;
    };
}

#endif