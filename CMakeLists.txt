cmake_minimum_required(VERSION 3.21)

project(engine LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "source/*.cpp")

find_package(glfw3 CONFIG REQUIRED)
find_package(VulkanHeaders CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(engine ${SOURCES})

target_compile_options(engine PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

target_link_libraries(engine PRIVATE 
    glfw 
    Vulkan::Vulkan 
    Vulkan::Headers
)

target_include_directories(engine PRIVATE "include")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(engine PRIVATE DEBUG_BUILD_TYPE)
endif()