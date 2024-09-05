#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"

const int	N_POINTS = 9 * 9 * 9;
vec3_t		cubePoints[N_POINTS];
vec2_t		projectedPoints[N_POINTS];
float		fov_factor = 128;
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

	/* Start loading array of vectors */
	int		pointCount = 0;
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3_t		newPoint = {.x = x,.y = y,.z = z};
				cubePoints[pointCount++] = newPoint;
			}
		}
	}
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

vec2_t
Project(vec3_t point) {
	vec2_t		projectedPoint = {
		.x = (fov_factor * point.x),
		.y = (fov_factor * point.y)
	};
	return projectedPoint;
}

void
Update(void)
{
	for (int i = 0; i < N_POINTS; i++) {
		vec3_t		point = cubePoints[i];
		vec2_t		projectedPoint = Project(point);
		projectedPoints[i] = projectedPoint;
	}
}


void
Render(void)
{
	for (int i = 0; i < N_POINTS; i++) {
		vec2_t		projectedPoint = projectedPoints[i];
		DrawRectangle(projectedPoint.x + windowWidth / 2,
			      projectedPoint.y + windowHeight / 2,
			      4,
			      4,
			      0xFFFFFF00);
	}

	RenderColorBuffer();
	ClearColorBuffer(0xFF000000);
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
