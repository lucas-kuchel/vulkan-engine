#pragma once

#include <utils/references.hpp>

#include <memory>

namespace engine::renderer {
    class Instance;
    class Surface;
    class Queue;

    struct DeviceCreateInfo {
        Instance& instance;
        Surface& surface;

        utils::ReferenceList<Queue> queues;
    };

    class Device {
        class Backend;

    public:
        Device();
        ~Device();

        Device(const Device&) = delete;
        Device(Device&&) noexcept = default;

        Device& operator=(const Device&) = delete;
        Device& operator=(Device&&) noexcept = default;

        void create(const DeviceCreateInfo& createInfo);

        Backend& getBackend();

    private:
        struct BackendCreateInfo {
            Instance& instance;
            Surface& surface;

            utils::ReferenceList<Queue> queues;
        };

        class Backend {
        public:
            Backend(const BackendCreateInfo& createInfo);
            virtual ~Backend() = default;

            Backend(const Backend&) = delete;
            Backend(Backend&&) noexcept = default;

            Backend& operator=(const Backend&) = delete;
            Backend& operator=(Backend&&) noexcept = delete;

            Instance& instance;
            Surface& surface;

            utils::ReferenceList<Queue> queues;
        };

        std::unique_ptr<Backend> backend_;

        friend class MetalDeviceBackend;
        friend class VulkanDeviceBackend;
    };
}