# Install script for directory: C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Main_Project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2023.3.4/bin/mingw/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.4.0-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/cmake-build-debug/Dependencies/assimp/lib/libassimpd.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/anim.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/aabb.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/ai_assert.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/camera.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/color4.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/color4.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/cmake-build-debug/Dependencies/assimp-master/code/../include/assimp/config.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/ColladaMetaData.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/commonMetaData.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/defs.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/cfileio.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/light.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/material.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/material.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/matrix3x3.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/matrix3x3.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/matrix4x4.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/matrix4x4.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/mesh.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/ObjMaterial.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/pbrmaterial.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/GltfMaterial.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/postprocess.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/quaternion.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/quaternion.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/scene.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/metadata.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/texture.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/types.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/vector2.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/vector2.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/vector3.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/vector3.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/version.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/cimport.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/AssertHandler.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/importerdesc.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Importer.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/DefaultLogger.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/ProgressHandler.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/IOStream.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/IOSystem.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Logger.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/LogStream.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/NullLogger.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/cexport.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Exporter.hpp"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/DefaultIOStream.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/DefaultIOSystem.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/ZipArchiveIOSystem.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/SceneCombiner.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/fast_atof.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/qnan.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/BaseImporter.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Hash.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/MemoryIOWrapper.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/ParsingUtils.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/StreamReader.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/StreamWriter.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/StringComparison.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/StringUtils.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/SGSpatialSort.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/GenericProperty.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/SpatialSort.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/SkeletonMeshBuilder.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/SmallVector.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/SmoothingGroups.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/SmoothingGroups.inl"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/StandardShapes.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/RemoveComments.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Subdivision.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Vertex.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/LineSplitter.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/TinyFormatter.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Profiler.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/LogAux.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Bitmap.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/XMLTools.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/IOStreamBuffer.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/CreateAnimMesh.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/XmlParser.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/BlobIOSystem.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/MathFunctions.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Exceptional.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/ByteSwapper.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Compiler/poppack1.h"
    "C:/Users/Bobal/Nextcloud/Documents/University/Year 2/Coursework/Graphics/Main_Project/Dependencies/assimp-master/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

