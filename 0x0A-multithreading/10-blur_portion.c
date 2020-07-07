#include "multithreading.h"

/*              1111111111 */
/*    01234567890123456789 x */
/*  0 xxxxxxxxxxxxxxxxxxxx */
/*  1 xxxxxxxxxxxxxxxxxxxx */
/*  2 xxxxxxxxxxxxxxxxxxxx */
/*  3 xxx11111xxxxxxxxxxxx */
/*  4 xxx11111xxxxxxxxxxxx */
/*  5 xxx11O11ooooOooxxxxx */
/*  6 xxx11111oooooooxxxxx */
/*  7 xxx11111oooooooxxxxx */
/*  8 xxxxxooooooooooxxxxx */
/*  9 xxxxxooooooooooxxxxx */
/* 10 xxxxxooooooooooxxxxx */
/* 11 xxxxxooooooooooxxxxx */
/* 12 xxxxxooooooooooxxxxx */
/* 13 xxxxxooooooooooxxxxx */
/* 14 xxxxxooooooooooSxxxx */
/* 15 xxxxxxxxxxxxxxxxxxxx */
/* 16 xxxxxxxxxxxxxxxxxxxx */
/* 17 xxxxxxxxxxxxxxxxxxxx */
/* 18 xxxxxxxxxxxxxxxxxxxx */
/* 19 xxxxxxxxxxxxxxxxxxxx */
/*  y */

/* 11111 */
/* 11111 */
/* 11111 */
/* 11111 */
/* 11111 */

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

/**
 * get_sums - initialise sums for rgb and kernel
 * @r_sum:	pointer to sum of red values
 * @g_sum:	pointer to sum of green values
 * @b_sum:	pointer to sum of blue values
 * @k_sum:	pointer to sum of kernel values
 * @portion:	pointer to structure with information needed to blur
 * @pixels:	double array of pixels
 * @x:		x position for pixels array of pixel to blur
 * @y:		y position for pixels array of pixel to blur
 */
void get_sums(float *r_sum, float *g_sum, float *b_sum, float *k_sum,
		const blur_portion_t *portion, const pixel_t **pixels,
		const size_t x, const size_t y)
{
	ssize_t grid_x, grid_y, grid_stop_x, grid_stop_y;
	size_t half_kernel, k_x, k_y;

	half_kernel = portion->kernel->size / 2;
	grid_x = x - half_kernel, grid_y = y - half_kernel;
	grid_stop_y = grid_y + portion->kernel->size;
	grid_stop_x = grid_x + portion->kernel->size;
	for (grid_y = y - half_kernel, k_y = *r_sum = *g_sum = *b_sum = *k_sum = 0;
			grid_y < grid_stop_y; ++grid_y, ++k_y)
	{
		for (grid_x = x - half_kernel, k_x = 0; grid_x < grid_stop_x;
				++grid_x, ++k_x)
		{
			if (grid_x > -1 && grid_y > -1 &&
					grid_x < (ssize_t) portion->img->w &&
					grid_y < (ssize_t) portion->img->h)
			{
				*r_sum += portion->kernel->matrix[k_y][k_x] *
					pixels[grid_y][grid_x].r;
				*g_sum += portion->kernel->matrix[k_y][k_x] *
					pixels[grid_y][grid_x].g;
				*b_sum += portion->kernel->matrix[k_y][k_x] *
					pixels[grid_y][grid_x].b;
				*k_sum += portion->kernel->matrix[k_y][k_x];
			}
		}
	}
}

/**
 * blur_pixel - blur individual pixel
 * @portion:	pointer to structure with information needed to blur
 * @pixels:	double array of pixels
 * @x:		x position for pixels array of pixel to blur
 * @y:		y position for pixels array of pixel to blur
 * @px:		index of pixel to blur for output array
 *
 * Using pixels double array for simplified 1 to 1 traversal of image with
 * kernel
 */
void blur_pixel(const blur_portion_t *portion, const pixel_t **pixels,
		const size_t x, const size_t y, const size_t px)
{
	float r_avg, g_avg, b_avg, k_sum;

	get_sums(&r_avg, &g_avg, &b_avg, &k_sum, portion, pixels, x, y);
	r_avg /= k_sum, g_avg /= k_sum, b_avg /= k_sum;
	portion->img_blur->pixels[px].r = r_avg;
	portion->img_blur->pixels[px].g = g_avg;
	portion->img_blur->pixels[px].b = b_avg;
}

/**
 * convert_array - create 2-D pixel_t array from 1-D array
 * @img: pointer to img struct containing 1-D pixel_t array
 *
 * Return: created array or NULL on malloc fail
 */
pixel_t **convert_array(const img_t *img)
{
	pixel_t **pixels;
	size_t i, j, k;

	if (!img || img->w == 0 || img->h == 0)
		return (NULL);
	pixels = malloc(img->h * sizeof(*pixels));
	if (!pixels)
		return (NULL);
	for (i = k = 0; i < img->h; ++i)
	{
		pixels[i] = malloc(img->w * sizeof(**pixels));
		if (!pixels[i])
			return (NULL);
		for (j = 0; j < img->w; ++j, ++k)
			pixels[i][j] = img->pixels[k];
	}
	return (pixels);
}

/**
 * blur_portion - blur portion of an image using Gaussian blur
 * @portion: pointer to structure with information needed to blur
 */
void blur_portion(blur_portion_t const *portion)
{
	size_t i, j, px, start, stop_x, stop_y;
	pixel_t **pixels;

	if (!portion)
		return;
	pixels = convert_array(portion->img);
	if (!pixels)
		return;
	start = px = portion->x + portion->y * portion->img->w;
	stop_x = start + portion->w;
	stop_y = stop_x + portion->img->w * (portion->h - 1);
	for (i = portion->x; i < portion->w + portion->x; ++i)
		for (j = portion->y; j < portion->h + portion->y; ++j)
		{
			blur_pixel(portion, (const pixel_t **)pixels, i, j, px);
			px += portion->img->w;
			if (px >= stop_y)
			{
				px = start += 1;
				if (px >= stop_x)
					break;
			}
		}
	for (i = 0; i < portion->img->h; ++i)
		free(pixels[i]);
	free(pixels);
}
