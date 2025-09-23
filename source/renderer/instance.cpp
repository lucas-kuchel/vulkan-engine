#include <renderer/instance.hpp>
#include <renderer/instance/metal.hpp>
#include <renderer/instance/vulkan.hpp>

namespace engine::renderer {
    Instance::Instance() : backend_(nullptr) {
    }

    void Instance::create(const InstanceCreateInfo& createInfo) {
        if (backend_) {
            throw std::runtime_error("Instance has already been created");
        }

        BackendCreateInfo backendCreateInfo = {
            .context = createInfo.context,
            .applicationName = createInfo.applicationName,
            .applicationVersionMajor = createInfo.applicationVersionMajor,
            .applicationVersionMinor = createInfo.applicationVersionMinor,
            .applicationVersionPatch = createInfo.applicationVersionPatch,
            .engineName = createInfo.engineName,
            .engineVersionMajor = createInfo.engineVersionMajor,
            .engineVersionMinor = createInfo.engineVersionMinor,
            .engineVersionPatch = createInfo.engineVersionPatch,
            .requestDebug = createInfo.requestDebug,
        };

#if defined(PLATFORM_APPLE)
        backend_ = std::make_unique<MetalInstanceBackend>(backendCreateInfo);
#else
        backend_ = std::make_unique<VulkanInstanceBackend>(backendCreateInfo);
#endif
    }

    Instance::~Instance() {
    }

    Instance::Backend& Instance::getBackend() {
        return *backend_.get();
    }

    Instance::Backend::Backend(const BackendCreateInfo& createInfo)
        : context(createInfo.context),
          applicationName(createInfo.applicationName),
          applicationVersionMajor(createInfo.applicationVersionMajor),
          applicationVersionMinor(createInfo.applicationVersionMinor),
          applicationVersionPatch(createInfo.applicationVersionPatch),
          engineName(createInfo.engineName),
          engineVersionMajor(createInfo.applicationVersionMajor),
          engineVersionMinor(createInfo.applicationVersionMinor),
          engineVersionPatch(createInfo.applicationVersionPatch),
          requestDebug(createInfo.requestDebug) {
    }
}