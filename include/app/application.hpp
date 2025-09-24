#pragma once

#include <window/context.hpp>
#include <window/window.hpp>

#include <renderer/device.hpp>
#include <renderer/instance.hpp>
#include <renderer/queue.hpp>
#include <renderer/surface.hpp>
#include <renderer/swapchain.hpp>

#include <cstdint>
#include <string>

namespace engine::app {
    struct CreateInfo {
        std::uint32_t versionMajor;
        std::uint32_t versionMinor;
        std::uint32_t versionPatch;

        std::string name;
    };

    class Application {
    public:
        Application();
        ~Application();

        Application(const Application&) = delete;
        Application(Application&&) noexcept = delete;

        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) noexcept = delete;

        void create(const CreateInfo& createInfo);

        void update();

        bool shouldUpdate() const;

    private:
        bool shouldUpdate_;

        window::Context context_;
        window::Window window_;

        renderer::Instance instance_;
        renderer::Surface surface_;
        renderer::Device device_;
        renderer::Swapchain swapchain_;

        renderer::Queue renderQueue_;
        renderer::Queue presentQueue_;
    };
}