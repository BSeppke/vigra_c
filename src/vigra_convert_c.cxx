#include "vigra_convert_c.h"
#include <cstring>

LIBEXPORT int vigra_convert_grayband_to_argb_c(const float *arr, char* argb_arr, const int width, const int height)
{ 
    const float* gray_ptr = arr;
    const float* gray_end = gray_ptr + (width*height);
    
    char* argb_ptr = argb_arr;
    
    for ( ; gray_ptr != gray_end; ++gray_ptr, argb_ptr+=4)
    {
        argb_ptr[0] = 255;
        argb_ptr[1] = (unsigned char)(*gray_ptr);
        argb_ptr[2] = (unsigned char)(*gray_ptr);
        argb_ptr[3] = (unsigned char)(*gray_ptr);
    }
    return 0;
}

LIBEXPORT int vigra_convert_rgbbands_to_argb_c(const float *r_arr, const float *g_arr, const float *b_arr, char* argb_arr, const int width, const int height)
{ 
    const float* r_ptr = r_arr;
    const float* g_ptr = g_arr;
    const float* b_ptr = b_arr;
    const float* r_end = r_ptr + (width*height);
    
    char* argb_ptr = argb_arr;
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, argb_ptr+=4)
    {
        argb_ptr[0] = 255;
        argb_ptr[1] = (unsigned char)(*r_ptr);
        argb_ptr[2] = (unsigned char)(*g_ptr);
        argb_ptr[3] = (unsigned char)(*b_ptr);
    }
    return 0;
}

LIBEXPORT int vigra_convert_argb_to_grayband_c(const char* argb_arr, float *arr, const int width, const int height)
{ 
    const char* argb_ptr = argb_arr;
    
    float* gray_ptr = arr;
    float* gray_end = gray_ptr + (width*height);
    
    
    for ( ; gray_ptr != gray_end; ++gray_ptr, argb_ptr+=4)
    {
        // since all bands are equal valued - we take the first one... 
        // argb_ptr[0] would be alpha!
        *gray_ptr = (float)argb_ptr[1];
    }
    return 0;
}

LIBEXPORT int vigra_convert_argb_to_rgbbands_c(const char* argb_arr, float *r_arr, float *g_arr, float *b_arr, const int width, const int height)
{ 
    const char* argb_ptr = argb_arr;
    
    float* r_ptr = r_arr;
    float* g_ptr = g_arr;
    float* b_ptr = b_arr;
    float* r_end = r_ptr + (width*height);
    
    
    for ( ; r_ptr != r_end ; ++r_ptr, ++g_ptr, ++b_ptr, argb_ptr+=4)
    {
        // argb_ptr[0] would be alpha!
        *r_ptr = argb_ptr[1];
        *g_ptr = argb_ptr[2];
        *b_ptr = argb_ptr[3];
    }
    return 0;
}



LIBEXPORT int vigra_copy_double_array_c(const double* src, double *dest, const int length)
{ 
    memcpy(dest,src,length*sizeof(double));
    return 0;
}

LIBEXPORT int vigra_copy_float_array_c(const float* src, float *dest, const int length)
{ 
    memcpy(dest,src,length*sizeof(float));
    return 0;
}

LIBEXPORT int vigra_copy_int_array_c(const int* src, int *dest, const int length)
{ 
    memcpy(dest,src,length*sizeof(int));
    return 0;
}

LIBEXPORT int vigra_copy_uint8_array_c(const unsigned char* src, unsigned char *dest, const int length)
{ 
    memcpy(dest,src,length*sizeof(unsigned char));
    return 0;
}