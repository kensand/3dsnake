all: 3dsnake

3dsnake: 3dsnake.o LoadShaders.o ObjectLoader.o gl3w.o
	g++ 3dsnake.o LoadShaders.o ObjectLoader.o gl3w.o -o 3dsnake -ldl -lglfw -lGL -lglut -lGLEW -lGLU

3dsnake.o: 3dsnake.cpp
	g++ 3dsnake.cpp -c

LoadShaders.o: LoadShaders.cpp
	g++ LoadShaders.cpp -c

ObjectLoader.o: ObjectLoader.cpp
	g++ ObjectLoader.cpp -c

gl3w.o: gl3w.c gl3w.h
	g++ gl3w.c gl3w.h -c

clean:
	rm -rf *.o *.gch 3dsnake
