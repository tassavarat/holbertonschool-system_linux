#include "multithreading.h"

/*               1111111111 */
/*     01234567890123456789 x */
/*  0  00000111112222233333 */
/*  1  00000111112222233333 */
/*  2  00000111112222233333 */
/*  3  00000111112222233333 */
/*  4  00000111112222233333 */
/*  5  00000111112222233333 */
/*  6  00000111112222233333 */
/*  7  00000111112222233333 */
/*  8  00000111112222233333 */
/*  9  00000111112222233333 */
/* 10  00000111112222233333 */
/* 11  00000111112222233333 */
/* 12  00000111112222233333 */
/* 13  00000111112222233333 */
/* 14  00000111112222233333 */
/* 15  00000111112222233333 */
/* 16  00000111112222233333 */
/* 17  00000111112222233333 */
/* 18  00000111112222233333 */
/* 19  00000111112222233333 */
/*  y */

/* 11111 */
/* 11111 */
/* 11111 */
/* 11111 */
/* 11111 */

/**
 * blur_portion_thread - blur portion of an image using Gaussian blur
 * @tinfo: pointer to structure with pointers to portion and pixels
 */
void blur_portion_thread(tinfo_t *tinfo)
{
	size_t i, j, px, start, stop_x, stop_y;
	blur_portion_t *portion = tinfo->portion;

	if (!portion)
		return;
	start = px = portion->x + portion->y * portion->img->w;
	stop_x = start + portion->w;
	stop_y = stop_x + portion->img->w * (portion->h - 1);
	for (i = portion->x; i < portion->w + portion->x; ++i)
		for (j = portion->y; j < portion->h + portion->y; ++j)
		{
			blur_pixel(portion, (const pixel_t **)tinfo->pixels, i, j, px);
			px += portion->img->w;
			if (px >= stop_y)
			{
				px = start += 1;
				if (px >= stop_x)
					break;
			}
		}
}

/**
 * thread_start - entry point for thread
 * @arg: pointer to struct containing thread and image blur information
 *
 * Return: NULL
 */
void *thread_start(void *arg)
{
	blur_portion_thread((tinfo_t *)arg);
	pthread_exit(NULL);
}

/**
 * init - initialise dynamic memory
 * @tinfo:	double pointer to argument for thread_start()
 * @portion:	double pointer to structure with information needed to blur
 * @pixels:	pointer to 2-D array representation of image pixels
 * @img:	pointer to source image
 * @img_blur:	pointer to destination image
 * @kernel:	pointer to convolution kernel
 *
 * Return: 0 on success or 1 on malloc fail
 */
int init(tinfo_t **tinfo, blur_portion_t **portion, pixel_t ***pixels,
		img_t const *img, img_t *img_blur, kernel_t const *kernel)
{
	int i;
	size_t offset;

	*tinfo = malloc(NUM_THREADS * sizeof(**tinfo));
	if (!*tinfo)
		return (1);
	*portion = malloc(NUM_THREADS * sizeof(**portion));
	if (!*portion)
		return (1);
	for (i = 0; i < NUM_THREADS; ++i)
	{
		(*portion)[i].img = img, (*portion)[i].img_blur = img_blur;
		(*portion)[i].kernel = kernel;
		if ((*portion)[i].img->w <= (size_t) NUM_THREADS &&
				(size_t) i < (*portion)[i].img->w)
		{
			(*portion)[i].x = i;
			(*portion)[i].y = 0;
			(*portion)[i].w = 1;
			(*portion)[i].h = (*portion)[i].img->h;
		}
		else
		{
			offset = (*portion)[i].img->w / (NUM_THREADS);
			(*portion)[i].x = offset * i;
			(*portion)[i].y = 0;
			(*portion)[i].w = offset;
			(*portion)[i].h = (*portion)[i].img->h;
		}
	}
	*pixels = convert_array(img);
	if (!*pixels)
		return (1);
	return (0);
}

/**
 * blur_image - blur entire image using Gaussian blur
 * @img_blur:	pointer to destination image
 * @img:	pointer to source image
 * @kernel:	pointer to convolution kernel
 */
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{
	tinfo_t *tinfo;
	blur_portion_t *portion;
	pixel_t **pixels;
	int i, s;

	if (!img_blur || !img || !kernel)
		return;
	if (init(&tinfo, &portion, &pixels, img, img_blur, kernel))
		return;
	for (i = 0; i < NUM_THREADS; ++i)
	{
		tinfo[i].tnum = i;
		tinfo[i].portion = &portion[i];
		tinfo[i].pixels = pixels;
		s = pthread_create(&tinfo[i].tid, NULL, &thread_start, tinfo + i);
		if (s != 0)
			return;
	}
	for (i = 0; i < NUM_THREADS; ++i)
	{
		s = pthread_join(tinfo[i].tid, NULL);
		if (s != 0)
			return;
	}
	for (i = 0; (size_t) i < img->h; ++i)
		free(pixels[i]);
	free(pixels);
	free(portion);
	free(tinfo);
}
