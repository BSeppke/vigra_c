#include "vigra_imgproc_c.h"

#include <iostream>

#include <vigra/resizeimage.hxx>
#include <vigra/affinegeometry.hxx>
#include <vigra/basicgeometry.hxx>
#include <vigra/multi_fft.hxx>
#include <vigra/correlation.hxx>
#include <vigra/multi_localminmax.hxx>


LIBEXPORT int vigra_resizeimage_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const int width2, const int height2, const int resize_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        vigra::Shape2 shape2(width2,height2);
        ImageView img(shape, arr);
        ImageView img2(shape2, arr2);
      
        switch(resize_method)
        {
            case 4:
                vigra::resizeImageSplineInterpolation(img, img2, vigra::BSpline<4, float>());
                break;
            case 3:
                vigra::resizeImageSplineInterpolation(img, img2, vigra::BSpline<3, float>());
                break;
            case 2:
                vigra::resizeImageSplineInterpolation(img, img2, vigra::BSpline<2, float>());
                break;
            case 1:
                vigra::resizeImageLinearInterpolation(img, img2);
                break;
            case 0:
                vigra::resizeImageNoInterpolation(img, img2);
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

LIBEXPORT int vigra_rotateimage_c( const PixelType *arr, const PixelType *arr2, const int width, const int height, const float angle, const int resize_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        if (resize_method == 4)
        {
            vigra::SplineImageView<4, float> spline4(img);
            vigra::rotateImage(spline4, img2, angle);
        }
        else if (resize_method == 3)
        {
            vigra::SplineImageView<3, float> spline3(img);
            vigra::rotateImage(spline3, img2, angle);
        }
        else if (resize_method == 2)
        {
            vigra::SplineImageView<2, float> spline2(img);
            vigra::rotateImage(spline2, img2, angle);
        }
        else if (resize_method == 1)
        {
            vigra::SplineImageView<1, float> spline1(img);
            vigra::rotateImage(spline1, img2, angle);
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_affinewarpimage_c( const PixelType *arr, const PixelType *arr2, double *affineMatrix, const int width, const  int height, const int resize_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
		
		vigra::MultiArrayView<2, double, vigra::UnstridedArrayTag> mat(vigra::Shape2(3, 3) , affineMatrix);
        
        if (resize_method == 4)
        {
            vigra::SplineImageView<4, float> spline4(img);
            vigra::affineWarpImage(spline4, img2, mat);
        }
        else if (resize_method == 3)
        {
            vigra::SplineImageView<3, float> spline3(img);
            vigra::affineWarpImage(spline3, img2, mat);
        }
        else if (resize_method == 2)
        {
            vigra::SplineImageView<2, float> spline2(img);
            vigra::affineWarpImage(spline2, img2, mat);
        }
        else if (resize_method == 1)
        {
            vigra::SplineImageView<1, float> spline1(img);
            vigra::affineWarpImage(spline1, img2, mat);
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


LIBEXPORT int vigra_reflectimage_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const int reflect_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        if(reflect_method>=1 && reflect_method <=3)
        {
            vigra::reflectImage(img, img2, static_cast<vigra::Reflect>(reflect_method));
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

LIBEXPORT int vigra_fouriertransform_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width, const int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        ImageView img3(shape, arr3);
        vigra::MultiArray<2, vigra::FFTWComplex<PixelType> > fourier(shape);
        	
        vigra::fourierTransform(img, fourier);
        moveDCToCenter(fourier);
        
        auto i2_iter = img2.begin(),
             i3_iter = img3.begin();
        
        for(auto f_iter= fourier.begin(); f_iter != fourier.end(); ++f_iter, ++i2_iter, ++i3_iter)
        {
            *i2_iter = f_iter->real();
            *i3_iter = f_iter->imag();
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}


LIBEXPORT int vigra_fastcrosscorrelation_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width, const int height, const int mask_width, const int mask_height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        vigra::Shape2 mask_shape(mask_width, mask_height);
        ImageView mask(mask_shape, arr2);
        ImageView corr(shape, arr3);
        
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

LIBEXPORT int vigra_fastnormalizedcrosscorrelation_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width,const int height, const int mask_width, const int mask_height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        
        //only allow odd masks (because results are in center coords)
        if( mask_width % 2 == 0 || mask_height %2 == 0)
        {
            return 2;
        }
        
        vigra::Shape2 mask_shape(mask_width, mask_height);
        ImageView mask(mask_shape, arr2);
        ImageView corr(shape, arr3);
        
	    vigra::fastNormalizedCrossCorrelation(img, mask, corr);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}


LIBEXPORT int vigra_localmaxima_c(const PixelType *arr, const PixelType *arr2, const  int width, const  int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        vigra::localMaxima(img, img2);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_localminima_c(const PixelType *arr, const PixelType *arr2, const  int width, const  int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        vigra::localMinima(img, img2);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_subimage_c(const PixelType *arr, const PixelType *arr2, const  int width, const int height,  const  int left, const int upper,  const  int right, const int lower)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        
        int cut_w = right - left,
            cut_h = lower - upper;
        
        //Check for cuttof measures
        if(cut_w > 0 && cut_w <= width && cut_h > 0 && cut_h <= height)
        {
            vigra::Shape2 cut_shape(cut_w,cut_h);
            ImageView cut_img(cut_shape, arr2);
            
            cut_img = img.subarray(vigra::Shape2(left, upper), vigra::Shape2(right, lower));
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
LIBEXPORT int vigra_paddimage_c(const PixelType *arr, const PixelType *arr2, const  int width, const int height,  const  int left, const int upper,  const  int right, const int lower)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        
        int padd_w = right + left  + width,
            padd_h = lower + upper + height;
        
        //Check for padding measures
        if(padd_w >= width && padd_h >= height)
        {
            vigra::Shape2 padd_shape(padd_w, padd_h);
            ImageView padd_img(padd_shape, arr2);
            
            padd_img.subarray(vigra::Shape2(left, upper), vigra::Shape2(left+width, upper+height)) = img;
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
