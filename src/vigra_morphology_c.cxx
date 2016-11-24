#include "vigra_morphology_c.h"

#include <vigra/flatmorphology.hxx>
#include <vigra/distancetransform.hxx>
#include <vigra/shockfilter.hxx>


LIBEXPORT int vigra_distancetransform_c(const PixelType * arr_in,
                                        const PixelType * arr_out,
                                        const int width,
                                        const int height,
                                        const float background_label,
                                        const int norm)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if(norm>=0 && norm <= 2)
            vigra::distanceTransform(img_in, img_out, background_label, norm);
        else
            return 2;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_discerosion_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const int radius)
{
    try
    {
        //Create gray scale image views for the arrays
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

LIBEXPORT int vigra_discdilation_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int radius)
{
    try
    {
        //Create gray scale image views for the arrays
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

LIBEXPORT int vigraext_upwind_c(const PixelType * arr_in,
                                const PixelType * arr_fac_in,
                                const PixelType * arr_out,
                                const int width,
                                const int height,
                                const float weight)
{
    try
    {
        //Create gray scale image views for the arrays
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


