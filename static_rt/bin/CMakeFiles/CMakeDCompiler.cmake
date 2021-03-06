SET(CMAKE_D_COMPILER "/usr/bin/dmd")
SET(CMAKE_D_COMPILER_ARG1 "")
SET(CMAKE_D_COMPILER_ID "")
SET(CMAKE_D_PLATFORM_ID "")

SET(CMAKE_AR "/usr/bin/ar")
SET(CMAKE_RANLIB "/usr/bin/ranlib")
SET(CMAKE_LINKER "/usr/bin/ld")
SET(CMAKE_COMPILER_IS_GDC )
SET(CMAKE_COMPILER_IS_DMD )
SET(CMAKE_D_COMPILER_LOADED 1)
SET(CMAKE_COMPILER_IS_MINGW )
SET(CMAKE_COMPILER_IS_CYGWIN )
IF(CMAKE_COMPILER_IS_CYGWIN)
  SET(CYGWIN 1)
  SET(UNIX 1)
ENDIF(CMAKE_COMPILER_IS_CYGWIN)

SET(CMAKE_D_COMPILER_ENV_VAR "DC")

IF(CMAKE_COMPILER_IS_MINGW)
  SET(MINGW 1)
ENDIF(CMAKE_COMPILER_IS_MINGW)
SET(CMAKE_D_SOURCE_FILE_EXTENSIONS d)
SET(CMAKE_D_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
# Prefer to use D's linker.
# The D value 40 beats CXX value of 30 and C value of 10
SET(CMAKE_D_LINKER_PREFERENCE 40 )
SET(CMAKE_D_LINKER_PREFERENCE_PROPOGATES 1 )
# Save compiler ABI information.
SET(CMAKE_D_SIZEOF_DATA_PTR "")
SET(CMAKE_D_COMPILER_ABI "")

IF(CMAKE_D_SIZEOF_DATA_PTR)
  SET(CMAKE_SIZEOF_VOID_P "${CMAKE_D_SIZEOF_DATA_PTR}")
ENDIF(CMAKE_D_SIZEOF_DATA_PTR)

IF(CMAKE_D_COMPILER_ABI)
  SET(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_D_COMPILER_ABI}")
ENDIF(CMAKE_D_COMPILER_ABI)

SET(CMAKE_D_HAS_ISYSROOT "")


SET(CMAKE_D_IMPLICIT_LINK_LIBRARIES "")
SET(CMAKE_D_IMPLICIT_LINK_DIRECTORIES "")
