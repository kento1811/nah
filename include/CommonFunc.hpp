#pragma once

#include<windows.h>
#include<string.h>
#include<iostream>
#include"../bin/SDL2/SDL.h"
#include"../bin/SDL2/SDL_image.h"
#include"../bin/SDL2/SDL_ttf.h"

#include<iostream>

#define GRAVITY_SPEED 3
#define MAX_FALL_SPEED 15
#define PLAYER_SPEED 7
#define BLANK_TILE 0

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640
#define COLOR_KEY_R 100
#define COLOR_KEY_G 60
#define COLOR_KEY_B 100
#define FRAME_RATE 68

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define JUMP_COOLDOWN 5

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;
static TTF_Font* Sans = TTF_OpenFont("save/open-sans/OpernSans-Regular.ttf", 12);

struct Input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
};

struct Map{
    int startX;
    int startY;

    int maxX;
    int maxY;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* fileName;

};

class font{
    public:
    ~font();
    void loadFont(SDL_Renderer* renderer,std::string path,int size,SDL_Color color);
    void setMess(const char* message,SDL_Renderer* renderer);
    void setRect(SDL_Rect rect);
    void render(SDL_Renderer* renderer);
    private:
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect rectMess;
};

namespace storage{
    extern int score;

}