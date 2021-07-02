#HelloCAD a simple cad platform

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(HelloCAD)

cmake_policy(SET CMP0100 NEW)

# add our macro directory to cmake search path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Qt5 COMPONENTS Core)

# Enable automoc, autouic and auto rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(Qt5Core_FOUND)
  set(QT5_FOUND TRUE)
  set(QT5_BIN_DIR ${_qt5_install_prefix}/../../bin)
endif(Qt5Core_FOUND)

set(OPENMESH_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/../LibPack/OpenMesh" CACHE PATH "Directory of OpenMesh")
find_package (OpenMesh REQUIRED)

option(BUILD_TEST "Build test." OFF)
if(BUILD_TEST)
  set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/../LibPack/GTest" CACHE PATH "Directory of google test.")
  find_package(GTest REQUIRED)
  set(GTEST_BIN_DIR ${GTEST_INCLUDE_DIR}/../bin)
endif(BUILD_TEST)

option(BUILD_VLD "Visual leak detect." OFF)
if(BUILD_VLD)
  set(VLD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../LibPack/VLD/include" CACHE PATH "Directory of vld include.")
  set(VLD_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/../LibPack/VLD/lib" CACHE PATH "Directory of vld library.")
  set(VLD_RUNTIME_DIR "${CMAKE_SOURCE_DIR}/../LibPack/VLD/bin" CACHE PATH "Directory of vld runtime.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)