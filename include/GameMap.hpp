#pragma once
#include"CommonFunc.hpp"
#include"BaseObject.hpp"
#include"string"

#define MAX_TILE 20

class GameMap{
    public:
    GameMap(){;};
    ~GameMap(){;};

    void LoadMap(char* fileName);
    void LoadTile(SDL_Renderer* renderer);
    void DrawMap(SDL_Renderer* renderer);
    private:
    Map gameMap;
    BaseObject tileMat[MAX_TILE];
};