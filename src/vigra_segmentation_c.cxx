#include "vigra_segmentation_c.h"

#include <iostream> //Needed for <vigra/labelVolume.hxx>

#include <vigra/labelimage.hxx>
#include <vigra/watersheds.hxx>
#include <vigra/edgedetection.hxx>


LIBEXPORT int vigra_labelimage_c(const PixelType *arr,const  PixelType *arr2, const int width, int height)
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

LIBEXPORT int vigra_watersheds_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height)
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

LIBEXPORT int vigra_cannyedgeimage_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark)
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

LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark)
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

LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const PixelType *arr,const  PixelType *arr2, const  int width,const  int height, const float mark)
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
