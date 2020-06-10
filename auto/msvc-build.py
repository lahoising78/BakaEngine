#! /usr/local/bin/python3

'''
This file is meant to be used when creating the project with an msvc environment.
It will copy the necessary .dll files and place them next to the project executable.

command structure:
    msvc-build.py <build_dir> <sdl2_path>

an example:
    msvc-build.py ./build D:/dev-libs/sdl2
'''

from shutil import copyfile
import os.path
import sys
import platform

# Get the build path and sdl2 paths
build_dir = sys.argv[1]
sdl2_path = sys.argv[2]
glew_dir = ''

# remove trailing \\ or /. The rest of the code assumes these are not present
if build_dir[-1] == '/' or build_dir[-1] == '\\':
    build_dir = build_dir[:-1]

if sdl2_path[-1] == '/' or build_dir[-1] == '\\':
    sdl2_path = sdl2_path[:-1]

# process command line arguments
from enum import Enum

class ArgState(Enum):
    NORMAL = 0
    GLEW = 1

arg_state = 0
args = sys.argv[3:]
for a in args:
    print('arg: ' + a)

    # if we are in -glew state, this argument must be the directory where glew is
    if arg_state == ArgState.GLEW:
        print('specified glew dir is: ' + a)
        glew_dir = a
        arg_state = ArgState.NORMAL

    if a == '-glew':
        print('specifying glew dir')
        arg_state = ArgState.GLEW

build_dir.replace("/", "\\")
sdl2_path.replace("/", "\\")
print("identifying dir and sdl2 path:", build_dir, sdl2_path)

if os.path.exists(build_dir):
    print('build dir exists')
else:
    print('error the build directory specified does not exist. Please create it before using this script')

possible_lib_paths = [ "lib\\" ]

lib_32_paths = ['lib32\\', 'lib\\x86\\']
lib_64_paths = ['lib64\\', 'lib\\x64\\']

arch = platform.machine()
arch_lib_path=[]
if 'AMD64' in arch:
    arch_lib_path = lib_64_paths
else:
    arch_lib_path = lib_32_paths

for lib in arch_lib_path:
    possible_lib_paths.append(lib)

possible_dll_names = [ 'SDL2.dll' ]

sdl2_dll_path = ['', '']
for p in possible_lib_paths:
    for dll in possible_dll_names:
        if os.path.exists( sdl2_path + "\\" + p + dll ):
            temp = sdl2_path + '\\' + p + dll
            ti = -1
            
            if '32' in temp or 'x86' in temp:
                ti = 0
            else:
                ti = 1
            
            sdl2_dll_path[ti] = temp
            print(dll + ' was found:', sdl2_dll_path[ti])
            break

if sdl2_dll_path == ['', '']:
    print('Unable to find .dll. Tried the following:')
    for p in possible_lib_paths:
        for dll in possible_dll_names:
            print(sdl2_path + '\\' + p + dll)
    sys.exit(0)

# print('copying ' + str(sdl2_dll_path) + ' to ' + build_dir)

build_types = [ 'Release', 'Debug' ]

print()
for dll in sdl2_dll_path:
    if dll == '': continue

    for f in possible_dll_names:
        src = dll
        print('copying ' + src + ' to ' + build_dir + '\\' + f)
        copyfile(src, build_dir + '\\' + f)
        for build in build_types:
            p = build_dir + '\\' + build
            if os.path.exists(p):
                dst = p + '\\' + f
                print('copying ' + src + ' to ' + dst)
                copyfile(src, dst)

if glew_dir != '':
    print()
    glew_dll_name='glew32.dll'
    glew_dll_path = glew_dir + "\\bin\\" + glew_dll_name
    if not os.path.exists(glew_dll_path):
        print('unable to find glew32.dll at specified location:', glew_dll_path)
        sys.exit(0)

    src = glew_dll_path
    for build in build_types:
        p = build_dir + '\\' + build
        if os.path.exists(p):
            dst = p + '\\' + glew_dll_name
            print('copying ' + src + ' to ' + dst)
            copyfile(src, dst)