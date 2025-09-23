#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/instance.hpp>

#include <vector>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanInstanceBackend : public Instance::Backend {
    public:
        VulkanInstanceBackend(const Instance::BackendCreateInfo& createInfo);
        ~VulkanInstanceBackend();

        VkInstance instance;
        VkPhysicalDevice physicalDevice;

        std::vector<VkQueueFamilyProperties> queueFamilies;
        std::vector<std::uint32_t> queueFamilyOccupations;
    };
}

#endif