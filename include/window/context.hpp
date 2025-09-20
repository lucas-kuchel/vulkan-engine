#pragma once

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