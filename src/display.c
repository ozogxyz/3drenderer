#include "display.h"

bool
InitializeWindow(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	/* Use SDL to query max screen width and height */
	SDL_DisplayMode	displayMode;
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
DrawPixel(int x, int y, uint32_t color)
{
        if (x < windowWidth && y < windowHeight)
                colorBuffer[windowWidth * y + x] = color;
}

void
ClearColorBuffer(uint32_t color)
{
	for (int y = 0; y < windowHeight; y++) {
		for (int x = 0; x < windowWidth; x++) {
                        DrawPixel(x, y, color);
		}
	}
}

void
DrawRectangle(int x, int y, int width, int height, uint32_t color)
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int		currentX = x + i;
			int		currentY = y + j;
                        DrawPixel(currentX, currentY, color);
		}
	}
}

void
DrawGrid(uint32_t color)
{
	for (int y = 0; y < windowHeight; y += 10) {
		for (int x = 0; x < windowWidth; x += 10) {
                        DrawPixel(x, y, color);
		}
	}
}


void
RenderColorBuffer(void)
{
	SDL_UpdateTexture(colorBufferTexture,
			  NULL,
			  colorBuffer,
			  (int)(windowWidth * sizeof(uint32_t)));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void
DestroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
