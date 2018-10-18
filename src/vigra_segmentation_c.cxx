/************************************************************************/
/*                                                                      */
/*               Copyright 2008-2017 by Benjamin Seppke                 */
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
#include <limits>


/**
 * @file
 * @brief Implementation of segmentation algorithms
 */

static const unsigned long long MAX_FLOAT_INTEGER = pow(2, std::numeric_limits<float>::digits-1)*2;

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
        
        vigra::MultiArray<2, unsigned int> labels(width, height);
        
        auto labelCount = vigra::labelImage(img_in, labels, eight_connectivity);
        
        if (labelCount > MAX_FLOAT_INTEGER)
        {
            return -1;
        }
        else
        {
            img_out = labels;
            return labelCount;
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

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
        
        vigra::MultiArray<2, unsigned int> labels(width, height);
        
        auto labelCount = vigra::labelImageWithBackground(img_in, labels, eight_connectivity, background);
        
        if (labelCount > MAX_FLOAT_INTEGER)
        {
            return -1;
        }
        else
        {
            img_out = labels;
            return labelCount;
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

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
        
        vigra::MultiArray<2, unsigned int> labels(width, height);
        unsigned int labelCount = 0;
        
        if(eight_connectivity)
        {
            labelCount = vigra::watershedsUnionFind(img_in, labels, vigra::EightNeighborCode());
        }
        else
        {
            labelCount = vigra::watershedsUnionFind(img_in, labels, vigra::FourNeighborCode());
        }
        if (labelCount > MAX_FLOAT_INTEGER)
        {
            return -1;
        }
        else
        {
            img_out = labels;
            return labelCount;
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

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
        
        vigra::MultiArray<2, unsigned int> labels(width, height);
        //Fill labels image woth markers
        labels = img_inout;
        
        unsigned int labelCount = 0;
        
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
                labelCount = vigra::watershedsRegionGrowing(img_in256, labels,
                                vigra::EightNeighborCode(),
                                options);
            }
            else
            {
                labelCount = vigra::watershedsRegionGrowing(img_in256, labels,
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
                labelCount =  vigra::watershedsRegionGrowing(img_in, labels,
                                vigra::EightNeighborCode(),
                                options);
            }
            else
            {
                labelCount =  vigra::watershedsRegionGrowing(img_in, labels,
                                vigra::FourNeighborCode(),
                                options);
            }
        }
        
        if (labelCount > MAX_FLOAT_INTEGER)
        {
            return -1;
        }
        else
        {
            img_inout = labels;
            return labelCount;
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

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
        auto labelCount = vigra::slicSuperpixels(img_in, labels, intensityScaling, seedDistance, vigra::SlicOptions().iterations(iterations));
        
        if (labelCount > MAX_FLOAT_INTEGER)
        {
            return -1;
        }
        else
        {
            img_out = labels;
            return labelCount;
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

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
        
        vigra::MultiArray<2, unsigned int> labels(shape);
        
        // transform image to Lab color space
        vigra::transformMultiArray(srcMultiArrayRange(src), destMultiArray(src),
                                   vigra::RGBPrime2LabFunctor<float>());
        
        //int seedDistance = 15;
        //double intensityScaling = 20.0;
        
        // compute seeds automatically, perform 40 iterations, and scale intensity differences
        // down to 1/20 before comparing with spatial distances
        auto labelCount = vigra::slicSuperpixels(src, labels, intensityScaling, seedDistance,
                                      vigra::SlicOptions().iterations(iterations));
        
        if (labelCount > MAX_FLOAT_INTEGER)
        {
            return -1;
        }
        else
        {
            img_out  = labels;
            return labelCount;
        }
    }
    catch (vigra::StdException & e)
    {
        return -1;
    }
}

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
        // x=  0       - > region_size,
        // x=( 1 ..  2) -> upperleft-x and y-coord
        // x=( 3 ..  4) -> lowerright-x and y-coord
        // x=( 5 ..  6) -> mean-x and y-coord
        // x=  7        -> min grey value
        // x=  8        -> max grey value
        // x=  9        -> mean grey value
        // x= 10        -> std.dev. grey value
        // x=(11 .. 12) -> major ev: x and y-coord
        // x=(13 .. 14) -> minor ev: x and y-coord
        // x= 15        -> major ew
        // x= 16        -> minor ew
        // x=(17 .. 18) -> grey value weighted mean-x and y-coord
        // x=19         -> perimeter (region contour length)
        // x=20         -> skewness
        // x=21         -> kurtosis
        vigra::Shape2 shape_out(22, max_label+1);
        ImageView img_out(shape_out, arr_out);
        
        typedef
            AccumulatorChainArray<vigra::CoupledArrays<2, PixelType, unsigned int>,
                Select< DataArg<1>, LabelArg<2>, // in which array to look (coordinates are always arg 0)
                        Count,
                        Coord<Minimum>, Coord<Maximum>, Coord<Mean>,
                        Minimum, Maximum, Mean, StdDev,
                        RegionAxes, RegionRadii,
                        Weighted<Coord<Mean> >,
                        RegionPerimeter,
                        Skewness, Kurtosis > >
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
            
            img_out(11,i) = get<RegionAxes>(a,i)(0,0);
            img_out(12,i) = get<RegionAxes>(a,i)(1,0);
            img_out(13,i) = get<RegionAxes>(a,i)(0,1);
            img_out(14,i) = get<RegionAxes>(a,i)(1,1);
            
            img_out(15,i) = get<RegionRadii>(a,i)[0];
            img_out(16,i) = get<RegionRadii>(a,i)[1];
            
            img_out(17, i) = get<Weighted<Coord<Mean>>>(a,i)[0];
            img_out(18, i) = get<Weighted<Coord<Mean>>>(a,i)[1];
            
            img_out(19, i) = get<RegionPerimeter>(a,i);
            
            img_out(20, i) = get<Skewness>(a,i);
            img_out(21, i) = get<Kurtosis>(a,i);
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

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
        
        using namespace vigra::multi_math;
        
        //weights array (RGB->grey)
        vigra::MultiArray<2, double> weights = 0.3*img_red + 0.59*img_green + 0.11*img_blue;
        
        
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
        // x=(19 .. 20) -> major ev: x and y-coord
        // x=(21 .. 22) -> minor ev: x and y-coord
        // x=23         -> major ew
        // x=24         -> minor ew
        // x=(25 .. 26) -> luminace weighted mean-x and y-coord
        // x=27         -> perimeter (region contour length)
        // x=(28 .. 30) -> skewness (red, green, blue)
        // x=(31 .. 33) -> kurtosis (red, green, blue)
        vigra::Shape2 shape_out(34, max_label+1);
        ImageView img_out(shape_out, arr_out);
        
        typedef
            AccumulatorChainArray<vigra::CoupledArrays<2, vigra::RGBValue<float>, double, unsigned int>,
                Select< DataArg<1>, WeightArg<2>, LabelArg<3>, // in which array to look (coordinates are always arg 0)
                        Count,
                        Coord<Minimum>, Coord<Maximum>, Coord<Mean>,
                        Minimum, Maximum, Mean, StdDev,
                        RegionAxes, RegionRadii,
                        Weighted<Coord<Mean>>,
                        RegionPerimeter,
                        Skewness, Kurtosis  > >
            AccumulatorType;
        
        AccumulatorType a;
        
        extractFeatures(src, weights, labels, a);

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
            
            img_out(19,i) = get<RegionAxes>(a,i)(0,0);
            img_out(20,i) = get<RegionAxes>(a,i)(1,0);
            img_out(21,i) = get<RegionAxes>(a,i)(0,1);
            img_out(22,i) = get<RegionAxes>(a,i)(1,1);
            
            img_out(23,i) = get<RegionRadii>(a,i)[0];
            img_out(24,i) = get<RegionRadii>(a,i)[1];
            
            img_out(25, i) = get<Weighted<Coord<Mean>>>(a,i)[0];
            img_out(26, i) = get<Weighted<Coord<Mean>>>(a,i)[1];
            
            img_out(27, i) = get<RegionPerimeter>(a,i);
            
            img_out(28, i) = get<Skewness>(a,i)[0];
            img_out(29, i) = get<Skewness>(a,i)[1];
            img_out(30, i) = get<Skewness>(a,i)[2];
            
            img_out(31, i) = get<Kurtosis>(a,i)[0];
            img_out(32, i) = get<Kurtosis>(a,i)[1];
            img_out(33, i) = get<Kurtosis>(a,i)[2];
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
