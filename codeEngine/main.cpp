#define SDL_MAIN_HANDLED

#include"../include/CommonFunc.hpp"
#include"../include/BaseObject.hpp"
#include"../include/GameMap.hpp"
#include"../include/MainObject.hpp"

//g++ codeEngine/*.cpp -o main -Llib -lSDL2 -lSDL2_image
//git add*
//git commit -m " "
//git push origin master

BaseObject backGround;

void init(){
        // initizile
    if(SDL_Init(SDL_INIT_VIDEO) >0){
        std::cout<<"SDL_Init video had failed "<<SDL_GetError()<<"\n";
    }
    if(!IMG_Init(IMG_INIT_PNG)){
        std::cout<<"IMG_Init png had failed "<<SDL_GetError()<<"\n";
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    gWindow = SDL_CreateWindow("game 1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
}

void loadBackGround(){
    backGround.LoadImg("save/background.png",gRenderer);
    backGround.SetRect({0,0,SCREEN_WIDTH,SCREEN_HEIGHT});
}

void Close(){
    backGround.Free();

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]){
    init();
    loadBackGround();
    GameMap map;
    char mapName[20] = "save/map01.dat";
    map.LoadMap(mapName);
    map.LoadTile(gRenderer);

    MainObject player;
    player.SetRect({0,0,480,64});
    player.LoadImg("save/player_right.png",gRenderer);
    player.SetClip();

    int fps = 1000/FRAME_RATE;
    bool isRunning =true;
    while(isRunning){
        int frameRateStart = SDL_GetTicks();

        while(SDL_PollEvent(&gEvent) != 0){
            if(gEvent.type == SDL_QUIT){
                isRunning = false;
            }

            player.HandleInputAction(gEvent,gRenderer);
        }


        SDL_RenderClear(gRenderer);

        backGround.Render(gRenderer);
        

        Map mapData = map.getMap();

        player.SetMapXY(mapData.startX,mapData.startY);
        player.DoPlayer(mapData);
        player.Show(gRenderer);

        map.SetMap(mapData);
        map.DrawMap(gRenderer);

        SDL_RenderPresent(gRenderer);


        int delta = SDL_GetTicks() - frameRateStart;
        if(delta < fps){
            SDL_Delay(fps-delta);
        }
        
    }

    Close();
    return 0;
}