#include <app/application.hpp>

namespace engine::app
{
    Application::Application()
        : shouldUpdate_(true) {
    }

    Application::~Application() {
    }

    void Application::create(const CreateInfo&) {
        window::CreateInfo windowCreateInfo = {
            .width = 800,
            .height = 600,
            .title = "New Window",
            .visibility = window::Visibility::WINDOWED,
            .context = context_,
            .resizable = true,
        };

        window_.create(windowCreateInfo);
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