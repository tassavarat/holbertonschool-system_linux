#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include "list.h"
#include <pthread.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

#define NUM_THREADS get_nprocs()

typedef void *(*task_entry_t)(void *);

/**
 * enum task_status_e - Task statuses
 *
 * @PENDING: Task is pending
 * @STARTED: Task has been started
 * @SUCCESS: Task has completed successfully
 * @FAILURE: Task has completed with issues
 */
typedef enum task_status_e
{
    PENDING = 0,
    STARTED,
    SUCCESS,
    FAILURE
} task_status_t;

/**
 * struct task_s - Executable task structure
 *
 * @entry:  Pointer to a function to serve as the task entry
 * @param:  Address to a custom content to be passed to the entry function
 * @status: Task status, default to PENDING
 * @result: Stores the return value of the entry function
 * @lock:   Task mutex
 */
typedef struct task_s
{
    task_entry_t    entry;
    void        *param;
    task_status_t   status;
    void        *result;
    pthread_mutex_t lock;
} task_t;

/**
 * struct pixel_s - RGB pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */
typedef struct pixel_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

/**
 * struct img_s - Image
 *
 * @w:      Image width
 * @h:      Image height
 * @pixels: Array of pixels
 */
typedef struct img_s
{
	size_t w;
	size_t h;
	pixel_t *pixels;
} img_t;

/**
 * struct kernel_s - Convolution kernel
 *
 * @size:   Size of the matrix (both width and height)
 * @matrix: Kernel matrix
 */
typedef struct kernel_s
{
	size_t size;
	float **matrix;
} kernel_t;

/**
 * struct blur_portion_s - Information needed to blur a portion of an image
 *
 * @img:      Source image
 * @img_blur: Destination image
 * @x:        X position of the portion in the image
 * @y:        Y position of the portion in the image
 * @w:        Width of the portion
 * @h:        Height of the portion
 * @kernel:   Convolution kernel to use
 */
typedef struct blur_portion_s
{
	img_t const *img;
	img_t *img_blur;
	size_t x;
	size_t y;
	size_t w;
	size_t h;
	kernel_t const *kernel;
} blur_portion_t;

/**
 * struct tinfo_s - argument for thread_start()
 * @tid:	id returned by pthread_create()
 * @tnum:	application-defined thread number
 * @portion:	pointer to blur_portion_s struct
 * @pixels:	pointer to 2-D array representation of image pixels
 */
typedef struct tinfo_s
{
	pthread_t tid;
	int tnum;
	blur_portion_t *portion;
	pixel_t **pixels;
} tinfo_t;

void *thread_entry(void *arg);
int tprintf(char const *format, ...);
void blur_portion(blur_portion_t const *portion);
pixel_t **convert_array(const img_t *img);
void blur_pixel(const blur_portion_t *portion, const pixel_t **pixels,
		const size_t x, const size_t y, const size_t px);
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel);
int tprintf(char const *format, ...);
list_t *prime_factors(char const *s);
task_t *create_task(task_entry_t entry, void *param);

#endif /* MULTITHREADING_H */
