#ifndef VIGRA_MORPHOLOGY_C_H
#define VIGRA_MORPHOLOGY_C_H

#include "config.h"


LIBEXPORT int vigra_distancetransform_c(const PixelType * arr_in,
                                        const PixelType * arr_out,
                                        const int width,
                                        const int height,
                                        const float background_label,
                                        const int norm);

LIBEXPORT int vigra_discerosion_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const int radius);

LIBEXPORT int vigra_discdilation_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int radius);

LIBEXPORT int vigraext_upwind_c(const PixelType * arr_in,
                                const PixelType * arr_fac_in,
                                const PixelType * arr_out,
                                const int width,
                                const int height,
                                const float weight);

#endif
