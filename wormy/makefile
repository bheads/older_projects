

CC=dmd
LIBS= -L-lDerelictSDL -L-lDerelictSDLImage -L-lDerelictUtil -L-lDerelictSDLttf -L-ldl -L-lDerelictSDLmixer
BIN=wormy
FLAGS=-debug -gc
OBJ= \
     worm.o \
     menu.o \
     game.o \
     pause.o \
     death.o \
     graphics.o \
     input.o \
     fps.o \
     state.o \
     statemanager.o \
     core.o \
     sdl.o \
     sound.o \
     window.o \
	 main.o


all: ${OBJ}
	${CC} ${OBJ} -of${BIN} ${FLAGS} ${LIBS} 


%.o: src/%.d
	${CC} -c $< ${FLAGS}

clean:
	rm -rf *.o ${BIN}

