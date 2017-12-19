makeme: main.c position/position.c sdl_helper/sdl_helper.c position/position.h sdl_helper/sdl_helper.h
	gcc -o main main.c position/position.c sdl_helper/sdl_helper.c -lSDL2_image -g `sdl2-config --cflags --libs` -pthread -lm

