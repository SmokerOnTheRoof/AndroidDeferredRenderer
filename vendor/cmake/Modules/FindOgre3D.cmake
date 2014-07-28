# - Try to find Ogre3D
# Once done this will define
#  OGRE3D_FOUND - System has Ogre3D
#  OGRE3D_INCLUDE_DIRS - The Ogre3D include directories
#  OGRE3D_LIBRARIES - The libraries needed to use Ogre3D
#  OGRE3D_DEFINITIONS - Compiler switches required for using Ogre3D
#  OGRE3D_DYNAMIC_LIBS - Dynamic libraries for Ogre3D
#  OGRE3D_CG - Path to the cg lib # ToDo: find out what that is
#  OGRE_GAME_PLUGINS - The Ogre plugins # ToDo: Only set plugins which are actually used

set(OGRE3D_INCLUDE_DIRS "${SE_THIRD_PARTY_DIR}/Ogre3D/include/OGRE"
                        "${SE_THIRD_PARTY_DIR}/Ogre3D/include/OGRE/Overlay") # ToDo: is this really necessary?


if(WIN32)

    if(${MSVC11})
    
        set(OGRE3D_LIBRARIES    debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Debug/OgreMain_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Debug/OgreOverlay_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Debug/OgrePaging_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Debug/OgreProperty_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Debug/OgreRTShaderSystem_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Debug/OgreTerrain_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Debug/OgreVolume_d.lib"
                                
                                optimized "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Release/OgreMain.lib"
                                optimized "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Release/OgreOverlay.lib"
                                optimized "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Release/OgrePaging.lib"
                                optimized "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Release/OgreProperty.lib"
                                optimized "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Release/OgreRTShaderSystem.lib"
                                optimized "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Release/OgreTerrain.lib"
                                optimized "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc11/Release/OgreVolume.lib")
    
        if(${SE_DEBUG})                
            set(OGRE3D_DYNAMIC_LIBS "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/OgreMain_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/OgreMain_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/OgreOverlay_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/OgreOverlay_d.pdb")
                                    
            set (OGRE3D_CG          "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/cg.dll")
            
            set (OGRE_GAME_PLUGINS  "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_BSPSceneManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_BSPSceneManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_CgProgramManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_CgProgramManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_OctreeSceneManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_OctreeSceneManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_OctreeZone_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_OctreeZone_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_ParticleFX_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_ParticleFX_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_PCZSceneManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_PCZSceneManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/RenderSystem_GL_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/RenderSystem_GL_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_CgProgramManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Debug/Plugin_CgProgramManager_d.pdb")

        else()
            set(OGRE3D_DYNAMIC_LIBS "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/OgreMain.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/OgreOverlay.dll")
                                    
            set (OGRE3D_CG          "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/cg.dll")

            set (OGRE_GAME_PLUGINS  "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_BSPSceneManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_BSPSceneManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_CgProgramManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_CgProgramManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_OctreeSceneManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_OctreeSceneManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_OctreeZone.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_OctreeZone.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_ParticleFX.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_ParticleFX.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_PCZSceneManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_PCZSceneManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/RenderSystem_GL.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/RenderSystem_GL.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_CgProgramManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc11/Release/Plugin_CgProgramManager.pdb"
                                    )
                                    
        endif(${SE_DEBUG})
               
    endif(${MSVC11})

    if(${MSVC10})
    
        set(OGRE3D_LIBRARIES    debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Debug/OgreMain_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Debug/OgreOverlay_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Debug/OgrePaging_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Debug/OgreProperty_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Debug/OgreRTShaderSystem_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Debug/OgreTerrain_d.lib"
                                debug       "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Debug/OgreVolume_d.lib"
                                
                                optimized   "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Release/OgreMain.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Release/OgreOverlay.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Release/OgrePaging.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Release/OgreProperty.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Release/OgreRTShaderSystem.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Release/OgreTerrain.lib"
                                optimized   "${SE_THIRD_PARTY_DIR}/Ogre3D/lib/vc10/Release/OgreVolume.lib")
    
        if(${SE_DEBUG})                
            set(OGRE3D_DYNAMIC_LIBS "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/OgreMain_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/OgreMain_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/OgreOverlay_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/OgreOverlay_d.pdb")
                                    
            set (OGRE3D_CG          "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/cg.dll")
            
            set (OGRE_GAME_PLUGINS  "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_BSPSceneManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_BSPSceneManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_CgProgramManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_CgProgramManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_OctreeSceneManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_OctreeSceneManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_OctreeZone_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_OctreeZone_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_ParticleFX_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_ParticleFX_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_PCZSceneManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_PCZSceneManager_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/RenderSystem_GL_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/RenderSystem_GL_d.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_CgProgramManager_d.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Debug/Plugin_CgProgramManager_d.pdb")
            
        else()
            set(OGRE3D_DYNAMIC_LIBS "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/OgreMain.dll"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/OgreOverlay.dll")
                                    
            set (OGRE3D_CG          "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/cg.dll")
            
            set (OGRE_GAME_PLUGINS  "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_BSPSceneManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_BSPSceneManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_CgProgramManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_CgProgramManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_OctreeSceneManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_OctreeSceneManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_OctreeZone.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_OctreeZone.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_ParticleFX.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_ParticleFX.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_PCZSceneManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_PCZSceneManager.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/RenderSystem_GL.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/RenderSystem_GL.pdb"
                                    "${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_CgProgramManager.dll"
                                    #"${SE_THIRD_PARTY_DIR}/Ogre3D/bin/vc10/Release/Plugin_CgProgramManager.pdb"
                                    )
            
        endif(${SE_DEBUG})
                            
    endif(${MSVC10})
                        
endif(WIN32)

find_package(Boost  REQUIRED)
find_package(Ois    REQUIRED)

set(OGRE3D_LIBRARIES    ${OGRE3D_LIBRARIES}
                        ${OIS_LIBRARIES}
                        ${BOOST_LIBRARIES})

set(OGRE3D_INCLUDE_DIRS ${OGRE3D_INCLUDE_DIRS}
                        ${OIS_INCLUDE_DIRS}
                        ${BOOST_INCLUDE_DIRS})

set(OGRE3D_DYNAMIC_LIBS ${OGRE3D_DYNAMIC_LIBS}
                        ${OIS_DYNAMIC_LIBS}
                        ${OGRE3D_CG})