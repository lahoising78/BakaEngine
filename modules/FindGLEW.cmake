set(GLEW_PATH "" CACHE PATH "path to GLEW")
SET(GLEW_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
	${GLEW_PATH}
	$ENV{GLEWDIR}
)

FIND_PATH(GLEW_INCLUDE_DIRS GL/glew.h
	HINTS
    $ENV{GLEWDIR}
    PATH_SUFFIXES include
	PATHS ${GLEW_SEARCH_PATHS}
)

FIND_LIBRARY(GLEW_LIBRARIES
    NAMES GLEW glew32 glew32s
    HINT
    $ENV{GLEWDIR}
    PATH_SUFFIXES lib lib/Release/x64 lib/Release/Win32
    PATHS ${GLEW_SEARCH_PATHS}
)

message("include: ${GLEW_INCLUDE_DIRS}\nlibs: ${GLEW_LIBRARIES}")

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW REQUIRED_VARS GLEW_INCLUDE_DIRS GLEW_LIBRARIES)