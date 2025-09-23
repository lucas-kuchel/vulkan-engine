#include <renderer/device.hpp>
#include <renderer/device/metal.hpp>
#include <renderer/device/vulkan.hpp>

#include <stdexcept>

namespace engine::renderer {
    Device::Device()
        : backend_(nullptr) {
    }

    void Device::create(const DeviceCreateInfo& createInfo) {
        if (backend_) {
            throw std::runtime_error("Surface has already been created");
        }

        BackendCreateInfo backendCreateInfo = {
            .instance = createInfo.instance,
            .surface = createInfo.surface,
            .queues = createInfo.queues,
        };

#if defined(PLATFORM_APPLE)
        backend_ = std::make_unique<MetalDeviceBackend>(backendCreateInfo);
#else
        backend_ = std::make_unique<VulkanDeviceBackend>(backendCreateInfo);
#endif
    }

    Device::~Device() {
    }

    Device::Backend& Device::getBackend() {
        return *backend_.get();
    }

    Device::Backend::Backend(const BackendCreateInfo& createInfo)
        : instance(createInfo.instance), surface(createInfo.surface), queues(createInfo.queues) {
    }
}