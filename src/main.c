#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>

uint32_t       *colorBuffer = NULL;
SDL_Texture    *colorBufferTexture = NULL;
bool		isRunning = false;
SDL_Renderer   *renderer = NULL;
SDL_Window     *window = NULL;
int		windowHeight = 600;
int		windowWidth = 800;


bool
InitializeWindow(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

        /* Use SDL to query max screen width and height */
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        windowWidth = displayMode.w;
        windowHeight = displayMode.h;

	/* Create an SDL window. */
	window = SDL_CreateWindow(NULL,
				  SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED,
				  windowWidth,
				  windowHeight,
				  SDL_WINDOW_BORDERLESS);

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

        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	return true;
}

void
setup(void)
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
processInput(void)
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
update(void)
{
}

void
clearColorBuffer(uint32_t color)
{
	for (int y = 0; y < windowHeight; y++) {
		for (int x = 0; x < windowWidth; x++) {
			colorBuffer[windowWidth * y + x] = color;
		}
	}
}


void
drawGrid(uint32_t color)
{
        for (int y = 0; y < windowHeight; y += 10) {
                 for (int x = 0; x < windowWidth; x += 10) {
                         colorBuffer[windowWidth * y + x] = color;
                 }
        }
}

void
drawRectangle(int x, int y, int width, int height, uint32_t color)
{
        for (int j = y; j < y + height; j++) {
                for (int i = x; i < x + width; i++) {
                        colorBuffer[windowWidth * j + i] = color;
                }
        }
}

void
renderColorBuffer(void)
{
	SDL_UpdateTexture(colorBufferTexture,
			  NULL,
			  colorBuffer,
			  (int)(windowWidth * sizeof(uint32_t)));
        SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void
render(void)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

        drawGrid(0xFF0000FF);
        drawRectangle(400, 400, 100, 200, 0xFF00FEBC);

	renderColorBuffer();
	clearColorBuffer(0xFFFFFFFF);

	SDL_RenderPresent(renderer);
}

void
destroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int
main(void)
{
	isRunning = InitializeWindow();

	setup();

	while (isRunning) {
		processInput();
		update();
		render();
	}

	destroyWindow();
	return 0;
}
