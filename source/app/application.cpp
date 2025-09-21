#include <app/application.hpp>

namespace engine::app {
    Application::Application()
        : shouldUpdate_(true) {
    }

    Application::~Application() {
    }

    void Application::create(const CreateInfo& createInfo) {
        window::Window::CreateInfo windowCreateInfo = {
            .size = {800, 600},
            .title = "New Window",
            .visibility = window::Visibility::WINDOWED,
            .context = context_,
            .resizable = true,
        };

        window_.create(windowCreateInfo);

        renderer::Instance::CreateInfo instanceCreateInfo = {
            .context = context_,
            .applicationName = createInfo.name,
            .applicationVersionMajor = createInfo.versionMajor,
            .applicationVersionMinor = createInfo.versionMinor,
            .applicationVersionPatch = createInfo.versionPatch,
            .engineName = "engine",
            .engineVersionMajor = 0,
            .engineVersionMinor = 0,
            .engineVersionPatch = 1,
            .requestDebug = true,
        };

        instance_.create(instanceCreateInfo);

        renderer::Surface::CreateInfo surfaceCreateInfo = {
            .instance = instance_,
            .window = window_,
        };

        surface_.create(surfaceCreateInfo);

        // std::uint32_t physicalDeviceCount = 0;
        //
        // if (vkEnumeratePhysicalDevices(instance_, &physicalDeviceCount, nullptr) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to enumerate VkPhysicalDevices");
        // }
        //
        // std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        //
        // if (vkEnumeratePhysicalDevices(instance_, &physicalDeviceCount, physicalDevices.data()) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to enumerate VkPhysicalDevices");
        // }
        //
        // for (auto& device_ : physicalDevices) {
        //     VkPhysicalDeviceProperties deviceProperties;
        //     vkGetPhysicalDeviceProperties(device_, &deviceProperties);
        //
        //     if (deviceProperties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        //         continue;
        //     }
        //
        //     std::uint32_t queueFamilyCount = 0;
        //     vkGetPhysicalDeviceQueueFamilyProperties(device_, &queueFamilyCount, nullptr);
        //     std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        //     vkGetPhysicalDeviceQueueFamilyProperties(device_, &queueFamilyCount, queueFamilies.data());
        //
        //     for (std::uint32_t i = 0; i < queueFamilyCount; i++) {
        //         VkBool32 presentSupported = VK_FALSE;
        //         if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
        //             vkGetPhysicalDeviceSurfaceSupportKHR(device_, i, surface_, &presentSupported) == VK_SUCCESS &&
        //             presentSupported) {
        //             physicalDevice_ = device_;
        //             graphicsQueueFamilyIndex_ = i;
        //             break;
        //         }
        //     }
        //
        //     if (physicalDevice_ != VK_NULL_HANDLE) {
        //         break;
        //     }
        // }
        //
        // if (physicalDevice_ == VK_NULL_HANDLE) {
        //     throw std::runtime_error("failed to find a suitable discrete GPU with graphics + present support");
        // }
        //
        // float queuePriority = 1.0f;
        //
        // VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
        //     .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        //     .pNext = nullptr,
        //     .flags = 0,
        //     .queueFamilyIndex = graphicsQueueFamilyIndex_,
        //     .queueCount = 1,
        //     .pQueuePriorities = &queuePriority,
        // };
        //
        // std::vector<const char*> deviceExtensions = {
        //     "VK_KHR_swapchain",
        // };
        //
        // VkDeviceCreateInfo deviceCreateInfo = {
        //     .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        //     .pNext = nullptr,
        //     .flags = 0,
        //     .queueCreateInfoCount = 1,
        //     .pQueueCreateInfos = &deviceQueueCreateInfo,
        //     .enabledLayerCount = 0,
        //     .ppEnabledLayerNames = nullptr,
        //     .enabledExtensionCount = (std::uint32_t)deviceExtensions.size(),
        //     .ppEnabledExtensionNames = deviceExtensions.data(),
        //     .pEnabledFeatures = nullptr,
        // };
        //
        // if (vkCreateDevice(physicalDevice_, &deviceCreateInfo, nullptr, &device_) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to create VkDevice");
        // }
        //
        // vkGetDeviceQueue(device_, graphicsQueueFamilyIndex_, 0, &graphicsQueue_);
        //
        // VkSurfaceCapabilitiesKHR surfaceCapabilities;
        //
        // if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice_, surface_, &surfaceCapabilities) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to query VkPhysicalDevice surface capabilities");
        // }
        //
        // uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
        //
        // if (surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceCapabilities.maxImageCount) {
        //     imageCount = surfaceCapabilities.maxImageCount;
        // }
        //
        // std::uint32_t formatCount = 0;
        //
        // if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice_, surface_, &formatCount, nullptr) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to query VkSurfaceKHR surface formats");
        // }
        //
        // std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
        //
        // if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice_, surface_, &formatCount, surfaceFormats.data()) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to query VkSurfaceKHR surface formats");
        // }
        //
        // VkSurfaceFormatKHR surfaceFormat = surfaceFormats.front();
        //
        // VkExtent2D extent = surfaceCapabilities.currentExtent;
        // if (extent.width == UINT32_MAX) {
        //     extent.width = window_.getSize().x;
        //     extent.height = window_.getSize().y;
        // }
        //
        // VkSwapchainCreateInfoKHR swapchainCreateInfo = {
        //     .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        //     .pNext = nullptr,
        //     .flags = 0,
        //     .surface = surface_,
        //     .minImageCount = imageCount,
        //     .imageFormat = surfaceFormat.format,
        //     .imageColorSpace = surfaceFormat.colorSpace,
        //     .imageExtent = extent,
        //     .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        //     .preTransform = surfaceCapabilities.currentTransform,
        //     .presentMode = VK_PRESENT_MODE_FIFO_KHR,
        //     .clipped = VK_TRUE,
        //     .oldSwapchain = nullptr,
        // };
        //
        // if (vkCreateSwapchainKHR(device_, &swapchainCreateInfo, nullptr, &swapchain_) != VK_SUCCESS) {
        //     throw std::runtime_error("failed to create VkSwapchainKHR");
        // }
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