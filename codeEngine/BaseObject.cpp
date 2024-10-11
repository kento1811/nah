#define SDL_MAIN_HANDLED

#include"../include/BaseObject.hpp"

void BaseObject::LoadImg(const char* fileName,SDL_Renderer* renderer){
    SDL_Texture* texture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(fileName);

    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B ) );

    texture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
    if(texture == NULL){std::cout<<"IMG Load Texture had failed "<<SDL_GetError()<<"\n";}
    SDL_FreeSurface(loadedSurface);
    objTex =  texture;
}

void BaseObject::Render(SDL_Renderer* renderer,const SDL_Rect* clip){
    SDL_Rect renderQuad = {rect.x,rect.y,rect.w,rect.h};
    SDL_RenderCopy(renderer,objTex,clip,&renderQuad);
}

void BaseObject::Free(){
    SDL_DestroyTexture(objTex);
}