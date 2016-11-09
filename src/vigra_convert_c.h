#ifndef VIGRA_CONVERT_C_H
#define VIGRA_CONVERT_C_H

#include "config.h"

LIBEXPORT int vigra_convert_grayband_to_argb_c(const PixelType *arr, char* argb_arr, const int width, const int height);
LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const PixelType *r_arr, const PixelType *g_arr, const PixelType *b_arr, char* argb_arr, const int width, const int height);
LIBEXPORT int vigra_convert_argb_to_grayband_c(const char* argb_arr, PixelType *arr, const int width, const int height);
LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const char* argb_arr, PixelType *r_arr, PixelType *g_arr, PixelType *b_arr, const int width, const int height);

LIBEXPORT int vigra_copy_double_array_c(const double* src, double *dest, const int length);
LIBEXPORT int vigra_copy_float_array_c(const float* src, float *dest, const int length);
LIBEXPORT int vigra_copy_int_array_c(const int* src, int *dest, const int length);
LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char* src, unsigned char *dest, const int length);

#endif
