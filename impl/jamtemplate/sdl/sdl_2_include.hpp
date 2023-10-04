#ifndef JAMTEMPLATE_SDL_2_INCLUDE_HPP
#define JAMTEMPLATE_SDL_2_INCLUDE_HPP

#if JT_ENABLE_WEB
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_syswm.h>
#else
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_syswm.h"
#endif

#endif // JAMTEMPLATE_SDL_2_INCLUDE_HPP
