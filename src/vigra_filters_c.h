#ifndef VIGRA_FILTERS_C_H
#define VIGRA_FILTERS_C_H

#include "config.h"

LIBEXPORT int vigra_convolveimage_c(const PixelType *arr_in, const PixelType *arr_out, const double *kernel_arr_in, const int width_in, const int height_in, const int kernel_width_in, const int kernel_height_in);
LIBEXPORT int vigra_separableconvolveimage_c(const PixelType *arr_in, const PixelType *arr_out, const double *kernel_arr_h, const double *kernel_arr_v, const int width_in, const int height_in, const int kernel_width_in, const int kernel_height_in);
LIBEXPORT int vigra_gaussiangradient_c(const PixelType *arr_in, const PixelType *arr_out, const PixelType *arr3, const int width_in, const int height_in, const float sigma);
LIBEXPORT int vigra_gaussiangradientmagnitude_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, const float sigma);
LIBEXPORT int vigra_gaussiansmoothing_c(const PixelType *arr , const PixelType *arr_out, const int width_in, const int height_in, const float sigma);
LIBEXPORT int vigra_laplacianofgaussian_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, const float scale);
LIBEXPORT int vigra_hessianmatrixofgaussian_c(const PixelType *arr_in, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width_in, const int height_in, const float scale);
LIBEXPORT int vigra_structuretensor_c(const PixelType *arr_in, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width_in, const int height_in, const float inner_scale, const float outer_scale);
LIBEXPORT int vigra_boundarytensor_c(const PixelType *arr_in, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width_in, const int height_in, const float scale);
LIBEXPORT int vigra_boundarytensor1_c(const PixelType *arr_in, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width_in, const int height_in, const float scale);
LIBEXPORT int vigra_gradientenergytensor_c(const PixelType *arr_in, const double *arr_derivKernel, const double *arr_smoothKernel, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width_in, const int height_in, const int derivKernel_size, const int smoothKernel_size);
LIBEXPORT int vigra_tensoreigenrepresentation_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_lEV, const PixelType *arr_sEV, const PixelType *arr_ang, const int width_in, const int height_in);
LIBEXPORT int vigra_tensortrace_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_trace, const int width_in, const int height_in);
LIBEXPORT int vigra_tensortoedgecorner_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_edgeness, const PixelType *arr_orientation, const PixelType *arr_cornerness, const int width_in, const int height_in);
LIBEXPORT int vigra_hourglassfilter_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_hgxx, const PixelType *arr_hgxy, const PixelType *arr_hgyy, const int width_in, const int height_in, const float sigma, const float rho);
LIBEXPORT int vigra_gaussiansharpening_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, const float sharpening_factor, const float scale);
LIBEXPORT int vigra_simplesharpening_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, float sharpening_factor);
LIBEXPORT int vigra_nonlineardiffusion_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, const float edge_threshold, const float scale);
LIBEXPORT int vigra_distancetransform_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, const float background_label, const int norm);
LIBEXPORT int vigra_shockfilter_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, const float sigma, const float rho, const float upwind_factor_h, const int iterations);

#endif
