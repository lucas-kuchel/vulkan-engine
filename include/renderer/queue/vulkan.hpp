#pragma once

#if !defined(PLATFORM_APPLE)

#include <renderer/queue.hpp>

#include <vulkan/vulkan.h>

namespace engine::renderer {
    class VulkanQueueBackend : public Queue::Backend {
    public:
        VulkanQueueBackend(const Queue::BackendCreateInfo& createInfo);
        ~VulkanQueueBackend();

        VkQueue queue;

        std::uint32_t familyIndex;
        std::uint32_t queueIndex;
    };
}

#endif