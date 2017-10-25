/************************************************************************/
/*                                                                      */
/*               Copyright 2008-2017 by Benjamin Seppke                 */
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
#include <algorithm>


/**
 * @file
 * @brief Implementation of image filters
 */

LIBEXPORT int vigra_convert_grayband_to_argb_c(const PixelType *arr_in,
                                               char * argb_arr_out,
                                               const int width,
                                               const int height)
{
    const PixelType* gray_ptr = arr_in;
    const PixelType* gray_end = gray_ptr + (width*height);
    
    unsigned char* argb_ptr = (unsigned char*)argb_arr_out;
    
    for ( ; gray_ptr != gray_end; ++gray_ptr, argb_ptr+=4)
    {
        argb_ptr[0] = 255;
        argb_ptr[1] = vigra::max(vigra::min(*gray_ptr, 255.0f), 0.0f);
        argb_ptr[2] = argb_ptr[1];
        argb_ptr[3] = argb_ptr[1];
    }
    return 0;
}

LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const PixelType * arr_r_in,
                                               const PixelType * arr_g_in,
                                               const PixelType * arr_b_in,
                                               char * argb_arr_out,
                                               const int width,
                                               const int height)
{
    const PixelType* r_ptr = arr_r_in;
    const PixelType* g_ptr = arr_g_in;
    const PixelType* b_ptr = arr_b_in;
    const PixelType* r_end = r_ptr + (width*height);
    
    unsigned char* argb_ptr = (unsigned char*)argb_arr_out;
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, argb_ptr+=4)
    {
        argb_ptr[0] = 255;
        argb_ptr[1] = vigra::max(vigra::min(*r_ptr, 255.0f), 0.0f);
        argb_ptr[2] = vigra::max(vigra::min(*g_ptr, 255.0f), 0.0f);
        argb_ptr[3] = vigra::max(vigra::min(*b_ptr, 255.0f), 0.0f);
    }
    return 0;
}

LIBEXPORT int vigra_convert_rgbabands_to_argb_c(const PixelType * arr_r_in,
                                                const PixelType * arr_g_in,
                                                const PixelType * arr_b_in,
                                                const PixelType * arr_a_in,
                                                char * argb_arr_out,
                                                const int width,
                                                const int height)
{
    const PixelType* r_ptr = arr_r_in;
    const PixelType* g_ptr = arr_g_in;
    const PixelType* b_ptr = arr_b_in;
    const PixelType* a_ptr = arr_a_in;
    const PixelType* r_end = r_ptr + (width*height);
    
    unsigned char* argb_ptr = (unsigned char*)argb_arr_out;
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, ++a_ptr, argb_ptr+=4)
    {
        argb_ptr[0] = vigra::max(vigra::min(*a_ptr, 255.0f), 0.0f);
        argb_ptr[1] = vigra::max(vigra::min(*r_ptr, 255.0f), 0.0f);
        argb_ptr[2] = vigra::max(vigra::min(*g_ptr, 255.0f), 0.0f);
        argb_ptr[3] = vigra::max(vigra::min(*b_ptr, 255.0f), 0.0f);
    }
    return 0;
}

LIBEXPORT int vigra_convert_argb_to_grayband_c(const char * argb_arr_in,
                                               PixelType * arr_out,
                                               const int width,
                                               const int height)
{
    const unsigned char* argb_ptr = (const unsigned char*)argb_arr_in;
    
    PixelType* gray_ptr = arr_out;
    PixelType* gray_end = gray_ptr + (width*height);
    
    
    for ( ; gray_ptr != gray_end; ++gray_ptr, argb_ptr+=4)
    {
        // since all bands are equal valued - we take the first one...
        // argb_ptr[0] would be alpha!
        *gray_ptr = (PixelType)argb_ptr[1];
    }
    return 0;
}

LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const char * argb_arr_in,
                                               PixelType * arr_r_out,
                                               PixelType * arr_g_out,
                                               PixelType * arr_b_out,
                                               const int width,
                                               const int height)
{
    const unsigned char* argb_ptr = (const unsigned char*)argb_arr_in;
    
    PixelType* r_ptr = arr_r_out;
    PixelType* g_ptr = arr_g_out;
    PixelType* b_ptr = arr_b_out;
    PixelType* r_end = r_ptr + (width*height);
    
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, argb_ptr+=4)
    {
        // argb_ptr[0] would be alpha!
        *r_ptr = (PixelType)argb_ptr[1];
        *g_ptr = (PixelType)argb_ptr[2];
        *b_ptr = (PixelType)argb_ptr[3];
    }
    return 0;
}

LIBEXPORT int vigra_convert_argb_to_rgbabands_c(const char * argb_arr_in,
                                               PixelType * arr_r_out,
                                               PixelType * arr_g_out,
                                               PixelType * arr_b_out,
                                               PixelType * arr_a_out,
                                               const int width,
                                               const int height)
{
    const unsigned char* argb_ptr = (const unsigned char*)argb_arr_in;
    
    PixelType* r_ptr = arr_r_out;
    PixelType* g_ptr = arr_g_out;
    PixelType* b_ptr = arr_b_out;
    PixelType* a_ptr = arr_a_out;
    PixelType* r_end = r_ptr + (width*height);
    
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, ++a_ptr, argb_ptr+=4)
    {
        *a_ptr = (PixelType)argb_ptr[0];
        *r_ptr = (PixelType)argb_ptr[1];
        *g_ptr = (PixelType)argb_ptr[2];
        *b_ptr = (PixelType)argb_ptr[3];
    }
    return 0;
}

LIBEXPORT int vigra_copy_double_array_c(const double * arr_in,
                                        double * arr_out,
                                        const int size)
{
    memcpy(arr_out,arr_in,size*sizeof(double));
    return 0;
}

LIBEXPORT int vigra_copy_float_array_c(const float * arr_in,
                                       float * arr_out,
                                       const int size)
{
    memcpy(arr_out,arr_in,size*sizeof(float));
    return 0;
}

LIBEXPORT int vigra_copy_int_array_c(const int * arr_in,
                                     int * arr_out,
                                     const int size)
{
    memcpy(arr_out,arr_in,size*sizeof(int));
    return 0;
}

LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char * arr_in,
                                       unsigned char * arr_out,
                                       const int size)
{ 
    memcpy(arr_out,arr_in,size*sizeof(unsigned char));
    return 0;
}

LIBEXPORT int vigra_init_double_array_c(double * arr_io,
                                        const int size,
                                        double value)
{
    std::fill(arr_io, arr_io+size, value);
    return 0;
}

LIBEXPORT int vigra_init_float_array_c(float * arr_io,
                                       const int size,
                                       float value)
{
    std::fill(arr_io, arr_io+size, value);
    return 0;
}

LIBEXPORT int vigra_init_int_array_c(int * arr_io,
                                     const int size,
                                     int value)
{
    std::fill(arr_io, arr_io+size, value);
    return 0;
}

LIBEXPORT int vigra_init_uint8_array_c(unsigned char * arr_io,
                                       const int size,
                                       unsigned char value)
{ 
    std::fill(arr_io, arr_io+size, value);
    return 0;
}
