#pragma once

#include <window/event.hpp>

#include <memory>
#include <queue>
#include <string>

#include <glm/glm.hpp>

namespace engine::window
{
    enum class Visibility {
        FULLSCREEN,
        WINDOWED,
        MINIMISED,
    };

    class Context;

    struct CreateInfo {
        glm::uvec2 size;
        std::string title;

        Visibility visibility;
        Context& context;

        bool resizable;
    };

    class Window {
    public:
        Window();
        ~Window();

        Window(const Window& other) = delete;
        Window(Window&& other) noexcept = default;

        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) noexcept = default;

        void create(const CreateInfo& createInfo);
        void setSize(glm::uvec2 size);
        void setPosition(glm::uvec2 position);
        void setTitle(const std::string& title);
        void setVisibility(Visibility visibility);

        [[nodiscard]] std::queue<Event>& queryEvents() noexcept;
        [[nodiscard]] const glm::uvec2& getSize() const noexcept;
        [[nodiscard]] const glm::uvec2& getPosition() const noexcept;
        [[nodiscard]] const std::string& getTitle() const noexcept;
        [[nodiscard]] const Visibility& getVisibility() const noexcept;

    private:
        class Backend;

        friend class Backend;

        std::unique_ptr<Backend> backend_;

        glm::uvec2 size_;
        glm::uvec2 position_;
        std::string title_;

        Visibility visibility_;

        std::queue<Event> events_;
    };
}