#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace engine::window {
    class Context;
}

namespace engine::renderer {
    struct InstanceCreateInfo {
        window::Context& context;

        std::string applicationName;

        std::uint32_t applicationVersionMajor;
        std::uint32_t applicationVersionMinor;
        std::uint32_t applicationVersionPatch;

        std::string engineName;

        std::uint32_t engineVersionMajor;
        std::uint32_t engineVersionMinor;
        std::uint32_t engineVersionPatch;

        bool requestDebug;
    };

    class Instance {
        class Backend;

    public:
        Instance();
        ~Instance();

        Instance(const Instance&) = delete;
        Instance(Instance&&) noexcept = default;

        Instance& operator=(const Instance&) = delete;
        Instance& operator=(Instance&&) noexcept = default;

        void create(const InstanceCreateInfo& createInfo);

        Backend& getBackend();

    private:
        struct BackendCreateInfo {
            window::Context& context;

            std::string applicationName;

            std::uint32_t applicationVersionMajor;
            std::uint32_t applicationVersionMinor;
            std::uint32_t applicationVersionPatch;

            std::string engineName;

            std::uint32_t engineVersionMajor;
            std::uint32_t engineVersionMinor;
            std::uint32_t engineVersionPatch;

            bool requestDebug;
        };

        class Backend {
        public:
            Backend(const BackendCreateInfo& createInfo);
            virtual ~Backend() = default;

            Backend(const Backend&) = delete;
            Backend(Backend&&) noexcept = default;

            Backend& operator=(const Backend&) = delete;
            Backend& operator=(Backend&&) noexcept = delete;

            window::Context& context;

            std::string applicationName;

            std::uint32_t applicationVersionMajor;
            std::uint32_t applicationVersionMinor;
            std::uint32_t applicationVersionPatch;

            std::string engineName;

            std::uint32_t engineVersionMajor;
            std::uint32_t engineVersionMinor;
            std::uint32_t engineVersionPatch;

            bool requestDebug;
        };

        std::unique_ptr<Backend> backend_;

        friend class MetalInstanceBackend;
        friend class VulkanInstanceBackend;
    };
}