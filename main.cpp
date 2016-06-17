#include <iostream>
#include <SDL2/SDL.h>

// Window
// ==========================================================
const char* WINDOW_TITLE = "SDL Window";

const int WINDOW_WIDTH = 800;
const int WINDOW_WIDTH_HALF = WINDOW_WIDTH / 2;

const int WINDOW_HEIGHT = 600;
const int WINDOW_HEIGHT_HALF = WINDOW_HEIGHT / 2;

// FPS
// ==========================================================
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

bool initSDL() {
	bool initialized = true;
	if (SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
	  std::cout << " SDL Failed to initialize: " << SDL_GetError() << std::endl;
		initialized = false;
	}
	return initialized;
}

SDL_Window* createSDLWindow() {
	return SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);
};

SDL_Renderer* createSDLRenderer(SDL_Window* &window) {
	return SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
};

void closeSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main( int argc, char* args[] )
{
  if(!initSDL()) { return 0; }

  SDL_Window* window = createSDLWindow();
  SDL_Renderer* renderer = createSDLRenderer(window);

  SDL_Event event;

  Uint32 frameStart, frameTime;

  bool isRunning = true;
  while(isRunning)
  {
    frameStart = SDL_GetTicks();

    while( SDL_PollEvent(&event) != 0 )
    {
      if( event.type == SDL_QUIT )
      {
    	  isRunning = false;
    	}
    }

    SDL_SetRenderDrawColor(renderer, 000, 000, 000, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < DELAY_TIME)
    {
      SDL_Delay((int) (DELAY_TIME - frameTime));
    }
  }
  closeSDL(window, renderer);
  return 0;
}
