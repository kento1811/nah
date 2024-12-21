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
    
    if(!(status == WALK_LEFT && inputType.right ==1 || status ==WALK_RIGHT && inputType.left ==1) && inputType.jump ==0){
        if(status == WALK_LEFT){
            LoadImg("save/player_left.png",renderer);
        }
        else {
            LoadImg("save/player_right.png",renderer);
        }
    }
    if(inputType.jump ==1 ){
        if(!(status == WALK_LEFT && inputType.right ==1 || status ==WALK_RIGHT && inputType.left ==1)){
            if(status == WALK_LEFT){
                LoadImg("save/jum_left.png",renderer);
            }
            else {
                LoadImg("save/jum_right.png",renderer);
            }
        }
    }
    
    if(inputType.left == 1 && inputType.right ==1){
        frame =0;
    }
    else if(inputType.left == 1 || inputType.right ==1){
        frame = ((++frame)%16);
    } else {frame =0;};

    rect.x = posX - mapX;
    rect.y = posY - mapY;

    SDL_Rect* currentClip = &frameClip[frame/2];
    SDL_Rect renderQuad = {rect.x,rect.y,widthFrame,heightFrame};

    SDL_RenderCopy(renderer,objTex,currentClip,&renderQuad);

}

void MainObject::HandleInputAction(SDL_Event e,SDL_Renderer* renderer){
    if(e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_UP:
        case SDLK_w:
            inputType.jump =jumpCooldown !=0 ? 0:1;
            break;

        case SDLK_RIGHT:
        case SDLK_d:
            status = WALK_RIGHT;
            inputType.right = 1;
            break;

        case SDLK_LEFT:
        case SDLK_a:
            status = WALK_LEFT;
            inputType.left = 1;
            break;
        }


    } else if( e.type ==SDL_KEYUP){
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_UP:
        case SDLK_w:
            inputType.jump =0;
            jumpCooldown = JUMP_COOLDOWN;
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
}

void MainObject::DoPlayer(Map& mapData){
    valX=0;
    valY += GRAVITY_SPEED;

    if(valY > MAX_FALL_SPEED){
        valY = GRAVITY_SPEED;
    }

    if(inputType.left==1){
        valX -= PLAYER_SPEED;
    }
    if(inputType.right ==1){
        valX += PLAYER_SPEED;
    }

    if(inputType.jump ==1 && onGround && jumpCooldown == 0){
        
        valY = -6*GRAVITY_SPEED;

        if(-posY + groundPos > 3*TILE_SIZE +16){
            onGround = false;
            jumpCooldown = JUMP_COOLDOWN;
        }
    }

    CheckToMap(mapData);
    CenterMap(mapData);
}

void MainObject::CenterMap(Map& gameMap){

    gameMap.startX = posX - (SCREEN_WIDTH/2);
    if(gameMap.startX <0){
        gameMap.startX = 0;
    } else if(gameMap.startX + SCREEN_WIDTH >= gameMap.maxX){
        gameMap.startX = gameMap.maxY - SCREEN_WIDTH;
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
    x2 = (posX + valX + heightFrame -1)/TILE_SIZE;

    y1 = (posY+1)/TILE_SIZE;
    y2 = (posY + heightMin -1)/TILE_SIZE;

    if(x1 >=0 && x2<=MAX_MAP_X && y1>=0 && y2 <= MAX_MAP_Y){
        if(valX >0){
            if(mapData.tile[y1][x2] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE){
                posX = x2*TILE_SIZE;
                posX -=  widthFrame +1;
                valX =0;
            }
        }

        else if(valX <0){
            if(mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y2][x1] != BLANK_TILE){
                posX = (x1+1)*TILE_SIZE;
                valX=0;
            }
        }
    }
    
    //check vertical
    int widthMin = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;

    x1 = (posX)/TILE_SIZE;
    x2 = (posX + widthMin )/TILE_SIZE;

    y1 = (posY + valY)/TILE_SIZE;
    y2 = (posY + valY + heightFrame -1)/TILE_SIZE;

    if(x1 >=0 && x2<=MAX_MAP_X && y1>=0 && y2 <= MAX_MAP_Y){

        if(valY >0){
            if(mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE){
                posY = y2*TILE_SIZE;
                posY -=  heightFrame +1;
                valY =0;
                onGround =true;
                groundPos = posY;
                jumpCooldown = jumpCooldown == 0 ?0: jumpCooldown -1 ;
            }
        }
        else if(valY <0){
            if(mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y1][x2] != BLANK_TILE){
                posY = (y1+1)*TILE_SIZE;
                valY=0;
                onGround =false;
            }
        }
    }

    posX += valX;


    posY += valY;

    if(posX <0){
        posX =0;
    }

    if(posX + widthFrame - mapX > SCREEN_WIDTH){
        posX = SCREEN_WIDTH-widthFrame -1;
    }

    if(posY <0){
        posY =0;
        onGround =false;
    }

    if(posY + heightFrame -mapY> SCREEN_HEIGHT){
        posY = SCREEN_HEIGHT-heightFrame -1;
    }
    
}