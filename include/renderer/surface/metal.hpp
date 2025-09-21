#pragma once

#if defined(PLATFORM_APPLE)

#include <renderer/surface.hpp>

namespace engine::renderer {
    class MetalSurfaceBackend : public Surface::Backend {
    public:
        MetalSurfaceBackend(const Surface::Backend::CreateInfo& createInfo);
        ~MetalSurfaceBackend();

    private:
    };
}

#endif