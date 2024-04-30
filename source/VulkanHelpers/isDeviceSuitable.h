#include <vector>
#include <optional>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete(){
        return graphicsFamily.has_value();
    }
};

inline QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    
    int i = 0;

    for (const auto& quereFamily : queueFamilies){
        if(quereFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
            indices.graphicsFamily = i;
        }
        
        if(indices.isComplete()){
            break;
        }
        i++;
    }
    return indices;
}

inline bool isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);
    return indices.isComplete();
}