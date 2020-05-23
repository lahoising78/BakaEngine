project(Baka)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")

find_package(SDL2 REQUIRED)
message("SDL2 includes: ${SDL2_INCLUDE_DIR}")

file(
    GLOB baka_src
    "include/*.h"
    "src/*.cpp"
    "platforms/baka_open_gl/include/*.h"
    "platforms/baka_open_gl/src/*.cpp"
)

file(
    GLOB baka_vulkan
    "platforms/baka_vulkan/include/*.h"
    "platforms/baka_vulkan/src/*.cpp"
)

add_library(
    baka_engine
    "${baka_src}"
    "${baka_vulkan}"
)

target_include_directories(baka_engine PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(baka_engine ${SDL2_LIBRARY})

find_package(Vulkan)
if( Vulkan_FOUND )
    # if(${CMAKE_VERSION} VERSION_LESS "3.12.4")
    target_compile_definitions(baka_engine PUBLIC VULKAN_AVAILABLE)

    target_include_directories(baka_engine PUBLIC Vulkan::Vulkan)
    target_link_libraries(baka_engine Vulkan::Vulkan)

    target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/platforms/baka_vulkan/include")
    set(baka_src ${baka_src} ${baka_vulkan})

    message("Vulkan includes: ${Vulkan_INCLUDE_DIR}")
endif()

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL)
target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/platforms/baka_open_gl/include")

target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
