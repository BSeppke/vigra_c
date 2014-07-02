#include "os_settings.h"

LIBEXPORT int vigra_convolveimage_c(const float *arr, float *arr2, const double *kernel_arr,const int width,const  int height,const int kernel_width,const  int kernel_height);

LIBEXPORT int vigra_separableconvolveimage_c(const float *arr, float *arr2, const double *kernel_arr_h, const double *kernel_arr_v, const int width,const  int height,const int kernel_width,const  int kernel_height);

LIBEXPORT int vigra_gaussiangradient_c(const float *arr, const float *arr2, const float *arr3, const  int width,const  int height,const  float sigma);

LIBEXPORT int vigra_gaussiangradientmagnitude_c(const float *arr, const float *arr2,const  int width,const  int height,const  float sigma);

LIBEXPORT int vigra_gaussiansmoothing_c(const float *arr ,const float *arr2,const  int width,const  int height,const  float sigma);

LIBEXPORT int vigra_laplacianofgaussian_c(const float *arr, const float *arr2,const  int width,const int height,const  float scale);

LIBEXPORT int vigra_hessianmatrixofgaussian_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float scale);

LIBEXPORT int vigra_structuretensor_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float inner_scale, const float outer_scale);

LIBEXPORT int vigra_boundarytensor_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float scale);

LIBEXPORT int vigra_boundarytensor1_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float scale);

LIBEXPORT int vigra_gradientenergytensor_c(const float *arr, const double *arr_derivKernel, const double *arr_smoothKernel, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const int derivKernel_size, const int smoothKernel_size);

LIBEXPORT int vigra_tensoreigenrepresentation_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_lEV, const float *arr_sEV, const float *arr_ang, const int width, const int height);

LIBEXPORT int vigra_tensortrace_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_trace, const int width, const int height);

LIBEXPORT int vigra_tensortoedgecorner_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_edgeness, const float *arr_orientation, const float *arr_cornerness, const int width, const int height);

LIBEXPORT int vigra_hourglassfilter_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_hgxx, const float *arr_hgxy, const float *arr_hgyy, const int width, const int height, const float sigma, const float rho);

LIBEXPORT int vigra_gaussiansharpening_c(const float *arr, const float *arr2,const int width, const int height, const float sharpening_factor, const float scale);

LIBEXPORT int vigra_simplesharpening_c(const float *arr, const float *arr2, const int width, const int height, float sharpening_factor);

LIBEXPORT int vigra_nonlineardiffusion_c(const float *arr, const float *arr2, const int width, const int height, const float edge_threshold, const float scale);

LIBEXPORT int vigra_distancetransform_c(const float *arr, const float *arr2, const int width, const int height, const float background_label, const int norm);
