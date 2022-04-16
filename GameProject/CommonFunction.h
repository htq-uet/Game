#pragma once
#include <Windows.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* gwindow = NULL;
static SDL_Renderer* gscreen = NULL;
static SDL_Event event;

static Mix_Music* background_music;
static Mix_Chunk* sound[50];


const int ColorKeyRed = 167;
const int ColorKeyGreen = 175;
const int ColorKeyBlue = 180;

#define QUIT 2
#define TILE_SIZE 32
 
#define MAP_MAP_X 55
#define MAP_MAP_Y 30





typedef struct Input {
	int left;
	int right;
	int stayleft;
	int stayright;
	int jump;
};

typedef struct Map {
	int startx;
	int starty;

	int maxx;
	int maxy;

	int tile[MAP_MAP_Y][MAP_MAP_X];
	const char* mapfile;
}Map;
