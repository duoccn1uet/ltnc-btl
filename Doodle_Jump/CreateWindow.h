#ifndef CREATEWINDOW_H_INCLUDED
#define CREATEWINDOW_H_INCLUDED

#include "CommonFunc.h"

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

#endif // CREATEWINDOW_H_INCLUDED
