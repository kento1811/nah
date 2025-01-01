#pragma once
#include"BaseObject.hpp"

#define enemySpeed 4

class enemyObject : public BaseObject{
    public:
    enemyObject(){
        status = 1; 
        frame = 0;
        alive = true;};
    ~enemyObject(){Free();};
    void setRect(SDL_Rect p_rect);
    void HandleMove(Map& mapData);
    bool Colision(int x, int y,int w,int h);
    void Show(SDL_Renderer* renderer,float mapX,float mapY);
    void SetClip();
    bool isAlive(){return alive;};

    private:
    bool alive;
    float posX;
    float posY;
    int frame;
    int status;
    int widthFrame;
    int heightFrame;
    SDL_Rect frameClip[8];
};

