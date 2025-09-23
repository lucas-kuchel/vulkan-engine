#include <renderer/queue.hpp>
#include <renderer/queue/metal.hpp>
#include <renderer/queue/vulkan.hpp>

#include <stdexcept>

namespace engine::renderer {
    Queue::Queue()
        : backend_(nullptr) {
    }

    void Queue::create(const CreateInfo& createInfo) {
        if (backend_) {
            throw std::runtime_error("Queue has already been created");
        }

        Backend::CreateInfo backendCreateInfo = {
            .type = createInfo.type,
            .instance = createInfo.instance,
            .surface = createInfo.surface,
        };

#if defined(PLATFORM_APPLE)
        backend_ = std::make_unique<MetalQueueBackend>(backendCreateInfo);
#else
        backend_ = std::make_unique<VulkanQueueBackend>(backendCreateInfo);
#endif
    }

    Queue::~Queue() {
    }

    Queue::Backend& Queue::getBackend() {
        return *backend_.get();
    }

    Queue::Backend::Backend(const CreateInfo& createInfo)
        : type(createInfo.type), instance(createInfo.instance), surface(createInfo.surface) {
    }
}