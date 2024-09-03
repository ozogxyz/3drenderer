#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "display.h"


bool		isRunning = false;

void
Setup(void)
{
	colorBuffer = (uint32_t *) malloc(sizeof(uint32_t) * windowWidth * windowHeight);
	colorBufferTexture = SDL_CreateTexture(renderer,
					       SDL_PIXELFORMAT_ARGB8888,
					       SDL_TEXTUREACCESS_STREAMING,
					       windowWidth,
					       windowHeight);
	if (!colorBuffer)
		fprintf(stderr, "Error allocating color buffer.\n");
}

void
ProcessInput(void)
{
	SDL_Event	event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isRunning = false;
		break;
	}

}

void
Update(void)
{
}


void
Render(void)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	DrawGrid(0xFF0000FF);
	DrawRectangle(400, 400, 100, 200, 0xFF00FEBC);

	RenderColorBuffer();
	ClearColorBuffer(0xFFFFFFFF);

	SDL_RenderPresent(renderer);
}


int
main(void)
{
	isRunning = InitializeWindow();

	Setup();

	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}

	DestroyWindow();
	return 0;
}
