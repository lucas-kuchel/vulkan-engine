#pragma once

#include <window/context.hpp>
#include <window/window.hpp>

#include <cstdlib>
#include <string>

namespace engine::app
{
    struct CreateInfo {
        std::size_t versionMajor;
        std::size_t versionMinor;
        std::size_t versionPatch;

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
    };
}