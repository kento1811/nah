#define SDL_MAIN_HANDLED

#include"../include/enemyObject.hpp"

void enemyObject::setRect(SDL_Rect p_rect){
    rect.x =p_rect.x;
    rect.y =p_rect.y;
    rect.w =p_rect.w;
    rect.h=p_rect.h;

    posX = rect.x;
    posY = rect.y;
    heightFrame = rect.h;
    widthFrame = rect.w/8;
}

void enemyObject::HandleMove(Map& mapData){
    int x1 = 0;
    int x2 = 0;
    
    int y1 = 0;
    int y2 =0;

    x1 = (posX + status*enemySpeed)/TILE_SIZE;
    x2 = (posX + status*enemySpeed + widthFrame )/TILE_SIZE;

    y1 = (posY + heightFrame )/TILE_SIZE;
    y2 = posY/TILE_SIZE;


    if(x1 >=0 && x2<MAX_MAP_X && y1>=0 && y1 < MAX_MAP_Y){
        if(status >0){
            if(mapData.tile[y2][x2] != BLANK_TILE || mapData.tile[y1+1][x2] == BLANK_TILE ){
                status =-status;
            }
        } else if(status < 0){
            if( mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y1+1][x1] == BLANK_TILE){
                status = -status;
            }
        }
    }

    posX += status*enemySpeed;
};

bool enemyObject::Colision(int x, int y,int w,int h){
    if((int(posX)/TILE_SIZE == x/TILE_SIZE || int(posX)/TILE_SIZE == (x+w)/TILE_SIZE) && 
    (int(posY)/TILE_SIZE == y/TILE_SIZE || int(posY)/TILE_SIZE == (y+h)/TILE_SIZE)){
        alive = false;
        return true;
    }
    return false;
}

void enemyObject::SetClip(){
    if(widthFrame >0 && heightFrame >0){
        for(int i =0;i<8;i++){
            frameClip[i].x = i*widthFrame;
            frameClip[i].y = 0;
            frameClip[i].w = widthFrame;
            frameClip[i].h = heightFrame;
        }
    }
}

void enemyObject::Show(SDL_Renderer* renderer,float mapX,float mapY){

    frame = ((++frame)%40);

    if(posX+widthFrame >=mapX && posX <= mapX+SCREEN_WIDTH && posY +heightFrame>=mapY && posY <= mapY+SCREEN_HEIGHT){
        rect.x = posX- mapX;
        rect.y = posY - mapY;

        SDL_Rect* currentClip = &frameClip[frame/5];
        SDL_Rect renderQuad = {rect.x,rect.y,widthFrame,heightFrame};

        SDL_RenderCopy(renderer,objTex,currentClip,&renderQuad);
    }

}