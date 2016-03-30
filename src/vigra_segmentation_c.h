#ifndef VIGRA_SEGMENTATION_C_H
#define VIGRA_SEGMENTATION_C_H

#include "config.h"

LIBEXPORT int vigra_labelimage_c(const PixelType *arr,const  PixelType *arr2, const int width, int height);
LIBEXPORT int vigra_watersheds_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height);
LIBEXPORT int vigra_cannyedgeimage_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark);
LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark);
LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height, const float mark);

#endif
