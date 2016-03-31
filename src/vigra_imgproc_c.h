#ifndef VIGRA_IMGPROC_C_H
#define VIGRA_IMGPROC_C_H

#include "config.h"

LIBEXPORT int vigra_resizeimage_c(const PixelType *arr, const PixelType *arr2, const  int width, const int height, const int width2, const int height2, const int resize_method);
LIBEXPORT int vigra_rotateimage_c( const PixelType *arr, const PixelType *arr2, const int width, const int height, const float angle, const int resize_method);
LIBEXPORT int vigra_affinewarpimage_c( const PixelType *arr, const float  *arr2, double *affineMatrix, const int width, const int height, const int resize_method);
LIBEXPORT int vigra_reflectimage_c(const PixelType *arr, const PixelType *arr2, const  int width, const  int height, const int reflect_method);
LIBEXPORT int vigra_fouriertransform_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width, const int height);
LIBEXPORT int vigra_fastcrosscorrelation_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width,const int height, const int mask_width, const int mask_height);
LIBEXPORT int vigra_fastnormalizedcrosscorrelation_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width,const int height, const int mask_width, const int mask_height);
LIBEXPORT int vigra_localmaxima_c(const PixelType *arr, const PixelType *arr2, const  int width, const  int height);
LIBEXPORT int vigra_localminima_c(const PixelType *arr, const PixelType *arr2, const  int width, const  int height);

#endif
