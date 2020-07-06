#include "multithreading.h"

void blur_pixel(blur_portion_t const *portion, size_t pixel)
{
	size_t grid_start, grid_stop_x, grid_stop_y, half_kernel, grid_idx, k_x, k_y;
	float r_avg, g_avg, b_avg, k_sum;

	half_kernel = portion->kernel->size / 2;
	grid_idx = grid_start = (pixel - half_kernel) - half_kernel * portion->img->w;
	grid_stop_x = grid_start + portion->kernel->size;
	grid_stop_y = grid_stop_x + portion->img->w * (portion->kernel->size - 1);
	k_x = k_y = 0;
	r_avg = g_avg = b_avg = 0;
	/* printf("pixel: %lu\n", pixel); */
	/* printf("grid_start: %lu\n", grid_start); */
	/* printf("grid_stop_x: %lu\n", grid_stop_x); */
	/* printf("grid_stop_y: %lu\n", grid_stop_y); */
	while (grid_idx < grid_stop_y)
	{
		/* printf("subp: %lu\n", grid_idx); */
		/* printf("img_r: %i * matrix: %f = %f\n", portion->img->pixels[pixel].r, portion->kernel->matrix[k_y][k_x], portion->img->pixels[pixel].r * portion->kernel->matrix[k_y][k_x]); */
		/* printf("img_r: %i\n", portion->img->pixels[pixel].r); */
		/* printf("img_g: %i\n", portion->img->pixels[pixel].g); */
		/* printf("img_b: %i\n", portion->img->pixels[pixel].b); */
		r_avg += portion->kernel->matrix[k_y][k_x] * portion->img->pixels[pixel].r;
		g_avg += portion->kernel->matrix[k_y][k_x] * portion->img->pixels[pixel].g;
		b_avg += portion->kernel->matrix[k_y][k_x] * portion->img->pixels[pixel].b;
		++grid_idx, ++k_x;
		if (grid_idx >= grid_stop_x)
		{
			grid_stop_x += portion->img->w;
			grid_idx = grid_start += portion->img->w;
			k_x = 0;
			++k_y;
		}
	}
	for (k_y = 0, k_sum = 0; k_y < portion->kernel->size; ++k_y)
	{
		for (k_x = 0; k_x < portion->kernel->size; ++k_x)
		{
			/* printf("%f ", portion->kernel->matrix[k_y][k_x]); */
			k_sum += portion->kernel->matrix[k_y][k_x];
		}
		/* putchar('\n'); */
	}
	printf("r_sum: %f\ng_sum: %f\nb_sum: %f\n", r_avg, g_avg, b_avg);
	printf("kernel sum: %f\n", k_sum);
	r_avg /= k_sum;
	g_avg /= k_sum;
	b_avg /= k_sum;
	printf("r_avg: %f\ng_avg: %f\nb_avg: %f\n", r_avg, g_avg, b_avg);
	printf("before:\nblur_r: %i\nblur_g: %i\nblur_b: %i\n", portion->img_blur->pixels[pixel].r, portion->img_blur->pixels[pixel].g, portion->img_blur->pixels[pixel].b);
	portion->img_blur->pixels[pixel].r = r_avg;
	portion->img_blur->pixels[pixel].g = g_avg;
	portion->img_blur->pixels[pixel].b = b_avg;
	printf("after\nblur_r: %i\nblur_g: %i\nblur_b: %i\n", portion->img_blur->pixels[pixel].r, portion->img_blur->pixels[pixel].g, portion->img_blur->pixels[pixel].b);
	/* exit(1); */
}

/* 0 indexed */
/* x-pos: y-pos + x */
/* y-pos: y * img_w */
/* start_blur: x-pos */
/* stop_blur: (absolute position + w) + img_w * (w - 1) */
/* kernel start: (absolute position - kernel size / 2) - kernel size / 2 * img_w */
/* img_w: 20 */
/* img_h  20 */
/* w: 10 */
/* h: 10 */
/* x:  5 */
/* y:  5 */

/* OG */
/*   0 xxxxxxxxxxxxxxxxxxxx  19 */
/*  20 xxxxxxxxxxxxxxxxxxxx  39 */
/*  40 xxxxxxxxxxxxxxxxxxxx  59 */
/*  60 xxxxxxxxxxxxxxxxxxxx  79 */
/*  80 xxxxxxxxxxxxxxxxxxxx  99 */
/* 100 xxxxxxxxxxxxxxxxxxxx 119 start 105-112*/
/* 120 xxxxxxxxxxxxxxxxxxxx 139 next  125-132 */
/* 140 xxxxxxxxxxxxxxxxxxxx 159 */
/* 160 xxxxxxxxxxxxxxxxxxxx 179 */
/* 180 xxxxxxxxxxxxxxxxxxxx 199 */
/* 200 xxxxxxxxxxxxxxxxxxxx 219 */
/* 220 xxxxxxxxxxxxxxxxxxxx 239 */
/* 240 xxxxxxxxxxxxxxxxxxxx 259 */
/* 260 xxxxxxxxxxxxxxxxxxxx 279 */
/* 280 xxxxxxxxxxxxxxxxxxxx 299 stop 295 */
/* 300 xxxxxxxxxxxxxxxxxxxx 319 */
/* 320 xxxxxxxxxxxxxxxxxxxx 339 */
/* 340 xxxxxxxxxxxxxxxxxxxx 359 */
/* 360 xxxxxxxxxxxxxxxxxxxx 379 */
/* 380 xxxxxxxxxxxxxxxxxxxx 399 */

/* cpy */
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
void *thread_start(void *arg)
{
	tinfo_t *tinfo = arg;
	size_t i, start_pixel, stop_pixel_y, stop_pixel_x;

	/* if (tinfo->tnum != 0) */
	/* 	pthread_exit(NULL); */
	/* printf("tnum: %i\n", tinfo->tnum); */
	/* printf("w: %lu\n", tinfo->portion->w); */
	/* printf("h: %lu\n", tinfo->portion->h); */
	/* printf("x: %lu\n", tinfo->portion->x); */
	/* printf("y: %lu\n", tinfo->portion->y); */
	/* printf("img_w: %lu\n", tinfo->portion->img->w); */
	/* printf("img_h: %lu\n", tinfo->portion->img->h); */
	i = start_pixel = tinfo->portion->y * tinfo->portion->img->w + tinfo->portion->x + tinfo->tnum;
	stop_pixel_x = start_pixel - tinfo->tnum + tinfo->portion->w;
	stop_pixel_y = stop_pixel_x + tinfo->portion->img->w * (tinfo->portion->h - 1);
	/* printf("start_pixel: %lu\n", start_pixel); */
	/* printf("stop_pixel_x: %lu\n", stop_pixel_x); */
	/* printf("stop_pixel_y: %lu\n", stop_pixel_y); */
	while (i < stop_pixel_y)
	{
		/* printf("pixel: %lu\n", i); */
		blur_pixel(tinfo->portion, i);
		i += tinfo->portion->img->w;
		if (i > stop_pixel_y)
		{
			i = start_pixel += NUM_THREADS;
			if (i >= stop_pixel_x)
				pthread_exit(NULL);
		}
	}
	pthread_exit(NULL);
}

/**
 * blur_portion - blur portion of an image using Gaussian blur
 * @portion: pointer to structure with information needed to blur
 */
/* img.w: 960 */
/* img.h: 540 */
/* w: 480 */
/* h: 270 */
/* x: 240 */
/* y: 135 */
void blur_portion(blur_portion_t const *portion)
{
	int i;
	int s;
	tinfo_t *tinfo;

	if (!portion)
		return;
	printf("NUM_THREADS: %i\n", NUM_THREADS);
	tinfo = calloc(NUM_THREADS, sizeof(*tinfo));
	for (i = 0; i < NUM_THREADS; ++i)
	{
		tinfo[i].tnum = i;
		tinfo[i].portion = portion;
		s = pthread_create(&tinfo[i].tid, NULL, &thread_start, tinfo + i);
		if (s != 0)
			goto out;
	}
	for (i = 0; i < NUM_THREADS; ++i)
	{
		s = pthread_join(tinfo[i].tid, NULL);
		if (s != 0)
		{
out:
			perror(NULL);
			return;
		}
	}
	free(tinfo);
}
