cmake_minimum_required(VERSION 3.22.1)

project(vulkan-3d-viewer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)

find_package(glfw3 3.4 REQUIRED)

add_executable(${PROJECT_NAME} source/main.cpp
                               source/vulkanHandler.cpp  
                               source/vulkanHandler.h  
                               )

target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)


