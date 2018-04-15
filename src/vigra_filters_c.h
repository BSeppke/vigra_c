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

#ifndef VIGRA_FILTERS_C_H
#define VIGRA_FILTERS_C_H

#include "config.h"

/**
 * @file
 * @brief Header file for image filters
 *
 * @defgroup filters Image Filters
 * @{
 *    @brief Linear and non-linear image filtering algorithms
 */


/**
 * Image convolution.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::convolveImage
 * </a>
 * function to C to perform a convolution for a single band and a kernel.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param kernel_arr_in Flat input array (kernel) of size kernel_width*kernel_height.
 * \param[out] arr_out Flat array of the convolution result (band) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param kernel_width The width of the flat kernel array.
 * \param kernel_height The height the flat kernel array.
 * \param border_treatment The border treatment mode, according to VIGRA's border treatment modes:
   0 = BORDER_TREATMENT_AVOID:  do not operate on a pixel where the kernel doe not fit in the image
   1 = BORDER_TREATMENT_CLIP:   clip kernel at image border (this is only useful if the kernel is >= 0 everywhere)
   2 = BORDER_TREATMENT_REPEAT: repeat the nearest valid pixel
   3 = BORDER_TREATMENT_REFLECT: reflect image at last row/column
   4 = BORDER_TREATMENT_WRAP : wrap image around (periodic boundary conditions)
   5 = BORDER_TREATMENT_ZEROPAD: assume that all outside points have value zero
 *
 * \return 0 if the convolution was successful,
 *         3 if the border treatment mode is invalid,
 *         2 if the kernel size are not odd,
 *         1 else.
 */
LIBEXPORT int vigra_convolveimage_c(const PixelType * arr_in,
                                    const double * kernel_arr_in,
                                    const PixelType * arr_out,
                                    const int width,
                                    const int height,
                                    const int kernel_width,
                                    const int kernel_height,
                                    const int border_treatment);

/**
 * Separable image convolution.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::separableConvolveImage
 * </a>
 * function to C to perform a convolution for a single band and a kernel.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param kernel_h_arr_in Flat input array (horizonal kernel) of size kernel_width.
 * \param kernel_v_arr_in Flat input array (vertical kernel) of size kernel_height.
 * \param[out] arr_out Flat array of the convolution result (band) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param kernel_width The width of the flat horizontal kernel array.
 * \param kernel_height The height the flat vertical kernel array.
 * \param border_treatment The border treatment mode, according to VIGRA's border treatment modes:
   0 = BORDER_TREATMENT_AVOID:  do not operate on a pixel where the kernel doe not fit in the image
   1 = BORDER_TREATMENT_CLIP:   clip kernel at image border (this is only useful if the kernel is >= 0 everywhere)
   2 = BORDER_TREATMENT_REPEAT: repeat the nearest valid pixel
   3 = BORDER_TREATMENT_REFLECT: reflect image at last row/column
   4 = BORDER_TREATMENT_WRAP : wrap image around (periodic boundary conditions)
   5 = BORDER_TREATMENT_ZEROPAD: assume that all outside points have value zero
 *
 * \return 0 if the convolution was successful,
 *         3 if the border treatment mode is invalid,
 *         2 if the kernel size are not odd,
 *         1 else.
 */
LIBEXPORT int vigra_separableconvolveimage_c(const PixelType * arr_in,
                                             const double * kernel_h_arr_in,
                                             const double * kernel_v_arr_in,
                                             const PixelType * arr_out,
                                             const int width,
                                             const int height,
                                             const int kernel_width,
                                             const int kernel_height,
                                             const int border_treatment);

/**
 * Computation of the first order partial derivatives by means of a convolution 
 * of an image band with the first order derivative of a Gaussian.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::gaussianGradient
 * </a>
 * function to C to compute both partial derivates (in x- and y-direction) at a
 * given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_gx_out Flat array (the partial derivative in x-direction) of size width*height.
 * \param[out] arr_gy_out Flat array (the partial derivative in y-direction) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (Gaussian std.dev.) for which the gradient shall be computed.
 *
 * \return 0 if the gradient computation was successful, 1 else.
 */
LIBEXPORT int vigra_gaussiangradient_c(const PixelType * arr_in,
                                       const PixelType * arr_gx_out,
                                       const PixelType * arr_gy_out,
                                       const int width,
                                       const int height,
                                       const float sigma);

/**
 * Computation of the strength of the first order partial derivatives by means 
 * of a convolution of an image band with the first order derivative of a Gaussian.
 * 
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::gaussianGradientMagnitude
 * </a>
 * function to C to compute
 * the gradient magnitude at a given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (gradient magnitude) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (Gaussian std.dev.) for which the gradient shall be computed.
 *
 * \return 0 if the gradient computation was successful, 1 else.
 */
LIBEXPORT int vigra_gaussiangradientmagnitude_c(const PixelType * arr_in,
                                                const PixelType * arr_out,
                                                const int width,
                                                const int height,
                                                const float sigma);

/**
 * Computation of the Gaussian smoothing by means of a convolution of an image
 * band with a 2D-Gaussian function.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::gaussianSmoothing
 * </a>
 * function to C to compute the result at a given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (smoothed) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (Gaussian std.dev.) for which the smoothing shall be computed.
 *
 * \return 0 if the smoothing was successful, 1 else.
 */
LIBEXPORT int vigra_gaussiansmoothing_c(const PixelType * arr_in,
                                        const PixelType * arr_out,
                                        const int width,
                                        const int height,
                                        const float sigma);

/**
 * Computation of the Laplacian of Gaussian (LoG).
 *
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::laplacianOfGaussian
 * </a> 
 * function to C to compute the result of the LoG at a given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (LoG) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param scale The scale (gaussian std.dev.) for which the LoG shall be computed.
 *
 * \return 0 if the LoG was computed successfully, 1 else.
 */
LIBEXPORT int vigra_laplacianofgaussian_c(const PixelType * arr_in,
                                          const PixelType * arr_out,
                                          const int width,
                                          const int height,
                                          const float scale);

/**
 * Computation of the Hessian matrix using Gaussians, thus HoG, of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::hessianMatrixOfGaussians
 * </a>
 * function to C to compute the partial second order derivatives I_xx, I_xy and
 * I_yy of an image band at a given scale (Gaussian std.dev.).
 * This is performed by successive convolutions with derived Gaussian kernels.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_xx_out Flat array (second derivative in x-direction) of size width*height.
 * \param[out] arr_xy_out Flat array (mixed derivative in xy-direction) of size width*height.
 * \param[out] arr_yy_out Flat array (second derivative in y-direction) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param scale The scale (gaussian std.dev.) for which the Hessian shall be computed.
 *
 * \return 0 if the Hessian was computed successfully, 1 else.
 */
LIBEXPORT int vigra_hessianmatrixofgaussian_c(const PixelType * arr_in,
                                              const PixelType * arr_xx_out,
                                              const PixelType * arr_xy_out,
                                              const PixelType * arr_yy_out,
                                              const int width,
                                              const int height,
                                              const float scale);

/**
 * Computation of the Gaussian sharpening.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::gaussianSharpening
 * </a>
 * function to C to compute the result at a given scale (Gaussian std.dev.) and 
 * using a sharpening factor based on a gaussian.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (sharpened) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sharpening_factor The sharpening factor.
 * \param scale The scale for which the sharpening shall be computed.
 *
 * \return 0 if the sharpening was successful, 1 else.
 */
LIBEXPORT int vigra_gaussiansharpening_c(const PixelType * arr_in,
                                         const PixelType * arr_out,
                                         const int width,
                                         const int height,
                                         const float sharpening_factor,
                                         const float scale);

/**
 * Computation of a simple sharpening.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::simpleSharpening
 * </a>
 * function to C to compute the result using a sharpening factor.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (sharpened) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sharpening_factor The sharpening factor.
 *
 * \return 0 if the sharpening was successful, 1 else.
 */
LIBEXPORT int vigra_simplesharpening_c(const PixelType * arr_in,
                                       const PixelType * arr_out,
                                       const int width,
                                       const int height,
                                       float sharpening_factor);

/**
 * Computation of a non-linear median filter.
 * This function wraps the vigra::medianFilter function to C to compute
 * the result at a given window size, for whic the median value is derived.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (nl-diffused) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param window_width The width of the median window.
 * \param window_height The height of the median window.
 * \param border_treatment The border treatment mode according to VIGRA's border treatment modes,
          but without the BORDER_TREATMENT_CLIP mode:
   0 = BORDER_TREATMENT_AVOID:  do not operate on a pixel where the kernel doe not fit in the image
   2 = BORDER_TREATMENT_REPEAT: repeat the nearest valid pixel
   3 = BORDER_TREATMENT_REFLECT: reflect image at last row/column
   4 = BORDER_TREATMENT_WRAP : wrap image around (periodic boundary conditions)
   5 = BORDER_TREATMENT_ZEROPAD: assume that all outside points have value zero
 *
 * \return 0 if the median filter was successful,
           2 if the border_treatment is not allowed,
           1 else.
 */
LIBEXPORT int vigra_medianfilter_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int window_width,
	                               const int window_height,
	                               const int border_treatment);
                                   
/**
 * Computation of a non-linear (nl) diffusion filter.
 * This function wraps the vigra::nonlinearDiffusion function to C to compute
 * the result at a given scale (Gaussian std.dev.) and using an edge threshold.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (nl-diffused) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param edge_threshold The edge threshold factor.
 * \param scale The scale for which the nl diffusion shall be computed.
 *
 * \return 0 if the nl diffusion was successful, 1 else.
 */
LIBEXPORT int vigra_nonlineardiffusion_c(const PixelType * arr_in,
                                         const PixelType * arr_out,
                                         const int width,
                                         const int height,
                                         const float edge_threshold,
                                         const float scale);

/**
 * Computation of a non-linear (nl) coherence enhancing shock filter.
 * This function wraps the vigra::shockFilter function to C to compute
 * the result in an iterative fashion.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (shock filtered) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The inner scale for which the filter shall be computed.
 * \param rho The outer scale for which the filter shall be computed.
 * \param upwind_factor_h The morpholical strength of the filter.
 * \param iterations The iterations to be carried out.
 *
 * \return 0 if the computation was successful, 
 *         2 if iterations are 0, 
 *         1 else.
 */
LIBEXPORT int vigra_shockfilter_c(const PixelType *arr_in,
                                  const PixelType *arr_out,
                                  const int width,
                                  const int height,
                                  const float sigma,
                                  const float rho,
                                  const float upwind_factor_h,
                                  const int iterations);

/**
 * Computation of a non-local mean filter.
 * This function wraps the vigra::nonLocalMean function for the 2d case
 * to C to compute the result in an iterative fashion.
 * All arrays must have been allocated before the call of this function.
 * For "good" default values see the vigranumpy example. They are noted
 * inside brackets of the end of each parameter.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (shock filtered) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param policy_type The Policy, must be 0 or 1:
                                        0 = Ratio Policy,
                                        1 = Norm Policy.
 * \param sigma The sigma value of the policy (P0=10.0, P1=50.0).
 * \param meanRatio The mean ratio value of the policy (P0=0.95, P1=5.0).
 * \param varRatio The variance ratio of the policy (0.5).
 * \param epsilon The epsilon of the policy (0.00001).
 * \param sigmaSpatial The sigma value of the filter (2.0).
 * \param searchRadius The search radius of the filter (5).
 * \param patchRadius The patch radius of the filter (either 1 or 2).
 * \param sigmaMean The expected mean sigma value for the filter (10.0).
 * \param stepSize The step size of the filter (2).
 * \param iterations The iterations to be carried out. (10)
 * \param nThreads The threads used for the computation of the filter (8).
 * \param verbose If true, prints out status infos (True).
 *
 * \return 0 if the computation was successful,
 *         2 if the policy_type is neither 0 nor 1,
 *         1 else.
 */
LIBEXPORT int vigra_nonlocalmean_c(const PixelType *arr_in,
                                   const PixelType *arr_out,
                                   const int width,
                                   const int height,
                                   const int policy_type,
                                   const float sigma,
                                   const float meanRatio,
                                   const float varRatio,
                                   const float epsilon,
                                   const float sigmaSpatial,
                                   const int searchRadius,
                                   const int patchRadius,
                                   const float sigmaMean,
                                   const int stepSize,
                                   const int iterations,
                                   const int nThreads,
                                   const bool verbose);
/**
 * @}
 */
 
#endif
