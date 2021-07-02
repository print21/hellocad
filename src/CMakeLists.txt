#HelloCAD a simple cad platform

add_subdirectory(kernel)

add_subdirectory(data)

add_subdirectory(view)

add_subdirectory(hellocad)

if(BUILD_TEST)
    add_subdirectory(Test)
endif(BUILD_TEST)
