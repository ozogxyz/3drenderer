#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window     *window;
SDL_Renderer   *renderer;

bool
InitializeWindow(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}
	/* Create an SDL window. */
	window = SDL_CreateWindow(
				  NULL,
				  SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED,
				  800,
				  600,
				  SDL_WINDOW_BORDERLESS
		);

        if (!window) {
                fprintf(stderr, "Error creating SDL window.\n");
                return false;
        }

        /* Create an SDL renderer. */
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (!renderer) {
                fprintf(stderr, "Error creating SDL renderer.\n");
                return false;
        }

	return true;
}

int
main(void)
{
	InitializeWindow();

	return 0;
}
