#include "App.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv) 
{
    App app;
    
    app.Setup();

    while(app.IsRunning())
    {
        app.Input();
        app.Update();
        app.Render();
    }
    return 0;
}
    











