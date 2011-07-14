    
    FIND_PACKAGE(OpenSSL REQUIRED)

    SET( BIN ../duplinker )

    SET( FILES main.c )

    SET( LIBS ${OPENSSL_LIBRARIES} )

    SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3" )

    ADD_EXECUTABLE( ${BIN} ${FILES} )
    TARGET_LINK_LIBRARIES( ${BIN} ${LIBS} )
   
