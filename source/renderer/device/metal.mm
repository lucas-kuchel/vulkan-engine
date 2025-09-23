#if defined(PLATFORM_APPLE)

#include <renderer/device/metal.hpp>

namespace engine::renderer {
    MetalDeviceBackend::MetalDeviceBackend(const Instance::Backend::CreateInfo& createInfo) : Instance::Backend(createInfo) {
    }

    MetalDeviceBackend::~MetalDeviceBackend() {
    }
}

#endif