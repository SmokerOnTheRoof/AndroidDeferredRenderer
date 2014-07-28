# - Try to find Boost
# Once done this will define
#  BOOST_FOUND - System has Boost
#  BOOST_INCLUDE_DIRS - The Boost include directories
#  BOOST_LIBRARIES - The libraries needed to use Boost
#  BOOST_DEFINITIONS - Compiler switches required for using Boost

SET(BOOST_INCLUDE_DIRS  "${SE_THIRD_PARTY_DIR}/boost/include")

if(WIN32)

    if(${MSVC11})
    
        set(BOOST_LIBRARIES debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Debug/libboost_chrono-vc110-mt-gd-1_53.lib"
                            debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Debug/libboost_date_time-vc110-mt-gd-1_53.lib"
                            debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Debug/libboost_system-vc110-mt-gd-1_53.lib"
                            debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Debug/libboost_thread-vc110-mt-gd-1_53.lib"
                                    
                            debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Release/libboost_chrono-vc110-mt-1_53.lib"
                            debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Release/libboost_date_time-vc110-mt-1_53.lib"
                            debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Release/libboost_system-vc110-mt-1_53.lib"
                            debug   "${SE_THIRD_PARTY_DIR}/boost/lib/vc11/Release/libboost_thread-vc110-mt-1_53.lib")
        
    endif(${MSVC11})
    
    if(${MSVC10})
    
        set(BOOST_LIBRARIES debug       "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_chrono-vc100-mt-gd-1_55.lib"
                            debug       "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_date_time-vc100-mt-gd-1_55.lib"
                            debug       "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_system-vc100-mt-gd-1_55.lib"
                            debug       "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_thread-vc100-mt-gd-1_55.lib"
                            debug       "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_filesystem-vc100-mt-gd-1_55.lib"
                            
                            optimized   "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_chrono-vc100-mt-1_55.lib"
                            optimized   "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_date_time-vc100-mt-1_55.lib"
                            optimized   "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_system-vc100-mt-1_55.lib"
                            optimized   "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_thread-vc100-mt-1_55.lib"
                            optimized   "${SE_THIRD_PARTY_DIR}/boost/lib/vc10/libboost_filesystem-vc100-mt-1_55.lib")   
    endif(${MSVC10})
    
endif(WIN32)