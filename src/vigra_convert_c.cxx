#include "vigra_convert_c.h"

#include <cstring>


/**
 * Converts a single band grayvalue image into its Alpha,RGB representation.
 * The greyavalue is therefore copied and casted to 0..255 into each R,B, and B
 * value and the alpha value is set to 255 (opaque). All arrays must have been
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
                                               const int height)
{
    const PixelType* gray_ptr = arr_in;
    const PixelType* gray_end = gray_ptr + (width*height);
    
    unsigned char* argb_ptr = (unsigned char*)argb_arr_out;
    
    for ( ; gray_ptr != gray_end; ++gray_ptr, argb_ptr+=4)
    {
        argb_ptr[0] = 255;
        argb_ptr[1] = *gray_ptr;
        argb_ptr[2] = *gray_ptr;
        argb_ptr[3] = *gray_ptr;
    }
    return 0;
}

/**
 * Converts the single band images (r,g,b) into its combined Alpha,RGB representation.
 * The r,g,b-vaues are therefore copied and casted to 0..255 into each R,B, and B
 * value and the alpha value is set to 255 (opaque). All arrays must have been
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
                                               const int height)
{
    const PixelType* r_ptr = r_arr_in;
    const PixelType* g_ptr = g_arr_in;
    const PixelType* b_ptr = b_arr_in;
    const PixelType* r_end = r_ptr + (width*height);
    
    unsigned char* argb_ptr = (unsigned char*)argb_arr_out;
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, argb_ptr+=4)
    {
        argb_ptr[0] = 255;
        argb_ptr[1] = *r_ptr;
        argb_ptr[2] = *g_ptr;
        argb_ptr[3] = *b_ptr;
    }
    return 0;
}

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
                                               const int height)
{
    const unsigned char* argb_ptr = (const unsigned char*)argb_arr_in;
    
    PixelType* gray_ptr = arr_out;
    PixelType* gray_end = gray_ptr + (width*height);
    
    
    for ( ; gray_ptr != gray_end; ++gray_ptr, argb_ptr+=4)
    {
        // since all bands are equal valued - we take the first one...
        // argb_ptr[0] would be alpha!
        *gray_ptr = (float)argb_ptr[1];
    }
    return 0;
}

/**
 * Converts the combined Alpha,RGB representation into its single band images (r,g,b).
 * The R,G,B-vaues are therefore copied and casted to float into each r,g, and b
 * output band and the alpha value is omitted. All arrays must have been
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
                                               const int height)
{
    const unsigned char* argb_ptr = (const unsigned char*)argb_arr_in;
    
    PixelType* r_ptr = r_arr_out;
    PixelType* g_ptr = g_arr_out;
    PixelType* b_ptr = b_arr_out;
    PixelType* r_end = r_ptr + (width*height);
    
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, argb_ptr+=4)
    {
        // argb_ptr[0] would be alpha!
        *r_ptr = (float)argb_ptr[1];
        *g_ptr = (float)argb_ptr[2];
        *b_ptr = (float)argb_ptr[3];
    }
    return 0;
}

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
                                        const int size)
{
    memcpy(arr_out,arr_in,size*sizeof(double));
    return 0;
}

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
                                       const int size)
{
    memcpy(arr_out,arr_in,size*sizeof(float));
    return 0;
}

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
                                     const int size)
{
    memcpy(arr_out,arr_in,size*sizeof(int));
    return 0;
}

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
                                       const int size)
{ 
    memcpy(arr_out,arr_in,size*sizeof(unsigned char));
    return 0;
}
