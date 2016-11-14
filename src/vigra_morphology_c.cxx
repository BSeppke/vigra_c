#include "vigra_morphology_c.h"

#include <vigra/flatmorphology.hxx>
#include <vigra/shockfilter.hxx>


LIBEXPORT int vigra_discerosion_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const int radius)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::MultiArray<2, unsigned char> b_img = img_in;
        vigra::discErosion(b_img, img_out, radius);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_discdilation_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const int radius)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::MultiArray<2, unsigned char> b_img = img_in;
        vigra::discDilation(b_img, img_out, radius);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigraext_upwind_c(const PixelType *arr_in, const PixelType *arr_fac_in, const PixelType *arr_out, const int width, const int height, const float weight)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_fac_in(shape, arr_fac_in);
        ImageView img_out(shape, arr_out);
        
        vigra::upwindImage(img_in, img_fac_in, img_out, weight);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}


