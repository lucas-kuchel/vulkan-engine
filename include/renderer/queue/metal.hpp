#pragma once

#if defined(PLATFORM_APPLE)

#include <renderer/queue.hpp>

namespace engine::renderer {
    class MetalQueueBackend : public Queue::Backend {
    public:
        MetalQueueBackend(const Queue::Backend::CreateInfo& createInfo);
        ~MetalQueueBackend();
    };
}

#endif