#HelloCAD a simple cad platform

find_package(Qt5 COMPONENTS Core Gui Widgets)

set(MAIN_LIBS
	acg
	core
	common
	data
	view
)

set(WINDOW_SRCS
	TreeView.cpp
	TreeView.h
	TreeItems.cpp
	TreeItems.h
	AttributeView.cpp
	AttributeView.h
)

source_group("window" FILES ${WINDOW_SRCS})

set(MAIN_SRCS
	${WINDOW_SRCS}
	main.cpp
	MainWindow.cpp
	MainWindow.h
)

set(MAIN_INC
	${OPENMESH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/Src
	${CMAKE_SOURCE_DIR}/Src/kernel
)

add_definitions(-D_USE_MATH_DEFINES)

if(BUILD_VLD)
	list(APPEND MAIN_INC ${VLD_INCLUDE_DIR})
	list(APPEND MAIN_LIBS ${VLD_LIBRARY_DIR}/vld_x64.lib ${VLD_LIBRARY_DIR}/vld.lib)
	add_definitions(-DUSE_VLD)
endif(BUILD_VLD)

include_directories(
	${MAIN_INC}
)

add_executable(HelloCAD ${MAIN_SRCS})
target_link_libraries(HelloCAD ${MAIN_LIBS})

set_target_properties(HelloCAD PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set_target_properties(HelloCAD PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set_target_properties(HelloCAD PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)

if(BUILD_VLD)
add_custom_command(TARGET HelloCADMain POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VLD_RUNTIME_DIR}/dbghelp.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VLD_RUNTIME_DIR}/Microsoft.DTfW.DHL.manifest ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VLD_RUNTIME_DIR}/vld_x64.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
)
endif(BUILD_VLD)