#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "App.h"

int main() {
 
    App app;
    try {
		app.Setup();
	
		do {
		    app.Input();
		    app.Update();
		    app.Render();
		} while (app.IsRunning());

		app.Destroy();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
    
	return EXIT_SUCCESS;
}