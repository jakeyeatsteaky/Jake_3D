#include <iostream>
#include <vector>
#include <cmath>

#include "Graphics.h"


SDL_Window* Graphics::window = nullptr;
SDL_GLContext Graphics::openGL_context = NULL;
int Graphics::window_width = Graphics::WINDOW_WIDTH;
int Graphics::window_height = Graphics::WINDOW_HEIGHT;


bool Graphics::CreateSDLWindow()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL\n";
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("Jake-3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if(!window) {
        std::cerr << "Error creating SDL Window\n";
        return false;
    }

    openGL_context = SDL_GL_CreateContext(window);
    if(openGL_context == NULL) { 
        std::cerr << "Error creating OpenGL Context\n";
        return false;
    }

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glViewport(0,0,window_width,window_height);

    return true;
}

void Graphics::DestroyWindow()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::ClearScreen(uint32_t color)
{
    glClearColor(1.0f, 0.f, 0.f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
} 

void Graphics::RenderFrame()
{
    SDL_GL_SwapWindow(window);
}

void Graphics::DrawRect(const SDL_Rect& rect, uint32_t color)
{
    
}

// void Graphics::DrawPoints(std::vector<Vec2<int>*> points, uint32_t color)
// {
//     SDL_SetRenderDrawColor(renderer, color >> 24, color >> 16, color >> 8, color);
//     for(auto point: points)
//     {
//         int x = point->xPos;
//         int y = point->yPos;
//         int size = 2;
//         SDL_RenderDrawLine(renderer,x-size, y-size, x+size, y-size);
//         SDL_RenderDrawLine(renderer,x-size, y-size, x-size, y+size);
//         SDL_RenderDrawLine(renderer,x-size, y+size, x+size, y+size);
//         SDL_RenderDrawLine(renderer,x+size, y+size, x+size, y-size);
//     }
// }

void Graphics::DrawCircle(int c_x, int c_y, int radius)
{
    const float PI = 3.141592f;
    int x,y,i;
    for(i = 0; i < 360; ++i) {
        x = radius * cos(i * PI / 180) + c_x;
        y = radius * sin(i * PI / 180) + c_y;
        //SDL_RenderDrawPoint(renderer, x,y);
    }
}


