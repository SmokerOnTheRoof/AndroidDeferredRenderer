# - Try to find NativeAppGlue
# Once done this will define
#  NATIVE_APP_GLUE_FOUND - System has native app glue
#  NATIVE_APP_GLUE_INCLUDE_DIRS - The native app glue include directories
#  NATIVE_APP_GLUE_LIBRARIES - The libraries needed to use native app glue
#  NATIVE_APP_GLUE_DEFINITIONS - Compiler switches required for using native app glue

set(NATIVE_APP_GLUE_DIR "${SE_THIRD_PARTY_DIR}/google/android/native_app_glue")

set(NATIVE_APP_GLUE_INCLUDE_DIRS "${NATIVE_APP_GLUE_DIR}/src" CACHE PATH "Include directory for native app glue")

# ToDo: hard coded path
set(NATIVE_APP_GLUE_LIBRARIES   "${NATIVE_APP_GLUE_DIR}/bin/19/arm/libandroid_native_app_glue.a" CACHE FILEPATH "Native app glue lib")

