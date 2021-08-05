#HelloCAD a simple cad platform

find_package(Qt5 COMPONENTS Core Gui Widgets)

set(MAIN_LIBS
	acg
    core
	common
	view
)

set(MAIN_SRCS
    main.cpp
	MainWindow.cpp
	MainWindow.h
)

set(MAIN_INC
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

set_target_properties(HelloCAD PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build/$<CONFIG>)
set_target_properties(HelloCAD PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib/$<CONFIG>)
set_target_properties(HelloCAD PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib/$<CONFIG>)

if(BUILD_VLD)
add_custom_command(TARGET HelloCADMain POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VLD_RUNTIME_DIR}/dbghelp.dll ${CMAKE_BINARY_DIR}/Build/$<CONFIG>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VLD_RUNTIME_DIR}/Microsoft.DTfW.DHL.manifest ${CMAKE_BINARY_DIR}/Build/$<CONFIG>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VLD_RUNTIME_DIR}/vld_x64.dll ${CMAKE_BINARY_DIR}/Build/$<CONFIG>
)
endif(BUILD_VLD)