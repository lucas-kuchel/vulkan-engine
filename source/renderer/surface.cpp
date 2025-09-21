#include <renderer/surface.hpp>
#include <renderer/surface/metal.hpp>
#include <renderer/surface/vulkan.hpp>

namespace engine::renderer {
    Surface::Surface() : backend_(nullptr) {
    }

    void Surface::create(const CreateInfo& createInfo) {
        if (backend_) {
            throw std::runtime_error("Surface has already been created");
        }

        Backend::CreateInfo backendCreateInfo = {
            .instance = createInfo.instance,
            .window = createInfo.window,
        };

#if defined(PLATFORM_APPLE)
        backend_ = std::make_unique<MetalSurfaceBackend>(backendCreateInfo);
#else
        backend_ = std::make_unique<VulkanSurfaceBackend>(backendCreateInfo);
#endif
    }

    Surface::~Surface() {
    }

    Surface::Backend& Surface::getBackend() {
        return *backend_.get();
    }

    Surface::Backend::Backend(const CreateInfo& createInfo) : createInfo(createInfo) {
    }
}