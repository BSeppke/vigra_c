#ifndef VIGRA_MORPHOLOGY_C_H
#define VIGRA_MORPHOLOGY_C_H

#include "config.h"

LIBEXPORT int vigra_discerosion_c(const PixelType *arr, const PixelType *arr2,const  int width,const  int height,const  int radius);
LIBEXPORT int vigra_discdilation_c(const PixelType *arr, const PixelType *arr2,const  int width,const  int height,const  int radius);

LIBEXPORT int vigraext_upwind_c(const PixelType *arr, const PixelType *arr2,  const PixelType *arr3, const  int width,const  int height,const float weight);

#endif
