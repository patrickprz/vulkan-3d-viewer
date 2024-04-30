#pragma once
#include <cstdlib>
#include <vector>
#include <optional>
#include <cstring>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

class VulkanHandler{
    public:
        void run();
    private:
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        #ifdef NDEBUG
            const bool enableValidationLayers = false;
        #else
            const bool enableValidationLayers = true;
        #endif


        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;

            bool isComplete(){
                return graphicsFamily.has_value();
            }
        };

        GLFWwindow* window;
        VkInstance instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
        void createInstance();
        void pickPhysicalDevice();
        void createLogicalDevice();
};