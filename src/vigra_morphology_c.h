#include "os_settings.h"

LIBEXPORT int vigra_discerosion_c(const float *arr, const float *arr2,const  int width,const  int height,const  int radius);

LIBEXPORT int vigra_discdilation_c(const float *arr, const float *arr2,const  int width,const  int height,const  int radius);

LIBEXPORT int vigraext_upwind_c(const float *arr, const float *arr2,  const float *arr3, const  int width,const  int height,const float weight);
