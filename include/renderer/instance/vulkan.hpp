#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/instance.hpp>

#include <vector>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanInstanceBackend : public Instance::Backend {
    public:
        VulkanInstanceBackend(const Instance::Backend::CreateInfo& createInfo);
        ~VulkanInstanceBackend();

        VkInstance instance;
        VkPhysicalDevice physicalDevice;

        std::vector<VkQueueFamilyProperties> queueFamilies;
    };
}

#endif