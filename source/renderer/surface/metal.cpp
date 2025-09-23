#include <renderer/surface.hpp>

#include <renderer/surface/metal.hpp>

namespace engine::renderer {
    MetalSurfaceBackend::MetalSurfaceBackend(const Surface::Backend::CreateInfo& createInfo)
        : Surface::Backend(createInfo) {
    }

    MetalSurfaceBackend::~MetalSurfaceBackend() {
    }
}