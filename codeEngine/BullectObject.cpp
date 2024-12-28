#define SDL_MAIN_HANDLED

#include"../include/BulletObject.hpp"

void BulletObject::HandleMove(Map& mapData){
    int ax[2] , ay[2];
    ax[0] = (valX )/TILE_SIZE;
    ax[1] = (valX + rect.w -1)/TILE_SIZE;
    ay[0] = (rect.y)/TILE_SIZE;
    ay[1] = (rect.y + rect.h -1)/TILE_SIZE;
    for(int i =0 ; i<2;i++){
        for(int j = 0 ; j<2;j++){
            if(mapData.tile[ay[i]][ax[j]] != 0){
                isShoot = false;
                break;
            }
        }
        if(!isShoot){
            break;
        }
    }

    rect.x += status*BULLET_SPEED;
    valX +=status*BULLET_SPEED;

    if(rect.x < 0 || rect.x + rect.w > SCREEN_WIDTH){
        isShoot = false;
        std::cout<<"2 ";
    }
}
