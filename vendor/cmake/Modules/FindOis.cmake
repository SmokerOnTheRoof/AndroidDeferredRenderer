# - Try to find OIS
# Once done this will define
#  OIS_FOUND - System has OIS
#  OIS_INCLUDE_DIRS - The OIS include directories
#  OIS_LIBRARIES - The libraries needed to use OIS
#  OIS_DEFINITIONS - Compiler switches required for using OIS
#  OIS_DYNAMIC_LIBS - Dynamic libraries for OIS

set(OIS_INCLUDE_DIRS    "${SE_THIRD_PARTY_DIR}/OIS/include")


if(WIN32)

    if(${MSVC11})
    
        set(OIS_LIBRARIES   debug       "${SE_THIRD_PARTY_DIR}/OIS/lib/vc11/Debug/OIS_d.lib"
                            optimized   "${SE_THIRD_PARTY_DIR}/OIS/lib/vc11/Release/OIS.lib")
    
        if(${SE_DEBUG})                
            set(OIS_DYNAMIC_LIBS    "${SE_THIRD_PARTY_DIR}/OIS/bin/vc11/Debug/OIS_d.dll")
        else()
            set(OIS_DYNAMIC_LIBS    "${SE_THIRD_PARTY_DIR}/OIS/bin/vc11/Release/OIS.dll")
        endif(${SE_DEBUG})
                
    endif(${MSVC11})
    
    if(${MSVC10})
    
        set(OIS_LIBRARIES   debug       "${SE_THIRD_PARTY_DIR}/OIS/lib/vc10/Debug/OIS_d.lib"
                            optimized   "${SE_THIRD_PARTY_DIR}/OIS/lib/vc10/Release/OIS.lib")
    
        if(${SE_DEBUG})                
            set(OIS_DYNAMIC_LIBS    "${SE_THIRD_PARTY_DIR}/OIS/bin/vc10/Debug/OIS_d.dll")
        else()
            set(OIS_DYNAMIC_LIBS    "${SE_THIRD_PARTY_DIR}/OIS/bin/vc10/Release/OIS.dll")
        endif(${SE_DEBUG})
                            
    endif(${MSVC10})

endif(WIN32)
