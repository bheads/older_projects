cmake_minimum_required(VERSION 2.8)
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules )
set( CMAKE_D_USE_PHOBOS True )

PROJECT( raytracer D)
    ADD_SUBDIRECTORY( src )

