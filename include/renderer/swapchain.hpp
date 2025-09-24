#pragma once

#include <memory>

namespace engine::renderer {
    class Swapchain;
    class Surface;
    class Queue;

    struct SwapchainCreateInfo {
        Swapchain& device;
        Surface& surface;
        Queue& renderQueue;
        Queue& presentQueue;

        std::size_t imageCount;

        bool synchronise;
    };

    class Swapchain {
        class Backend;

    public:
        Swapchain();
        ~Swapchain();

        Swapchain(const Swapchain&) = delete;
        Swapchain(Swapchain&&) noexcept = default;

        Swapchain& operator=(const Swapchain&) = delete;
        Swapchain& operator=(Swapchain&&) noexcept = default;

        void create(const SwapchainCreateInfo& createInfo);

        Backend& getBackend();

    private:
        struct BackendCreateInfo {
            Swapchain& device;
            Surface& surface;
            Queue& renderQueue;
            Queue& presentQueue;

            std::size_t imageCount;

            bool synchronise;
        };

        class Backend {
        public:
            Backend(const BackendCreateInfo& createInfo);
            virtual ~Backend() = default;

            Backend(const Backend&) = delete;
            Backend(Backend&&) noexcept = default;

            Backend& operator=(const Backend&) = delete;
            Backend& operator=(Backend&&) noexcept = delete;

            Swapchain& device;
            Surface& surface;
            Queue& renderQueue;
            Queue& presentQueue;

            std::size_t imageCount;

            bool synchronise;
        };

        std::unique_ptr<Backend> backend_;

        friend class MetalSwapchainBackend;
        friend class VulkanSwapchainBackend;
    };
}