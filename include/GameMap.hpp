#pragma once
#include"CommonFunc.hpp"
#include"BaseObject.hpp"
#include"enemyObject.hpp"
#include<vector>
#include"string"

#define MAX_TILE 20

class GameMap{
    public:
    GameMap(){;};
    ~GameMap(){;};

    void LoadMap(char* fileName);
    void LoadTile(SDL_Renderer* renderer);
    void DrawMap(SDL_Renderer* renderer);
    Map getMap() const {return gameMap;};
    std::vector<enemyObject*> getEnemyList(){return enemyList;}
    void SetMap(Map&  mapData){gameMap = mapData;};
    private:
    Map gameMap;
    BaseObject tileMat[MAX_TILE];
    std::vector<enemyObject* > enemyList;
};