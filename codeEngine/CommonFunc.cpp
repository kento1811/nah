#include"../include/CommonFunc.hpp"

font::~font(){
    SDL_FreeSurface(surfaceMessage);
SDL_DestroyTexture(Message);
}

void font::loadFont(SDL_Renderer* renderer,std::string path,int size,SDL_Color color){
    font = TTF_OpenFont(path.c_str(), size);
    this->color = color;
}

void font::setMess(const char* message,SDL_Renderer* renderer){
    surfaceMessage = TTF_RenderText_Solid(font,message,color); 
}

void font::setRect(SDL_Rect rect){
    rectMess.x =rect.x;
    rectMess.y =rect.y;
    rectMess.w =rect.w;
    rectMess.h =rect.h;
}

void font::render(SDL_Renderer* renderer){
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_RenderCopy(renderer, Message, NULL, &rectMess);

}