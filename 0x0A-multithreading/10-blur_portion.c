#include "multithreading.h"

/**
 * blur_pixel - blur individual pixel
 * @portion: pointer to structure with information needed to blur
 * @pixel: index of pixel to blur
 */
void blur_pixel(blur_portion_t const *portion, size_t pixel)
{
	ssize_t grid_start, grid_idx, grid_stop_x, grid_stop_y;
	size_t k_x, k_y, half_kernel;
	float r_avg, g_avg, b_avg, k_sum;
	int offset;

	half_kernel = portion->kernel->size / 2;
	grid_idx = grid_start = (pixel - half_kernel) - half_kernel * portion->img->w;
	grid_stop_x = grid_start + portion->kernel->size;
	grid_stop_y = grid_stop_x + portion->img->w * (portion->kernel->size - 1);
	offset = k_sum = k_x = k_y = r_avg = g_avg = b_avg = 0;
	printf("pixel: %lu\n", pixel);
	printf("grid_start: %li\n", grid_start);
	printf("grid_stop_x: %li\n", grid_stop_x);
	printf("grid_stop_y: %li\n", grid_stop_y);
	while (grid_idx < grid_stop_y)
	{
		printf("grid_idx: %li\n", grid_idx);
		printf("grid_stop_x: %li\n", grid_stop_x);
		if (grid_idx > -1 && grid_idx < grid_stop_x && grid_idx >= grid_start + offset)
		{
			/* printf("grid_start: %li\n", grid_start); */
			/* printf("grid_stop_x: %li\n", grid_stop_x); */
			/* printf("prev_start: %i\n", abs(prev_start)); */
			printf("grid_idx: %li", grid_idx);
			/* prev_start = grid_start; */
			r_avg +=
				portion->kernel->matrix[k_y][k_x] * portion->img->pixels[grid_idx].r;
			g_avg +=
				portion->kernel->matrix[k_y][k_x] * portion->img->pixels[grid_idx].g;
			b_avg +=
				portion->kernel->matrix[k_y][k_x] * portion->img->pixels[grid_idx].b;
			printf("\t%f\n", portion->kernel->matrix[k_y][k_x]);
			k_sum += portion->kernel->matrix[k_y][k_x];
		}
		++grid_idx, ++k_x;
		if (grid_idx >= grid_stop_x)
		{
			/* puts("entered"); */
			grid_stop_x += portion->img->w;
			if (grid_start < 0 && grid_start + (ssize_t) portion->img->w > -1)
			{
				offset = -grid_start;
				/* printf("offset: %i\n", offset); */
			}
			grid_idx = grid_start += portion->img->w;
			k_x = 0;
			++k_y;
			/* putchar('\n'); */
		}
	}
	/* printf("k_sum: %f\n", k_sum); */
	/* putchar('\n'); */
	/* for (k_y = 0, k_sum = 0; k_y < portion->kernel->size; ++k_y) */
	/* 	for (k_x = 0; k_x < portion->kernel->size; ++k_x) */
	/* 		k_sum += portion->kernel->matrix[k_y][k_x]; */
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

	/* kernel->matrix = malloc(kernel->size * sizeof(float *)); */
	/* for (i = 0; i < kernel->size; i++) */
	/* { */
	/* 	kernel->matrix[i] = malloc(kernel->size * sizeof(float)); */
	/* 	for (j = 0; j < kernel->size; j++) */
	/* 		fscanf(f, "%f", &kernel->matrix[i][j]); */
	/* } */
pixel_t **convert_array(img_t const *img)
{
	pixel_t **pixels;
	size_t i, j, k;

	if (!img || img->w == 0 || img->h == 0)
		return (NULL);
	pixels = malloc(img->h * sizeof(*pixels));
	if (!pixels)
		return (NULL);
	for (i = k = 0; i < img->w; ++i)
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
	size_t i, start_pixel, stop_pixel_y, stop_pixel_x;
	pixel_t **pixels;

	if (!portion)
		return;
	pixels = convert_array(portion->img);
	if (!pixels)
		return;
	exit(1);
	i = start_pixel = portion->y * portion->img->w + portion->x;
	stop_pixel_x = start_pixel + portion->w;
	stop_pixel_y = stop_pixel_x + portion->img->w * (portion->h - 1);
	/* printf("start_pixel: %lu\n", start_pixel); */
	/* printf("stop_pixel_x: %lu\n", stop_pixel_x); */
	/* printf("stop_pixel_y: %lu\n", stop_pixel_y); */
	/* exit(1); */
	while (i < stop_pixel_y)
	{
		/* printf("pixel: %lu\n", i); */
		blur_pixel(portion, i);
		i += portion->img->w;
		if (i >= stop_pixel_y)
		{
			i = start_pixel += 1;
			if (i >= stop_pixel_x)
				break;
		}
	}
}
