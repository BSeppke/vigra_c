#ifndef VIGRA_CONVERT_C_H
#define VIGRA_CONVERT_C_H

#include "config.h"
/**
 * Converts a single band grayvalue image into its Alpha,RGB representation.
 * The greyavalue is therefore copied and casted to 0..255 into each R,B, and B
 * value and the alpha value is set to 255 (opaque).All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_in Flat input array of size width*height.
 * \param[out] argb_arr_out Flat output array of size width*height*4.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successfull, else uncatched error.
 */
LIBEXPORT int vigra_convert_grayband_to_argb_c(const PixelType *arr_in,
                                               char * argb_arr_out,
                                               const int width,
                                               const int height);

/**
 * Converts the single band images (r,g,b) into its combined Alpha,RGB representation.
 * The r,g,b-vaues are therefore copied and casted to 0..255 into each R,B, and B
 * value and the alpha value is set to 255 (opaque).All arrays must have been
 * allocated before the call of this function.
 *
 * \param r_arr_in Flat input array (red band) of size width*height.
 * \param g_arr_in Flat input array (green band) of size width*height.
 * \param b_arr_in Flat input array (blue band) of size width*height.
 * \param[out] argb_arr_out Flat output array of size width*height*4.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successfull, else uncatched error.
 */
LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const float * r_arr_in,
                                               const float * g_arr_in,
                                               const float * b_arr_in,
                                               char * argb_arr_out,
                                               const int width,
                                               const int height);

/**
 * Converts the combined Alpha,RGB representation into its grayvalue band
 * Since this function shall only be called if all the R,G,B-vaues are equal,
 * we simply cast the values of the R-band to float, the alpha value is omitted.
 * All arrays must have been allocated before the call of this function.
 *
 * \param argb_arr_in Flat input arrayof  size width*height*4.
 * \param[out] arr_out Flat output array of size width*height.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successfull, else uncatched error.
 */
LIBEXPORT int vigra_convert_argb_to_grayband_c(const char * argb_arr_in,
                                               PixelType * arr_out,
                                               const int width,
                                               const int height);

/**
 * Converts the combined Alpha,RGB representation into its single band images (r,g,b).
 * The R,G,B-vaues are therefore copied and casted to float into each r,g, and b
 * output band and the alpha value is omitted.All arrays must have been
 * allocated before the call of this function.
 *
 * \param argb_arr_in Flat input array of size width*height*4.
 * \param[out] r_arr_out Flat output array (red band) of size width*height.
 * \param[out] g_arr_out Flat output array (green band) of size  width*height.
 * \param[out] b_arr_out Flat output array (blue band) of size width*height.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successfull, else uncatched error.
 */
LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const char * argb_arr_in,
                                               float * r_arr_out,
                                               float * g_arr_out,
                                               float * b_arr_out,
                                               const int width,
                                               const int height);

/**
 * Fast flat array value copying for double arrays. All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_in Flat input array of size size.
 * \param arr_out Flat output array of size size.
 * \param size The size of both arrays.
 *
 * \return 0 if the copying was successfull, else uncatched error.
 */
LIBEXPORT int vigra_copy_double_array_c(const double * arr_in,
                                        double * arr_out,
                                        const int size);

/**
 * Fast flat array value copying for (single) float arrays. All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_in Flat input array of size size.
 * \param arr_out Flat output array of size size.
 * \param size The size of both arrays.
 *
 * \return 0 if the copying was successfull, else uncatched error.
 */
LIBEXPORT int vigra_copy_float_array_c(const float * arr_in,
                                       float * arr_out,
                                       const int size);

/**
 * Fast flat array value copying for integer arrays. All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_in Flat input array of size size.
 * \param arr_out Flat output array of size size.
 * \param size The size of both arrays.
 *
 * \return 0 if the copying was successfull, else uncatched error.
 */
LIBEXPORT int vigra_copy_int_array_c(const int * arr_in,
                                     int * arr_out,
                                     const int size);

/**
 * Fast flat array value copying for unsigned char arrays. All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_in Flat input array of size size.
 * \param arr_out Flat output array of size size.
 * \param size The size of both arrays.
 *
 * \return 0 if the copying was successfull, else uncatched error.
 */
LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char * arr_in,
                                       unsigned char * arr_out,
                                       const int size);
                                       
#endif
