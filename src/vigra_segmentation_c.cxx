#include "vigra_segmentation_c.h"

#include <iostream> //Needed for <vigra/labelVolume.hxx>

#include <vigra/labelimage.hxx>
#include <vigra/watersheds.hxx>
#include <vigra/edgedetection.hxx>
#include <vigra/slic.hxx>
#include <vigra/colorconversions.hxx>


LIBEXPORT int vigra_labelimage_c(const PixelType *arr, const PixelType *arr2, const int width, int height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        return vigra::labelImage(img, img2, true);
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

LIBEXPORT int vigra_watersheds_c(const PixelType *arr, const PixelType *arr2, const int width, const int height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        return vigra::watershedsUnionFind(img, img2);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
}

LIBEXPORT int vigra_slic_gray_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const int seedDistance, const double intensityScaling, const int iterations)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        //We need to define a new array here to avoid abiguities inside the extractFeatures for (float, float)
        vigra::MultiArray<2, unsigned int> labels(shape);
        
        //int seedDistance = 15;
        //double intensityScaling = 20.0;
        
        // compute seeds automatically, perform 40 iterations, and scale intensity differences
        // down to 1/20 before comparing with spatial distances
        unsigned int count = vigra::slicSuperpixels(img, labels, intensityScaling, seedDistance, vigra::SlicOptions().iterations(iterations));
        
        img2 = labels;
        return count;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
}

LIBEXPORT int vigra_slic_rgb_c(const PixelType *arr_r, const PixelType *arr_g, const PixelType *arr_b, const PixelType *arr2, const int width, const int height, const int seedDistance, const double intensityScaling, const int iterations)
{
    try
    {
        //write the color channels from the different arrays
        vigra::Shape2 shape(width,height);
        ImageView img_red(shape, arr_r);
        ImageView img_green(shape, arr_g);
        ImageView img_blue(shape, arr_b);
        
        ImageView img2(shape, arr2);
        
        vigra::MultiArray<2, vigra::RGBValue<float> > src(shape);
        // fill src image
        src.bindElementChannel(0) = img_red;
        src.bindElementChannel(1) = img_green;
        src.bindElementChannel(2) = img_blue;
        
        // transform image to Lab color space
        vigra::transformMultiArray(srcMultiArrayRange(src), destMultiArray(src), vigra::RGBPrime2LabFunctor<float>() );
        
        //int seedDistance = 15;
        //double intensityScaling = 20.0;
        
        // compute seeds automatically, perform 40 iterations, and scale intensity differences
        // down to 1/20 before comparing with spatial distances
        return vigra::slicSuperpixels(src, img2, intensityScaling, seedDistance, vigra::SlicOptions().iterations(iterations));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
}

LIBEXPORT int vigra_cannyedgeimage_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const float scale, const float gradient_threshold, const float mark)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        vigra::cannyEdgeImage(img, img2, scale, gradient_threshold, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const float scale, const float gradient_threshold, const float mark)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
        
        vigra::differenceOfExponentialEdgeImage(img, img2, scale, gradient_threshold, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const float mark)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        vigra::Shape2 shape2(2*width-1, 2*height-1);
        ImageView img2(shape2, arr2);
        
        vigra::regionImageToCrackEdgeImage(img, img2, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
