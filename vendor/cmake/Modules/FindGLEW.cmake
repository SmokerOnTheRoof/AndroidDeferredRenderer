# - Try to find SDL
# Once done this will define
#  GLEW_FOUND - System has GLEW
#  GLEW_INCLUDE_DIRS - The GLEW include directories
#  GLEW_LIBRARIES - The libraries needed to use GLEW
#  GLEW_DEFINITIONS - Compiler switches required for using GLEW

set(GLEW_VERSION 1.10.0)


set(GLEW_DIR "${SE_THIRD_PARTY_DIR}/GLEW/${GLEW_VERSION}")

set(GLEW_INCLUDE_DIRS "${GLEW_DIR}/include")

if(WIN32)
    
        set(GLEW_LIBRARIES   debug       "${GLEW_DIR}/lib/Debug/Win32/glew32sd.lib"
                            optimized   "${GLEW_DIR}/lib/Release/Win32/glew32s.lib")

endif(WIN32)
