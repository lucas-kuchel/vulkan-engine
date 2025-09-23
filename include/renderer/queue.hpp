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

    struct QueueCreateInfo {
        QueueType type;
        Instance& instance;
        Surface& surface;
    };

    class Queue {
        class Backend;

    public:
        Queue();
        ~Queue();

        Queue(const Queue&) = delete;
        Queue(Queue&&) noexcept = default;

        Queue& operator=(const Queue&) = delete;
        Queue& operator=(Queue&&) noexcept = default;

        void create(const QueueCreateInfo& createInfo);

        Backend& getBackend();

    private:
        struct BackendCreateInfo {
            QueueType type;
            Instance& instance;
            Surface& surface;
        };

        class Backend {
        public:
            Backend(const BackendCreateInfo& createInfo);
            virtual ~Backend() = default;

            Backend(const Backend&) = delete;
            Backend(Backend&&) noexcept = default;

            Backend& operator=(const Backend&) = delete;
            Backend& operator=(Backend&&) noexcept = delete;

            QueueType type;
            Instance& instance;
            Surface& surface;
        };

        std::unique_ptr<Backend> backend_;

        friend class MetalQueueBackend;
        friend class VulkanQueueBackend;
    };
}