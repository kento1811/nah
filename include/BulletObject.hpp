#pragma once
#include"CommonFunc.hpp"
#include"BaseObject.hpp"
#include"GameMap.hpp"

#define BULLET_SPEED 20


class BulletObject : public BaseObject{
    public:
    bool HandleMove(Map& mapData,std::vector<enemyObject*> enemyList);
    bool isMove(){return isShoot;};
    void setStatus(int status){this->status = status;}
    void setShoot(bool isShoot){this->isShoot = isShoot;};
    void setX(float x){valX = x;}
    private:
    bool isShoot;
    float valX;
    int status;
};
