
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
    std::cout << "log:EXIT_SUCCESS" << std::endl;
    return EXIT_SUCCESS;
}