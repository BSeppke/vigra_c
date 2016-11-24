#ifndef VIGRA_MORPHOLOGY_C_H
#define VIGRA_MORPHOLOGY_C_H

#include "config.h"

/**
 * Computation of the distance transform.
 * This function wraps the vigra::distanceTransform function to C to compute
 * the distance transform for a (binary) image band w.r.t. a given background label
 * and a L-distance norm. 
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (distance transform) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param backgound_label The intensity of the background.
 * \param norm The norm of the distance, 0-max, 1-block, 2-euclidean.
 *
 * \return 0 if the distanceTransform was successful,
 *         2 if the norm is <0 or >2,
 *         1 else.
 */
LIBEXPORT int vigra_distancetransform_c(const PixelType * arr_in,
                                        const PixelType * arr_out,
                                        const int width,
                                        const int height,
                                        const float background_label,
                                        const int norm);

/**
 * Computation of the morpholgical erosion operator.
 * This function wraps the vigra::discErosion function to C to compute
 * the erosion for a binary image band w.r.t. a given disc radius.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (eroded) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param radius The radius of the erosion mask.
 *
 * \return 0 if the erosion was successful, 1 else.
 */
LIBEXPORT int vigra_discerosion_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const int radius);

/**
 * Computation of the morpholgical dilation operator.
 * This function wraps the vigra::discDilation function to C to compute
 * the dilation for a binary image band w.r.t. a given disc radius.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_out Flat array (dilated) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param radius The radius of the dilation mask.
 *
 * \return 0 if the dilation was successful, 1 else.
 */
LIBEXPORT int vigra_discdilation_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int radius);

/**
 * Computation of the morpholgical upwdind operator.
 * This function wraps the vigra::upwindImage function to C to compute
 * the upwinding for a binary image band w.r.t. a given factor array of same
 * size and a constant weight.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param[out] arr_fac_in Flat array (upwinding factors) of size width*height.
 * \param[out] arr_out Flat array (upwinded) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param weight The constant upwinding weight.
 *
 * \return 0 if the upwinding was successful, 1 else.
 */
LIBEXPORT int vigra_upwindimage_c(const PixelType * arr_in,
                                  const PixelType * arr_fac_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const float weight);

#endif
