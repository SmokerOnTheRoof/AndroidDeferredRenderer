cmake_minimum_required(VERSION 2.8)

project(android_native_app_glue)

add_Library(android_native_app_glue STATIC
                                    android_native_app_glue.c
                                    android_native_app_glue.h)

# ToDo: Workaround to force cmake to invoke the c++ compiler, because i havn't tested the
#       c compiler yet.
SET_SOURCE_FILES_PROPERTIES(android_native_app_glue.c PROPERTIES LANGUAGE CXX )