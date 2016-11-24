#ifndef VIGRA_FILTERS_C_H
#define VIGRA_FILTERS_C_H

#include "config.h"

/**
 * Image convolution. This function wraps the vigra::convolveImage function to
 * C to perform a convolution for a single band and a kernel. 
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
 * \param kernel_arr_in Flat input array (kernel) of size kernel_width*kernel_height.
 * \param[out] arr_out Flat array of the convolution result (band) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param kernel_width The width of the flat kernel array.
 * \param kernel_height The height the flat kernel array.
 *
 * \return 0 if the convolution was successful,
 *         2 if kernel dimensions are not odd,
 *         1 else.
 */
LIBEXPORT int vigra_convolveimage_c(const PixelType * arr_in,
                                    const double * kernel_arr_in,
                                    const PixelType * arr_out,
                                    const int width,
                                    const int height,
                                    const int kernel_width,
                                    const int kernel_height);

/**
 * Separable image convolution. This function wraps the vigra::separableconvolveImage 
 * function to C to perform a convolution for a single band and a kernel.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
 * \param kernel_h_arr_in Flat input array (horizonal kernel) of size kernel_width.
 * \param kernel_v_arr_in Flat input array (vertical kernel) of size kernel_height.
 * \param[out] arr_out Flat array of the convolution result (band) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param kernel_width The width of the flat horizontal kernel array.
 * \param kernel_height The height the flat vertical kernel array.
 *
 * \return 0 if the convolution was successful,
 *         2 if kernel dimensions are not odd,
 *         1 else.
 */
LIBEXPORT int vigra_separableconvolveimage_c(const PixelType * arr_in,
                                             const double * kernel_h_arr_in,
                                             const double * kernel_v_arr_in,
                                             const PixelType * arr_out,
                                             const int width,
                                             const int height,
                                             const int kernel_width,
                                             const int kernel_height);

/**
 * Computation of the first order partial derivatives by means of a convolution 
 * of an image band with the first order derivative of a Gaussian.
 * This function wraps the vigra::gaussianGradient function to C to compute both
 * partial derivates (in x- and y-direction) at a given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
 * \param[out] arr_gx_out Flat array (the partial derivative in x-direction) of size width*height.
 * \param[out] arr_gy_out Flat array (the partial derivative in y-direction) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (Gaussian std.dev.) for with the gradient shall be computed.
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
 * This function wraps the vigra::gaussianGradientMagnitue function to C to compute 
 * the gradient magnitude at a given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
 * \param[out] arr_out Flat array (gradient magnitude) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (Gaussian std.dev.) for with the gradient shall be computed.
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
 * This function wraps the vigra::gaussianSmoothing function to C to compute
 * the result at a given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
 * \param[out] arr_out Flat array (smoothed) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (Gaussian std.dev.) for with the smoothing shall be computed.
 *
 * \return 0 if the smoothing was successful, 1 else.
 */
LIBEXPORT int vigra_gaussiansmoothing_c(const PixelType * arr_in,
                                        const PixelType * arr_out,
                                        const int width,
                                        const int height,
                                        const float sigma);

/**
 * Computation of the Laplacian of Gaussian. This function wraps the 
 * vigra::laplacianOfGaussian function to C to compute the result of the LoG at
 * a given scale (Gaussian std.dev.).
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (LoG) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (gaussian std.dev.) for with the LoG shall be computed.
 *
 * \return 0 if the LoG was computed successfully, 1 else.
 */
LIBEXPORT int vigra_laplacianofgaussian_c(const PixelType * arr_in,
                                          const PixelType * arr_out,
                                          const int width,
                                          const int height,
                                          const float scale);

/**
 * Computation of the Hessian matrix of an image band. This function wraps the
 * vigra::hessianMatrixOfGaussian function to C to compute the partial second 
 * order derivatives I_xx, I_xy and I_yy a given scale (Gaussian std.dev.). 
 * This is performed by successive convolutions with derived Gaussian kernels.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_xx_out Flat array (second derivative in x-direction) of size width*height.
 * \param[out] arr_xy_out Flat array (mixed derivative in xy-direction) of size width*height.
 * \param[out] arr_yy_out Flat array (second derivative in y-direction) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The scale (gaussian std.dev.) for with the Hessian shall be computed.
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
 * This function wraps the vigra::gaussianSharpening function to C to compute
 * the result at a given scale (Gaussian std.dev.) and using a sharpening factor.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
 * \param[out] arr_out Flat array (sharpened) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sharpening_factor The sharpening factor.
 * \param scale The scale for with the sharpening shall be computed.
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
 * Computation of a simple shaprening.
 * This function wraps the vigra::simpleSharpening function to C to compute
 * the result using a sharpening factor.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
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
 * Computation of a non-linear (nl) diffusion filter.
 * This function wraps the vigra::nonlinearDiffusion function to C to compute
 * the result at a given scale (Gaussian std.dev.) and using an edge threshold.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band)of size width*height.
 * \param[out] arr_out Flat array (nl-diffused) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param edge_threshold The edge threshold factor.
 * \param scale The scale for with the nl diffusion shall be computed.
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
 * \param arr_in Flat input array (band)of size width*height.
 * \param[out] arr_out Flat array (shock filtered) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param sigma The inner scale for with the filter shall be computed.
 * \param rho The outer scale for with the filter shall be computed.
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

#endif
