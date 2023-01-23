# Install script for directory: E:/cours/VSION/TP5/arUco/aruco-3.1.12

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Dev/Aruco3112")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES
    "E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/aruco-uninstalled.pc"
    "E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/aruco.pc"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aruco" TYPE FILE FILES "E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/arucoConfig.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/src/cmake_install.cmake")
  include("E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/utils_gl/cmake_install.cmake")
  include("E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/utils/cmake_install.cmake")
  include("E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/utils_markermap/cmake_install.cmake")
  include("E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/utils_calibration/cmake_install.cmake")
  include("E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/utils_dcf/cmake_install.cmake")
  include("E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/utils_fractal/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/cours/VSION/TP5/arUco/aruco-3.1.12/build/x64/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
