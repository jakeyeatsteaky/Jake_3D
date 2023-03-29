#ifndef APP_H
#define APP_H
#include "Graphics.h"

class App
{
public:
    App() = default;
    ~App() = default;

    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();

private:
    bool running = false;

};

#endif