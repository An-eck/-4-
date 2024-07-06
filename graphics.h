#ifndef GRAPHICS_H
#define GRAPHICS_H
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>


const int HEIGHT = 700;
const int WIDTH = 1000;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Event event;
extern TTF_Font* font;

void drawRectangle(int x1, int y1, int x2, int y2, std::string str, int borderWidth, int r, int g, int b);

void drawThickLine(int x1, int y1, int x2, int y2, int lineWidth);
bool initSDL();
void closeSDL();
void clearSDL();
#endif