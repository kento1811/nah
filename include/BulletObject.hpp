#pragma once
#include"CommonFunc.hpp"
#include"BaseObject.hpp"

#define BULLET_SPEED 20

class BulletObject : public BaseObject{
    public:
    void HandleMove(Map& mapData);
    bool isMove(){return isShoot;};
    void setStatus(int status){this->status = status;}
    void setShoot(bool isShoot){this->isShoot = isShoot;};
    void setX(float x){valX = x;}
    private:
    bool isShoot;
    float valX;
    int status;
};
