#include "graphics.h"
#include <cmath>
#include <filesystem>
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;
TTF_Font* font = nullptr;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL can not be initialised " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Binary Logic Functions", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Failed to create the window " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Failed to create the renderer" << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Got an error when initiating a font " << TTF_GetError() << std::endl;
        return false;
    }
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path fontPath = currentPath / "lato/Lato-Black.ttf";
    font = TTF_OpenFont(fontPath.string().c_str(), 24);

    if (font == NULL) {
        std::cerr << "Couldn't open the font" << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
void clearSDL() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void drawThickLine(int x1, int y1, int x2, int y2, int lineWidth) {
    double angleX;
    double angleY;
    if (x2-x1 == 0) {
        angleY = 0.0;
        angleX = 1.0;
    }
    else if (y2-y1 == 0) {
        angleX = 0.0;
        angleY = 1.0;
    } else {
       angleY = std::tan((y2-y1)/(x2-x1));
       angleX = 1.0;
    }
    for (int i = -lineWidth / 2; i <= lineWidth / 2; ++i) {
        SDL_RenderDrawLine(renderer, x1 + i*angleX, y1 + i*angleY, x2 + i*angleX, y2 + i*angleY);
    }
}

void drawRectangle(int x1, int y1, int x2, int y2, std::string str, int borderWidth, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    drawThickLine(x1, y1, x2, y1, borderWidth);
    drawThickLine(x2, y1, x2, y2, borderWidth);
    drawThickLine(x1, y2, x2, y2, borderWidth);
    drawThickLine(x1, y1, x1, y2, borderWidth);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), {255, 255, 255}); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = x1+10;
    Message_rect.y = y1 + 10;
    Message_rect.w = (x2 - x1 - 20);
    Message_rect.h = (y2 - y1 - 20);
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
    return;
}


