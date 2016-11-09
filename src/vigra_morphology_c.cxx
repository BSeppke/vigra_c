#include "vigra_morphology_c.h"

#include <vigra/flatmorphology.hxx>
#include <vigra/shockfilter.hxx>


LIBEXPORT int vigra_discerosion_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const int radius)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        vigra::MultiArray<2, unsigned char> b_img = img;
        vigra::discErosion(b_img, img2, radius);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_discdilation_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const int radius)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        vigra::MultiArray<2, unsigned char> b_img = img;
        vigra::discDilation(b_img, img2, radius);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigraext_upwind_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width, const int height, const float weight)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        ImageView img3(shape, arr3);
        
        vigra::upwindImage(img, img2, img3, weight);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}


