#include "os_settings.h"

LIBEXPORT int vigra_resizeimage_c(const float *arr, const float *arr2, const  int width, const int height, const int width2, const int height2, const int resize_method);

LIBEXPORT int vigra_rotateimage_c( const float *arr, const float *arr2, const int width, const int height, const float angle, const int resize_method);

LIBEXPORT int vigra_affinewarpimage_c( const float *arr, const float  *arr2, double *affineMatrix, const int width, const int height, const int resize_method);

LIBEXPORT int vigra_reflectimage_c(const float *arr, const float *arr2, const  int width, const  int height, const int reflect_method);

LIBEXPORT int vigra_fouriertransform_c(const float *arr, const float *arr2, const float *arr3, const int width, const int height);
