include(AndroidBuild)

macro (setup_version_var variableName)
    if (DEFINED ${variableName})
        string (REGEX MATCHALL "[0-9]+" _versionComponents "${${variableName}}")
        list (LENGTH _versionComponents _len)
        if (${_len} GREATER 0)
            list(GET _versionComponents 0 ${variableName}_MAJOR)
        endif()
        if (${_len} GREATER 1)
            list(GET _versionComponents 1 ${variableName}_MINOR)
        endif()
        if (${_len} GREATER 2)
            list(GET _versionComponents 2 ${variableName}_PATCH)
        endif()
        if (${_len} GREATER 3)
            list(GET _versionComponents 3 ${variableName}_TWEAK)
        endif()
        set (${variableName}_COUNT ${_len})
    else()
        set (${variableName}_COUNT 0)
        set (${variableName} "")
    endif()
endmacro()

macro(se_print  varName)
    message(STATUS   "${varName} = ${${varName}}")
endmacro(se_print   varName)

macro(init_vars)

    se_print(CMAKE_CXX_COMPILER)
    se_print(CMAKE_C_COMPILER)
    se_print(CMAKE_SYSTEM)
    se_print(CMAKE_CXX_COMPILER_NAME)
    se_print(CMAKE_SYSTEM_NAME)
    se_print(CMAKE_HOST_SYSTEM_NAME)
    
    se_print(CMAKE_CXX_COMPILER_VERSION)
    set(SE_COMPILER_VERSION ${CMAKE_CXX_COMPILER_VERSION})
    setup_version_var(SE_COMPILER_VERSION)
    se_print(SE_COMPILER_VERSION)
    
    se_print(CMAKE_CXX_FLAGS)
    se_print(SE_COMPILER_VERSION_MAJOR)
    se_print(SE_COMPILER_VERSION_MINOR)
    se_print(SE_COMPILER_VERSION_PATCH)
    se_print(SE_COMPILER_VERSION_TWEAK)
    se_print(CMAKE_CONFIGURATION_TYPES)
    #set(SE_BUILD_TYPE  CACHE)
    
    if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(SE_DEBUG ON)
        set(SE_INSTALL_CONFIGURATION    "Debug")
    else()
        set(SE_DEBUG OFF)
        set(SE_INSTALL_CONFIGURATION    "Release")
    endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    se_print(CMAKE_BUILD_TYPE)
    se_print(SE_INSTALL_CONFIGURATION)
    
    init_SE_ANDROID_BUILD_vars()
    
endmacro(init_vars)

macro(se_project projectName)
    project(${projectName})
    message(STATUS)
    message(STATUS  "Configuring project ${projectName}")
    message(STATUS)
endmacro(se_project)

macro(se_copy_files)

    #ToDo: This works but sucks.
    #       Maybe it might be better to just copy the whole asset directory as a special target.
    #       Might be interesting to configure cross-platform assets.

    set(COPY_IF_DIFFERENT ${CMAKE_COMMAND} -E copy)

    set(CopyCommand "")
    
    set(FileList "")
    
    FOREACH(SRC_FILE ${ARGN})
        set(CopyCommand ${CopyCommand} COMMAND ${COPY_IF_DIFFERENT} ${SRC_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/")
        set(FileList ${FileList} ${SRC_FILE})
    ENDFOREACH(SRC_FILE ${ARGN})
    message(Awesome copy command = ${CopyCommand})
    add_custom_target(OpenGLAppFiles ALL
                       ${CopyCommand}
                       COMMENT "Copying ${FileList} to ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/")
endmacro(se_copy_files target destination)

macro(se_add_executable)

    if(NOT SE_ANDROID_BUILD)
        add_executable(${ARGN})
    elseif(SE_ANDROID_BUILD)

    endif(NOT SE_ANDROID_BUILD)

endmacro(se_add_executable)

macro(se_target_link_libraries)

    if(NOT SE_ANDROID_BUILD)
        target_link_libraries(${ARGN})
    elseif(SE_ANDROID_BUILD)
    
    endif(NOT SE_ANDROID_BUILD)

endmacro(se_target_link_libraries)

macro(se_add_library)

    if(NOT SE_ANDROID_BUILD)
        add_library(${ARGN})
        buildAndroidNDKLib(${ARGV0})
    elseif(SE_ANDROID_BUILD)
# ToDo: check if it is a shared lib
    endif(NOT SE_ANDROID_BUILD)

endmacro(se_add_library)

