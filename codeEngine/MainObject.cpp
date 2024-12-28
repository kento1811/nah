#define SDL_MAIN_HANDLED

#include"../include/MainObject.hpp" 


void MainObject::LoadImg(const char* path,SDL_Renderer* renderer){
    BaseObject::LoadImg(path,renderer);

    widthFrame = rect.w/8;
    heightFrame = rect.h;
}

void MainObject::SetClip(){
    if(widthFrame >0 && heightFrame >0){
        for(int i =0;i<8;i++){
            frameClip[i].x = i*widthFrame;
            frameClip[i].y = 0;
            frameClip[i].w = widthFrame;
            frameClip[i].h = heightFrame;
        }
    }
}

void MainObject::Show(SDL_Renderer* renderer){
    
    LoadImgPlayer(renderer);

    
    if(inputType.left == 1 && inputType.right ==1){
        frame =0;
    }
    else if(inputType.left == 1 || inputType.right ==1){
        frame = ((++frame)%35);
    } else {frame =0;};

    rect.x = posX - mapX;
    rect.y = posY - mapY;

    SDL_Rect* currentClip = &frameClip[frame/5];
    SDL_Rect renderQuad = {rect.x,rect.y,widthFrame,heightFrame};

    SDL_RenderCopy(renderer,objTex,currentClip,&renderQuad);

}

void MainObject::HandleInputAction(SDL_Event e,SDL_Renderer* renderer){
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_SPACE){
            BulletObject* bullet = new BulletObject();
            if(status == WALK_LEFT){
                bullet->LoadImg("./save/bullet_left.png",renderer);
                bullet->setStatus(-1);
                bullet->SetRect({int(rect.x-1) ,int(rect.y +heightFrame*0.3 ),11,10});
                
            } else if(status == WALK_RIGHT){
                bullet->LoadImg("./save/bullet_right.png",renderer);
                bullet->setStatus(1);
                bullet->SetRect({int(rect.x+widthFrame+1) ,int(rect.y +heightFrame*0.3),11,10});
            }
            bullet->setX(posX);
            bullet->setShoot(true);
            BulletList.push_back(bullet);
        }
    }
    if(e.type == SDL_KEYDOWN && isCameBack){
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            inputType.jump =1;
            break;

        case SDLK_RIGHT:
        case SDLK_d:
            inputType.right = 1;
            break;

        case SDLK_LEFT:
        case SDLK_a:
            inputType.left = 1;
            break;
        }


    } else if( e.type ==SDL_KEYUP && isCameBack){
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            inputType.jump =0;
            break;

        case SDLK_RIGHT:
        case SDLK_d:
            inputType.right = 0;
            break;

        case SDLK_LEFT:
        case SDLK_a:
            inputType.left = 0;
            break;

        }
    }

    if(inputType.right){
        status = WALK_RIGHT;
    } else if(inputType.left){
        status = WALK_LEFT;
    }
}

void MainObject::DoPlayer(Map& mapData){
    valY += GRAVITY_SPEED;
    
    if(valY > MAX_FALL_SPEED){
        valY = GRAVITY_SPEED;
    }

    if(isCameBack){

        valX=0;


        if(inputType.left==1){
            valX -= PLAYER_SPEED;
        }
        if(inputType.right ==1){
            valX += PLAYER_SPEED;
        }

        if(inputType.jump ==1 && onGround){
            
            valY = -12*GRAVITY_SPEED;
            onGround = false;
        }

    }
    
        CheckToMap(mapData);
        CenterMap(mapData);
}

void MainObject::HandleBullet(SDL_Renderer* renderer,Map& mapData){
    for(int i = 0 ;i< BulletList.size();i++){
        BulletObject* bullet = BulletList.at(i);
        if(bullet != NULL){
            if(bullet->isMove())
            {
                bullet->HandleMove(mapData);
                bullet->Render(renderer);
            } else {
                BulletList.erase(BulletList.begin() +i);

                if(bullet != NULL){
                    delete bullet;
                    bullet = NULL;
                }
            }
        }
    }
}


void MainObject::CenterMap(Map& gameMap){

    gameMap.startX = posX - (SCREEN_WIDTH/2);
    if(gameMap.startX <0){
        gameMap.startX = 0;
    } else if(gameMap.startX + SCREEN_WIDTH >= gameMap.maxX){
        gameMap.startX = gameMap.maxX - SCREEN_WIDTH;
    }

    gameMap.startY = posY - (SCREEN_HEIGHT/2);
    if(gameMap.startY <0){
        gameMap.startY = 0;
    } else if(gameMap.startY + SCREEN_HEIGHT >= gameMap.maxY){
        gameMap.startY = gameMap.maxY - SCREEN_HEIGHT;
    }

}

void MainObject::CheckToMap(Map& mapData){
    int x1 = 0;
    int x2 = 0;
    
    int y1 = 0;
    int y2 = 0;

    
    //check Horizontal  
    int heightMin = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;

    x1 = (posX + valX)/TILE_SIZE;
    x2 = (posX + valX + widthFrame -1)/TILE_SIZE;

    y1 = (posY)/TILE_SIZE;
    y2 = (posY + heightMin -1)/TILE_SIZE;

    if(x1 >=0 && x2<MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y){

        if(valX >0){
            if(mapData.tile[y1][x2] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE){
                if(!Colision(mapData,x1,x2,y1,y2)){
                    posX = x2*TILE_SIZE;
                    posX -=  (widthFrame +1);
                    valX =0;
                }
            }
        }

        else if(valX <0){
            if(mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y2][x1] != BLANK_TILE){
                if(!Colision(mapData,x1,x2,y1,y2)){
                    posX = (x1+1)*TILE_SIZE;
                    valX=0;
                }
            }
        }
    }
    
    //check vertical
    int widthMin = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;

    x1 = (posX)/TILE_SIZE;
    x2 = (posX + widthMin)/TILE_SIZE;

    y1 = (posY + valY)/TILE_SIZE;
    y2 = (posY + valY + heightFrame -1)/TILE_SIZE;

    if(x1 >=0 && x2<MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y){

        if(valY >0){
            if(mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE){
                if(!Colision(mapData,x1,x2,y1,y2)){
                    posY = y2*TILE_SIZE;
                    posY -=  (heightFrame +1);
                    valY =0;
                    onGround =true;
                    if(mapData.tile[y2][x1] != BLANK_TILE){groundPosX = x1;} else{groundPosX =x2;}
                    isCameBack = true;
                }
            } else {
                onGround = false;
            }
        }
        else if(valY <0){
            if(mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y1][x2] != BLANK_TILE){
                if(!Colision(mapData,x1,x2,y1,y2)){
                    posY = (y1+1)*TILE_SIZE;
                    valY=0;
                }
            }
        }
    }

    posX += valX;


    posY += valY;

    if(posX <0){
        posX =0;
    }

    if(posX + widthFrame - mapX >= SCREEN_WIDTH){
        posX = SCREEN_WIDTH-widthFrame -1;
    }

    if(posY <0){
        posY =0;
    }

    if(posY >= SCREEN_HEIGHT + 10){
        posX =groundPosX*TILE_SIZE;
        posY =-2*TILE_SIZE;
        isCameBack = false;
        valX =0;
        inputType.right =0;
        inputType.left =0;
        inputType.jump =0;
    }
}

void MainObject::LoadImgPlayer(SDL_Renderer* renderer){

        if(onGround){
            if(status == WALK_LEFT){
                LoadImg("./save/player_left.png",renderer);
            }
            else if(status ==WALK_RIGHT){
                LoadImg("./save/player_right.png",renderer);
            }
        }
        else{
            if(status == WALK_LEFT){
                LoadImg("./save/jum_left.png",renderer);
            }
            else if(status == WALK_RIGHT){
                LoadImg("./save/jum_right.png",renderer);
            }
        }

}

bool MainObject::Colision(Map& mapData,int x1,int x2,int y1,int y2){
    int ax[2] , ay[2];
    ax[0] = x1;
    ax[1] = x2;
    ay[0] = y1;
    ay[1] = y2;
    bool isColision = false;
    
    for(int i =0 ; i<2;i++){
        for(int j = 0 ; j<2;j++){
            if(mapData.tile[ay[i]][ax[j]] == 4){
                mapData.tile[ay[i]][ax[j]] = 0;
                score++;
                isColision = true;
            }
            if(ax[j] == 392 && ay[i] == 7){
                mapData.tile[ay[i]][ax[j]] = 2;
                posY -= 64;
            }
        }
    }

    return isColision;
}