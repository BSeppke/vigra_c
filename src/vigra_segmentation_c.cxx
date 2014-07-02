#include "vigra_segmentation_c.h"

#include "vigra/basicimageview.hxx"
#include "vigra/labelimage.hxx"
#include <iostream> //needed for std::cerr inside vigra/labelVolume.hxx
#include "vigra/watersheds.hxx"
#include "vigra/edgedetection.hxx"
#include "vigra/configVersion.hxx"


LIBEXPORT int vigra_labelimage_c(const float *arr,const  float *arr2, const int width, int height)
{
    try
    {
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
      return vigra::labelImage(srcImageRange(img), destImage(img2), true);
       
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

LIBEXPORT int vigra_watersheds_c(const float *arr,const  float *arr2, const  int width,const  int height)
{
    try
    {
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
		
#if VIGRA_VERSION_MAJOR<2 && VIGRA_VERSION_MINOR<8
		return vigra::watersheds(srcImageRange(img), destImage(img2));
#else
		return vigra::watershedsUnionFind(srcImageRange(img), destImage(img2));
#endif       
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
}

LIBEXPORT int vigra_cannyedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark)
{
    try
    {
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
      vigra::cannyEdgeImage(srcImageRange(img), destImage(img2), scale, gradient_threshold, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float scale, const float gradient_threshold, const float mark)
{
    try
    {
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
      vigra::differenceOfExponentialEdgeImage(srcImageRange(img), destImage(img2), scale, gradient_threshold, mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const float *arr,const  float *arr2, const  int width,const  int height, const float mark)
{
    try
    {
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, 2*width-1, 2*height-1);    
	  vigra::regionImageToCrackEdgeImage(srcImageRange(img), destImage(img2), mark);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
