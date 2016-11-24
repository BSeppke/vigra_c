#ifndef VIGRA_TENSORS_C_H
#define VIGRA_TENSORS_C_H

#include "config.h"


/**
 * Computation of the Structure Tensor of an image band. This function wraps the
 * vigra::structureTensor function to C to compute the spatially smoothed products 
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
 * Computation of the Boundary Tensor of an image band. This function wraps the
 * vigra::boundaryTensor function to C.
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
 * Computation of the Boundary Tensor (without the first order component) of an
 * image band. This function wraps the vigra::boundaryTensor1 function to C.
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
 * Computation of the Gradient Energy Tensor of an image band. This function 
 * wraps the vigra::gradientEnergyTensor function to C.
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
 * \param derivKernel The size of the derivative kernel array.
 * \param smoothKernel The size of the smoothing kernel array.
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
 * This function wraps the vigra::tensorEigenRepresentation function to C.
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
 * This function wraps the vigra::tensorTrace function to C.
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
 * Computation of the Egeness/Cornerness representation of a tensor.
 * This function wraps the vigra::tensorToEdgeCorner function to C.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_xx_in Flat array (Tensor xx) of size width*height.
 * \param arr_xy_in Flat array (Tensor xy) of size width*height.
 * \param arr_yy_in Flat array (Tensor yy) of size width*height.
 * \param[out] arr_edgeness_out Flat array (edgeness) of size width*height.
 * \param[out] arr_orientation_out Flat array (orientation of the edge) of size width*height.
 * \param[out] arr_ang_outarr_cornerness_outFlat array (cornerness) of size width*height.
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
 * Filering of a tensor using the Hourglass filter.
 * This function wraps the correct application of the vigra::hourGlassFilter 
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


#endif
