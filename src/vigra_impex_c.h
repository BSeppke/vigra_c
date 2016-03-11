#include "os_settings.h"

LIBEXPORT int vigra_importgrayimage_c(float *arr, int width, int height, const char * filename);

LIBEXPORT int vigra_exportgrayimage_c(const float *arr, int width, int height, const char * filename);

LIBEXPORT int vigra_importrgbimage_c(float *arr_r, float *arr_g, float *arr_b, int width, int height, const char * filename);

LIBEXPORT int vigra_exportrgbimage_c(const float *arr_r, const float *arr_g, const float *arr_b, int width, int height, const char * filename);

LIBEXPORT int get_width_c(const char * filename);

LIBEXPORT int get_height_c(const char * filename);

LIBEXPORT int get_numbands_c(const char * filename);
