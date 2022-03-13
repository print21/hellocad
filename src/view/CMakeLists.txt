
find_package(Qt5 COMPONENTS Core Gui Widgets)

add_definitions(-DVIEW_LIB -D_USE_MATH_DEFINES -DNOMINMAX -DINCLUDE_TEMPLATES)
add_definitions(-DACGDLL -DUSEACG)

include_directories(
    ${OPENMESH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/kernel
)

set(ACGVIEW_LIBS
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	acg
	core
	common
	data
)

set(ACGVIEW_SRCS
	ViewExport.h
	ViewAdmin.cpp
	ViewAdmin.h
	ViewDocument.cpp
	ViewDocument.h
	ACGViewer.cpp
	ACGViewer.h
	SceneCoordSys.cpp
	SceneCoordSys.h
	ViewFeatureBase.h
	ViewFeatureBase.cpp
	ViewPolyFeature.h
	ViewPolyFeature.cpp
)

add_library(view SHARED ${ACGVIEW_SRCS})
target_link_libraries(view ${ACGVIEW_LIBS})

set_target_properties(view PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set_target_properties(view PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set_target_properties(view PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

add_custom_command(TARGET view POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT5_BIN_DIR}/Qt5Gui$<$<CONFIG:Debug>:d>.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT5_BIN_DIR}/Qt5Widgets$<$<CONFIG:Debug>:d>.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT5_BIN_DIR}/Qt5OpenGL$<$<CONFIG:Debug>:d>.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT5_BIN_DIR}/Qt5Network$<$<CONFIG:Debug>:d>.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
)