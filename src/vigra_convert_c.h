#include "os_settings.h"

LIBEXPORT int vigra_convert_grayband_to_argb_c(const float *arr, char* argb_arr, const int width, const  int height);

LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const float *r_arr, const float *g_arr, const float *b_arr, char* argb_arr, const int width, const  int height);

LIBEXPORT int vigra_convert_argb_to_grayband_c(const char* argb_arr, float *arr, const int width, const  int height);

LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const char* argb_arr, float *r_arr, float *g_arr, float *b_arr, const int width, const  int height);

LIBEXPORT int vigra_copy_double_array_c(const double* src, double *dest, const int length);

LIBEXPORT int vigra_copy_float_array_c(const float* src, float *dest, const int length);

LIBEXPORT int vigra_copy_int_array_c(const int* src,  int *dest, const int length);

LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char* src, unsigned char *dest, const int length);
