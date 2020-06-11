project(Baka)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")

find_package(SDL2 REQUIRED)
message("SDL2 includes: ${SDL2_INCLUDE_DIR}")

file(
    GLOB baka_src
    "include/*.h"
    "src/*.cpp"
    "external/glm/glm/*.hpp"
    "external/glm/glm/*.inl"
)

file(
    GLOB baka_vk
    "platforms/include/baka_vk/*.h"
    "platforms/src/baka_vk/*.cpp"
)

file(
    GLOB baka_gl
    "platforms/include/baka_gl/*.h"
    "platforms/src/baka_gl/*.cpp"
)

add_library(
    baka_engine
    "${baka_src}"
    "${baka_vk}"
    "${baka_gl}"
)

target_include_directories(baka_engine PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(baka_engine ${SDL2_LIBRARY})

target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/glm")

# VULKAN
find_package(Vulkan)
if( Vulkan_FOUND )
    target_include_directories(baka_engine PUBLIC Vulkan::Vulkan)
    target_link_libraries(baka_engine Vulkan::Vulkan)
    
    target_compile_definitions(baka_engine PUBLIC VULKAN_AVAILABLE)
    message("Vulkan includes: ${Vulkan_INCLUDE_DIR}")
endif()

# OPENGL 
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL)
if( OPENGL_FOUND )

    find_package(GLEW REQUIRED)
    target_link_libraries(baka_engine ${GLEW_LIBRARIES})
    target_include_directories(baka_engine PUBLIC ${GLEW_INCLUDE_DIRS})

    # target_include_directories(baka_engine PUBLIC OpenGL::GL)
    target_link_libraries(baka_engine OpenGL::GL)

    target_compile_definitions(baka_engine PUBLIC OPEN_GL_AVAILABLE)
    message("Glew includes: ${GLEW_INCLUDE_DIRS}")
endif()

target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/platforms/include")
target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# make important directories be retrievable from code
add_compile_definitions(BAKA_WORKSPACE_PATH="${CMAKE_SOURCE_DIR}")
add_compile_definitions(BAKA_ENGINE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
add_compile_definitions(BAKA_EXECUTABLE_PATH="${CMAKE_BINARY_DIR}")

# Copy the shaders to get a good filepath thing from engine
file(
    GLOB shaders
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*"
)

set( shader_outdir "${CMAKE_CURRENT_BINARY_DIR}/shaders" )
foreach( f ${shaders} )
    get_filename_component(filename ${f} NAME)
    set(outfile "${shader_outdir}/${filename}")
    message("copy ${filename} to ${outfile}")
    configure_file(${f} ${outfile} COPYONLY)
endforeach()