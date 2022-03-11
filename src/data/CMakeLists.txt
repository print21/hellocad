#HelloCAD a simple cad platform

find_package(Qt5 COMPONENTS Core)

add_definitions(-DDATA_LIB)

include_directories(
    ${OPENMESH_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Src
    ${CMAKE_SOURCE_DIR}/Src/kernel
)

set(DATA_LIBS
    Qt5::Core
    core
    common
)

set(FEATURE_SRCS
    DataCubeFeature.cpp
    DataCubeFeature.h
)

source_group("Features" FILES ${FEATURE_SRCS})

set(DATA_SRCS
    ${FEATURE_SRCS}
    DataExport.h
    DataAdmin.h
    DataAdmin.cpp
    DataDocument.h
    DataDocument.cpp
    DataFeatureBase.h
    DataFeatureBase.cpp
)

add_library(data SHARED ${DATA_SRCS})
target_link_libraries(data ${DATA_LIBS})

set_target_properties(data PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set_target_properties(data PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set_target_properties(data PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)

