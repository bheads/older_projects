CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

    Find_Package(SFML REQUIRED COMPONENTS Graphics Windows )
    INCLUDE_DIRECTORIES( ${SFML_INCLUDE_DIR} )

    message( STATUS ${SFML_INCLUDE_DIR} )
    message( STATUS ${SFML_LIBRARY} )

    add_executable( test test.cpp )
    target_link_libraries( test ${SFML_LIBRARY} )



