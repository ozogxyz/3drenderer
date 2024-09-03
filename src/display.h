#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


/* Variables and global declaration */
uint32_t       *colorBuffer;
SDL_Texture    *colorBufferTexture;
SDL_Renderer   *renderer;
SDL_Window     *window;
int		windowHeight;
int		windowWidth;

/* Function prototypes */
bool		InitializeWindow(void);
void		DrawRectangle(int x, int y, int width, int height, uint32_t color);
void		DrawGrid(uint32_t color);
void		RenderColorBuffer(void);
void		ClearColorBuffer(uint32_t color);
void		DestroyWindow(void);

#endif
