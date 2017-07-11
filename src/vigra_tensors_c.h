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

#ifndef VIGRA_TENSORS_C_H
#define VIGRA_TENSORS_C_H

#include "config.h"

/**
 * @file 
 * @brief Header file for Tensor-based algorithms
 *
 * @defgroup tensors Tensor-based algorithms
 * @{
 *    @brief Functions for Tensor based image processing and analysis
 */
 
/**
 * Computation of the Structure Tensor of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__ConvolutionFilters.html">
 * vigra::structureTensor
 * </a> 
 * function to C to compute the spatially smoothed products
 * of the first order image derivatives: smooth(I_x^2), smooth(I_x*I_y) and
 * smooth(I_y^2). The gradient estinmation is performed by convolutions with 
 * derived Gaussian kernels of a given std. dev. The smoothing is also performed
 * by a convolution with gaussian, but at another scale.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_xx_out Flat array (smooth(I_x^2)) of size width*height.
 * \param[out] arr_xy_out Flat array (smooth(I_x*I_y)) of size width*height.
 * \param[out] arr_yy_out Flat array (smooth(I_y^2)) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param inner_scale The scale (gaussian std.dev.) for the derivative computation.
 * \param outer_scale The scale (gaussian std.dev.) for the smoothing computation.
 *
 * \return 0 if the Structure Tensor was computed successfully, 1 else.
 */
LIBEXPORT int vigra_structuretensor_c(const PixelType * arr_in,
                                      const PixelType * arr_xx_out,
                                      const PixelType * arr_xy_out,
                                      const PixelType * arr_yy_out,
                                      const int width,
                                      const int height,
                                      const float inner_scale,
                                      const float outer_scale);

/**
 * Computation of the Boundary Tensor of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__TensorImaging.html">
 * vigra::boundaryTensor
 * </a> 
 * function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_xx_out Flat array (Boundary Tensor xx) of size width*height.
 * \param[out] arr_xy_out Flat array (Boundary Tensor xy) of size width*height.
 * \param[out] arr_yy_out Flat array (Boundary Tensor yy) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param scale The scale (gaussian std.dev.) of the boundary tensor.
 *
 * \return 0 if the Boundary Tensor was computed successfully, 1 else.
 */
LIBEXPORT int vigra_boundarytensor_c(const PixelType * arr_in,
                                     const PixelType * arr_xx_out,
                                     const PixelType * arr_xy_out,
                                     const PixelType * arr_yy_out,
                                     const int width,
                                     const int height,
                                     const float scale);

/**
 * Computation of the Boundary Tensor (without the zero order component) of an
 * image band. 
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__TensorImaging.html">
 * vigra::boundaryTensor1
 * </a> 
 * function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_xx_out Flat array (Boundary Tensor xx) of size width*height.
 * \param[out] arr_xy_out Flat array (Boundary Tensor xy) of size width*height.
 * \param[out] arr_yy_out Flat array (Boundary Tensor yy) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param scale The scale (gaussian std.dev.) of the boundary tensor.
 *
 * \return 0 if the Boundary Tensor was computed successfully, 1 else.
 */
LIBEXPORT int vigra_boundarytensor1_c(const PixelType * arr_in,
                                      const PixelType * arr_xx_out,
                                      const PixelType * arr_xy_out,
                                      const PixelType * arr_yy_out,
                                      const int width,
                                      const int height,
                                      const float scale);

/**
 * Computation of the Gradient Energy Tensor of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__TensorImaging.html">
 * vigra::gradientEnergyTensor
 * </a> 
 * function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param arr_derivKernel_in Flat input array (derivation kernel) of size derivKernel_size.
 * \param arr_smoothKernel_in Flat input array (smoothing kernel) of size smoothKernel_size.
 * \param[out] arr_xx_out Flat array (Boundary Tensor xx) of size width*height.
 * \param[out] arr_xy_out Flat array (Boundary Tensor xy) of size width*height.
 * \param[out] arr_yy_out Flat array (Boundary Tensor yy) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param derivKernel_size The size of the derivative kernel array.
 * \param smoothKernel_size The size of the smoothing kernel array.
 *
 * \return 0 if the Gradient Energy Tensor was computed successfully,
 *         2 if kernel dimensions are not odd,
 *         1 else.
 */
LIBEXPORT int vigra_gradientenergytensor_c(const PixelType * arr_in,
                                           const double * arr_derivKernel_in,
                                           const double * arr_smoothKernel_in,
                                           const PixelType * arr_xx_out,
                                           const PixelType * arr_xy_out,
                                           const PixelType * arr_yy_out,
                                           const int width,
                                           const int height,
                                           const int derivKernel_size,
                                           const int smoothKernel_size);

/**
 * Computation of the Eigenvalue/Eigenvector representation of a tensor.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__TensorImaging.html">
 * vigra::tensorEigenRepresentation
 * </a> 
 * function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_xx_in Flat array (Tensor xx) of size width*height.
 * \param arr_xy_in Flat array (Tensor xy) of size width*height.
 * \param arr_yy_in Flat array (Tensor yy) of size width*height.
 * \param[out] arr_lEV_out Flat array (major Eigenvalues) of size width*height.
 * \param[out] arr_sEV_out Flat array (minor Eigenvalues) of size width*height.
 * \param[out] arr_ang_out Flat array (angle of largest Eigenvalue) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 *
 * \return 0 if the Eigenvalues were computed successfully, 1 else
 */
LIBEXPORT int vigra_tensoreigenrepresentation_c(const PixelType * arr_xx_in,
                                                const PixelType * arr_xy_in,
                                                const PixelType * arr_yy_in,
                                                const PixelType * arr_lEV_out,
                                                const PixelType * arr_sEV_out,
                                                const PixelType * arr_ang_out,
                                                const int width,
                                                const int height);

/**
 * Computation of the trace of a tensor.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__TensorImaging.html">
 * vigra::tensorTrace
 * </a> 
 * function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_xx_in Flat array (Tensor xx) of size width*height.
 * \param arr_xy_in Flat array (Tensor xy) of size width*height.
 * \param arr_yy_in Flat array (Tensor yy) of size width*height.
 * \param[out] arr_trace_out Flat array (trace of the tensor) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 *
 * \return 0 if the Tensor trace was computed successfully, 1 else
 */
LIBEXPORT int vigra_tensortrace_c(const PixelType * arr_xx_in,
                                  const PixelType * arr_xy_in,
                                  const PixelType * arr_yy_in,
                                  const PixelType * arr_trace_out,
                                  const int width,
                                  const int height);

/**
 * Computation of the Edgeness/Cornerness representation of a tensor.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__TensorImaging.html">
 * vigra::tensorToEdgeCorner
 * </a>
 * function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_xx_in Flat array (Tensor xx) of size width*height.
 * \param arr_xy_in Flat array (Tensor xy) of size width*height.
 * \param arr_yy_in Flat array (Tensor yy) of size width*height.
 * \param[out] arr_edgeness_out Flat array (edgeness) of size width*height.
 * \param[out] arr_orientation_out Flat array (orientation of the edge) of size width*height.
 * \param[out] arr_cornerness_out Flat array (cornerness) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 *
 * \return 0 if the Edgeness/Cornerness was computed successfully, 1 else
 */
LIBEXPORT int vigra_tensortoedgecorner_c(const PixelType * arr_xx_in,
                                         const PixelType * arr_xy_in,
                                         const PixelType * arr_yy_in,
                                         const PixelType * arr_edgeness_out,
                                         const PixelType * arr_orientation_out,
                                         const PixelType * arr_cornerness_out,
                                         const int width,
                                         const int height);

/**
 * Filtering of a tensor using the Hourglass filter.
 * This function wraps the correct application of the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__TensorImaging.html">
 * vigra::hourGlassFilter
 * </a>
 * function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_xx_in Flat array (Tensor xx) of size width*height.
 * \param arr_xy_in Flat array (Tensor xy) of size width*height.
 * \param arr_yy_in Flat array (Tensor yy) of size width*height.
 * \param[out] arr_hgxx_out Flat array (filtered Tensor xx) of size width*height.
 * \param[out] arr_hgxy_out Flat array (filtered Tensor xy) of size width*height.
 * \param[out] arr_hgyy_out array (filtered Tensor yy) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The std. dev. of the Hourglass Filter.
 * \param rho The opening angle of the Hourglass Filter.
 *
 * \return 0 if the Tensor filtering was successful, 1 else
 */
LIBEXPORT int vigra_hourglassfilter_c(const PixelType * arr_xx_in,
                                      const PixelType * arr_xy_in,
                                      const PixelType * arr_yy_in,
                                      const PixelType * arr_hgxx_out,
                                      const PixelType * arr_hgxy_out,
                                      const PixelType * arr_hgyy_out,
                                      const int width,
                                      const int height,
                                      const float sigma,
                                      const float rho);


/**
 * @}
 */
 
#endif
