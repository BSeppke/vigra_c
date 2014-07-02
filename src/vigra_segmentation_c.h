#include "os_settings.h"

LIBEXPORT int vigra_labelimage_c(const float *arr,const  float *arr2, const int width, int height);

LIBEXPORT int vigra_watersheds_c(const float *arr,const  float *arr2, const  int width,const  int height);

LIBEXPORT int vigra_cannyedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark);

LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark);

LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float mark);