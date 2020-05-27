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

file(
    GLOB baka_gl
    "platforms/baka_open_gl/include/*.h"
    "platforms/baka_open_gl/src/*.cpp"
)

add_library(
    baka_engine
    "${baka_src}"
    "${baka_vulkan}"
)

target_include_directories(baka_engine PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(baka_engine ${SDL2_LIBRARY})

# VULKAN
find_package(Vulkan)
if( Vulkan_FOUND )
    # if(${CMAKE_VERSION} VERSION_LESS "3.12.4")

    target_include_directories(baka_engine PUBLIC Vulkan::Vulkan)
    target_link_libraries(baka_engine Vulkan::Vulkan)

    set(baka_src ${baka_src} ${baka_vulkan})
    
    target_compile_definitions(baka_engine PUBLIC VULKAN_AVAILABLE)
    message("Vulkan includes: ${Vulkan_INCLUDE_DIR}")
endif()
target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/platforms/baka_vulkan/include")

# OPENGL 
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL)
if( OPENGL_FOUND )

    find_package(GLEW REQUIRED)
    target_link_libraries(baka_engine ${GLEW_LIBRARIES})
    target_include_directories(baka_engine PUBLIC ${GLEW_INCLUDE_DIRS})

    target_include_directories(baka_engine PUBLIC OpenGL::OpenGL)
    target_link_libraries(baka_engine OpenGL::OpenGL)

    set(baka_src ${baka_src} ${baka_gl})

    target_compile_definitions(baka_engine PUBLIC OPEN_GL_AVAILABLE)
    message("OpenGL includes: ${OPENGL_INCLUDE_DIR}")
    
endif()
target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/platforms/baka_open_gl/include")

target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

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