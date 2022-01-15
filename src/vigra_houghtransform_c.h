/************************************************************************/
/*                                                                      */
/*               Copyright 2020-2022 by Benjamin Seppke                 */
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

#ifndef VIGRA_HOUGHTRANSFORM_C_H
#define VIGRA_HOUGHTRANSFORM_C_H

#include "config.h"

/**
 * @file
 * @brief Header file for hough transforms
 *
 * @defgroup hough Hough transforms
 * @{
 *    @brief Hough transforms, which may be used to find lines and circles in binary images
 */
 
 /**
  * Computation of the hough transform for lines.
  * All arrays must have been allocated before the call of this function.
  *
  * \param arr_in Flat input array (band) of size width*height.
  * \param width The width of the flat array.
  * \param height The height of the flat array.
  * \param angles Count of Angular division: 360 means 1 degree precision.
  * \param min_supporters minimal suppporters needed for a "find". 
  *
  * \return Pointer to HougLines structure.
  */
 LIBEXPORT void* vigra_houghtransform_lines_c(const PixelType * arr_in,
     const int width,
     const int height,
     const int angles,
     const int min_supporters);
     
/**
 * Get the count of hough lines from the given hough lines structure.
 * \param hough_lines Pointer to the hough lines structure
 * \result Number of lines, 0 on error.
 */
LIBEXPORT int vigra_houghtransform_get_line_count_c(const void * hough_lines);

/**
 * Getter for the found hough lines.
 * All arrays must have been allocated before the call of this function.
 *
 * \param hough_lines Pointer to the hough lines structure
 * \param arr_out Flat input array (band) of size width*height.
 * \param width The width of the flat array (must be 3)
 * \param height The height of the flat array (must be vigra_houghtransform_get_line_count_c(hough_lines)
 *
 * \return 0 on sucess, else 1.
 */
LIBEXPORT int vigra_houghtransform_get_lines_c(const void * hough_lines,
    PixelType * arr_out,
    const int width,
    const int height);
    
/**
 * Frees the given hough lines structure.
 *  \param hough_lines Pointer to the hough lines structure
 *  \return 0 on success, else 1.
 */
LIBEXPORT int vigra_houghtransform_delete_lines_c(void * hough_lines);


/**
 * Computation of the hough transform for circles.
 * All arrays must have been allocated before the call of this function.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 * \param min_radius Minimal radius of the circles.
 * \param max_radius Maximal radius of the circles.
 * \param min_supporters minimal suppporters needed for a "find".
 *
 * \return Pointer to HougLines structure.
 */
LIBEXPORT void* vigra_houghtransform_circles_c(const PixelType * arr_in,
    const int width,
    const int height,
    const int min_radius,
    const int max_radius,
    const int min_supporters);

/**
 * Get the count of hough circles from the given hough circles structure.
 * \param hough_circles Pointer to the hough circles structure
 * \result Number of circles, 0 on error.
 */
LIBEXPORT int vigra_houghtransform_get_circle_count_c(const void * hough_cicles);

/**
 * Getter for the found hough circles.
 * All arrays must have been allocated before the call of this function.
 *
 * \param hough_circles Pointer to the hough liness structure
 * \param arr_out Flat input array (band) of size width*height.
 * \param width The width of the flat array (must be 4)
 * \param height The height of the flat array (must be vigra_houghtransform_get_circle_count_c(hough_circles)
 *
 * \return 0 on sucess, else 1.
 */
 LIBEXPORT int vigra_houghtransform_get_circles_c(const void * hough_circles,
    PixelType * arr_out,
    const int width,
    const int height);

/**
 * Frees the given hough circles structure.
 * \param hough_circles Pointer to the hough curcles structure
 * \return 0 on success, else 1.
 */
LIBEXPORT int vigra_houghtransform_delete_circles_c(void * hough_circles);

/**
 * @}
 */
 
#endif
