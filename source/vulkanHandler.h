#include <GLFW/glfw3.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "VulkanHelpers/checkValidationLayerSupport.h"
#include "VulkanHelpers/isDeviceSuitable.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanHandler {
public:
    void run();

private:
    GLFWwindow* window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;

    void initWindow();

    void initVulkan();

    void mainLoop();

    void cleanup();

    void createInstance();

    void pickPhysicalDevice();

    void createLogicalDevice();

    std::vector<const char*> getRequiredExtensions();

};
