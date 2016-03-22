#include "vigra_imgproc_c.h"

#include "vigra/resizeimage.hxx"
#include "vigra/affinegeometry.hxx"
#include "vigra/basicgeometry.hxx"
#include "vigra/fftw3.hxx"

LIBEXPORT int vigra_resizeimage_c(const float *arr, const float *arr2, const int width, const int height, const int width2, const int height2, const int resize_method)
{
    try
    {
      // create a gray scale image of appropriate size
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width2, height2);
      
      switch(resize_method){
        case 4:
            vigra::resizeImageSplineInterpolation(srcImageRange(img),destImageRange(img2),vigra::BSpline<4, float>());
            break;
        case 3:
            vigra::resizeImageSplineInterpolation(srcImageRange(img),destImageRange(img2),vigra::BSpline<3, float>());
            break;
        case 2:
            vigra::resizeImageSplineInterpolation(srcImageRange(img),destImageRange(img2),vigra::BSpline<2, float>());
            break;
        case 1:
            vigra::resizeImageLinearInterpolation(srcImageRange(img),destImageRange(img2));
            break;
        case 0:
            vigra::resizeImageNoInterpolation(srcImageRange(img),destImageRange(img2));
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

LIBEXPORT int vigra_rotateimage_c( const float *arr, const float *arr2, const int width, const int height, const float angle, const int resize_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::BasicImageView<float> img(arr, width, height);
        vigra::BasicImageView<float> img2(arr2, width, height);
        
        if (resize_method == 4){
            vigra::SplineImageView<4, float> spline4(srcImageRange(img));
            vigra::rotateImage(spline4, destImage(img2), angle);
        }
        else if (resize_method == 3){
            vigra::SplineImageView<3, float> spline3(srcImageRange(img));
            vigra::rotateImage(spline3, destImage(img2), angle);
        }
        else if (resize_method == 2){
            vigra::SplineImageView<2, float> spline2(srcImageRange(img));
            vigra::rotateImage(spline2, destImage(img2), angle);
        }
        else if (resize_method == 1){
            vigra::SplineImageView<1, float> spline1(srcImageRange(img));
            vigra::rotateImage(spline1, destImage(img2), angle);
        }
        else if (resize_method == 0){
            vigra::SplineImageView<0, float> spline0(srcImageRange(img));
            vigra::rotateImage(spline0, destImage(img2), angle);
	}
        else {        
            return 2;
	}
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_affinewarpimage_c( const float *arr, const float *arr2, double *affineMatrix, const int width, const  int height, const int resize_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::BasicImageView<float> img(arr, width, height);
        vigra::BasicImageView<float> img2(arr2, width, height);
		
		typedef vigra::MultiArrayView<2, double>::difference_type Shape;
		vigra::MultiArrayView<2, double> mat(Shape(3, 3) , affineMatrix);
        
        if (resize_method == 4){
            vigra::SplineImageView<4, float> spline4(srcImageRange(img));
            vigra::affineWarpImage(spline4, destImageRange(img2), mat);
        }
        else if (resize_method == 3){
            vigra::SplineImageView<3, float> spline3(srcImageRange(img));
            vigra::affineWarpImage(spline3, destImageRange(img2), mat);
        }
        else if (resize_method == 2){
            vigra::SplineImageView<2, float> spline2(srcImageRange(img));
            vigra::affineWarpImage(spline2, destImageRange(img2), mat);
        }
        else if (resize_method == 1){
            vigra::SplineImageView<1, float> spline1(srcImageRange(img));
            vigra::affineWarpImage(spline1, destImageRange(img2), mat);
        }
        else if (resize_method == 0){
            vigra::SplineImageView<0, float> spline0(srcImageRange(img));
            vigra::affineWarpImage(spline0, destImageRange(img2), mat);
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


LIBEXPORT int vigra_reflectimage_c(const float *arr, const float *arr2, const int width, const int height, const int reflect_method)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::BasicImageView<float> img(arr, width, height);
        vigra::BasicImageView<float> img2(arr2, width, height);
        
        if(reflect_method>=1 && reflect_method <=3){
            vigra::reflectImage(srcImageRange(img), destImage(img2), static_cast<vigra::Reflect>(reflect_method));
        }
        else
            return 2;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_fouriertransform_c(const float *arr, const float *arr2, const float *arr3, const int width, const int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::BasicImageView<float> img(arr, width, height);
        vigra::BasicImageView<float> img2(arr2, width, height);
        vigra::BasicImageView<float> img3(arr3, width, height);

        vigra::FFTWComplexImage fourier(width, height), 
        						rearrangedFourier(width, height);
        	
        vigra::fourierTransform(srcImageRange(img), destImage(fourier));
        moveDCToCenter(srcImageRange(fourier), destImage(rearrangedFourier));
        vigra::copyImage(srcImageRange(rearrangedFourier, vigra::FFTWRealAccessor<double>()), destImage(img2));
        vigra::copyImage(srcImageRange(rearrangedFourier, vigra::FFTWImaginaryAccessor<double>()), destImage(img3));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
