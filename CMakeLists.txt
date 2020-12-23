project(Baka)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")

# make important directories be retrievable from code
add_compile_definitions(BAKA_WORKSPACE_PATH="${CMAKE_SOURCE_DIR}")
add_compile_definitions(BAKA_ENGINE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
add_compile_definitions(BAKA_EXECUTABLE_PATH="${CMAKE_BINARY_DIR}")

find_package(SDL2 REQUIRED)
message("SDL2 includes: ${SDL2_INCLUDE_DIR}")

file(
    GLOB baka_src
    "include/**.h"
    "src/**.cpp"
    "include/lights/*.h"
    "src/lights/*.cpp"
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
    baka_engine STATIC
    "${baka_src}"
    "${baka_vk}"
    "${baka_gl}"
)

target_include_directories(baka_engine PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(baka_engine ${SDL2_LIBRARY})

target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/glm")
target_include_directories(baka_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/baka_allocators")

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

function(copy_dll target base_lib_path possible_paths possible_names)
    foreach(possible_path ${possible_paths})
        foreach(dll ${possible_names})
            set(dll_file "${base_lib_path}/${possible_path}/${dll}")
            message("try dll ${dll_file}")
            if(EXISTS "${dll_file}")
                add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${dll_file}"
                        "$<TARGET_FILE_DIR:${target}>")
                break()
            endif(EXISTS "${dll_file}")
        endforeach(dll ${sdl2_dll_names})
    endforeach(possible_path ${sdl2_dll_paths})
endfunction()

# copy SDL2.dll and glew32.dll if on msvc
macro(baka_import_dlls target)
    if( MSVC )
        set(sdl2_possible_paths lib)
        if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
            set(sdl2_possible_paths "${sdl2_possible_paths};lib64;lib/x64")
        else()
            set(sdl2_possible_paths "${sdl2_possible_paths};lib32;lib/x86")
        endif()
        copy_dll(
            ${target}
            "${SDL2_PATH}"
            "${sdl2_possible_paths}"
            "SDL2.dll"
        )

        set(glew_possible_paths .)
        if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
            set(glew_possible_paths "${glew_possible_paths};Release/x64")
        else()
            set(glew_possible_paths "${glew_possible_paths};Release/Win32")
        endif()
        copy_dll(
            ${target}
            "${GLEW_PATH}/bin"
            "${glew_possible_paths}"
            "glew32.dll"
        )
    endif()
endmacro()

# Copy default resources to build dir
set(assets_dir "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(assets_output_dir "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
add_compile_definitions(BAKA_ASSETS_DIR="${assets_output_dir}assets")
message("${assets_dir} -> ${assets_output_dir}")
file(COPY "${assets_dir}" DESTINATION "${assets_output_dir}")