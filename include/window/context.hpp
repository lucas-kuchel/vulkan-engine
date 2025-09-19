#pragma once

#include <GLFW/glfw3.h>

namespace engine::window
{
    class Context {
    public:
        Context();
        ~Context();

        void pollEvents();
        void awaitEvents();
        void awaitEventsTimeout(double timeout);
    };
}