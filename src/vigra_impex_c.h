#ifndef VIGRA_IMPEX_C_H
#define VIGRA_IMPEX_C_H

#include "config.h"

LIBEXPORT int vigra_importgrayimage_c(PixelType *arr, int width, int height, const char * filename);
LIBEXPORT int vigra_exportgrayimage_c(const PixelType *arr, int width, int height, const char * filename);
LIBEXPORT int vigra_importrgbimage_c(PixelType *arr_r, PixelType *arr_g, PixelType *arr_b, int width, int height, const char * filename);
LIBEXPORT int vigra_exportrgbimage_c(const PixelType *arr_r, const PixelType *arr_g, const PixelType *arr_b, int width, int height, const char * filename);

LIBEXPORT int get_width_c(const char * filename);
LIBEXPORT int get_height_c(const char * filename);
LIBEXPORT int get_numbands_c(const char * filename);

#endif
