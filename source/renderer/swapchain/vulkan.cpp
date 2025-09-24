#if !defined(PLATFORM_APPLE)

#include <renderer/device/vulkan.hpp>
#include <renderer/instance/vulkan.hpp>
#include <renderer/queue/vulkan.hpp>
#include <renderer/surface/vulkan.hpp>
#include <renderer/swapchain/vulkan.hpp>

#include <window/window.hpp>

namespace engine::renderer {
    VulkanSwapchainBackend::VulkanSwapchainBackend(const Swapchain::BackendCreateInfo& createInfo)
        : Swapchain::Backend(createInfo) {
        auto& instanceInfo = static_cast<VulkanInstanceBackend&>(instance.getBackend());
        auto& surfaceInfo = static_cast<VulkanSurfaceBackend&>(surface.getBackend());
        auto& deviceInfo = static_cast<VulkanDeviceBackend&>(device.getBackend());

        VkSurfaceCapabilitiesKHR surfaceCapabilities;

        if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(instanceInfo.physicalDevice, surfaceInfo.surface, &surfaceCapabilities) != VK_SUCCESS) {
            throw std::runtime_error("failed to enumerate surface capabilities");
        }

        VkExtent2D extent;

        if (surfaceCapabilities.currentExtent.width != std::numeric_limits<std::uint32_t>::max()) {
            extent = surfaceCapabilities.currentExtent;
        }
        else {
            extent.width = glm::clamp(surfaceInfo.window.getSize().x, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
            extent.height = glm::clamp(surfaceInfo.window.getSize().y, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
        }

        std::uint32_t formatCount = 0;

        if (vkGetPhysicalDeviceSurfaceFormatsKHR(instanceInfo.physicalDevice, surfaceInfo.surface, &formatCount, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("failed to get surface formats");
        }

        std::vector<VkSurfaceFormatKHR> formats(formatCount);

        if (vkGetPhysicalDeviceSurfaceFormatsKHR(instanceInfo.physicalDevice, surfaceInfo.surface, &formatCount, formats.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to get surface formats");
        }

        VkSurfaceFormatKHR chosenFormat = formats[0];

        if (formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED) {
            chosenFormat.format = VK_FORMAT_B8G8R8A8_SRGB;
            chosenFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        }
        else {
            for (const auto& format : formats) {
                if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                    chosenFormat = format;
                    break;
                }
            }
        }

        std::uint32_t presentModeCount = 0;

        if (vkGetPhysicalDeviceSurfacePresentModesKHR(instanceInfo.physicalDevice, surfaceInfo.surface, &presentModeCount, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("failed to get surface present modes");
        }

        std::vector<VkPresentModeKHR> presentModes(formatCount);

        if (vkGetPhysicalDeviceSurfacePresentModesKHR(instanceInfo.physicalDevice, surfaceInfo.surface, &presentModeCount, presentModes.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to get surface present modes");
        }

        VkPresentModeKHR chosenPresentMode = VK_PRESENT_MODE_FIFO_KHR;

        std::int32_t chosenPriority = -1;

        for (const auto& mode : presentModes) {
            std::int32_t priority = -1;

            if (mode == VK_PRESENT_MODE_MAILBOX_KHR) {
                priority = 4;
            }
            else if (!synchronise && mode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                priority = 3;
            }
            else if (mode == VK_PRESENT_MODE_FIFO_LATEST_READY_EXT) {
                priority = 2;
            }
            else if (mode == VK_PRESENT_MODE_FIFO_RELAXED_KHR) {
                priority = 1;
            }
            else if (mode == VK_PRESENT_MODE_FIFO_KHR) {
                priority = 0;
            }

            if (priority > chosenPriority) {
                chosenPriority = priority;
                chosenPresentMode = mode;
            }
        }

        VkSwapchainCreateInfoKHR swapchainCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            .pNext = nullptr,
            .flags = 0,
            .surface = surfaceInfo.surface,
            .minImageCount = std::max(std::min(static_cast<std::uint32_t>(imageCount), surfaceCapabilities.maxImageCount), surfaceCapabilities.minImageCount), // You might have already set this earlier.
            .imageFormat = chosenFormat.format,
            .imageColorSpace = chosenFormat.colorSpace,
            .imageExtent = extent,
            .imageArrayLayers = 1,
            .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
            .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .queueFamilyIndexCount = 0,
            .pQueueFamilyIndices = nullptr,
            .preTransform = surfaceCapabilities.currentTransform,
            .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            .presentMode = chosenPresentMode,
            .clipped = VK_TRUE,
            .oldSwapchain = swapchain,
        };

        std::uint32_t graphicsFamilyIndex = static_cast<VulkanQueueBackend&>(renderQueue.getBackend()).familyIndex;
        std::uint32_t presentFamilyIndex = static_cast<VulkanQueueBackend&>(presentQueue.getBackend()).familyIndex;

        if (graphicsFamilyIndex != presentFamilyIndex) {
            std::uint32_t queueFamilyIndices[] = {graphicsFamilyIndex, presentFamilyIndex};

            swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swapchainCreateInfo.queueFamilyIndexCount = 2;
            swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
        }

        if (vkCreateSwapchainKHR(deviceInfo.device, &swapchainCreateInfo, nullptr, &swapchain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swapchain");
        }
    }

    VulkanSwapchainBackend::~VulkanSwapchainBackend() {
        auto& deviceInfo = static_cast<VulkanDeviceBackend&>(device.getBackend());

        if (swapchain != VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(deviceInfo.device, swapchain, nullptr);
        }
    }
}

#endif