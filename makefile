INCS=`pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
STDC=-std=c++11
all: main
main: main.o scene.o file_inspection.o game.o
	g++ $(STDC) -Wall main.o scene.o file_inspection.o game.o -o main $(INCS)
main.o: main.cpp
	g++ $(STDC) -c main.cpp -o main.o
scene.o: scene.cpp
	g++ $(STDC) -c scene.cpp -o scene.o
file_inspection.o: file_inspection.cpp
	g++ $(STDC) -c file_inspection.cpp -o file_inspection.o
game.o: game.cpp
	g++ $(STDC) -c game.cpp -o game.o
clean:
	rm *.o main
