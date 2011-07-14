INCLUDE_DIRECTORIES ( ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR})

ADD_EXECUTABLE( ../rt 
        main.d

        image.d
        vector.d
        matrix.d
        ray.d
        onb.d
        shape.d
        raytrace.d
        camera.d
        )

