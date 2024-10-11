#define SDL_MAIN_HANDLED

#include"include/GameMap.hpp"

void GameMap::LoadMap(char* FileName){
    FILE* fp =NULL;
    fopen_s(&fp,FileName,"rb");
    if(fp == NULL){
        return;
    }
    
    gameMap.maxX = 0;
    gameMap.maxY =0;
    for(int i= 0; i<MAX_MAP_Y;i++){
        for(int j =0;j<MAX_MAP_X;j++){
            fscanf_s(fp,"%d",&gameMap.tile[i][j]);
            int val = gameMap.tile[i][j];
            if(val>0){
                if(i> gameMap.maxY ){
                    gameMap.maxY = i;
                }

                if(j>gameMap.maxX){
                    gameMap.maxX = j;
                }
            }
        }
    }

    gameMap.maxX = (gameMap.maxX +1)*TILE_SIZE;
    gameMap.maxY = (gameMap.maxY +1)*TILE_SIZE;

    gameMap.startX = 0;
    gameMap.startY = 0;

    gameMap.fileName = FileName;
    fclose(fp); 
}

void GameMap::LoadTile(SDL_Renderer* renderer){
    char fileImg[30];
    FILE* fp =NULL;

    for(int i =0 ;i<MAX_TILE;i++){
        sprintf_s(fileImg,"save/%d.png",i);
        fopen_s(&fp,fileImg,"rb");

        if(fp == NULL){
            continue;
        }
        fclose(fp);

        tileMat[i].LoadImg(fileImg,renderer);
    }
}

void GameMap::DrawMap(SDL_Renderer* renderer){
        int x1=0;
        int x2=0;
     
        int y1=0;
        int y2=0;

        int mapX = gameMap.startX/TILE_SIZE;
        x1 = -1*(gameMap.startX%TILE_SIZE);
        x2 = x1 + SCREEN_WIDTH +(x1 == 0? 0:TILE_SIZE);

        int mapY = gameMap.startY/TILE_SIZE;
        y1 = -1*(gameMap.startY%TILE_SIZE);
        y2 = y1 + SCREEN_HEIGHT +(y1 == 0? 0:TILE_SIZE);

        for(int i =y1;i<y2;i+=TILE_SIZE){

            mapX = gameMap.startX/TILE_SIZE;

            for(int j = x1;j<x2;j+=TILE_SIZE){

                int val =gameMap.tile[mapY][mapX];
                if(val>0){
                    tileMat[val].SetRect({j,i,TILE_SIZE,TILE_SIZE});
                    tileMat[val].Render(renderer);
                }
                mapX++;
            }
            mapY++;
        }
}