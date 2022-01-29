#HelloCAD a simple cad platform

find_package(Qt5 COMPONENTS Core)

add_definitions(-DDATA_LIB)

include_directories(
    ${CMAKE_SOURCE_DIR}/Src
    ${CMAKE_SOURCE_DIR}/Src/kernel
)

set(DATA_LIBS
	Qt5::Core
	core
	common
)

set(DATA_SRCS
    DataExport.h
    DataAdmin.h
    DataAdmin.cpp
    DataDocument.h
    DataDocument.cpp
    DataFeatureBase.h
    DataFeatureBase.cpp
    DataPolyMesh.cpp
    DataPolyMesh.h
)

add_library(data SHARED ${DATA_SRCS})
target_link_libraries(data ${DATA_LIBS})

set_target_properties(data PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set_target_properties(data PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set_target_properties(data PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)

