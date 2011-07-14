CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

    set( SOURCE 
            error.cpp
            hash.cpp
            filefunc.cpp
            strfunc.cpp
            config.cpp
            map.cpp
	        packer.cpp )

    if( UNIX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPOSIX" )
    endif( UNIX )

    if( APPLE )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOSX" )
    endif( APPLE )

    if( DEFINED EBUG )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEBUG" )
    endif( DEFINED EBUG )

    add_executable( ../pkr ${SOURCE} )

