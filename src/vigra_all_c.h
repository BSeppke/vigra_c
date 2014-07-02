//#include "vigra_impex_c.h"
#include "os_settings.h"

LIBEXPORT int vigra_importgrayimage_c(float *arr, int width, int height, const char * filename);
LIBEXPORT int vigra_exportgrayimage_c(const float *arr, int width, int height, const char * filename);
LIBEXPORT int vigra_importrgbimage_c(float *arr_r, float *arr_g, float *arr_b, int width, int height, const char * filename);
LIBEXPORT int vigra_exportrgbimage_c(const float *arr_r, const float *arr_g, const float *arr_b, int width, int height, const char * filename);
LIBEXPORT int get_width_c(const char * filename);
LIBEXPORT int get_height_c(const char * filename);
LIBEXPORT int get_numbands_c(const char * filename);

//#include "vigra_filters_c.h"
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

//#include "vigra_segmentation_c.h"
LIBEXPORT int vigra_labelimage_c(const float *arr,const  float *arr2, const int width, int height);
LIBEXPORT int vigra_watersheds_c(const float *arr,const  float *arr2, const  int width,const  int height);
LIBEXPORT int vigra_cannyedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark);
LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark);
LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float mark);

//#include "vigra_imgproc_c.h"
LIBEXPORT int vigra_resizeimage_c(const float *arr, const float *arr2, const  int width, const int height, const int width2, const int height2, const int resize_method);
LIBEXPORT int vigra_rotateimage_c( const float *arr, const float *arr2, const int width, const int height, const float angle, const int resize_method);
LIBEXPORT int vigra_affinewarpimage_c( const float *arr, const float  *arr2, double *affineMatrix, const int width, const int height, const int resize_method);
LIBEXPORT int vigra_reflectimage_c(const float *arr, const float *arr2, const  int width, const  int height, const int reflect_method);
LIBEXPORT int vigra_fouriertransform_c(const float *arr, const float *arr2, const float *arr3, const int width, const int height);

//#include "vigra_morphology_c.h"
LIBEXPORT int vigra_discerosion_c(const float *arr, const float *arr2,const  int width,const  int height,const  int radius);
LIBEXPORT int vigra_discdilation_c(const float *arr, const float *arr2,const  int width,const  int height,const  int radius);
LIBEXPORT int vigraext_upwind_c(const float *arr, const float *arr2,  const float *arr3, const  int width,const  int height,const float weight);

//#include "vigra_convert_c.h"
LIBEXPORT int vigra_convert_grayband_to_argb_c(const float *arr, unsigned char* argb_arr, const int width, const  int height);
LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const float *r_arr, const float *g_arr, const float *b_arr, unsigned char* argb_arr, const int width, const  int height);
LIBEXPORT int vigra_convert_argb_to_grayband_c(const unsigned char* argb_arr, float *arr, const int width, const  int height);
LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const unsigned char* argb_arr, float *r_arr, float *g_arr, float *b_arr, const int width, const  int height);
LIBEXPORT int vigra_copy_double_array_c(const double* src, double *dest, const int length);
LIBEXPORT int vigra_copy_float_array_c(const float* src, float *dest, const int length);
LIBEXPORT int vigra_copy_int_array_c(const int* src,  int *dest, const int length);
LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char* src, unsigned char *dest, const int length);

//#include "vigra_splineimageview_c.h"
#define SIV_CREATION_FUNCTION_SIGNATURE(splineDegree) \
LIBEXPORT void * vigra_create_splineimageview##splineDegree##_c (const float *arr, const int width, const int height);

SIV_CREATION_FUNCTION_SIGNATURE(1)
SIV_CREATION_FUNCTION_SIGNATURE(2)
SIV_CREATION_FUNCTION_SIGNATURE(3)
SIV_CREATION_FUNCTION_SIGNATURE(4)
SIV_CREATION_FUNCTION_SIGNATURE(5)


#define SIV_DELETION_FUNCTION_SIGNATURE(splineDegree) \
LIBEXPORT int vigra_delete_splineimageview##splineDegree##_c (void * siv);

SIV_DELETION_FUNCTION_SIGNATURE(1)
SIV_DELETION_FUNCTION_SIGNATURE(2)
SIV_DELETION_FUNCTION_SIGNATURE(3)
SIV_DELETION_FUNCTION_SIGNATURE(4)
SIV_DELETION_FUNCTION_SIGNATURE(5)



#define SIV_OPERATION_FUNCTION_SIGNATURE(function, splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_##function##_c (void * siv, double x, double y);

SIV_OPERATION_FUNCTION_SIGNATURE(dx,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dx,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dx,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dx,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dx,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dx3,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dx3,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dx3,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dx3,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dx3,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dxx,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dxx,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dxx,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dxx,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dxx,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dxxy,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dxxy,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dxxy,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dxxy,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dxxy,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dxy,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dxy,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dxy,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dxy,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dxy,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dxyy,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dxyy,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dxyy,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dxyy,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dxyy,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dy,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dy,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dy,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dy,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dy,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dy3,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dy3,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dy3,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dy3,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dy3,5)

SIV_OPERATION_FUNCTION_SIGNATURE(dyy,1)
SIV_OPERATION_FUNCTION_SIGNATURE(dyy,2)
SIV_OPERATION_FUNCTION_SIGNATURE(dyy,3)
SIV_OPERATION_FUNCTION_SIGNATURE(dyy,4)
SIV_OPERATION_FUNCTION_SIGNATURE(dyy,5)

SIV_OPERATION_FUNCTION_SIGNATURE(g2,1)
SIV_OPERATION_FUNCTION_SIGNATURE(g2,2)
SIV_OPERATION_FUNCTION_SIGNATURE(g2,3)
SIV_OPERATION_FUNCTION_SIGNATURE(g2,4)
SIV_OPERATION_FUNCTION_SIGNATURE(g2,5)

SIV_OPERATION_FUNCTION_SIGNATURE(g2x,1)
SIV_OPERATION_FUNCTION_SIGNATURE(g2x,2)
SIV_OPERATION_FUNCTION_SIGNATURE(g2x,3)
SIV_OPERATION_FUNCTION_SIGNATURE(g2x,4)
SIV_OPERATION_FUNCTION_SIGNATURE(g2x,5)

SIV_OPERATION_FUNCTION_SIGNATURE(g2xx,1)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xx,2)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xx,3)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xx,4)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xx,5)

SIV_OPERATION_FUNCTION_SIGNATURE(g2xy,1)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xy,2)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xy,3)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xy,4)
SIV_OPERATION_FUNCTION_SIGNATURE(g2xy,5)

SIV_OPERATION_FUNCTION_SIGNATURE(g2y,1)
SIV_OPERATION_FUNCTION_SIGNATURE(g2y,2)
SIV_OPERATION_FUNCTION_SIGNATURE(g2y,3)
SIV_OPERATION_FUNCTION_SIGNATURE(g2y,4)
SIV_OPERATION_FUNCTION_SIGNATURE(g2y,5)

SIV_OPERATION_FUNCTION_SIGNATURE(g2yy,1)
SIV_OPERATION_FUNCTION_SIGNATURE(g2yy,2)
SIV_OPERATION_FUNCTION_SIGNATURE(g2yy,3)
SIV_OPERATION_FUNCTION_SIGNATURE(g2yy,4)
SIV_OPERATION_FUNCTION_SIGNATURE(g2yy,5)


#define SIV_ACCESSOR_FUNCTION_SIGNATURE(splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_accessor_c(void * siv, double x, double y);

SIV_ACCESSOR_FUNCTION_SIGNATURE(1)
SIV_ACCESSOR_FUNCTION_SIGNATURE(2)
SIV_ACCESSOR_FUNCTION_SIGNATURE(3)
SIV_ACCESSOR_FUNCTION_SIGNATURE(4)
SIV_ACCESSOR_FUNCTION_SIGNATURE(5)



/************ ADDRESS BASED FUNCTIONS *****************/

#define SIV_ADDRESS_CREATION_FUNCTION_SIGNATURE(splineDegree) \
LIBEXPORT unsigned long vigra_create_splineimageview##splineDegree##_address_c (const float *arr, const int width, const int height);

SIV_ADDRESS_CREATION_FUNCTION_SIGNATURE(1)
SIV_ADDRESS_CREATION_FUNCTION_SIGNATURE(2)
SIV_ADDRESS_CREATION_FUNCTION_SIGNATURE(3)
SIV_ADDRESS_CREATION_FUNCTION_SIGNATURE(4)
SIV_ADDRESS_CREATION_FUNCTION_SIGNATURE(5)

#define SIV_DELETION_BY_ADDRESS_FUNCTION_SIGNATURE(splineDegree) \
LIBEXPORT int vigra_delete_splineimageview##splineDegree##_by_address_c (unsigned long address);

SIV_DELETION_BY_ADDRESS_FUNCTION_SIGNATURE(1)
SIV_DELETION_BY_ADDRESS_FUNCTION_SIGNATURE(2)
SIV_DELETION_BY_ADDRESS_FUNCTION_SIGNATURE(3)
SIV_DELETION_BY_ADDRESS_FUNCTION_SIGNATURE(4)
SIV_DELETION_BY_ADDRESS_FUNCTION_SIGNATURE(5)


#define SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(function, splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_##function##_by_address_c (unsigned long address, double x, double y);

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx3,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx3,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx3,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx3,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dx3,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxxy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxxy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxxy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxxy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxxy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxyy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxyy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxyy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxyy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dxyy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy3,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy3,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy3,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy3,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dy3,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dyy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dyy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dyy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dyy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(dyy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2x,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2x,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2x,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2x,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2x,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2xy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2y,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2y,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2y,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2y,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2y,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2yy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2yy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2yy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2yy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_SIGNATURE(g2yy,5)


#define SIV_ACCESSOR_BY_ADDRESS_FUNCTION_SIGNATURE(splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_accessor_by_address_c(unsigned long address, double x, double y);

SIV_ACCESSOR_BY_ADDRESS_FUNCTION_SIGNATURE(1)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_SIGNATURE(2)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_SIGNATURE(3)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_SIGNATURE(4)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_SIGNATURE(5)
