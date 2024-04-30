
#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include "vulkanHandler.h"


int main() {
    VulkanHandler app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
