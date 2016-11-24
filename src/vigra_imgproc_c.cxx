#include "vigra_imgproc_c.h"

#include <iostream>

#include <vigra/resizeimage.hxx>
#include <vigra/affinegeometry.hxx>
#include <vigra/basicgeometry.hxx>
#include <vigra/multi_fft.hxx>
#include <vigra/correlation.hxx>
#include <vigra/multi_localminmax.hxx>


LIBEXPORT int vigra_resizeimage_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width_in,
                                  const int height_in,
                                  const int width_out,
                                  const int height_out,
                                  const int resample_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape_in(width_in,height_in);
        vigra::Shape2 shape_out(width_out,height_out);
        ImageView img_in(shape_in, arr_in);
        ImageView img_out(shape_out, arr_out);
        
        switch(resample_method)
        {
            case 4:
                vigra::resizeImageSplineInterpolation(img_in, img_out, vigra::BSpline<4, float>());
                break;
            case 3:
                vigra::resizeImageSplineInterpolation(img_in, img_out, vigra::BSpline<3, float>());
                break;
            case 2:
                vigra::resizeImageSplineInterpolation(img_in, img_out, vigra::BSpline<2, float>());
                break;
            case 1:
                vigra::resizeImageLinearInterpolation(img_in, img_out);
                break;
            case 0:
                vigra::resizeImageNoInterpolation(img_in, img_out);
                break;
            default:
                return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_rotateimage_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const float angle,
                                  const int resample_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if (resample_method == 4)
        {
            vigra::SplineImageView<4, float> spline4(img_in);
            vigra::rotateImage(spline4, img_out, angle);
        }
        else if (resample_method == 3)
        {
            vigra::SplineImageView<3, float> spline3(img_in);
            vigra::rotateImage(spline3, img_out, angle);
        }
        else if (resample_method == 2)
        {
            vigra::SplineImageView<2, float> spline2(img_in);
            vigra::rotateImage(spline2, img_out, angle);
        }
        else if (resample_method == 1)
        {
            vigra::SplineImageView<1, float> spline1(img_in);
            vigra::rotateImage(spline1, img_out, angle);
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_affinewarpimage_c(const PixelType * arr_in,
                                      const PixelType * arr_out,
                                      double * affineMatrix,
                                      const int width,
                                      const int height,
                                      const int resample_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::MultiArrayView<2, double, vigra::UnstridedArrayTag> mat(vigra::Shape2(3, 3), affineMatrix);
        
        if (resample_method == 4)
        {
            vigra::SplineImageView<4, float> spline4(img_in);
            vigra::affineWarpImage(spline4, img_out, mat);
        }
        else if (resample_method == 3)
        {
            vigra::SplineImageView<3, float> spline3(img_in);
            vigra::affineWarpImage(spline3, img_out, mat);
        }
        else if (resample_method == 2)
        {
            vigra::SplineImageView<2, float> spline2(img_in);
            vigra::affineWarpImage(spline2, img_out, mat);
        }
        else if (resample_method == 1)
        {
            vigra::SplineImageView<1, float> spline1(img_in);
            vigra::affineWarpImage(spline1, img_out, mat);
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}


LIBEXPORT int vigra_reflectimage_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int reflect_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if(reflect_method>=1 && reflect_method <=3)
        {
            vigra::reflectImage(img_in, img_out,
                                static_cast<vigra::Reflect>(reflect_method));
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_fouriertransform_c(const PixelType * arr_in,
                                       const PixelType * arr_real_out,
                                       const PixelType * arr_imag_out,
                                       const int width,
                                       const int height)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img(shape, arr_in);
        ImageView img_real(shape, arr_real_out);
        ImageView img_imag(shape, arr_imag_out);
        vigra::MultiArray<2, vigra::FFTWComplex<PixelType> > fourier(shape);
        
        vigra::fourierTransform(img, fourier);
        moveDCToCenter(fourier);
        
        auto img_real_iter = img_real.begin(),
             img_imag_iter = img_imag.begin();
        
        for(auto f_iter= fourier.begin();
            f_iter != fourier.end();
            ++f_iter, ++img_real_iter, ++img_imag_iter)
        {
            *img_real_iter = f_iter->real();
            *img_imag_iter = f_iter->imag();
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}


LIBEXPORT int vigra_fastcrosscorrelation_c(const PixelType * arr_in,
                                           const PixelType * arr_mask_in,
                                           const PixelType * arr_out,
                                           const int width,
                                           const int height,
                                           const int mask_width,
                                           const int mask_height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr_in);
        vigra::Shape2 mask_shape(mask_width, mask_height);
        ImageView mask(mask_shape, arr_mask_in);
        ImageView corr(shape, arr_out);
        
        //only allow odd masks (because results are in center coords)
        if( mask_width % 2 == 0 || mask_height %2 == 0)
        {
            return 2;
        }
        
        vigra::fastCrossCorrelation(img, mask, corr);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_fastnormalizedcrosscorrelation_c(const PixelType * arr_in,
                                                     const PixelType * arr_mask_in,
                                                     const PixelType * arr_out,
                                                     const int width,
                                                     const int height,
                                                     const int mask_width,
                                                     const int mask_height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr_in);
        
        //only allow odd masks (because results are in center coords)
        if( mask_width % 2 == 0 || mask_height %2 == 0)
        {
            return 2;
        }
        
        vigra::Shape2 mask_shape(mask_width, mask_height);
        ImageView mask(mask_shape, arr_mask_in);
        ImageView corr(shape, arr_out);
        
        vigra::fastNormalizedCrossCorrelation(img, mask, corr);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}


LIBEXPORT int vigra_localmaxima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::localMaxima(img_in, img_out);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_localminima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::localMinima(img_in, img_out);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_subimage_c(const PixelType * arr_in,
                               const PixelType * arr_out,
                               const int width_in,
                               const int height_in,
                               const int left,
                               const int upper,
                               const int right,
                               const int lower)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape_in(width_in,height_in);
        ImageView img(shape_in, arr_in);
        
        int cut_w = right - left,
            cut_h = lower - upper;
        
        //Check for cuttof measures
        if(cut_w > 0 && cut_w <= width_in && cut_h > 0 && cut_h <= height_in)
        {
            vigra::Shape2 cut_shape_in(cut_w,cut_h);
            ImageView cut_img(cut_shape_in, arr_out);
            
            cut_img = img.subarray(vigra::Shape2(left, upper),
                                   vigra::Shape2(right, lower));
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_paddimage_c(const PixelType * arr_in,
                                const PixelType * arr_out,
                                const int width_in,
                                const int height_in,
                                const int left,
                                const int upper,
                                const int right,
                                const int lower)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape_in(width_in,height_in);
        ImageView img(shape_in, arr_in);
        
        int padd_w = right + left + width_in,
        padd_h = lower + upper + height_in;
        
        //Check for padding measures
        if(padd_w >= width_in && padd_h >= height_in)
        {
            vigra::Shape2 padd_shape_in(padd_w, padd_h);
            ImageView padd_img(padd_shape_in, arr_out);
            
            padd_img.subarray(vigra::Shape2(left, upper),
                              vigra::Shape2(left+width_in, upper+height_in)) = img;
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}
