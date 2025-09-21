#pragma once

#include <memory>

namespace engine::window {
    class Window;
}

namespace engine::renderer {
    class Instance;

    class Surface {
    private:
        class Backend {
        public:
            struct CreateInfo {
                Instance& instance;
                window::Window& window;
            };

            Backend(const CreateInfo& createInfo);
            virtual ~Backend() = default;

            Backend(const Backend&) = delete;
            Backend(Backend&&) noexcept = default;

            Backend& operator=(const Backend&) = delete;
            Backend& operator=(Backend&&) noexcept = delete;

            CreateInfo createInfo;
        };

    public:
        struct CreateInfo {
            Instance& instance;
            window::Window& window;
        };

        Surface();
        ~Surface();

        Surface(const Surface&) = delete;
        Surface(Surface&&) noexcept = default;

        Surface& operator=(const Surface&) = delete;
        Surface& operator=(Surface&&) noexcept = default;

        void create(const CreateInfo& createInfo);

        Backend& getBackend();

    private:
        std::unique_ptr<Backend> backend_;

        friend class MetalSurfaceBackend;
        friend class VulkanSurfaceBackend;
    };
}