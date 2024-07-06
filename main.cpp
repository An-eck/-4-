#include "logic.h"
#include "graphics.h"


int main() {
    if (!initSDL()) {
        return -1;
    }
    bool running = true;
    Program test;
    while (running) {

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                test.handleEvent(mouseX, mouseY);


            }

        }
        clearSDL();
        test.draw(mouseX, mouseY);
        SDL_RenderPresent(renderer); 

    }
    closeSDL();
    return 0;
}