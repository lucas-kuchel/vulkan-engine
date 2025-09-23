#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/device.hpp>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanDeviceBackend : public Device::Backend {
    public:
        VulkanDeviceBackend(const Device::BackendCreateInfo& createInfo);
        ~VulkanDeviceBackend();

        VkDevice device;
    };
}

#endif