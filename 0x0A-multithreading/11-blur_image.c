#include "multithreading.h"

/*              1111111111 */
/*     01234567890123456789 x */
/*  0  01234567012345670123 */
/*  1  01234567012345670123 */
/*  2  01234567012345670123 */
/*  3  01234567012345670123 */
/*  4  01234567012345670123 */
/*  5  01234567012345670123 */
/*  6  01234567012345670123 */
/*  7  01234567012345670123 */
/*  8  01234567012345670123 */
/*  9  01234567012345670123 */
/* 10  01234567012345670123 */
/* 11  01234567012345670123 */
/* 12  01234567012345670123 */
/* 13  01234567012345670123 */
/* 14  01234567012345670123 */
/* 15  01234567012345670123 */
/* 16  01234567012345670123 */
/* 17  01234567012345670123 */
/* 18  01234567012345670123 */
/* 19  01234567012345670123 */
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
			blur_pixel(portion, tinfo->pixels, i, j, px);
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
	tinfo_t *tinfo = arg;
	size_t i;

	for (i = tinfo->tnum; i < tinfo->portion->img->w; i += NUM_THREADS)
	{
		tinfo->portion->x = i, tinfo->portion->y = 0;
		tinfo->portion->w = 1;
		tinfo->portion->h = tinfo->portion->img->h;
		blur_portion_thread(tinfo);
	}
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
	*tinfo = calloc(NUM_THREADS, sizeof(**tinfo));
	if (!*tinfo)
		return (1);
	*portion = malloc(sizeof(**portion));
	if (!*portion)
		return (1);
	(*portion)->img = img, (*portion)->img_blur = img_blur;
	(*portion)->kernel = kernel;
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
		tinfo[i].portion = portion;
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
