#define SDL_MAIN_HANDLED

#include"../include/BulletObject.hpp"

bool BulletObject::HandleMove(Map& mapData,std::vector<enemyObject*> enemyList){
    int ax[2] , ay[2];
    ax[0] = (valX +status*BULLET_SPEED)/TILE_SIZE;
    ax[1] = (valX + rect.w -1 + status*BULLET_SPEED)/TILE_SIZE;
    ay[0] = (rect.y)/TILE_SIZE;
    ay[1] = (rect.y + rect.h -1)/TILE_SIZE;
    for(int i =0 ; i<2;i++){
        for(int j = 0 ; j<2;j++){

            if(mapData.tile[ay[i]][ax[j]] != 0){
                if(mapData.tile[ay[i]][ax[j]] == 9){
                    mapData.tile[ay[i]][ax[j]] = 0;
                }

                isShoot = false;
                return false;
            }
        }
        if(!isShoot){
            return false;
        }
    }

    for(int i = 0 ; i< enemyList.size();i++){
        enemyObject* enemy = enemyList.at(i);
        if(enemy != NULL){
            if(enemy->Colision(valX,rect.y,rect.w,rect.h)){
                isShoot = false;
                status = 0;
                storage::score+=5;
                return false;
            }
        }

 
    }

    rect.x += status*BULLET_SPEED;
    valX +=status*BULLET_SPEED;

    if(rect.x < 0 || rect.x + rect.w > SCREEN_WIDTH){
        isShoot = false;
        return false;
    }
    return true;
}
