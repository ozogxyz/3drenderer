#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


/* Variables and global declaration */
uint32_t       *color_buffer;
SDL_Texture    *color_buffer_texture;
SDL_Renderer   *renderer;
SDL_Window     *window;
int		window_height;
int		window_width;

/* Function prototypes */
bool		initialize_window(void);
void		draw_pixel(int x, int y, uint32_t color);
void		draw_rectangle(int x, int y, int width, int height, uint32_t color);
void		draw_grid(uint32_t color);
void		render_color_buffer(void);
void		clear_color_buffer(uint32_t color);
void		destroy_window(void);

#endif
