#pragma once

#include <memory>

namespace engine::window {
    class Window;
}

namespace engine::renderer {
    class Instance;

    struct SurfaceCreateInfo {
        Instance& instance;
        window::Window& window;
    };

    class Surface {
        class Backend;

    public:
        Surface();
        ~Surface();

        Surface(const Surface&) = delete;
        Surface(Surface&&) noexcept = default;

        Surface& operator=(const Surface&) = delete;
        Surface& operator=(Surface&&) noexcept = default;

        void create(const SurfaceCreateInfo& createInfo);

        Backend& getBackend();

    private:
        struct BackendCreateInfo {
            Instance& instance;
            window::Window& window;
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
            window::Window& window;
        };
        std::unique_ptr<Backend> backend_;

        friend class MetalSurfaceBackend;
        friend class VulkanSurfaceBackend;
    };
}