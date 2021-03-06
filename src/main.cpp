#ifndef APP_H
#define APP_H

#include <OpenGL/gl3.h>
#include "SDL.h"

#include "ogl.h"

SDL_DisplayMode display;
SDL_Window* window;
SDL_GLContext context;

void initialize() {

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  SDL_VideoInit(nullptr);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  SDL_GetCurrentDisplayMode(0, &display);

  window = SDL_CreateWindow("SDL",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            800, 600,
                            SDL_WINDOW_ALLOW_HIGHDPI |
                            SDL_WINDOW_OPENGL);

  context = SDL_GL_CreateContext(window);

  ogl::initialize();

}


int main(int argc, char** argv) {

  initialize();

  bool finished = false;

  SDL_Event event = SDL_Event{0};

  while (!finished) {

    while (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_QUIT:
        finished = true;
        break;
      }
    }

    ogl::render();

    SDL_GL_SwapWindow(window);

  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}

#endif
