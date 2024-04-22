#! /bin/make
# :vim: set noexpandtab:

CFLAGS = -lm `sdl2-config --cflags --libs`

3D_Jason: 3D_Jason.c
	$(CC) -o 3D_Jason 3D_Jason.c $(CFLAGS)
