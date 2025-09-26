#include <app/application.hpp>

namespace engine::app {
    Application::Application()
        : shouldUpdate_(true) {
    }

    Application::~Application() {
    }

    void Application::create(const CreateInfo& createInfo) {
        window::WindowCreateInfo windowCreateInfo = {
            .size = {800, 600},
            .title = "New Window",
            .visibility = window::Visibility::WINDOWED,
            .context = context_,
            .resizable = true,
        };

        window_.create(windowCreateInfo);

        renderer::InstanceCreateInfo instanceCreateInfo = {
            .context = context_,
            .applicationName = createInfo.name,
            .applicationVersionMajor = createInfo.versionMajor,
            .applicationVersionMinor = createInfo.versionMinor,
            .applicationVersionPatch = createInfo.versionPatch,
            .engineName = "engine",
            .engineVersionMajor = 0,
            .engineVersionMinor = 0,
            .engineVersionPatch = 1,
            .requestDebug = true,
        };

        instance_.create(instanceCreateInfo);

        renderer::SurfaceCreateInfo surfaceCreateInfo = {
            .instance = instance_,
            .window = window_,
        };

        surface_.create(surfaceCreateInfo);

        renderer::QueueCreateInfo renderQueueCreateInfo = {
            .type = renderer::QueueType::RENDER,
            .instance = instance_,
            .surface = surface_,
        };

        renderer::QueueCreateInfo presentQueueCreateInfo = {
            .type = renderer::QueueType::PRESENT,
            .instance = instance_,
            .surface = surface_,
        };

        renderQueue_.create(renderQueueCreateInfo);
        presentQueue_.create(presentQueueCreateInfo);

        renderer::DeviceCreateInfo deviceCreateInfo = {
            .instance = instance_,
            .surface = surface_,
            .queues = {renderQueue_, presentQueue_},
        };

        device_.create(deviceCreateInfo);

        renderer::SwapchainCreateInfo swapchainCreateInfo = {
            .instance = instance_,
            .surface = surface_,
            .device = device_,
            .renderQueue = renderQueue_,
            .presentQueue = presentQueue_,
            .imageCount = 3,
            .synchronise = false,
        };

        swapchain_.create(swapchainCreateInfo);
    }

    void Application::update() {
        context_.pollEvents();

        auto& events = window_.queryEvents();

        while (!events.empty()) {
            auto& event = events.front();

            switch (event.type) {
                case window::EventType::CLOSED:
                    shouldUpdate_ = false;
                    break;

                default:
                    break;
            }

            events.pop();
        }
    }

    bool Application::shouldUpdate() const {
        return shouldUpdate_;
    }
}