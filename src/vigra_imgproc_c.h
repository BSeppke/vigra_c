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

#ifndef VIGRA_IMGPROC_C_H
#define VIGRA_IMGPROC_C_H

#include "config.h"

/**
 * @file
 * @brief Header file for image processing algorithms
 *
 * @defgroup imgproc Image Processing
 * @{
 *    @brief Collection of general purpose image processing algorithms
 */

/**
 * Resizing of image bands. 
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__GeometricTransformations.html">
 * vigra::resizeImageSplineInterpolation
 * </a>
 * function to C to perform an interpolated resizing of two flat image arrays,
 * which must have been allocated at the correct sizes before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width_in*height_in.
 * \param[out] arr_out Flat array of the resizing result (band) of size width_out*height_out.
 * \param width_in The width of the flat input array.
 * \param height_in The height of the flat input array.
 * \param width_out The width of the flat output array.
 * \param height_out The height the flat output array.
 * \param resample_method The spline order for resampling. Must be in the interval [0, 4].
 *
 * \return 0 if the resizing was successful,
 *         2 if resample_method is < 0 or > 4,
 *         1 else.
 */
LIBEXPORT int vigra_resizeimage_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width_in,
                                  const int height_in,
                                  const int width_out,
                                  const int height_out,
                                  const int resample_method);

/**
 * Rotation of image bands.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__GeometricTransformations.html">
 * vigra::rotateImage
 * </a>
 * function to C to perform an interpolated rotation of a flat image array.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_out Flat array of the rotated result (band) of size width*height.
 * \param width The width of the flat arrays.
 * \param height The height of the flat arrays.
 * \param angle The rotation angle in degrees.
 * \param resample_method The spline order for resampling. Must be in the interval [1, 4].
 *
 * \return 0 if the rotation was successful,
 *         2 if resample_method is < 1 or > 4,
 *         1 else.
 */
LIBEXPORT int vigra_rotateimage_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const float angle,
                                  const int resample_method);

/**
 * Affine warping of image bands.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__GeometricTransformations.html">
 * vigra::affineWarpImage
 * </a>
 * function to C to perform an interpolated affine warping of a flat image array.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param affineMatrix Flat input array (affine matrix) of size 3*3.
 * \param[out] arr_out Flat array of the warped result (band) of size width*height.
 * \param width The width of the flat arrays.
 * \param height The height of the flat arrays.
 * \param resample_method The spline order for resampling. Must be in the interval [1, 4].
 *
 * \return 0 if the affine warping was successful,
 *         2 if resample_method is < 1 or > 4,
 *         1 else.
 */
LIBEXPORT int vigra_affinewarpimage_c(const PixelType * arr_in,
                                      const double * affineMatrix,
                                      const PixelType * arr_out,
                                      const int width,
                                      const int height,
                                      const int resample_method);

/**
 * Reflection of image bands w.r.t. the image axes.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__GeometricTransformations.html">
 * vigra::reflectImage
 * </a>
 * function to C to perform a reflection along each or both
 * axis of a flat image array.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_out Flat array of the reflected result (band) of size width*height.
 * \param width The width of the flat arrays.
 * \param height The height of the flat arrays.
 * \param reflect_method The reflection mode. Horizontal = 1, vertical = 2, both = 3.
 *
 * \return 0 if the reflection was successful,
 *         2 if reflect_method is < 1 or > 3,
 *         1 else.
 */
LIBEXPORT int vigra_reflectimage_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int reflect_method);

/**
 * Computation of the centered Fast Fourier Transform (FFT) of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__FourierTransform.html">
 * vigra::fourierTransform
 * </a>
 * function to C to perform an FFT of the image band and centers the DC after
 * transformation. Internally, this performs a thread safe call of the FFTW 
 * lib's tranformation functions.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_real_out Flat array of the real part of the FFT of size width*height.
 * \param[out] arr_imag_out Flat array of the imaginary part of the FFT of size width*height.
 * \param width The width of the flat arrays.
 * \param height The height of the flat arrays.
 *
 * \return 0 if the Fourier Transform was successful, 1 else.
 */
LIBEXPORT int vigra_fouriertransform_c(const PixelType * arr_in,
                                       const PixelType * arr_real_out,
                                       const PixelType * arr_imag_out,
                                       const int width,
                                       const int height);

/**
 * Computation of the inverse of a centered Fast Fourier Transform (FFT) of a
 * real and complex image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__FourierTransform.html">
 * vigra::fourierTransformInverse
 * </a>
 * function to C to perform an inverse FFT of the centered real and imaginary 
 * image bands. Internally, this performs a thread safe call of the FFTW
 * lib's tranformation functions.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_real_in Flat input array of the real part of the FFT of size width*height.
 * \param arr_imag_in Flat array of the imaginary part of the FFT of size width*height.
 * \param[out] arr_real_out Flat array of the real part after the iFFT of size width*height.
 * \param[out] arr_imag_out Flat array of the imaginary part after the iFFT of size width*height.
 * \param width The width of the flat arrays.
 * \param height The height of the flat arrays.
 *
 * \return 0 if the inverse Fourier Transform was successful, 1 else.
 */
LIBEXPORT int vigra_fouriertransforminverse_c(const PixelType * arr_real_in,
                                              const PixelType * arr_imag_in,
                                              const PixelType * arr_real_out,
                                              const PixelType * arr_imag_out,
                                              const int width,
                                              const int height);

/**
 * Computation of the fast (un-normalized) cross-correlation an image band w.r.t.
 * another (typically smaller) image, called template.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Correlation.html">
 * vigra::fastCrossCorrelation
 * </a>
 * function to C to perform a cross-correlation of the image band w.r.t the
 * template. For sake of efficiency, this is performed in fourier space.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param arr_template_in Flat array (tmeplate band) of size width*height.
 * \param[out] arr_out Flat array (correlation values) of size width*height.
 * \param width The width of the flat band arrays.
 * \param height The height of the flat band arrays.
 * \param template_width The width of the flat template array.
 * \param template_height The height of the flat template array.
 *
 * \return 0 if the computation was successful,
 *         2 if template dimensions are not odd,
 *         1 else.
 */
LIBEXPORT int vigra_fastcrosscorrelation_c(const PixelType * arr_in,
                                           const PixelType * arr_template_in,
                                           const PixelType * arr_out,
                                           const int width,
                                           const int height,
                                           const int template_width,
                                           const int template_height);

/**
 * Computation of the fast (normalized) cross-correlation an image band w.r.t.
 * another (typically smaller) image, called template.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__Correlation.html">
 * vigra::fastNormalizedCrossCorrelation
 * </a>
 * function to C to perform a normalized cross-correlation of the image band
 * w.r.t the template. For sake of efficiency, this is performed in fourier space
 * and using integral images.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param arr_template_in Flat array (tmeplate band) of size width*height.
 * \param[out] arr_out Flat array (correlation coefficents) of size width*height.
 * \param width The width of the flat band arrays.
 * \param height The height of the flat band arrays.
 * \param template_width The width of the flat template array.
 * \param template_height The height of the flat template array.
 *
 * \return 0 if the computation was successful,
 *         2 if template dimensions are not odd,
 *         1 else.
 */
LIBEXPORT int vigra_fastnormalizedcrosscorrelation_c(const PixelType * arr_in,
                                                     const PixelType * arr_template_in,
                                                     const PixelType * arr_out,
                                                     const int width,
                                                     const int height,
                                                     const int template_width,
                                                     const int template_height);

/**
 * Extraction of the local (intensity) maxima of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__LocalMinMax.html">
 * vigra::localMaxima
 * </a> 
 * function to C to perform a filtering of an image band w.r.t. its intensity maxima,
 * which are retured as the only non-zero pixel values in the resulting image band.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_out Flat array (marks for maxima) of size width*height.
 * \param width The width of the flat band arrays.
 * \param height The height of the flat band arrays.
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 *
 * \return 0 if the local maxima finding was successful, 1 else.
 */
LIBEXPORT int vigra_localmaxima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const bool eight_connectivity);

/**
 * Extraction of the local (intensity) mniima of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__LocalMinMax.html">
 * vigra::localMinima
 * </a> 
 * function to C to perform a filtering of an image band w.r.t. its intensity minima,
 * which are retured as the only non-zero pixel values in the resulting image band.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_out Flat array (marks for minima) of size width*height.
 * \param width The width of the flat band arrays.
 * \param height The height of the flat band arrays.
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 *
 * \return 0 if the local minima finding was successful, 1 else.
 */
LIBEXPORT int vigra_localminima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const bool eight_connectivity);

/**
 * Extraction of the sub-image of an image band.
 * This function wraps the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/classvigra_1_1MultiArrayView.html">
 * vigra::MultiArrayView::subarray
 * </a>
 * function to C to extract a sub-part of an image band w.r.t. the left, upper, 
 * right, and lower margins to the original image band.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width_in*height_in
 * \param[out] arr_out Flat array (sub-image band) of size (right-left)*(lower-upper).
 * \param width_in The width of the flat input band array.
 * \param height_in The height of the flat band array.
 * \param left The left margin w.r.t. the flat input array.
 * \param upper The upper margin w.r.t. the flat input array.
 * \param right The right margin w.r.t. the flat input array.
 * \param lower The lower margin w.r.t. the flat input array.
 *
 * \return 0 if the subimage extraction was successful, 
 *         2 if right<=left or lower<=upper,
 *         1 else.
 */
LIBEXPORT int vigra_subimage_c(const PixelType * arr_in,
                               const PixelType * arr_out,
                               const int width_in,
                               const int height_in,
                               const int left,
                               const int upper,
                               const int right,
                               const int lower);

/**
 * Padding of an image band. This function padds a given image band by adding a
 * given left, upper, right, and lower border to the original image.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width_in*height_in
 * \param[out] arr_out Flat array (padded image band) of size (width_in+right+left)*(height_in+lower+upper).
 * \param width_in The width of the flat input band array.
 * \param height_in The height of the flat band array.
 * \param left The left border to be padded to the flat input array.
 * \param upper The upper border to be padded to the flat input array.
 * \param right The right border to be padded to the flat input array.
 * \param lower The lower border to be padded to the flat input array.
 *
 * \return 0 if the subimage extraction was successful, 
 *         2 if right+left=1 or lower+upper=0,
 *         1 else.
 */
LIBEXPORT int vigra_paddimage_c(const PixelType * arr_in,
                                const PixelType * arr_out,
                                const int width_in,
                                const int height_in,
                                const int left,
                                const int upper,
                                const int right,
                                const int lower);
/**
 * Clipping of the intensities of an image band to two given values.
 * The clipping sets all values below low to low, above upp to upp and
 * lets the remaining values unchanged.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_out Flat array (band) of size width*height.
 * \param width The width of the flat band arrays.
 * \param height The height of the flat band arrays.
 * \param low The lower clipping value.
 * \param upp The upper clipping value.
 *
 * \return Always 0, memory overflow for arraya of different sizes.
 */
LIBEXPORT int vigra_clipimage_c(const PixelType * arr_in,
                                const PixelType * arr_out,
                                const int width,
                                const int height,
                                const PixelType low,
                                const PixelType upp);
/**
 * @}
 */

#endif
