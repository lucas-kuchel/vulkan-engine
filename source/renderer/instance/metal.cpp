#if defined(PLATFORM_APPLE)

#include <renderer/instance/metal.hpp>

namespace engine::renderer {
    MetalInstanceBackend::MetalInstanceBackend(const Instance::Backend::CreateInfo& createInfo) : Instance::Backend(createInfo) {
    }

    MetalInstanceBackend::~MetalInstanceBackend() {
    }
}

#endif