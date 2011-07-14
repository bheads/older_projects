

CC=dmd
LIBS= -L-lDerelictSDL -L-lDerelictSDLImage -L-lDerelictUtil -L-lDerelictSDLttf -L-ldl
BIN=nvzpf
FLAGS=-debug -gc
OBJ= state.o \
     statemainmenu.o \
     stategame.o \
     statepause.o \
     stategotstars.o \
     statemanager.o \
     statedead.o \
     statestageexit.o \
     camera.o \
     sdl.o \
     input.o \
     window.o \
     manager.o \
     graphics.o \
     graphicsmanager.o \
     gfx_id.o \
     gameobjects.o \
     gameworld.o \
     staticobject.o \
     dynamicobject.o \
     eventobject.o \
     aiobject.o \
     fps.o \
     ninja.o \
	 main.o


all: ${OBJ}
	${CC} ${OBJ} -of${BIN} ${FLAGS} ${LIBS} 


%.o: src/%.d
	${CC} -c $< ${FLAGS}

clean:
	rm -rf *.o ${BIN}

