#include <cstdint>
#include <iostream>
#include <vector>
#include <vulkan/vulkan_core.h>
#include "vulkanHandler.h"
#include "VulkanHelpers/checkExtensions.hpp"
#include "VulkanHelpers/isDeviceSuitable.hpp"
#include "VulkanHelpers/checkValidationLayerSupport.hpp"

//validation layer support


void VulkanHandler::run(){
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void VulkanHandler::initWindow(){
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    glfwInit();
    //glfw default is create openglap
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //disables resizable window 
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    std::cout << "log:glfwInit" << std::endl;    
}

void VulkanHandler::initVulkan(){
    std::cout << "log:initVulkan" << std::endl;
    createInstance();   
    pickPhysicalDevice();
    createLogicalDevice();
}

void VulkanHandler::mainLoop(){
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VulkanHandler::cleanup(){
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "log:cleanup" << std::endl;
}

void VulkanHandler::createInstance(){
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    std::cout << "log:validation layer supported" << std::endl;
    //opcional
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    //obrigatoria extensao global
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    //check vulkan extensions
    checkExtensions();

    uint32_t glfwExtensionCount = 0;

    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    //validation por hora zero
    //createInfo.enabledLayerCount = 0;

        
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    std::cout << "log:extensionCount = " << glfwExtensionCount << std::endl;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void VulkanHandler::pickPhysicalDevice(){
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            VkPhysicalDeviceProperties* properties;
            vkGetPhysicalDeviceProperties(device, properties);
            std::cout << "log:device " << properties->deviceName << std::endl;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
    std::cout << "log:device suitable" << std::endl;
}

void VulkanHandler::createLogicalDevice(){

}