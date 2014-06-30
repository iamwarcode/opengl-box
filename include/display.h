#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>

  class Display{
    private:
      SDL_Window *window;
      SDL_GLContext context;
    public:
      Display(int width, int height, const std::string& title);
      void Clear(float r, float g, float b, float a);
      void SwapBuffers();
      virtual ~Display();
  };
#endif