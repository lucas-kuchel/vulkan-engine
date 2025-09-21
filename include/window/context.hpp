#pragma once

#include <cstdint>

namespace engine::window
{
    class Context {
    public:
        Context();
        ~Context();

        void pollEvents();
        void awaitEvents();
        void awaitEventsTimeout(double timeout);

        [[nodiscard]] bool supportsVulkan() const;
        [[nodiscard]] const char** getRequiredInstanceExtensions(std::uint32_t* count) const;
    };
}