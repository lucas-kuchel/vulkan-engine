#if !defined(PLATFORM_APPLE)

#include <renderer/instance/vulkan.hpp>

#include <window/context.hpp>

#include <vector>

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

        std::uint32_t instanceLayerCount = 0;

        if (vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("failed to enumerate Vulkan instance layer properties");
        }

        std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
        std::vector<const char*> instanceLayers;

        if (vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to enumerate Vulkan instance layer properties");
        }

        for (auto& instanceLayer : instanceLayerProperties) {
            if (createInfo.requestDebug) {
                bool isValidationLayer = std::string_view(instanceLayer.layerName) == "VK_LAYER_KHRONOS_validation";
                bool isApiDumpLayer = std::string_view(instanceLayer.layerName) == "VK_LAYER_LUNARG_api_dump";

                if (isValidationLayer || isApiDumpLayer) {
                    instanceLayers.push_back(instanceLayer.layerName);
                }
            }
        }

        std::uint32_t layerCount = (std::uint32_t)instanceLayers.size();

        VkInstanceCreateInfo instanceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .pApplicationInfo = &applicationInfo,
            .enabledLayerCount = layerCount,
            .ppEnabledLayerNames = instanceLayers.data(),
            .enabledExtensionCount = instanceExtensionCount,
            .ppEnabledExtensionNames = instanceExtensions,
        };

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create VkInstance");
        }

        std::uint32_t physicalDeviceCount = 0;

        if (vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("failed to enumerate VkPhysicalDevices");
        }

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);

        if (vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to enumerate VkPhysicalDevices");
        }

        physicalDevice = VK_NULL_HANDLE;

        for (auto& device : physicalDevices) {
            VkPhysicalDeviceProperties deviceProperties;

            vkGetPhysicalDeviceProperties(device, &deviceProperties);

            if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            physicalDevice = physicalDevices.front();
        }

        std::uint32_t queueFamilyCount = 0;

        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        queueFamilies.resize(queueFamilyCount);

        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());
    }

    VulkanInstanceBackend::~VulkanInstanceBackend() {
        if (instance) {
            vkDestroyInstance(instance, nullptr);
        }
    }
}

#endif