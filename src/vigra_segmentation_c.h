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

#ifndef VIGRA_SEGMENTATION_C_H
#define VIGRA_SEGMENTATION_C_H

#include "config.h"

/**
 * @file
 * @brief Header file for segmentation algorithms
 *
 * @defgroup segmentation Image Segmentation
 * @{
 *    @brief Contains segmentation algorithms.
 */
 
/**
 * Labels the connected components of an image band.
 * This function wraps the vigra::labelImage function to C to carry out a
 * union-find algorithm. This finds the and sets unique labels for the connected
 * components of same grayvalues in the given image.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (labels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param eight_connectiviity If set to true, 8-conectivity is used, else 4.
 *
 * \return If the labelling was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_labelimage_c(const PixelType * arr_in,
                                 const PixelType * arr_out,
                                 const int width,
                                 const int height,
                                 const bool eight_connectivity);

/**
 * Applies the Watershed Transform to an image band.
 * This function wraps the vigra::watershedsUnionFind function to C to carry out a
 * union-find watershed segmentation algorithm. This first segments the image and
 * then finds the and sets unique labels for the connected components of same 
 * grayvalues in the given image. Use e.g. the reseult of vigra_gradientmagnitude_c
 * as an input for this function, since the watersheds of the gradient are good 
 * candidates for region boundaries.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (labels) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 *
 * \return If the segmentation was sucessful, the largest label assigned, else -1.
 */
LIBEXPORT int vigra_watersheds_c(const PixelType * arr_in,
                                 const PixelType * arr_out,
                                 const int width,
                                 const int height);

/**
 * Applies the SLIC segmenation to an image band.
 * This function wraps the vigra::slicSuperpixels function to C to carry out a
 * SLIC segmentation algorithm. This first segments the image and
 * then finds the and sets unique labels for the connected components of same 
 * grayvalues in the given image.
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
                                const int iterations);

/**
 * Applies the SLIC segmenation to an RGB image.
 * This function wraps the vigra::slicSuperpixels function to C to carry out a
 * SLIC segmentation algorithm on three single image bands, refering to the RGB-
 * bands. This first segments the image and then finds the and sets unique 
 * labels for the connected components of same grayvalues in the given image.
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
                               const int iterations);

/**
 * Computation of the Canny Edge Detector.
 * This function wraps the vigra::cannyEdgeImage function to C to compute
 * the Canny edgels at a given scale (Gaussian std.dev.) and using an edge
 * (gradient) threshold to mark all edgels on the given input band with a certain
 * grayvalue. The intensity of all other pixels in the result remain 0.
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
 * \return 0 if the nl diffusion was successful, 1 else.
 */
LIBEXPORT int vigra_cannyedgeimage_c(const PixelType * arr_in,
                                     const PixelType * arr_out,
                                     const int width,
                                     const int height,
                                     const float scale,
                                     const float gradient_threshold,
                                     const float mark);

/**
 * Computation of the Difference of Exponential (DoE) Edge Detector.
 * This function wraps the vigra::differenceOfExponentialEdgeImage function to C
 * to compute the DoE edgels at a given scale (Gaussian std.dev.) and using an edge
 * (gradient) threshold to mark all edgels on the given input band with a certain
 * grayvalue. The intensity of all other pixels in the result remain 0.
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
 * \return 0 if the nl diffusion was successful, 1 else.
 */
LIBEXPORT int vigra_differenceofexponentialedgeimage_c(const PixelType * arr_in,
                                                       const PixelType * arr_out,
                                                       const int width,
                                                       const int height,
                                                       const float scale,
                                                       const float gradient_threshold,
                                                       const float mark);

/**
 * Transforms a label image band into its crack-edge representation.
 * This function wraps the vigra::regionImageToCrackEdgeImage function to C
 * to transform a label image band into a (nearly 4x) as large image band, which
 * shows the boundaries between labels/regions by a given mark intensity. The size
 * of the output band has to be (2*width_in-1)*(2*height_in-1) for an input label
 * band of size width_in*height_in. All arrays must have been allocated with 
 * correct sizes before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width_in*height_in.
 * \param[out] arr_out Flat array (crack-edges) of size (2*width_in-1)*(2*height_in-1).
 * \param width_in The width of the flat array.
 * \param height_in The height of the flat array.
 * \param mark The intensity for marking the crack-edges in the resulting band.
 *
 * \return 0 if the nl diffusion was successful, 1 else.
 */
LIBEXPORT int vigra_regionimagetocrackedgeimage_c(const PixelType * arr_in,
                                                  const PixelType * arr_out,
                                                  const int width_in,
                                                  const int height_in,
                                                  const float mark);

/**
 * @}
 */

#endif
