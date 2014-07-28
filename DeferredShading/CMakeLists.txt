se_project(OpenGLTest)

#
#   First the lib
#

set(OPENGL_LIB_SOURCE   src/application.cpp
                        src/timer.cpp
                        src/render/renderer.cpp
                        src/render/gbuffer.cpp
                        src/render/shader.cpp
                        src/render/material.cpp
                        src/render/object.cpp
                        src/render/camera.cpp
                        src/render/directionallight.cpp
                        src/render/primitives/cube.cpp
                        src/render/primitives/quad.cpp
                        src/animation/manager.cpp
                        src/animation/controller.cpp
                        src/assets/loaderdesktop.cpp
                        src/assets/manager.cpp)

set(OPENGL_LIB_HEADERS  src/application.h
                        src/logging.h
                        src/plattformopengl.h
                        src/timer.h
                        src/render/renderer.h
                        src/render/gbuffer.h
                        src/render/primitives/primitive.h
                        src/render/primitives/quad.h
                        src/render/primitives/cube.h
                        src/render/shader.h
                        src/render/material.h
                        src/render/object.h
                        src/render/camera.h
                        src/render/directionallight.h
                        src/render/light.h
                        src/animation/manager.h
                        src/animation/controller.h
                        src/assets/loader.h
                        src/assets/loaderdesktop.h
                        src/assets/manager.h)
                        
set(LIB_TYPE    "")

find_package(GLM REQUIRED)

find_package(EasyLogging REQUIRED)

set(PLATFORM_INCLUDES   "")
set(PLATFORM_LIBS   "")

set(OPENGL_SHADER_SRC "")

if(WIN32)
    # ToDo: Also for unix and osx.
    set(OPENGL_LIB_SOURCE   ${OPENGL_LIB_SOURCE}
                            src/applicationdesktop.cpp)
    set(OPENGL_LIB_HEADERS  ${OPENGL_LIB_HEADERS}
                            src/applicationdesktop.h)
    
    find_package(SDL REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    set(PLATFORM_INCLUDES    ${SDL_INCLUDE_DIRS}
                            ${GLEW_INCLUDE_DIRS}
                            ${OPENGL_INCLUDE_DIR})
    
    set(PLATFORM_LIBS   ${SDL_LIBRARIES}
                        ${GLEW_LIBRARIES}
                        ${OPENGL_gl_LIBRARY})
                        
    set(OPENGL_SHADER_SRC   "${CMAKE_SOURCE_DIR}/assets/OpenGL4/directionallight.frag"
                            "${CMAKE_SOURCE_DIR}/assets/OpenGL4/directionallight.vert"
                            "${CMAKE_SOURCE_DIR}/assets/OpenGL4/geometry.frag"
                            "${CMAKE_SOURCE_DIR}/assets/OpenGL4/geometry.vert")
                        
endif(WIN32)

if(ANDROID)

    find_package(NativeAppGlue REQUIRED)

    set(OPENGL_LIB_SOURCE   ${OPENGL_LIB_SOURCE}
                            src/mainandroid.cpp
                            src/applicationandroid.cpp
                            src/assets/loaderandroid.cpp)
                            
    set(OPENGL_LIB_HEADERS  ${OPENGL_LIB_HEADERS}
                            src/applicationandroid.h
                            src/assets/loaderandroid.h)
                            
    set(LIB_TYPE    "SHARED")
    
    #se_print(NATIVE_APP_GLUE_INCLUDE_DIRS)
    
    set(PLATFORM_INCLUDES   ${PLATFORM_INCLUDES}
                            ${NATIVE_APP_GLUE_INCLUDE_DIRS})

    set(PLATFORM_LIBS       ${NATIVE_APP_GLUE_LIBRARIES}
                            -lGLESv3 
                            -lEGL 
                            -landroid 
                            -llog)
endif(ANDROID)

se_add_library(core  ${LIB_TYPE}    ${OPENGL_LIB_SOURCE}
                                    ${OPENGL_LIB_HEADERS}
                                    ${OPENGL_SHADER_SRC})

se_target_link_libraries(core  ${PLATFORM_LIBS})

#
#   Now the main application
#

if(WIN32)

    # ToDo: Also for unix and osx
    #       until i integrate Breakpad ;-)

    set(OPENGL_APP_SOURCE   src/maindesktop.cpp)

    se_add_executable(OpenGLApp   ${OPENGL_APP_SOURCE})

    se_target_link_libraries(OpenGLApp    core)

    se_copy_files(  ${OPENGL_SHADER_SRC})

    # ToDo: I want a function for that
#    add_custom_target(  OpenGLAppFiles ALL
#                        COMMAND ${COPY_IF_DIFFERENT} "${CMAKE_CURRENT_SOURCE_DIR}/src/directionallight.frag" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/"
#                        COMMAND ${COPY_IF_DIFFERENT} "${CMAKE_CURRENT_SOURCE_DIR}/src/directionallight.vert" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/"
#                        COMMAND ${COPY_IF_DIFFERENT} "${CMAKE_CURRENT_SOURCE_DIR}/src/geometry.frag" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/"
#                        COMMAND ${COPY_IF_DIFFERENT} "${CMAKE_CURRENT_SOURCE_DIR}/src/geometry.vert" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/"
#                        COMMENT "File Command")

endif(WIN32)
                                   
#
#   Add the include directories
#

include_directories(    src
                        ${PLATFORM_INCLUDES}
                        ${GLM_INCLUDE_DIRS}
                        ${EASYLOGGING_INCLUDE_DIRS})
