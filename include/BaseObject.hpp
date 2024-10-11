#pragma once
#include"CommonFunc.hpp"

class BaseObject{
    public:
    BaseObject(){;};
    ~BaseObject(){;};

    void SetRect(SDL_Rect p_rect){rect.x =p_rect.x;rect.y =p_rect.y;rect.w =p_rect.w;rect.h=p_rect.h;};
    SDL_Rect GetRect(){return rect;};
    SDL_Texture* GetTexture(){return objTex;};

    void LoadImg(const char* fileName,SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer,const SDL_Rect* clip = NULL);
    void Free();
    private:
        SDL_Texture* objTex;
        SDL_Rect rect;
};