# - Try to find SDL
# Once done this will define
#  SDL_FOUND - System has SDL
#  SDL_INCLUDE_DIRS - The SDL include directories
#  SDL_LIBRARIES - The libraries needed to use SDL
#  SDL_DEFINITIONS - Compiler switches required for using SDL

set(SDL_VERSION 2.0.3)

set(SDL_INCLUDE_DIRS "${SE_THIRD_PARTY_DIR}/SDL/${SDL_VERSION}/include")

if(WIN32)
    
        set(SDL_LIBRARIES   debug       "${SE_THIRD_PARTY_DIR}/SDL/${SDL_VERSION}/build/win/x86/Debug/SDL2.lib"
                            optimized   "${SE_THIRD_PARTY_DIR}/SDL/${SDL_VERSION}/build/win/x86/Release/SDL2.lib"
                            winmm.lib
                            imm32.lib
                            version.lib
                            dinput8.lib
                            dxguid.lib
                            #dxerr.lib
                            )

                            # ToDo: Create a minimal config for SDL, because some of the features are not relevant anymore
                            
        set(SDL_INCLUDE_DIRS    ${SDL_INCLUDE_DIRS}
                                "${SE_THIRD_PARTY_DIR}/SDL/${SDL_VERSION}/win/x86/include")

endif(WIN32)

if(UNIX)

set(SDL_LIBRARIES   "${SE_THIRD_PARTY_DIR}/SDL/${SDL_VERSION}/build/android/19/libSDL2.a")

endif(UNIX)
