#if !defined(PLATFORM_APPLE)

#include <renderer/device/vulkan.hpp>
#include <renderer/instance/vulkan.hpp>
#include <renderer/queue/vulkan.hpp>
#include <renderer/surface/vulkan.hpp>

#include <window/window.hpp>

namespace engine::renderer {
    VulkanDeviceBackend::VulkanDeviceBackend(const Device::BackendCreateInfo& createInfo)
        : Device::Backend(createInfo), device(VK_NULL_HANDLE) {
        auto& vulkanInstanceBackend = static_cast<VulkanInstanceBackend&>(instance.getBackend());

        std::vector<std::uint32_t> familyIndexMappings;
        std::vector<std::vector<float>> familyIndexPriorities;

        for (auto& queue : queues) {
            auto& queueInfo = static_cast<VulkanQueueBackend&>(queue.get().getBackend());

            auto& index = queueInfo.familyIndex;

            if (familyIndexMappings.size() <= index) {
                familyIndexMappings.resize(index + 1, 0);
                familyIndexPriorities.resize(index + 1);
            }

            if (familyIndexMappings[index] < vulkanInstanceBackend.queueFamilies[index].queueCount) {
                familyIndexMappings[index]++;
                familyIndexPriorities[index].push_back(1.0f);
            }
        }

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        for (std::uint32_t i = 0; i < familyIndexMappings.size(); i++) {
            if (familyIndexMappings[i] == 0 || familyIndexPriorities[i].size() == 0) {
                continue;
            }

            VkDeviceQueueCreateInfo queueCreateInfo = {
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .pNext = nullptr,
                .flags = 0,
                .queueFamilyIndex = i,
                .queueCount = familyIndexMappings[i],
                .pQueuePriorities = familyIndexPriorities[i].data(),
            };

            queueCreateInfos.push_back(queueCreateInfo);
        }

        std::uint32_t queueCreateInfoCount = queueCreateInfos.size();

        VkDeviceCreateInfo deviceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueCreateInfoCount = queueCreateInfoCount,
            .pQueueCreateInfos = queueCreateInfos.data(),
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = nullptr,
            .enabledExtensionCount = 0,
            .ppEnabledExtensionNames = nullptr,
            .pEnabledFeatures = nullptr,
        };

        if (vkCreateDevice(vulkanInstanceBackend.physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create VkDevice");
        }

        for (auto& queue : queues) {
            auto& queueInfo = static_cast<VulkanQueueBackend&>(queue.get().getBackend());

            vkGetDeviceQueue(device, queueInfo.familyIndex, queueInfo.queueIndex, &queueInfo.queue);
        }
    }

    VulkanDeviceBackend::~VulkanDeviceBackend() {
        if (device != VK_NULL_HANDLE) {
            vkDestroyDevice(device, nullptr);
        }
    }
}

#endif