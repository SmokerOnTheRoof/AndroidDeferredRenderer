

# An Android project needs
#   1. AndroidManifest (I'm pretty sure this one needs to be written per app.)
#   2. res files
#       -> icons
#       -> layouts
#       -> values (String.xml)
#       -> assets (everything else what needs to be packaged)
#       -> jni
#           Android.mk
#           Application.mk
#               archsubfolder1
#                   Android.mk
#                   archsubsubfolder1
#						Android.mk
#                       libname1.so

# just for the record, because it might become interesting
#   based on the ADT plugin the android buildchain is
#       1. NDK-Build
#       2. Android Ressource Manager
#       3. Android Pre Compiler
#       4. Java Builder
#       5. Android Package Builder
#       6. Scanner Configuration Builder

macro(init_SE_ANDROID_BUILD_vars)
#    set(SE_ANDROID_BUILD OFF CACHE BOOL "Set to true to trigger android build.")
    
    if(ANDROID)
    
        #set(SE_ANDROID_STL_LIBNAME gnustl_shared)
    
        if(SE_ANDROID_BUILD)
        
            set(SE_ANDROID_NDK_ROOT "" CACHE PATH "Set the path to the Android NDK root.")
            if(NOT SE_ANDROID_NDK_ROOT)
                message(FATAL_ERROR "Android NDK location was not set.")
            endif(NOT SE_ANDROID_NDK_ROOT)
        
            set(android_jni_dir "${CMAKE_BINARY_DIR}/jni")
        
            set(SE_ANDROID_TARGET_ABI_VERSION 19 CACHE STRING "Target android abi version.")
            set(ANDROID_ABIS    9 10 11 12 13 14 15 16 17 18 19 20) # ToDo: Add the names
            set_property(CACHE SE_ANDROID_TARGET_ABI_VERSION PROPERTY STRINGS ${ANDROID_ABIS})
        
        
            # All cache items which will be set when cmake is called recursively 
            set(SE_SET_CMAKE_CMD_VARS   "-DSE_ANDROID_NDK_ROOT=${SE_ANDROID_NDK_ROOT}"
                                    "-DSE_ANDROID_TARGET_ABI_VERSION=${SE_ANDROID_TARGET_ABI_VERSION}"
                                    "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
        
            set(SE_ANDROID_TARGET_ARCH  armeabi)
        
            initAndroidBuild()
        
            buildAndroidNDKCmake()
            
            ndkBuildTarget()
            
            set(SE_ARCH_TARGET_NAMES "")
            
        elseif(NOT SE_ANDROID_BUILD)
    
            initAndroidBuildArch()
            
        endif(SE_ANDROID_BUILD)
    
    endif(ANDROID)
    
endmacro(init_SE_ANDROID_BUILD_vars)

function(initAndroidBuild)

    #set(mkdircommand "${CMAKE_COMMAND}" -E make_directory ${android_jni_dir})

    execute_process(COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/OpenGLES3 ${CMAKE_BINARY_DIR}/assets
                    OUTPUT_VARIABLE output
                RESULT_VARIABLE result
                ERROR_VARIABLE error)

    # Copy the res folder
    execute_process(COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/android/res ${CMAKE_BINARY_DIR}/res
                    OUTPUT_VARIABLE output
                    RESULT_VARIABLE result
                    ERROR_VARIABLE error)
    # copy the android manifest            
    execute_process(COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/android/AndroidManifest.xml ${CMAKE_BINARY_DIR}/AndroidManifest.xml
                    OUTPUT_VARIABLE output
                    RESULT_VARIABLE result
                    ERROR_VARIABLE error)
       
    # copy the project.properties
    execute_process(COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/android/project.properties ${CMAKE_BINARY_DIR}/project.properties
                    OUTPUT_VARIABLE output
                    RESULT_VARIABLE result
                    ERROR_VARIABLE error)
                
    # The android java src will be copied at cmake time
    #   this solution is far from perfect but for now i'm only interested in the c++ src
    #   ToDo: There might be a better way. Maybe library project can help here.
    #         If nothing else helps try symlinking the folder.
                
    execute_process(COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/android/src ${CMAKE_BINARY_DIR}/src
                    OUTPUT_VARIABLE output
                    RESULT_VARIABLE result
                    ERROR_VARIABLE error)
                
    #--build ${build_location}
    
        message("Result = ${result}")
        message("Out = ${output}")
        message("Error = ${error}")
    # ToDo: The directory needs to be created too.
    
    configure_file( "${CMAKE_MODULE_PATH}/AndroidSubdirAndroid.mk.in"
                    "${android_jni_dir}/Android.mk"
                    )
    
    configure_file( "${CMAKE_MODULE_PATH}/AndroidApplication.mk.in" 
                    "${android_jni_dir}/Application.mk"
                    )

    set(build_library_root  "${android_jni_dir}/libs")
    
    # Create the Android.mk for the lib
    configure_file( "${CMAKE_MODULE_PATH}/AndroidArchAndroid.mk.in" #input
                    "${build_library_root}/Android.mk")
                    
    
                    
endfunction(initAndroidBuild)

function(initAndroidBuildArch)
    # Create the Android.mk for the lib
    configure_file( "${CMAKE_MODULE_PATH}/AndroidSubdirAndroid.mk.in"
                    "${CMAKE_BINARY_DIR}/Android.mk")

endfunction(initAndroidBuildArch)

function(buildAndroidNDKCmake)

    # needs to be called only once
    
    set(libname libs)

    message(BUILD ANDROID NDK LIB ${libname})
    
    set(build_library_root  "${android_jni_dir}/${libname}")
    
    # ToDo: For each architecture
    
    # set cmake command
    set(cm_build_args   -G ${CMAKE_GENERATOR} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/android-toolchain.cmake ) 
    set(cm_create_build_dir_command    "${CMAKE_COMMAND}" ${cm_build_args} ${SE_SET_CMAKE_CMD_VARS} ${CMAKE_SOURCE_DIR})
    
    set(current_arch "armeabi")
    set(build_location "${build_library_root}/${current_arch}")
    
    set(cm_build_command    ${CMAKE_COMMAND} --build ${build_location})

    se_print(cm_create_build_dir_command)

    set(mkdircommand "${CMAKE_COMMAND}" -E make_directory ${build_location})

    se_print(mkdircommand)

    #get_cmake_property(cmakeCache   CACHE_VARIABLES)

    build_command(cmakeCache)
    
    se_print(cmakeCache)
    
    # Create the build directory
    
    se_print(mkdircommand)
    execute_process(COMMAND  ${mkdircommand}
                OUTPUT_VARIABLE output
                RESULT_VARIABLE result
                ERROR_VARIABLE error)
    #--build ${build_location}
    
        message("Result = ${result}")
        message("Out = ${output}")
        message("Error = ${error}")
    

    
    # Generate the cmake build directory at cmake time
    se_print(SE_SET_CMAKE_CMD_VARS)
    se_print(cm_create_build_dir_command)
    execute_process(COMMAND  ${cm_create_build_dir_command}
                    WORKING_DIRECTORY ${build_location}
                    OUTPUT_VARIABLE output
                    RESULT_VARIABLE result
                    ERROR_VARIABLE error)
    
    if(NOT error)
        message("Result = ${result}")
        message("Out = ${output}")
        message("Error = ${error}")
    endif(NOT error)
    
    # Custom target which builds the project at build time

    set(SE_ARCH_TARGET_NAMES    ${SE_ARCH_TARGET_NAMES}
                                ${libname}-${current_arch} PARENT_SCOPE)
    
    add_custom_target(  ${libname}-${current_arch} 
                        ALL
                        COMMAND ${cm_build_command}
                        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/jni/${libname}/${current_arch}
                        COMMENT "Calling cmake for ${libname}-${current_arch}. Command = ${cm_build_command}.")


endfunction(buildAndroidNDKCmake)

function(buildAndroidNDKLib libname)
    message("Build lib ${libname}")
    message("${CMAKE_MODULE_PATH}/AndroidLibAndroid.mk.in"
                    "${CMAKE_CURRENT_BINARY_DIR}/Android.mk")
    configure_file( "${CMAKE_MODULE_PATH}/AndroidLibAndroid.mk.in"
                    "${CMAKE_CURRENT_BINARY_DIR}/Android.mk")
endfunction(buildAndroidNDKLib)

macro(ndkBuildTarget)

set(NDK_ARGUMENTS   "")

if(${SE_DEBUG})
    message(debug)
    set(NDK_ARGUMENTS   "NDK_DEBUG=1")
endif(${SE_DEBUG})

add_custom_target(  NDK_BUILD ALL
                    COMMAND ${SE_ANDROID_NDK_BUILD_COMMAND} ${NDK_ARGUMENTS}
                    COMMENT "Calling ndk-build from ${SE_ANDROID_NDK_BUILD_COMMAND}"
                    WORKING_DIRECTORY   ${CMAKE_BINARY_DIR})
                    
add_dependencies(NDK_BUILD ${SE_ARCH_TARGET_NAMES})
                                     
endmacro(ndkBuildTarget)