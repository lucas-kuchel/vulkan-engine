#include <app/application.hpp>

#include <print>

int main() {
    try {
        engine::app::CreateInfo createInfo = {
            .versionMajor = 0,
            .versionMinor = 0,
            .versionPatch = 1,
            .name = "my game",
        };

        engine::app::Application application;

        application.create(createInfo);

        while (application.shouldUpdate()) {
            application.update();
        }

        return 0;
    }
    catch (const std::exception& exception) {
        std::println("runtime error: {}", exception.what());

        return 1;
    }
}