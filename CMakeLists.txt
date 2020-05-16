project(Baka)

file(
    GLOB baka_src
    "include/*.h"
    "src/*.cpp"
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
    
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(baka_engine ${SDL2_LIBRARIES})

find_package(Vulkan)
if( Vulkan_FOUND )
    if(${CMAKE_VERSION} VERSION_LESS "3.12.4")
        target_compile_definitions(baka_engine PUBLIC VULKAN_AVAILABLE)
    else()
        add_compile_definitions(VULKAN_AVAILABLE)
    endif()

    target_include_directories(baka_engine PUBLIC Vulkan::Vulkan)
    target_link_libraries(baka_engine Vulkan::Vulkan)
    
    target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/platforms/baka_vulkan/include")
    set(baka_src ${baka_src} ${baka_vulkan})
endif()