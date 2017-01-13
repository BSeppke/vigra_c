/************************************************************************/
/*                                                                      */
/*               Copyright 2008-2016 by Benjamin Seppke                 */
/*       Cognitive Systems Group, University of Hamburg, Germany        */
/*                                                                      */
/*    This file is part of VIGRA_C package. For more infos visit:       */
/*        https://github.com/bseppke/vigra_c                            */
/*    Please direct questions, bug reports, and contributions to        */
/*    the GitHub page and use the methods provided there.               */
/*                                                                      */
/*    Permission is hereby granted, free of charge, to any person       */
/*    obtaining a copy of this software and associated documentation    */
/*    files (the "Software"), to deal in the Software without           */
/*    restriction, including without limitation the rights to use,      */
/*    copy, modify, merge, publish, distribute, sublicense, and/or      */
/*    sell copies of the Software, and to permit persons to whom the    */
/*    Software is furnished to do so, subject to the following          */
/*    conditions:                                                       */
/*                                                                      */
/*    The above copyright notice and this permission notice shall be    */
/*    included in all copies or substantial portions of the             */
/*    Software.                                                         */
/*                                                                      */
/*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    */
/*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES   */
/*    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND          */
/*    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT       */
/*    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,      */
/*    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      */
/*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR     */
/*    OTHER DEALINGS IN THE SOFTWARE.                                   */
/*                                                                      */
/************************************************************************/

#include "vigra_segmentation_c.h"
#include <iostream> //needed by labelVolume, which is needed by localMinMax
#include <vigra/labelimage.hxx>
#include <vigra/watersheds.hxx>
#include <vigra/edgedetection.hxx>
#include <vigra/accumulator.hxx>
#include <vigra/slic.hxx>
#include <vigra/colorconversions.hxx>


/**
 * @file
 * @brief Implementation of segmentation algorithms
 */

/**
 * Labels the connected components of an image band.
 * This function wraps the 
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Labeling.html">
 * vigra::labelImage
 * </a>
 * function to C to carry out a union-find algorithm. This finds the and sets 
 * unique labels for the connected components of same grayvalues in the given image.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (labels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 *
 * \return If the labelling was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_labelimage_c(const PixelType * arr_in,
                                 const PixelType * arr_out,
                                 const int width,
                                 const int height,
                                 const bool eight_connectivity)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        return vigra::labelImage(img_in, img_out, eight_connectivity);
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

/**
 * Labels the connected components of an image band w.r.t. a background intensity,
 * which should not be considered by the lageling.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Labeling.html">
 * vigra::labelImageWithBackground
 * </a>
 * function to C to carry out a union-find algorithm. This finds the and sets 
 * unique labels for the connected components of same grayvalues in the given image.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (labels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 * \param background Intensity value of the background. Will not be counted as
 *        any label and will get label-id 0 at the final result.
 *
 * \return If the labelling was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_labelimagewithbackground_c(const PixelType * arr_in,
                                               const PixelType * arr_out,
                                               const int width,
                                               const int height,
                                               const bool eight_connectivity,
                                               const PixelType background)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        return vigra::labelImageWithBackground(img_in, img_out, eight_connectivity, background);
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

/**
 * Applies the Watershed Transform to an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Superpixels.html">
 * vigra::watershedsUnionFind
 * </a> 
 * function to C to carry out a union-find watershed segmentation algorithm. 
 * This first segments the image and then finds the and sets unique labels for the
 * connected components of same grayvalues in the given image. Use e.g. the result
 * of vigra_gradientmagnitude_c as an input for this function, since the watersheds
 * of the gradient are good candidates for region boundaries.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (labels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 *
 * \return If the segmentation was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_watershedsunionfind_c(const PixelType * arr_in,
                                          const PixelType * arr_out,
                                          const int width,
                                          const int height,
                                          const bool eight_connectivity)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if(eight_connectivity)
        {
            return vigra::watershedsUnionFind(img_in, img_out, vigra::EightNeighborCode());
        }
        else
        {
            return vigra::watershedsUnionFind(img_in, img_out, vigra::FourNeighborCode());
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

/**
 * Applies the Watershed Transform to an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Superpixels.html">
 * vigra::watershedsRegionGrowing
 * </a> 
 * function to C to carry out a union-find watershed segmentation algorithm. 
 * This first segments the image and then finds the and sets unique labels for the
 * connected components of same grayvalues in the given image. Use e.g. the result
 * of vigra_gradientmagnitude_c as an input for this function, since the watersheds
 * of the gradient are good candidates for region boundaries.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param arr_inout Flat array of the seeds (in) of size width*height. 
                    Will contain the labels after processing.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 * \param keep_contours Keep the watersheds' contours in the resulting images.
 * \param use_turbo Normalize costs to 0..255 and use turbo algorithm for fast queue ordering.
 * \param stop_cost Stop the region growing if a cost is >= the given value. 
 *                  This will only be considered if the given value is >= 0.
 *
 * \return If the segmentation was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_watershedsregiongrowing_c(const PixelType * arr_in,
                                              const PixelType * arr_inout,
                                              const int width,
                                              const int height,
                                              const bool eight_connectivity,
                                              const bool keep_contours,
                                              const bool use_turbo,
                                              const double stop_cost)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_inout(shape, arr_inout);
        
        vigra::WatershedOptions options;
        
        if(keep_contours)
        {
            options = options.keepContours();
        }
        
        if(use_turbo)
        {
            options = options.turboAlgorithm(256);
            
            // quantize the gradient image to 256 gray levels
            vigra::MultiArray<2, unsigned char> img_in256(width, height);
            vigra::FindMinMax<float> minmax;
            vigra::inspectImage(img_in, minmax); // find original range
            vigra::transformImage(img_in, img_in256,
                                    linearRangeMapping(minmax, 0, 255));
            
            //Adapt the stop costs to 0..255, too.
            if(stop_cost>0)
            {
                options = options.stopAtThreshold(255.0*(stop_cost-minmax.min)/(minmax.max-minmax.min));
            }
            
            // call the turbo algorithm with 256 bins:
            if(eight_connectivity)
            {
                return vigra::watershedsRegionGrowing(img_in256, img_inout,
                            vigra::EightNeighborCode(),
                            options);
            }
            else
            {
                return vigra::watershedsRegionGrowing(img_in256, img_inout,
                            vigra::FourNeighborCode(),
                            options);
            }
        }
        else
        {
        
            if(stop_cost>0)
            {
                options = options.stopAtThreshold(stop_cost);
            }
            
            if(eight_connectivity)
            {
                return vigra::watershedsRegionGrowing(img_in, img_inout,
                            vigra::EightNeighborCode(),
                            options);
            }
            else
            {
                return vigra::watershedsRegionGrowing(img_in, img_inout,
                            vigra::FourNeighborCode(),
                            options);
            }
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

/**
 * Applies the SLIC segmenation to an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Superpixels.html">
 * vigra::slicSuperpixels
 * </a> 
 * function to C to carry out a SLIC segmentation algorithm. This first segments
 * the image and then finds the and sets unique labels for the connected components
 * of same grayvalues in the given image.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (labels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param seedDistance The initial distance between each seed.
 * \param intensityScaling How to scale the intensity down before comparing with spatial distances.
 * \param iterations The count of iterations.
 *
 * \return If the segmentation was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_slic_gray_c(const PixelType * arr_in,
                                const PixelType * arr_out,
                                const int width,
                                const int height,
                                const int seedDistance,
                                const double intensityScaling,
                                const int iterations)
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

/**
 * Applies the SLIC segmenation to an RGB image.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Superpixels.html">
 * vigra::slicSuperpixels
 * </a> 
 * function to C to carry out a SLIC segmentation algorithm on three single image
 * bands, refering to the RGB-bands. This first segments the image and then finds
 * the and sets unique labels for the connected components of same grayvalues in
 * the given image.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_r_in Flat input array (red band) of size width*height.
 * \param arr_g_in Flat input array (green band) of size width*height.
 * \param arr_b_in Flat input array (blue band) of size width*height.
 * \param[out] arr_out Flat array (labels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param seedDistance The initial distance between each seed.
 * \param intensityScaling How to scale the intensity down before comparing with spatial distances.
 * \param iterations The count of iterations.
 *
 * \return If the segmentation was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_slic_rgb_c(const PixelType * arr_r_in,
                               const PixelType * arr_g_in,
                               const PixelType * arr_b_in,
                               const PixelType * arr_out,
                               const int width,
                               const int height,
                               const int seedDistance,
                               const double intensityScaling,
                               const int iterations)
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
        vigra::transformMultiArray(srcMultiArrayRange(src), destMultiArray(src),
                                   vigra::RGBPrime2LabFunctor<float>());
        
        //int seedDistance = 15;
        //double intensityScaling = 20.0;
        
        // compute seeds automatically, perform 40 iterations, and scale intensity differences
        // down to 1/20 before comparing with spatial distances
        return vigra::slicSuperpixels(src, img_out, intensityScaling, seedDistance,
                                      vigra::SlicOptions().iterations(iterations));
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

/**
 * Computation of the Canny Edge Detector.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__EdgeDetection.html">
 * vigra::cannyEdgeImage
 * </a> 
 * function to C to compute the Canny edgels at a given scale (Gaussian std.dev.)
 * and using an edge (gradient) threshold to mark all edgels on the given input 
 * band with a certain grayvalue. The intensity of all other pixels in the result
 * remain 0.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (marked edgels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param scale The scale for which the gradient shall be computed.
 * \param gradient_threshold The minimum edge threshold.
 * \param mark The intensity for marking the edges in the resulting band.
 *
 * \return 0 if the computation was successful, 1 else.
 */
LIBEXPORT int vigra_cannyedgeimage_c(const PixelType * arr_in,
                                     const PixelType * arr_out,
                                     const int width,
                                     const int height,
                                     const float scale,
                                     const float gradient_threshold,
                                     const float mark)
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

/**
 * Computation of the Difference of Exponential (DoE) Edge Detector.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__EdgeDetection.html">
 * vigra::differenceOfExponentialEdgeImage
 * </a> 
 * function to C to compute the DoE edgels at a given scale (Gaussian std.dev.)
 * and using an edge (gradient) threshold to mark all edgels on the given input 
 * band with a certain grayvalue. The intensity of all other pixels in the 
 * result remain 0.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (marked edgels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param scale The scale for which the gradient shall be computed.
 * \param gradient_threshold The minimum edge threshold.
 * \param mark The intensity for marking the edges in the resulting band.
 *
 * \return 0 if the computation was successful, 1 else.
 */
LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const PixelType * arr_in,
                                                       const PixelType * arr_out,
                                                       const int width,
                                                       const int height,
                                                       const float scale,
                                                       const float gradient_threshold,
                                                       const float mark)
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

/**
 * Transforms a label image band into its crack-edge representation.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Labeling.html">
 * vigra::regionImageToCrackEdgeImage
 * </a> 
 * function to C to transform a label image band into a (nearly 4x) as large 
 * image band, which shows the boundaries between labels/regions by a given mark
 * intensity. The size of the output band has to be (2*width_in-1)*(2*height_in-1)
 * for an input label band of size width_in*height_in. 
 * All arrays must have been allocated with correct sizes before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width_in*height_in.
 * \param[out] arr_out Flat array (crack-edges) of size (2*width_in-1)*(2*height_in-1).
 * \param width_in The width of the flat array.
 * \param height_in The height of the flat array.
 * \param mark The intensity for marking the crack-edges in the resulting band.
 *
 * \return 0 if the crackedge image generation was successful, 1 else.
 */
LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const PixelType * arr_in,
                                                  const PixelType * arr_out,
                                                  const int width_in,
                                                  const int height_in,
                                                  const float mark)
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

/**
 * Extracts features from a given label image band w.r.t. its corresponding
 * grey value intensity band. This function internally maps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/namespacevigra_1_1acc.html">
 * vigra::extractFeatures
 * </a> function to estimate the basic features in a region-wise manner.
 * The following features will be extracted for each region:
 * 
 *  | Index         | Feature                       |
 *  | ------------- | ----------------------------- |
 *  |  0            | region_size                   |
 *  |  1,  2        | upperleft-x and y-coord       |
 *  |  3,  4        | lowerright-x and y-coord      |
 *  |  5,  6        | mean-x and y-coord            |
 *  |  7            | min grey value                |
 *  |  8            | max grey value                |
 *  |  9            | mean grey value               |
 *  | 10            | std.dev. grey value           |
 *
 * Each feature can be accessed in the output array by means of its index and 
 * region id by: output(index, region_id). Please make sure, that the output is 
 * allocated of size 11x(max_label+1).
 *
 * \param arr_gray_in Flat input array (band) of size width_in*height_in.
 * \param arr_labels_in Flat input array (labels) of size width_in*height_in.
 * \param[out] arr_out Flat array (results) of size 11*(max_label+1).
 * \param width_in The width of the flat array.
 * \param height_in The width of the flat array.
 * \param max_label The maximum region label to derive statistics for.
 *
 * \return 0 if the feature extraction was successful, 1 else.
 */
LIBEXPORT int vigra_extractfeatures_gray_c(const PixelType * arr_gray_in,
                                           const PixelType * arr_labels_in,
                                           const PixelType * arr_out,
                                           const int width_in,
                                           const int height_in,
                                           const int max_label)
{
    using namespace vigra::acc;
    
    try
    {
        vigra::Shape2 shape_in(width_in,height_in);
        
        ImageView img_in(shape_in, arr_gray_in);
        ImageView labels_in(shape_in, arr_labels_in);
        
        //temp copy to int-type array
        vigra::MultiArray<2, unsigned int> labels = labels_in;
        
        //Order (x,y) with y = region_id (from 0...max_label) and:
        // x=0    -> region_size,
        // x=(1..2) -> upperleft-x and y-coord
        // x=(3..4) -> lowerright-x and y-coord
        // x=(5..6) -> mean-x and y-coord
        // x=7      -> min grey value
        // x=8      -> max grey value
        // x=9      -> mean grey value
        // x=10     -> std.dev. grey value
        vigra::Shape2 shape_out(11, max_label+1);
        ImageView img_out(shape_out, arr_out);
        
        typedef
            AccumulatorChainArray<vigra::CoupledArrays<2, PixelType, unsigned int>,
                Select< DataArg<1>, LabelArg<2>, // in which array to look (coordinates are always arg 0)
                        Count,
                        Coord<Minimum>, Coord<Maximum>, Coord<Mean>,
                        Minimum, Maximum, Mean, StdDev > >
            AccumulatorType;
        
        AccumulatorType a;
        
        extractFeatures(img_in, labels, a);

        for(unsigned int i=0; i!=max_label+1; ++i)
        {
            img_out(0, i) = get<Count>(a,i);
            
            img_out(1, i) = get<Coord<Minimum>>(a,i)[0];
            img_out(2, i) = get<Coord<Minimum>>(a,i)[1];
            
            img_out(3, i) = get<Coord<Maximum>>(a,i)[0];
            img_out(4, i) = get<Coord<Maximum>>(a,i)[1];
            
            img_out(5, i) = get<Coord<Mean>>(a,i)[0];
            img_out(6, i) = get<Coord<Mean>>(a,i)[1];
            
            img_out(7, i) = get<Minimum>(a,i);
            img_out(8, i) = get<Maximum>(a,i);
            img_out(9, i) = get<Mean>(a,i);
            img_out(10,i) = get<StdDev>(a,i);
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

/**
 * Extracts features from a given label image band w.r.t. its corresponding
 * rgb value intensity bands. This function internally maps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/namespacevigra_1_1acc.html">
 * vigra::extractFeatures
 * </a> 
 * function to estimate the basic features in a region-wise manner. 
 * The following features will be extracted for each region:
 * 
 *  | Index         | Feature                       |
 *  | ------------- | ----------------------------- |
 *  |  0            | region_size                   |
 *  |  1,  2        | upperleft-x and y-coord       |
 *  |  3,  4        | lowerright-x and y-coord      |
 *  |  5,  6        | mean-x and y-coord            |
 *  |  7,  8,  9    | min red,green,blue value      |
 *  | 10, 11, 12    | max red,green,blue value      |
 *  | 13, 14, 15    | mean red,green,blue value     |
 *  | 16, 17, 18    | std.dev. red,green,blue value |
 *
 * Each feature can be accessed in the output array by means of its index and 
 * region id by: output(index, region_id). Please make sure, that the output is 
 * allocated of size 19x(max_label+1).
 *
 * \param arr_r_in Flat input array (red band) of size width_in*height_in.
 * \param arr_g_in Flat input array (green band) of size width_in*height_in.
 * \param arr_b_in Flat input array (blue band) of size width_in*height_in.
 * \param arr_labels_in Flat input array (labels) of size width_in*height_in.
 * \param[out] arr_out Flat array (results) of size 19*(max_label+1).
 * \param width_in The width of the flat array.
 * \param height_in The height of the flat array.
 * \param max_label The maximum region label to derive statistics for.
 *
 * \return 0 if the feature extraction was successful, 1 else.
 */
LIBEXPORT int vigra_extractfeatures_rgb_c( const PixelType * arr_r_in,
                                           const PixelType * arr_g_in,
                                           const PixelType * arr_b_in,
                                           const PixelType * arr_labels_in,
                                           const PixelType * arr_out,
                                           const int width_in,
                                           const int height_in,
                                           const int max_label)
{
    using namespace vigra::acc;
    
    try
    {
        //write the color channels from the different arrays
        vigra::Shape2 shape_in(width_in, height_in);
        ImageView img_red(shape_in, arr_r_in);
        ImageView img_green(shape_in, arr_g_in);
        ImageView img_blue(shape_in, arr_b_in);
        
        vigra::MultiArray<2, vigra::RGBValue<float> > src(shape_in);
        // fill src image
        src.bindElementChannel(0) = img_red;
        src.bindElementChannel(1) = img_green;
        src.bindElementChannel(2) = img_blue;
        
        ImageView labels_in(shape_in, arr_labels_in);
        
        //temp copy to int-type array
        vigra::MultiArray<2, unsigned int> labels = labels_in;
        
        //Order (x,y) with y = region_id (from 0...max_label) and:
        // x=0          -> region_size,
        // x=( 1 ..  2) -> upperleft-x and y-coord
        // x=( 3 ..  4) -> lowerright-x and y-coord
        // x=( 5 ..  6) -> mean-x and y-coord
        // x=( 7 ..  9) -> min r,g,b value
        // x=(10 .. 12) -> max r,g,b value
        // x=(13 .. 15) -> mean r,g,b value
        // x=(16 .. 18) -> stddev r,g,b value
        vigra::Shape2 shape_out(19, max_label+1);
        ImageView img_out(shape_out, arr_out);
        
        typedef
            AccumulatorChainArray<vigra::CoupledArrays<2, vigra::RGBValue<float>, unsigned int>,
                Select< DataArg<1>, LabelArg<2>, // in which array to look (coordinates are always arg 0)
                        Count,
                        Coord<Minimum>, Coord<Maximum>, Coord<Mean>,
                        Minimum, Maximum, Mean, StdDev > >
            AccumulatorType;
        
        AccumulatorType a;
        
        extractFeatures(src, labels, a);

        for(unsigned int i=0; i!=max_label+1; ++i)
        {
            img_out( 0, i) = get<Count>(a,i);
            
            img_out( 1, i) = get<Coord<Minimum>>(a,i)[0];
            img_out( 2, i) = get<Coord<Minimum>>(a,i)[1];
            
            img_out( 3, i) = get<Coord<Maximum>>(a,i)[0];
            img_out( 4, i) = get<Coord<Maximum>>(a,i)[1];
            
            img_out( 5, i) = get<Coord<Mean>>(a,i)[0];
            img_out( 6, i) = get<Coord<Mean>>(a,i)[1];
            
            img_out( 7, i) = get<Minimum>(a,i)[0];
            img_out( 8, i) = get<Minimum>(a,i)[1];
            img_out( 9, i) = get<Minimum>(a,i)[2];
            
            img_out(10, i) = get<Maximum>(a,i)[0];
            img_out(11, i) = get<Maximum>(a,i)[1];
            img_out(12, i) = get<Maximum>(a,i)[2];
            
            img_out(13, i) = get<Mean>(a,i)[0];
            img_out(14, i) = get<Mean>(a,i)[1];
            img_out(15, i) = get<Mean>(a,i)[2];
            
            img_out(16, i) = get<StdDev>(a,i)[0];
            img_out(17, i) = get<StdDev>(a,i)[1];
            img_out(18, i) = get<StdDev>(a,i)[2];
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
