#ifndef VIGRA_IMPEX_C_H
#define VIGRA_IMPEX_C_H

#include "config.h"

LIBEXPORT int vigra_importgrayimage_c(const PixelType *arr_out, int width, int height, const char * filename);
LIBEXPORT int vigra_exportgrayimage_c(const PixelType *arr_in, int width, int height, const char * filename);
LIBEXPORT int vigra_importrgbimage_c(const PixelType *arr_r_out, const PixelType *arr_g_out, const PixelType *arr_b_out, int width, int height, const char * filename);
LIBEXPORT int vigra_exportrgbimage_c(const PixelType *arr_r_in, const PixelType *arr_g_in, const PixelType *arr_b_in, int width, int height, const char * filename);

LIBEXPORT int get_width_c(const char * filename);
LIBEXPORT int get_height_c(const char * filename);
LIBEXPORT int get_numbands_c(const char * filename);

#endif
