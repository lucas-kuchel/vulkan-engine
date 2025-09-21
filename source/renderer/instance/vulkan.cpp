#if !defined(PLATFORM_APPLE)

#include <renderer/instance/vulkan.hpp>

#include <window/context.hpp>

namespace engine::renderer {
    VulkanInstanceBackend::VulkanInstanceBackend(const Instance::Backend::CreateInfo& createInfo) : Instance::Backend(createInfo) {
        if (!createInfo.context.supportsVulkan()) {
            throw std::runtime_error("system does not support Vulkan");
        }

        std::uint32_t apiVersion = 0;

        if (vkEnumerateInstanceVersion(&apiVersion) != VK_SUCCESS) {
            throw std::runtime_error("failed to enumerate Vulkan API version");
        }

        std::uint32_t applicationVersion = VK_MAKE_VERSION(createInfo.applicationVersionMajor, createInfo.applicationVersionMinor, createInfo.applicationVersionPatch);
        std::uint32_t engineVersion = VK_MAKE_VERSION(createInfo.engineVersionMajor, createInfo.engineVersionMinor, createInfo.engineVersionPatch);

        VkApplicationInfo applicationInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pNext = nullptr,
            .pApplicationName = createInfo.applicationName.c_str(),
            .applicationVersion = applicationVersion,
            .pEngineName = createInfo.engineName.c_str(),
            .engineVersion = engineVersion,
            .apiVersion = apiVersion,
        };

        std::uint32_t instanceExtensionCount = 0;

        const char** instanceExtensions = createInfo.context.getRequiredInstanceExtensions(&instanceExtensionCount);

        VkInstanceCreateInfo instanceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .pApplicationInfo = &applicationInfo,
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = nullptr,
            .enabledExtensionCount = instanceExtensionCount,
            .ppEnabledExtensionNames = instanceExtensions,
        };

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create VkInstance");
        }
    }

    VulkanInstanceBackend::~VulkanInstanceBackend() {
        if (instance) {
            vkDestroyInstance(instance, nullptr);
        }
    }
}

#endif