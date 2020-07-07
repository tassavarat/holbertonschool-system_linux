#include "multithreading.h"

/**
 * blur_pixel - blur individual pixel
 * @portion: pointer to structure with information needed to blur
 * @pixel: index of pixel to blur
 */
void blur_pixel(blur_portion_t const *portion, size_t pixel)
{
	ssize_t grid_start, grid_idx;
	size_t k_x, k_y, grid_stop_x, grid_stop_y, half_kernel;
	float r_avg, g_avg, b_avg, k_sum;

	half_kernel = portion->kernel->size / 2;
	grid_idx = grid_start = (pixel - half_kernel) - half_kernel * portion->img->w;
	grid_stop_x = grid_start + portion->kernel->size;
	grid_stop_y = grid_stop_x + portion->img->w * (portion->kernel->size - 1);
	k_x = k_y = 0;
	r_avg = g_avg = b_avg = 0;
	/* printf("pixel: %lu\n", pixel); */
	/* printf("grid_start: %li\n", grid_start); */
	/* printf("grid_stop_x: %li\n", grid_stop_x); */
	/* printf("grid_stop_y: %li\n", grid_stop_y); */
	while (grid_idx < (ssize_t) grid_stop_y)
	{
		/* if (grid_idx < 0 || grid_idx > ) */
		/* printf("grid_idx: %li\n", grid_idx); */
		r_avg +=
			portion->kernel->matrix[k_y][k_x] * portion->img->pixels[grid_idx].r;
		g_avg +=
			portion->kernel->matrix[k_y][k_x] * portion->img->pixels[grid_idx].g;
		b_avg +=
			portion->kernel->matrix[k_y][k_x] * portion->img->pixels[grid_idx].b;
		++grid_idx, ++k_x;
		if (grid_idx >= (ssize_t) grid_stop_x)
		{
			grid_stop_x += portion->img->w;
			grid_idx = grid_start += portion->img->w;
			k_x = 0;
			++k_y;
		}
	}
	for (k_y = 0, k_sum = 0; k_y < portion->kernel->size; ++k_y)
		for (k_x = 0; k_x < portion->kernel->size; ++k_x)
			k_sum += portion->kernel->matrix[k_y][k_x];
	r_avg /= k_sum;
	g_avg /= k_sum;
	b_avg /= k_sum;
	portion->img_blur->pixels[pixel].r = r_avg;
	portion->img_blur->pixels[pixel].g = g_avg;
	portion->img_blur->pixels[pixel].b = b_avg;
}

/* cpy */
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
/*   0 xxxxxxxxxxxxxxxxxxxx  19 */
/*  20 xxxxxxxxxxxxxxxxxxxx  39 */
/*  40 xxxxxxxxxxxxxxxxxxxx  59 */
/*  60 xxx11111xxxxxxxxxxxx  79 */
/*  80 xxx11111xxxxxxxxxxxx  99 */
/* 100 xxx11O11ooooOooxxxxx 119 start 105-112*/
/* 120 xxx11111oooooooxxxxx 139 next  125-132 */
/* 140 xxx11111oooooooxxxxx 159 */
/* 160 xxxxxooooooooooxxxxx 179 */
/* 180 xxxxxooooooooooxxxxx 199 */
/* 200 xxxxxooooooooooxxxxx 219 */
/* 220 xxxxxooooooooooxxxxx 239 */
/* 240 xxxxxooooooooooxxxxx 259 */
/* 260 xxxxxooooooooooxxxxx 279 */
/* 280 xxxxxooooooooooSxxxx 299 stop 295 */
/* 300 xxxxxxxxxxxxxxxxxxxx 319 */
/* 320 xxxxxxxxxxxxxxxxxxxx 339 */
/* 340 xxxxxxxxxxxxxxxxxxxx 359 */
/* 360 xxxxxxxxxxxxxxxxxxxx 379 */
/* 380 xxxxxxxxxxxxxxxxxxxx 399 */
/* 11111 */
/* 11111 */
/* 11111 */
/* 11111 */
/* 11111 */

/**
 * blur_portion - blur portion of an image using Gaussian blur
 * @portion: pointer to structure with information needed to blur
 */
void blur_portion(blur_portion_t const *portion)
{
	size_t i, start_pixel, stop_pixel_y, stop_pixel_x;

	if (!portion)
		return;
	i = start_pixel = portion->y * portion->img->w + portion->x;
	stop_pixel_x = start_pixel + portion->w;
	stop_pixel_y = stop_pixel_x + portion->img->w * (portion->h - 1);
	while (i < stop_pixel_y)
	{
		/* printf("pixel: %lu\n", i); */
		blur_pixel(portion, i);
		i += portion->img->w;
		if (i > stop_pixel_y)
		{
			i = start_pixel += 1;
			if (i >= stop_pixel_x)
				break;
		}
	}
}
