#pragma once

#include"BaseObject.hpp"
#include"BulletObject.hpp"
#include<vector>

class MainObject : public BaseObject {
    public:
    MainObject(){    
    valX =0;
    valY=0;
    posX =0;
    posY=0;
    widthFrame =0;
    heightFrame =0;
    frame = 0;
    inputType.left=0;
    inputType.down=0;
    inputType.jump=0;
    inputType.right=0;
    inputType.up=0;
    onGround = false;
    status = -1;
    mapX = 0;
    mapY = 0;
    isCameBack = true; 
    score =0;
    };
    ~MainObject(){BaseObject::Free();};

    enum WalkType{
        WALK_RIGHT,WALK_LEFT
    };

    void LoadImg(const char* fileName,SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);
    void HandleInputAction(SDL_Event e,SDL_Renderer* renderer);
    void SetClip();
    void DoPlayer(Map& mapData);
    void CheckToMap(Map& mapData);
    void SetMapXY(int X, int Y){mapX = X; mapY = Y;};
    void CenterMap(Map& gameMap);
    void LoadImgPlayer(SDL_Renderer* renderer);
    int getStatus(){return status;}
    bool Colision(Map& mapData,int x1,int x2,int y1,int y2);
    int GetScore(){return score;};
    void HandleBullet(SDL_Renderer* renderer,Map& mapdata);

    private:
    bool onGround;

    float valX;
    float valY;

    float posX;
    float posY;

    int widthFrame;
    int heightFrame;

    SDL_Rect frameClip[8];
    Input inputType;
    int frame;
    int status;

    int mapX;
    int mapY;

    float groundPosX;
    bool isCameBack;

    int score;

    std::vector<BulletObject*> BulletList;

};