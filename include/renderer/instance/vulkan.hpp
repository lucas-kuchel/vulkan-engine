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
    };
}

#endif