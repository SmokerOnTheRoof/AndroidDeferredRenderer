set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SKIP_RPATH ON)

set(SE_ANDROID_BUILD ON)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_SKIP_COMPATIBILITY_TESTS 1)

set(ANDROID ON)

# These are just set for cmake to not complain about missing compilers

set(CMAKE_SYSTEM_PROGRAM_PATH 	"${ANDROID_NDK_TOOLCHAIN_ROOT_PATH}/bin")

set(CMAKE_C_COMPILER "arm-linux-androideabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-androideabi-g++")

set(SE_ANDROID_STL_LIBNAME "gnustl_shared")

set(SE_ANDROID_NDK_BUILD_COMMAND "${SE_ANDROID_NDK_ROOT}/ndk-build")
