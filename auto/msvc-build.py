#! /usr/local/bin/python3

'''
This file is meant to be used when creating the project with an msvc environment.
It will copy the necessary .dll files and place them next to the project executable.
NOTE: you should build the project with cmake and the MSVC compiler before using this script
NOTE: if a dependency directory is not specified, the script will try to find it using the CMakeCache

command structure:
    msvc-build.py <build_dir> [-sdl2 <sdl2_dir>] [-glew <glew_dir>]

an example:
    msvc-build.py -sdl2 ./build D:/dev-libs/sdl2 -glew D:/dev-libs/glew

-sdl2 D:\\libs\\source\\SDL2 -glew D:\\libs\\installations\\glew
'''

from shutil import copyfile
import os.path
import sys
import platform

from enum import Enum
class ArgState(Enum):
    NORMAL = 0
    GLEW = 1
    SDL2 = 2

# Get the build path and sdl2 paths
build_dir = sys.argv[1]
sdl2_dir = ''
glew_dir = ''

# remove trailing \\ or /. The rest of the code assumes these are not present
if build_dir[-1] == '/' or build_dir[-1] == '\\':
    build_dir = build_dir[:-1]

# process command line arguments
arg_state = 0
args = sys.argv[2:]
for a in args:
    print('arg: ' + a)

    # notify states that the next arg will be the glew dir
    if a == '-glew':
        print('specifying glew dir')
        arg_state = ArgState.GLEW

    # if we are in -glew state, this argument must be the directory where glew is
    elif arg_state == ArgState.GLEW:
        print('specified glew dir is: ' + a)
        glew_dir = a
        arg_state = ArgState.NORMAL

    # notify states that the next arg will be the sdl2 dir
    elif a == '-sdl2':
        print('specifying sdl2 dir')
        arg_state = ArgState.SDL2

    # if we are in -sdl2 state, this argument must be the directory where sdl2 is
    elif arg_state == ArgState.SDL2:
        print('specified sdl2 dir is: ' + a)
        sdl2_dir = a
        arg_state = ArgState.NORMAL

build_dir.replace("/", "\\")

if not os.path.exists(build_dir):
    print('error the build directory specified does not exist. Please create it before using this script')
    sys.exit(0)

build_types = [ 'Release', 'Debug' ]

# ===================== OPEN CMAKE CACHE IF ONE OF THE DIRS WERE NOT SPECIFIED =====================
cmake_cache = ''
if sdl2_dir == '' or glew_dir == '':
    cmake_cache_path = build_dir + '\\CMakeCache.txt'
    if os.path.exists(cmake_cache_path):
        cmake_cache_file = open(cmake_cache_path, 'r')
        for l in cmake_cache_file:
            cmake_cache += l
        cmake_cache_file.close()

# ==================== SDL2 CMAKE CACHE ============================
if sdl2_dir == '':
    sdl2_dir_path_start = 'SDL2_PATH:PATH='
    sdl_dir_start = cmake_cache.find(sdl2_dir_path_start)
    sdl2_dir_end = cmake_cache.find('\n', sdl_dir_start)
    sdl2_dir = cmake_cache[sdl_dir_start + len(sdl2_dir_path_start): sdl2_dir_end]
    # print('sdl2 path:', sdl2_dir)

# ==================== GLEW CMAKE CACHE ============================
if glew_dir == '':
    glew_dir_path_start = 'GLEW_PATH:PATH='
    glew_dir_start = cmake_cache.find(glew_dir_path_start)
    glew_dir_end = cmake_cache.find('\n', glew_dir_start)
    glew_dir = cmake_cache[ glew_dir_start + len(glew_dir_path_start) : glew_dir_end ]
    # print( 'glew dir:', glew_dir )

# ===================== COPY SDL2 DLLs =========================
if sdl2_dir != '':
    if sdl2_dir[-1] == '/' or sdl2_dir[-1] == '\\':
        sdl2_dir = sdl2_dir[:-1]
    
    sdl2_dir.replace("/", "\\")
    print("sdl2 dir: " + sdl2_dir)
    
    possible_lib_paths = [ "lib\\" ]

    lib_32_paths = ['lib32\\', 'lib\\x86\\']
    lib_64_paths = ['lib64\\', 'lib\\x64\\']

    # make sure we query the dll for the correct architecture
    arch = platform.machine()
    arch_lib_path=[]
    if 'AMD64' in arch:
        arch_lib_path = lib_64_paths
    else:
        arch_lib_path = lib_32_paths

    for lib in arch_lib_path:
        possible_lib_paths.append(lib)

    possible_dll_names = [ 'SDL2.dll' ]

    # look for the dll in all the possible paths (probably just ${sdl2_dir}/lib/x64/SDL2.dll).
    sdl2_dll_path = ['', '']
    for p in possible_lib_paths:
        for dll in possible_dll_names:
            if os.path.exists( sdl2_dir + "\\" + p + dll ):
                temp = sdl2_dir + '\\' + p + dll
                ti = -1
                
                if '32' in temp or 'x86' in temp:
                    ti = 0
                else:
                    ti = 1
                
                sdl2_dll_path[ti] = temp
                print(dll + ' was found:', sdl2_dll_path[ti])
                break

    # couldn't find dlls int the specified locations, so print them
    if sdl2_dll_path == ['', '']:
        print('Unable to find .dll. Tried the following:')
        for p in possible_lib_paths:
            for dll in possible_dll_names:
                print(sdl2_dir + '\\' + p + dll)
        sys.exit(0)

    # copy the dlls that we found
    print()
    for dll in sdl2_dll_path:
        if dll == '': continue      # there's a chance one of the specified dll paths was not found, so skip it
        for f in possible_dll_names:
            src = dll
            print('copying ' + src + ' to ' + build_dir + '\\' + f)
            copyfile(src, build_dir + '\\' + f)
            for build in build_types:
                p = build_dir + '\\' + build
                # make sure that the build dirs exist
                if os.path.exists(p):
                    dst = p + '\\' + f
                    print('copying ' + src + ' to ' + dst)
                    copyfile(src, dst)

# ============================== COPY GLEW DLLs ==============================
if glew_dir != '':
    if glew_dir[-1] == '/' or glew_dir[-1] == '\\':
        glew_dir = glew_dir[:-1]
    
    glew_dir.replace("/", "\\")
    print()
    print("glew dir: " + glew_dir)

    glew_dll_name='glew32.dll'
    glew_dll_path = glew_dir + "\\bin"
    glew_dll_possible_paths = ["", "\\Release\\x64", "\\Release\\Win32"]
    
    for i in range(len(glew_dll_possible_paths)):
        glew_dll_possible_paths[i] = glew_dll_path + glew_dll_possible_paths[i] + "\\" + glew_dll_name

    dll_copied = False
    for glew_dll_path in glew_dll_possible_paths:
        if not os.path.exists(glew_dll_path):
            continue

        src = glew_dll_path
        for build in build_types:
            p = build_dir + '\\' + build
            if os.path.exists(p):
                dst = p + '\\' + glew_dll_name
                print('copying ' + src + ' to ' + dst)
                copyfile(src, dst)
                dll_copied = True

        if dll_copied:
            break

    if not dll_copied:
        print('unable to find glew32.dll at specified locations:')
        for p in glew_dll_possible_paths:
            print(p)