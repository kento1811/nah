#pragma once

#include<windows.h>
#include"string"
#include"../bin/SDL2/SDL.h"
#include"../bin/SDL2/SDL_image.h"
#include<iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640
#define COLOR_KEY_R 100
#define COLOR_KEY_G 60
#define COLOR_KEY_B 100

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;

struct Map{
    int startX;
    int startY;

    int maxX;
    int maxY;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* fileName;

};

