build:
	g++ -std=c++17 -Wall -I deps/SDL2/include -L deps/SDL2/lib/x64 -lSDL2 -lSDL2main -o sdl_app main.cpp -lmingw32 -lSDL2main -lSDL2

run:
	./sdl_app

build_and_run:
	g++ -std=c++17 -Wall -I deps/SDL2/include -L deps/SDL2/lib/x64 -lSDL2 -lSDL2main -o sdl_app main.cpp -lmingw32 -lSDL2main -lSDL2
	./sdl_app

clean:
	rm sdl_app
