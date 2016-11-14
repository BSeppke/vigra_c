#ifndef VIGRA_CONVERT_C_H
#define VIGRA_CONVERT_C_H

#include "config.h"

LIBEXPORT int vigra_convert_grayband_to_argb_c(const PixelType *arr_in, char* argb_arr_out, const int width, const int height);
LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const PixelType *r_arr_in, const PixelType *g_arr_in, const PixelType *b_arr_in, char* argb_arr_out, const int width, const int height);
LIBEXPORT int vigra_convert_argb_to_grayband_c(const char *argb_arr_in, PixelType *arr_out, const int width, const int height);
LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const char *argb_arr_in, PixelType *r_arr_out, PixelType *g_arr_out, PixelType *b_arr_out, const int width, const int height);

LIBEXPORT int vigra_copy_double_array_c(const double *arr_in, double *arr_out, const int size);
LIBEXPORT int vigra_copy_float_array_c(const float *arr_in, float *arr_out, const int size);
LIBEXPORT int vigra_copy_int_array_c(const int *arr_in, int *arr_out, const int size);
LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char *arr_in, unsigned char *arr_out, const int size);

#endif
