#include <iostream>

#include "App.h"
#include "SDL.h"

bool App::IsRunning()
{
    return running;
}

void App::Setup()
{
    //SeedRandom();
    running = Graphics::CreateWindow();
}

void App::Input()
{
   SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
            default:
                break;
        }
    }

}

void App::Update()
{
    int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - timePrevFrame);
    if (timeToWait > 0)
        SDL_Delay(timeToWait);

    float  deltaTime = (SDL_GetTicks() - timePrevFrame) / 1000.0f;
    if (deltaTime > 0.05)
        deltaTime = 0.05;
    timePrevFrame = SDL_GetTicks();
}

void App::Render()
{
    Graphics::ClearScreen(0xFF000000);

    Graphics::RenderFrame();
}

void App::Destroy()
{

}
