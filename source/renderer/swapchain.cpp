#include <renderer/swapchain.hpp>
#include <renderer/swapchain/metal.hpp>
#include <renderer/swapchain/vulkan.hpp>

#include <stdexcept>

namespace engine::renderer {
    Swapchain::Swapchain()
        : backend_(nullptr) {
    }

    void Swapchain::create(const SwapchainCreateInfo& createInfo) {
        if (backend_) {
            throw std::runtime_error("Swapchain has already been created");
        }

        BackendCreateInfo backendCreateInfo = {
            .device = createInfo.device,
            .surface = createInfo.surface,
            .renderQueue = createInfo.renderQueue,
            .presentQueue = createInfo.presentQueue,
            .imageCount = createInfo.imageCount,
            .synchronise = createInfo.synchronise,
        };

#if defined(PLATFORM_APPLE)
        backend_ = std::make_unique<MetalSwapchainBackend>(backendCreateInfo);
#else
        backend_ = std::make_unique<VulkanSwapchainBackend>(backendCreateInfo);
#endif
    }

    Swapchain::~Swapchain() {
    }

    Swapchain::Backend& Swapchain::getBackend() {
        return *backend_.get();
    }

    Swapchain::Backend::Backend(const BackendCreateInfo& createInfo)
        : device(createInfo.device), surface(createInfo.surface),
          renderQueue(createInfo.renderQueue), presentQueue(createInfo.presentQueue),
          imageCount(createInfo.imageCount), synchronise(createInfo.synchronise) {
    }
}