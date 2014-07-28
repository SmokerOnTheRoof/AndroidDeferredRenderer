# - Try to find Bullet
# Once done this will define
#  BULLET_FOUND - System has Bullet
#  BULLET_INCLUDE_DIRS - The Bullet include directories
#  BULLET_LIBRARIES - The libraries needed to use Bullet
#  BULLET_DEFINITIONS - Compiler switches required for using Bullet
#  BULLET_DYNAMIC_LIBS - Dynamic libraries for Bullet

set(BULLET_INCLUDE_DIRS "${SE_THIRD_PARTY_DIR}/Bullet/include")

if(WIN32)

    if(MSVC10)
    
        set (BULLET_LIBRARIES   debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletCollision_Debug.lib" 
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletDynamics_Debug.lib"    
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletFileLoader_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletMultiThreaded_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletSoftBody_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletSoftBodySolvers_OpenCL_Mini_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletWorldImporter_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletXmlWorldImporter_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/ConvexDecomposition_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/GIMPACTUtils_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/HACD_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/LinearMath_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/MiniCL_Debug.lib"
                                
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletCollision.lib" 
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletDynamics.lib"    
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletFileLoader.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletMultiThreaded.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletSoftBody.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletSoftBodySolvers_OpenCL_Mini.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletWorldImporter.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/BulletXmlWorldImporter.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/ConvexDecomposition.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/GIMPACTUtils.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/HACD.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/LinearMath.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc10/MiniCL.lib")
                                
    endif(MSVC10)

    if(MSVC11)
    
        set (BULLET_LIBRARIES   debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletCollision_Debug.lib" 
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletDynamics_Debug.lib"    
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletFileLoader_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletMultiThreaded_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletSoftBody_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletSoftBodySolvers_OpenCL_Mini_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletWorldImporter_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletXmlWorldImporter_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/ConvexDecomposition_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/GIMPACTUtils_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/HACD_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/LinearMath_Debug.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/MiniCL_Debug.lib"
                                
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletCollision.lib" 
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletDynamics.lib"    
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletFileLoader.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletMultiThreaded.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletSoftBody.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletSoftBodySolvers_OpenCL_Mini.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletWorldImporter.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/BulletXmlWorldImporter.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/ConvexDecomposition.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/GIMPACTUtils.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/HACD.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/LinearMath.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Bullet/lib/vc11/MiniCL.lib")
    
    endif(MSVC11)

endif(WIN32)

