#include <renderer/instance.hpp>
#include <renderer/surface.hpp>

#include <renderer/instance/vulkan.hpp>
#include <renderer/queue/vulkan.hpp>
#include <renderer/surface/vulkan.hpp>

#include <limits>

namespace engine::renderer {
    VulkanQueueBackend::VulkanQueueBackend(const Queue::Backend::CreateInfo& createInfo)
        : Queue::Backend(createInfo), queue(VK_NULL_HANDLE), familyIndex(std::numeric_limits<std::uint32_t>::max()), queueIndex(0) {
        auto& instanceData = static_cast<VulkanInstanceBackend&>(createInfo.instance.getBackend());
        auto& surfaceData = static_cast<VulkanSurfaceBackend&>(createInfo.surface.getBackend());

        auto& queueFamilies = instanceData.queueFamilies;

        VkQueueFlagBits queueTypeNeeded = VK_QUEUE_FLAG_BITS_MAX_ENUM;
        bool isPresentType = false;

        switch (createInfo.type) {
            case QueueType::COMPUTE:
                queueTypeNeeded = VK_QUEUE_COMPUTE_BIT;
                break;

            case QueueType::RENDER:
                queueTypeNeeded = VK_QUEUE_GRAPHICS_BIT;
                break;

            case QueueType::TRANSFER:
                queueTypeNeeded = VK_QUEUE_TRANSFER_BIT;
                break;

            case QueueType::PRESENT:
                isPresentType = true;
                break;
        }

        for (std::uint32_t i = 0; i < queueFamilies.size(); i++) {
            const auto& family = queueFamilies[i];

            if (isPresentType) {
                VkBool32 presentSupported = VK_FALSE;
                vkGetPhysicalDeviceSurfaceSupportKHR(instanceData.physicalDevice, i, surfaceData.surface, &presentSupported);

                if (presentSupported) {
                    familyIndex = i;
                    break;
                }
            }
            else if (family.queueFlags & queueTypeNeeded) {
                familyIndex = i;
                break;
            }
        }

        if (familyIndex == std::numeric_limits<std::uint32_t>::max()) {
            throw std::runtime_error("No suitable Vulkan queue family found");
        }

        queueIndex = 0;
    }

    VulkanQueueBackend::~VulkanQueueBackend() {
    }
}