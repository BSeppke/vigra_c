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

#ifndef VIGRA_IMPEX_C_H
#define VIGRA_IMPEX_C_H

#include "config.h"

/**
 * @file
 * @brief Header file for image import and export
 *
 * @defgroup impex Image import and export
 * @{
 *    @brief Image import and export facilities.
 */
 
/**
 * Import of a grayscale image from filesystem into a single band array.
 * This function checks if an image exists on file system and if it is grayscale.
 * If so, it is imported into the given flat array, which needs already to 
 * be allocated at correct size (width*hight).
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param[out] arr_out The flat (band) array for the image of size width*height.
 * \param width The width of the flat input band array.
 * \param height The height of the flat band array.
 * \param filename The filename of the image to be loaded.
 *
 * \return 0 if the grayscale image was imported from filesystem,
 *         2 if the image is not grayscale,
 *         3 if the dimensions do not fit to the image,
 *         1 else.
 */
LIBEXPORT int vigra_importgrayimage_c(const PixelType * arr_out,
                                      const int width,
                                      const int height,
                                      const char * filename);

/**
 * Import of an RGB image from filesystem into three single band arrays.
 * This function checks if an image exists on file system and if it is RGB.
 * If so, it is imported into the three given flat arrays, which needs already to
 * be allocated at correct size (width*hight each).
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param[out] arr_r_out The flat (red band) array for the image of size width*height.
 * \param[out] arr_g_out The flat (green band) array for the image of size width*height.
 * \param[out] arr_b_out The flat (blue band) array for the image of size width*height.
 * \param width The width of the flat input band array.
 * \param height The height of the flat band array.
 * \param filename The filename of the image to be loaded.
 *
 * \return 0 if the grayscale image was imported from filesystem,
 *         2 if the image is not grayscale,
 *         3 if the dimensions do not fit to the image,
 *         1 else.
 */
LIBEXPORT int vigra_importrgbimage_c(const PixelType * arr_r_out,
                                     const PixelType * arr_g_out,
                                     const PixelType * arr_b_out,
                                     const int width,
                                     const int height,
                                     const char * filename);

/**
 * Import of an ARGB image from filesystem into four single band arrays.
 * This function checks if an image exists on file system and if it is RGB with
 * at least one additional alpha band.
 * If so, it is imported into the four given flat arrays, which needs already to
 * be allocated at correct size (width*hight each).
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param[out] arr_r_out The flat (red band) array for the image of size width*height.
 * \param[out] arr_g_out The flat (green band) array for the image of size width*height.
 * \param[out] arr_b_out The flat (blue band) array for the image of size width*height.
 * \param[out] arr_a_out The flat (alpha band) array for the image of size width*height.
 * \param width The width of the flat input band array.
 * \param height The height of the flat band array.
 * \param filename The filename of the image to be loaded.
 *
 * \return 0 if the grayscale image was imported from filesystem,
 *         2 if the image is not grayscale,
 *         3 if the dimensions do not fit to the image,
 *         1 else.
 */
LIBEXPORT int vigra_importrgbaimage_c(const PixelType * arr_r_out,
                                      const PixelType * arr_g_out,
                                      const PixelType * arr_b_out,
                                      const PixelType * arr_a_out,
                                      const int width,
                                      const int height,
                                      const char * filename);

/**
 * Export of a grayscale image from a single band array to file system.
 * This function writes the given band as a grayvalue image to the file system.
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param arr_in The flat (band) array for the image of size width*height.
 * \param width The width of the flat input band array.
 * \param height The height of the flat band array.
 * \param filename The filename of the image to be saved.
 *
 * \return 0 if the grayscale image was saved to the filesystem, 1 else.
 */
LIBEXPORT int vigra_exportgrayimage_c(const PixelType * arr_in,
                                      const int width,
                                      const int height,
                                      const char * filename);

/**
 * Export of an RGB image from three single band arrays to file system.
 * This function writes the given bands as a RGB image to the file system.
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param arr_r_in The flat (red band) array for the image of size width*height.
 * \param arr_g_in The flat (green band) array for the image of size width*height.
 * \param arr_b_in The flat (blue band) array for the image of size width*height.
 * \param width The width of the flat input band array.
 * \param height The height of the flat band array.
 * \param filename The filename of the image to be saved.
 *
 * \return 0 if the RGB image was saved to the filesystem, 1 else.
 */
LIBEXPORT int vigra_exportrgbimage_c(const PixelType * arr_r_in,
                                     const PixelType * arr_g_in,
                                     const PixelType * arr_b_in,
                                     const int width,
                                     const int height,
                                     const char * filename);

/**
 * Export of an RGBA image from four single band arrays to file system.
 * This function writes the given bands as a RGBA image to the file system.
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param arr_r_in The flat (red band) array for the image of size width*height.
 * \param arr_g_in The flat (green band) array for the image of size width*height.
 * \param arr_b_in The flat (blue band) array for the image of size width*height.
 * \param arr_a_in The flat (alpha band) array for the image of size width*height.
 * \param width The width of the flat input band array.
 * \param height The height of the flat band array.
 * \param filename The filename of the image to be saved.
 *
 * \return 0 if the RGBA image was saved to the filesystem, 1 else.
 */
LIBEXPORT int vigra_exportrgbaimage_c(const PixelType * arr_r_in,
                                      const PixelType * arr_g_in,
                                      const PixelType * arr_b_in,
                                      const PixelType * arr_a_in,
                                      const int width,
                                      const int height,
                                      const char * filename);

/**
 * This function returns the image width of a given filename without importing
 * the data of that image from filesystem.
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param filename the file name of the image
 *
 * \return 0,   if an error occured or the image has no width,
 *         else the width of the image.
 */
LIBEXPORT int vigra_imagewidth_c(const char * filename);

/**
 * This function returns the image height of a given filename without importing
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param filename the file name of the image
 *
 * \return 0,   if an error occured or the image has no height,
 *         else the height of the image.
 */
LIBEXPORT int vigra_imageheight_c(const char * filename);

/**
 * This function returns the number of bands of an image of a given filename 
 * without importing the data of that image from filesystem.
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param filename the file name of the image
 *
 * \return 0,    if an error occured or the image has no bands,
 *         else  the number of bands of the image.
 */
LIBEXPORT int vigra_imagenumbands_c(const char * filename);

/**
 * This function returns the number of addiation (alpha-)bands of an image of a
 * given filename without importing the data of that image from filesystem.
 *
 * For more information, refer to the
 * <a href="https://ukoethe.github.io/vigra/doc-release/vigra/group__VigraImpex.html">
 * vigra Import/Export documentation
 * </a>.
 *
 * \param filename the file name of the image
 *
 * \return 0,   if an error occured or there are no additional bands,
 *         else the number of extra bands of the image.
 */
LIBEXPORT int vigra_imagenumextrabands_c(const char * filename);


/**
 * @}
 */
 
#endif
