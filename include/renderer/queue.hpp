#pragma once

#pragma once

#include <memory>

namespace engine::renderer {
    class Instance;
    class Surface;

    enum class QueueType {
        PRESENT,
        TRANSFER,
        COMPUTE,
        RENDER,
    };

    class Queue {
    private:
        class Backend {
        public:
            struct CreateInfo {
                QueueType type;
                Instance& instance;
                Surface& surface;
            };

            Backend(const CreateInfo& createInfo);
            virtual ~Backend() = default;

            Backend(const Backend&) = delete;
            Backend(Backend&&) noexcept = default;

            Backend& operator=(const Backend&) = delete;
            Backend& operator=(Backend&&) noexcept = delete;

            QueueType type;
            Instance& instance;
            Surface& surface;
        };

    public:
        struct CreateInfo {
            QueueType type;
            Instance& instance;
            Surface& surface;
        };

        Queue();
        ~Queue();

        Queue(const Queue&) = delete;
        Queue(Queue&&) noexcept = default;

        Queue& operator=(const Queue&) = delete;
        Queue& operator=(Queue&&) noexcept = default;

        void create(const CreateInfo& createInfo);

        Backend& getBackend();

    private:
        std::unique_ptr<Backend> backend_;

        friend class MetalQueueBackend;
        friend class VulkanQueueBackend;
    };
}