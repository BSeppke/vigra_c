#ifndef VIGRA_IMGPROC_C_H
#define VIGRA_IMGPROC_C_H

#include "config.h"

/**
 * Resizing of image bands. This function wraps the vigra::resizeImageSplineInterpolation
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
 * Rotation of image bands. This function wraps the vigra::rotateImage
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
 * Affine warping of image bands. This function wraps the vigra::affineWarpImage
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
 * Reflection of image bands w.r.t. the image axes. This function wraps the 
 * vigra::reflectImage function to C to perform a reflection along each or both
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
 * This function wraps the vigra::fourierTransform function to C to perform an
 * FFT of the image band and centers the DC after transformation. Internally, 
 * this performs a thread safe call of the FFTW lib's tranformation fucntions.
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
 * Computation of the fast (un-normalized) cross-correlation an image band w.r.t.
 * another (typically smaller) image, called template.
 * This function wraps the vigra::fastCrossCorrelation function to C to perform an
 * cross-correlation of the image band w.r.t the template. For sake of efficiency,
 * this is performed in fourier space.
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
 * This function wraps the vigra::fastNormalizedCrossCorrelation function to C to perform an
 * normalized cross-correlation of the image band w.r.t the template. For sake of efficiency,
 * this is performed in fourier space and using integral images.
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
 * This function wraps the vigra::localMaxima function to C to perform a filtering
 * of image band w.r.t. its intensity maxima, which are retured as the only
 * non-zero pixel values in the resulting image band.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_out Flat array (marks for maxima) of size width*height.
 * \param width The width of the flat band arrays.
 * \param height The height of the flat band arrays.
 *
 * \return 0 if the local maxima finding was successful, 1 else.
 */
LIBEXPORT int vigra_localmaxima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height);

/**
 * Extraction of the local (intensity) mniima of an image band.
 * This function wraps the vigra::localMinima function to C to perform a filtering
 * of image band w.r.t. its intensity minima,  which are retured as the only
 * non-zero pixel values in the resulting image band.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height
 * \param[out] arr_out Flat array (marks for minima) of size width*height.
 * \param width The width of the flat band arrays.
 * \param height The height of the flat band arrays.
 *
 * \return 0 if the local minima finding was successful, 1 else.
 */
LIBEXPORT int vigra_localminima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height);

/**
 * Extraction of the sub-image of an image band.
 * This function wraps the vigra::MultiArray::subarray function to C to extract a
 * of image band w.r.t. the left, upper, right, and lower margins to the original
 * image.
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

#endif
