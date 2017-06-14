/************************************************************************/
/*                                                                      */
/*               Copyright 2008-2016 by Benjamin Seppke                 */
/*       Cognitive Systems Group, University of Hamburg, Germany        */
/*                                                                      */
/*    This file is part of VIGRA_C package. For more infos visit:       */
/*        https://github.com/bseppke/vigra_c                            */
/*    Please direct questions, bug reports, and contributions to        */
/*    the GitHub page and use the methods provided there.               */
/*                                                                      */
/*    Permission is hereby granted, free of charge, to any person       */
/*    obtaining a copy of this software and associated documentation    */
/*    files (the "Software"), to deal in the Software without           */
/*    restriction, including without limitation the rights to use,      */
/*    copy, modify, merge, publish, distribute, sublicense, and/or      */
/*    sell copies of the Software, and to permit persons to whom the    */
/*    Software is furnished to do so, subject to the following          */
/*    conditions:                                                       */
/*                                                                      */
/*    The above copyright notice and this permission notice shall be    */
/*    included in all copies or substantial portions of the             */
/*    Software.                                                         */
/*                                                                      */
/*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    */
/*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES   */
/*    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND          */
/*    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT       */
/*    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,      */
/*    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      */
/*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR     */
/*    OTHER DEALINGS IN THE SOFTWARE.                                   */
/*                                                                      */
/************************************************************************/

#ifndef VIGRA_CONVERT_C_H
#define VIGRA_CONVERT_C_H

#include "config.h"

/**
 * @file
 * @brief Header file for conversion functions
 *
 * @defgroup convert Conversion Functions
 * @{
 *    @brief Conversion functions between internal external image representations
 */
/************************************************************************/
/*                                                                      */
/*               Copyright 2008-2016 by Benjamin Seppke                 */
/*       Cognitive Systems Group, University of Hamburg, Germany        */
/*                                                                      */
/*    This file is part of VIGRA_C package. For more infos visit:       */
/*        https://github.com/bseppke/vigra_c                            */
/*    Please direct questions, bug reports, and contributions to        */
/*    the GitHub page and use the methods provided there.               */
/*                                                                      */
/*    Permission is hereby granted, free of charge, to any person       */
/*    obtaining a copy of this software and associated documentation    */
/*    files (the "Software"), to deal in the Software without           */
/*    restriction, including without limitation the rights to use,      */
/*    copy, modify, merge, publish, distribute, sublicense, and/or      */
/*    sell copies of the Software, and to permit persons to whom the    */
/*    Software is furnished to do so, subject to the following          */
/*    conditions:                                                       */
/*                                                                      */
/*    The above copyright notice and this permission notice shall be    */
/*    included in all copies or substantial portions of the             */
/*    Software.                                                         */
/*                                                                      */
/*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    */
/*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES   */
/*    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND          */
/*    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT       */
/*    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,      */
/*    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      */
/*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR     */
/*    OTHER DEALINGS IN THE SOFTWARE.                                   */
/*                                                                      */
/************************************************************************/

#include "vigra_convert_c.h"
#include <cstring>


/**
 * @file
 * @brief Implementation of image filters
 */
 
/**
 * Converts a single band grayvalue image into its Alpha,RGB representation.
 * The greyavalue is therefore copied and casted to 0..255 into each R,G, and B
 * value and the alpha value is set to 255 (opaque). All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_in Flat input array of size width*height.
 * \param[out] argb_arr_out Flat output array of size width*height*4.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successful, else uncought error.
 */
LIBEXPORT int vigra_convert_grayband_to_argb_c(const PixelType *arr_in,
                                               char * argb_arr_out,
                                               const int width,
                                               const int height);

/**
 * Converts the single band images (r,g,b) into its combined Alpha,RGB representation.
 * The r,g,b-vaues are therefore copied and casted to 0..255 into each R,G, and B
 * value and the alpha value is set to 255 (opaque). All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_r_in Flat input array (red band) of size width*height.
 * \param arr_g_in Flat input array (green band) of size width*height.
 * \param arr_b_in Flat input array (blue band) of size width*height.
 * \param[out] argb_arr_out Flat output array of size width*height*4.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successful, else uncought error.
 */
LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const PixelType * arr_r_in,
                                               const PixelType * arr_g_in,
                                               const PixelType * arr_b_in,
                                               char * argb_arr_out,
                                               const int width,
                                               const int height);

/**
 * Converts the single band images (r,g,b,a) into its combined Alpha,RGB representation.
 * The r,g,b,a-vaues are therefore copied and casted to 0..255 into each R,G,B, and A
 * value and the alpha value is set to 255 (opaque). All arrays must have been
 * allocated before the call of this function.
 *
 * \param arr_r_in Flat input array (red band) of size width*height.
 * \param arr_g_in Flat input array (green band) of size width*height.
 * \param arr_b_in Flat input array (blue band) of size width*height.
 * \param arr_a_in Flat input array (alpha band) of size width*height.
 * \param[out] argb_arr_out Flat output array of size width*height*4.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successful, else uncought error.
 */
LIBEXPORT int vigra_convert_rgbabands_to_argb_c(const PixelType * arr_r_in,
                                                const PixelType * arr_g_in,
                                                const PixelType * arr_b_in,
                                                const PixelType * arr_a_in,
                                                char * argb_arr_out,
                                                const int width,
                                                const int height);

/**
 * Converts the combined Alpha,RGB representation into its grayvalue band
 * Since this function shall only be called if all the R,G,B-vaues are equal,
 * we simply cast the values of the R-band to float, the alpha value is omitted.
 * All arrays must have been allocated before the call of this function.
 *
 * \param argb_arr_in Flat input array of size width*height*4.
 * \param[out] arr_out Flat output array of size width*height.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successful, else uncought error.
 */
LIBEXPORT int vigra_convert_argb_to_grayband_c(const char * argb_arr_in,
                                               PixelType * arr_out,
                                               const int width,
                                               const int height);

/**
 * Converts the combined Alpha,RGB representation into its single band images (r,g,b).
 * The R,G,B-vaues are therefore copied and casted to float into each r,g, and b
 * output band and the alpha value is omitted. All arrays must have been
 * allocated before the call of this function.
 *
 * \param argb_arr_in Flat input array of size width*height*4.
 * \param[out] arr_r_out Flat output array (red band) of size width*height.
 * \param[out] arr_g_out Flat output array (green band) of size  width*height.
 * \param[out] arr_b_out Flat output array (blue band) of size width*height.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successful, else uncought error.
 */
LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const char * argb_arr_in,
                                               PixelType * arr_r_out,
                                               PixelType * arr_g_out,
                                               PixelType * arr_b_out,
                                               const int width,
                                               const int height);

/**
 * Converts the combined Alpha,RGB representation into its single band images (r,g,b).
 * The R,G,B,A-vaues are therefore copied and casted to float into each r,g,b and a
 * output band and the alpha value is omitted. All arrays must have been
 * allocated before the call of this function.
 *
 * \param argb_arr_in Flat input array of size width*height*4.
 * \param[out] arr_r_out Flat output array (red band) of size width*height.
 * \param[out] arr_g_out Flat output array (green band) of size  width*height.
 * \param[out] arr_b_out Flat output array (blue band) of size width*height.
 * \param[out] arr_a_out Flat output array (alpha band) of size width*height.
 * \param width The width of the image.
 * \param height The height of the image.
 *
 * \return 0 if the conversion was successful, else uncought error.
 */
LIBEXPORT int vigra_convert_argb_to_rgbabands_c(const char * argb_arr_in,
                                               PixelType * arr_r_out,
                                               PixelType * arr_g_out,
                                               PixelType * arr_b_out,
                                               PixelType * arr_a_out,
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
 * \return 0 if the copying was successful, else uncought error.
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
 * \return 0 if the copying was successful, else uncought error.
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
 * \return 0 if the copying was successful, else uncought error.
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
 * \return 0 if the copying was successful, else uncought error.
 */
LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char * arr_in,
                                       unsigned char * arr_out,
                                       const int size);

/**
 * Fast flat array value initializing for double arrays. The arrays must have been
 * allocated before the call of this function. Works in-place!
 *
 * \param arr_io Flat input/output array of size size.
 * \param size The size of the array.
 * \param value The value for initialization.
 *
 * \return 0 if the initialization was successful, else uncought error.
 */
LIBEXPORT int vigra_init_double_array_c(double * arr_io,
                                        const int size,
                                        double value);

/**
 * Fast flat array value initializing for float arrays. The arrays must have been
 * allocated before the call of this function. Works in-place!
 *
 * \param arr_io Flat input/output array of size size.
 * \param size The size of the array.
 * \param value The value for initialization.
 *
 * \return 0 if the initialization was successful, else uncought error.
 */
LIBEXPORT int vigra_init_float_array_c(float * arr_io,
                                       const int size,
                                       float value);

/**
 * Fast flat array value initializing for int arrays. The arrays must have been
 * allocated before the call of this function. Works in-place!
 *
 * \param arr_io Flat input/output array of size size.
 * \param size The size of the array.
 * \param value The value for initialization.
 *
 * \return 0 if the initialization was successful, else uncought error.
 */
LIBEXPORT int vigra_init_int_array_c(int * arr_io,
                                     const int size,
                                     int value);

/**
 * Fast flat array value initializing for unsigned char arrays. The arrays must have been
 * allocated before the call of this function. Works in-place!
 *
 * \param arr_io Flat input/output array of size size.
 * \param size The size of the array.
 * \param value The value for initialization.
 *
 * \return 0 if the initialization was successful, else uncought error.
 */
LIBEXPORT int vigra_init_uint8_array_c(unsigned char * arr_io,
                                       const int size,
                                       unsigned char value);

/**
 * @}
 */
#endif
