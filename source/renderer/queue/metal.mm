#if defined(PLATFORM_APPLE)

#include <renderer/surface.hpp>

#include <renderer/queue/metal.hpp>

namespace engine::renderer {
    MetalQueueBackend::MetalQueueBackend(const Queue::Backend::CreateInfo& createInfo)
        : Queue::Backend(createInfo) {
    }

    MetalQueueBackend::~MetalQueueBackend() {
    }
}

#endif