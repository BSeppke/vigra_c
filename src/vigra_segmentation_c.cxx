#include "vigra_segmentation_c.h"

#include <iostream> //Needed for <vigra/labelVolume.hxx>

#include <vigra/labelimage.hxx>
#include <vigra/watersheds.hxx>
#include <vigra/edgedetection.hxx>
#include <vigra/slic.hxx>
#include <vigra/colorconversions.hxx>


LIBEXPORT int vigra_labelimage_c(const PixelType *arr_in, const PixelType *arr_out, const int width, int height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        return vigra::labelImage(img_in, img_out, true);
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

LIBEXPORT int vigra_watersheds_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        return vigra::watershedsUnionFind(img_in, img_out);
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

LIBEXPORT int vigra_slic_gray_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const int seedDistance, const double intensityScaling, const int iterations)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        //We need to define a new array here to avoid abiguities inside the extractFeatures for (float, float)
        vigra::MultiArray<2, unsigned int> labels(shape);
        
        //int seedDistance = 15;
        //double intensityScaling = 20.0;
        
        // compute seeds automatically, perform 40 iterations, and scale intensity differences
        // down to 1/20 before comparing with spatial distances
        unsigned int count = vigra::slicSuperpixels(img_in, labels, intensityScaling, seedDistance, vigra::SlicOptions().iterations(iterations));
        
        img_out = labels;
        return count;
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

LIBEXPORT int vigra_slic_rgb_c(const PixelType *arr_r_in, const PixelType *arr_g_in, const PixelType *arr_b_in, const PixelType *arr_out, const int width, const int height, const int seedDistance, const double intensityScaling, const int iterations)
{
    try
    {
        //write the color channels from the different arrays
        vigra::Shape2 shape(width, height);
        ImageView img_red(shape, arr_r_in);
        ImageView img_green(shape, arr_g_in);
        ImageView img_blue(shape, arr_b_in);
        
        ImageView img_out(shape, arr_out);
        
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
        return vigra::slicSuperpixels(src, img_out, intensityScaling, seedDistance, vigra::SlicOptions().iterations(iterations));
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

LIBEXPORT int vigra_cannyedgeimage_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float scale, const float gradient_threshold, const float mark)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::cannyEdgeImage(img_in, img_out, scale, gradient_threshold, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float scale, const float gradient_threshold, const float mark)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::differenceOfExponentialEdgeImage(img_in, img_out, scale, gradient_threshold, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const PixelType *arr_in, const PixelType *arr_out, const int width_in, const int height_in, const float mark)
{
    try
    {
        vigra::Shape2 shape_in(width_in,height_in);
        ImageView img_in(shape_in, arr_in);
        vigra::Shape2 shape_out(2*width_in-1, 2*height_in-1);
        ImageView img_out(shape_out, arr_out);
        
        vigra::regionImageToCrackEdgeImage(img_in, img_out, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
