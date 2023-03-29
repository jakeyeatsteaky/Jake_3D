#include <iostream>
#include <vector>
#include <cmath>

#include "Graphics.h"

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;
int Graphics::window_width = Graphics::WINDOW_WIDTH;
int Graphics::window_height = Graphics::WINDOW_HEIGHT;


bool Graphics::CreateWindow()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL\n";
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    window = SDL_CreateWindow("Retro Interview Prep", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    if(!window) {
        std::cerr << "Error creating SDL Window\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        std::cerr << "Error creating SDL Renderer\n";
        return false;
    }

    return true;
}

void Graphics::DestroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::ClearScreen(uint32_t color)
{
    SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
    SDL_RenderClear(renderer);
} 

void Graphics::RenderFrame()
{
    SDL_RenderPresent(renderer);
}

void Graphics::DrawRect(const SDL_Rect& rect, uint32_t color)
{
    SDL_SetRenderDrawColor(renderer, color >> 24, color >> 16, color >> 8, color);
    SDL_RenderDrawRect(renderer, &rect);
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
        SDL_RenderDrawPoint(renderer, x,y);
    }
}


