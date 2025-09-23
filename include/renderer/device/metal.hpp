#pragma once

#if defined(PLATFORM_APPLE)

#include <renderer/device.hpp>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class MetalDeviceBackend : public Device::Backend {
    public:
        MetalDeviceBackend(const Device::BackendCreateInfo& createInfo);
        ~MetalDeviceBackend();
    };
}

#endif