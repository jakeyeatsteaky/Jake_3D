#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <vector>

#include "SDL.h"
#include "glad/glad.h"

const int FPS = 60;
const int MS_PER_FRAME = 1000/FPS;
static int timePrevFrame;

struct Graphics
{
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 800;
    static int window_width;
    static int window_height;
    static SDL_Window* window;
    static SDL_GLContext openGL_context;

    static int Width() {return window_width;}
    static int Height() {return window_height;}
    static bool CreateSDLWindow();
    static void DestroyWindow();
    static void ClearScreen(uint32_t color); 
    static void RenderFrame();

    static void DrawRect(const SDL_Rect& rect, uint32_t color);
    static void DrawCircle(int c_x, int c_y, int radius);
};


#endif