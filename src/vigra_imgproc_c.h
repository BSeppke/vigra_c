#ifndef VIGRA_IMGPROC_C_H
#define VIGRA_IMGPROC_C_H

#include "config.h"


LIBEXPORT int vigra_resizeimage_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width_in,
                                  const int height_in,
                                  const int width_out,
                                  const int height_out,
                                  const int resample_method);

LIBEXPORT int vigra_rotateimage_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const float angle,
                                  const int resample_method);

LIBEXPORT int vigra_affinewarpimage_c(const PixelType * arr_in,
                                      const PixelType * arr_out,
                                      double * affineMatrix,
                                      const int width,
                                      const int height,
                                      const int resample_method);

LIBEXPORT int vigra_reflectimage_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int reflect_method);

LIBEXPORT int vigra_fouriertransform_c(const PixelType * arr_in,
                                       const PixelType * arr_real_out,
                                       const PixelType * arr_imag_out,
                                       const int width,
                                       const int height);

LIBEXPORT int vigra_fastcrosscorrelation_c(const PixelType * arr_in,
                                           const PixelType * arr_mask_in,
                                           const PixelType * arr_out,
                                           const int width,
                                           const int height,
                                           const int mask_width,
                                           const int mask_height);

LIBEXPORT int vigra_fastnormalizedcrosscorrelation_c(const PixelType * arr_in,
                                                     const PixelType * arr_mask_in,
                                                     const PixelType * arr_out,
                                                     const int width,
                                                     const int height,
                                                     const int mask_width,
                                                     const int mask_height);

LIBEXPORT int vigra_localmaxima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height);

LIBEXPORT int vigra_localminima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height);

LIBEXPORT int vigra_subimage_c(const PixelType * arr_in,
                               const PixelType * arr_out,
                               const int width_in,
                               const int height_in,
                               const int left,
                               const int upper,
                               const int right,
                               const int lower);

LIBEXPORT int vigra_paddimage_c(const PixelType * arr_in,
                                const PixelType * arr_out,
                                const int width_in,
                                const int height_in,
                                const int left,
                                const int upper,
                                const int right,
                                const int lower);

#endif
