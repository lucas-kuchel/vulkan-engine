#pragma once

#if defined(PLATFORM_APPLE)

#include <renderer/instance.hpp>

namespace engine::renderer {
    class MetalInstanceBackend : public Instance::Backend {
    public:
        MetalInstanceBackend(const Instance::Backend::CreateInfo& createInfo);
        ~MetalInstanceBackend();

    private:
    };
}

#endif