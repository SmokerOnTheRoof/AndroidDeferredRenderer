#pragma once

#ifdef WIN32

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/GL.h>

#endif // WIN32

#ifdef ANDROID

#include <GLES3/GL3.h>
#include <GLES3/gl3ext.h>

#endif // ANDROID