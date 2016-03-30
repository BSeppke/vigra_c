#include "vigra_imgproc_c.h"

#include "vigra/resizeimage.hxx"
#include "vigra/affinegeometry.hxx"
#include "vigra/basicgeometry.hxx"
#include "vigra/multi_fft.hxx"


LIBEXPORT int vigra_resizeimage_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const int width2, const int height2, const int resize_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        vigra::Shape2 shape2(width2,height2);
        ImageView img(shape, arr);
        ImageView img2(shape2, arr);
      
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
		
		typedef vigra::MultiArrayView<2, double>::difference_type Shape;
		vigra::MultiArrayView<2, double> mat(Shape(3, 3) , affineMatrix);
        
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
