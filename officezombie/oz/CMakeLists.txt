CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

    Find_Package(SFML REQUIRED COMPONENTS Graphics Windows )
    INCLUDE_DIRECTORIES( ${SFML_INCLUDE_DIR} )

    set( SOURCE 
            filefunc.cpp
            strfunc.cpp
            inireader.cpp
            error.cpp
            engine.cpp
            input.cpp
            pack.cpp        
            mod_resource.cpp
            trophies.cpp
            images.cpp
            sfx.cpp
	    gfx.cpp
            animation.cpp
            gamedata.cpp
            map.cpp
            movable.cpp
            npc.cpp
            box.cpp
            player.cpp
            puzzle.cpp
	    evemt.cpp
            rendermap.cpp
            rand.cpp

            splash_state.cpp
            state_profile.cpp
            state_mainMenu.cpp
            state_game.cpp
            state_trophies.cpp
	    state_levelup.cpp
            state_puzzle.cpp
	    state_event.cpp

            oz.cpp )

    if( UNIX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPOSIX" )
    endif( UNIX )

    if( DEFINED EBUG )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEBUG" )
        if( UNIX )
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb" )
        endif( UNIX )
    endif( DEFINED EBUG )

    if( DEFINED OPT )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" )
    endif( DEFINED OPT )


#add_executable( ../officezombie  ${SOURCE} )
#target_link_libraries( ../officezombie ${SFML_LIBRARY} )
add_executable( officezombie WIN32 MACOSX_BUNDLE  ${SOURCE} )
target_link_libraries( officezombie ${SFML_LIBRARY} )

