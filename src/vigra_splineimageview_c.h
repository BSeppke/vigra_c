/************************************************************************/
/*                                                                      */
/*               Copyright 2008-2016 by Benjamin Seppke                 */
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

#ifndef VIGRA_SPLINEIMAGEVIEW_C_H
#define VIGRA_SPLINEIMAGEVIEW_C_H

#include "config.h"

/**
 * @file
 * @brief Header file for Spline Image Views on images
 *
 * @defgroup splineimageview Spline interpolation
 * @{
 *    @brief Contains interpolation access to images with repect to Spline Interpolation.
 */

/************ POINTER BASED FUNCTIONS *****************/

#define SIV_CREATION_FUNCTION_INTERFACE(order)                                    \
/**                                                                               \
 * Creates a SplineImageView for a given image band of ##order degree.            \
 *                                                                                \
 * \param arr_in Flat input array (band) of size width*height.                    \
 * \param width The width of the flat array.                                      \
 * \param height The height of the flat array.                                    \
 *                                                                                \
 * \return a (void) pointer to the created SplineImageView of order ##order       \
 */                                                                               \
LIBEXPORT void * vigra_create_splineimageview##order##_c(const PixelType *arr_in, \
                                                         const int width,         \
                                                         const int height);
SIV_CREATION_FUNCTION_INTERFACE(1)
SIV_CREATION_FUNCTION_INTERFACE(2)
SIV_CREATION_FUNCTION_INTERFACE(3)
SIV_CREATION_FUNCTION_INTERFACE(4)
SIV_CREATION_FUNCTION_INTERFACE(5)


#define SIV_DELETION_FUNCTION_INTERFACE(order)                        \
/**                                                                   \
 * Deletes a SplineImageView of ##order degree.                       \
 *                                                                    \
 * \param siv The pointer to the SplineImageView                      \
 *                                                                    \
 * \return Always 0.                                                  \
 */                                                                   \
LIBEXPORT int vigra_delete_splineimageview##order##_c(void * siv);

SIV_DELETION_FUNCTION_INTERFACE(1)
SIV_DELETION_FUNCTION_INTERFACE(2)
SIV_DELETION_FUNCTION_INTERFACE(3)
SIV_DELETION_FUNCTION_INTERFACE(4)
SIV_DELETION_FUNCTION_INTERFACE(5)



#define SIV_OPERATION_FUNCTION_INTERFACE(function, order)                     \
/**                                                                           \
 * Accesses the ##function of a SplineImageView of ##order degree             \
 * at a given position (inside the image/spline image view)                   \
 *                                                                            \
 * \param siv The pointer to the SplineImageView                              \
 * \param x The x position                                                    \
 * \param y The y position                                                    \
 *                                                                            \
 * \return The result of the function ##function at position x,y of the       \
 *         given SplineImageView of order ##order.                            \
 */                                                                           \
LIBEXPORT float vigra_splineimageview##order##_##function##_c(void * siv,     \
                                                              const double x, \
                                                              const double y);

SIV_OPERATION_FUNCTION_INTERFACE(dx,1)
SIV_OPERATION_FUNCTION_INTERFACE(dx,2)
SIV_OPERATION_FUNCTION_INTERFACE(dx,3)
SIV_OPERATION_FUNCTION_INTERFACE(dx,4)
SIV_OPERATION_FUNCTION_INTERFACE(dx,5)

SIV_OPERATION_FUNCTION_INTERFACE(dx3,1)
SIV_OPERATION_FUNCTION_INTERFACE(dx3,2)
SIV_OPERATION_FUNCTION_INTERFACE(dx3,3)
SIV_OPERATION_FUNCTION_INTERFACE(dx3,4)
SIV_OPERATION_FUNCTION_INTERFACE(dx3,5)

SIV_OPERATION_FUNCTION_INTERFACE(dxx,1)
SIV_OPERATION_FUNCTION_INTERFACE(dxx,2)
SIV_OPERATION_FUNCTION_INTERFACE(dxx,3)
SIV_OPERATION_FUNCTION_INTERFACE(dxx,4)
SIV_OPERATION_FUNCTION_INTERFACE(dxx,5)

SIV_OPERATION_FUNCTION_INTERFACE(dxxy,1)
SIV_OPERATION_FUNCTION_INTERFACE(dxxy,2)
SIV_OPERATION_FUNCTION_INTERFACE(dxxy,3)
SIV_OPERATION_FUNCTION_INTERFACE(dxxy,4)
SIV_OPERATION_FUNCTION_INTERFACE(dxxy,5)

SIV_OPERATION_FUNCTION_INTERFACE(dxy,1)
SIV_OPERATION_FUNCTION_INTERFACE(dxy,2)
SIV_OPERATION_FUNCTION_INTERFACE(dxy,3)
SIV_OPERATION_FUNCTION_INTERFACE(dxy,4)
SIV_OPERATION_FUNCTION_INTERFACE(dxy,5)

SIV_OPERATION_FUNCTION_INTERFACE(dxyy,1)
SIV_OPERATION_FUNCTION_INTERFACE(dxyy,2)
SIV_OPERATION_FUNCTION_INTERFACE(dxyy,3)
SIV_OPERATION_FUNCTION_INTERFACE(dxyy,4)
SIV_OPERATION_FUNCTION_INTERFACE(dxyy,5)

SIV_OPERATION_FUNCTION_INTERFACE(dy,1)
SIV_OPERATION_FUNCTION_INTERFACE(dy,2)
SIV_OPERATION_FUNCTION_INTERFACE(dy,3)
SIV_OPERATION_FUNCTION_INTERFACE(dy,4)
SIV_OPERATION_FUNCTION_INTERFACE(dy,5)

SIV_OPERATION_FUNCTION_INTERFACE(dy3,1)
SIV_OPERATION_FUNCTION_INTERFACE(dy3,2)
SIV_OPERATION_FUNCTION_INTERFACE(dy3,3)
SIV_OPERATION_FUNCTION_INTERFACE(dy3,4)
SIV_OPERATION_FUNCTION_INTERFACE(dy3,5)

SIV_OPERATION_FUNCTION_INTERFACE(dyy,1)
SIV_OPERATION_FUNCTION_INTERFACE(dyy,2)
SIV_OPERATION_FUNCTION_INTERFACE(dyy,3)
SIV_OPERATION_FUNCTION_INTERFACE(dyy,4)
SIV_OPERATION_FUNCTION_INTERFACE(dyy,5)

SIV_OPERATION_FUNCTION_INTERFACE(g2,1)
SIV_OPERATION_FUNCTION_INTERFACE(g2,2)
SIV_OPERATION_FUNCTION_INTERFACE(g2,3)
SIV_OPERATION_FUNCTION_INTERFACE(g2,4)
SIV_OPERATION_FUNCTION_INTERFACE(g2,5)

SIV_OPERATION_FUNCTION_INTERFACE(g2x,1)
SIV_OPERATION_FUNCTION_INTERFACE(g2x,2)
SIV_OPERATION_FUNCTION_INTERFACE(g2x,3)
SIV_OPERATION_FUNCTION_INTERFACE(g2x,4)
SIV_OPERATION_FUNCTION_INTERFACE(g2x,5)

SIV_OPERATION_FUNCTION_INTERFACE(g2xx,1)
SIV_OPERATION_FUNCTION_INTERFACE(g2xx,2)
SIV_OPERATION_FUNCTION_INTERFACE(g2xx,3)
SIV_OPERATION_FUNCTION_INTERFACE(g2xx,4)
SIV_OPERATION_FUNCTION_INTERFACE(g2xx,5)

SIV_OPERATION_FUNCTION_INTERFACE(g2xy,1)
SIV_OPERATION_FUNCTION_INTERFACE(g2xy,2)
SIV_OPERATION_FUNCTION_INTERFACE(g2xy,3)
SIV_OPERATION_FUNCTION_INTERFACE(g2xy,4)
SIV_OPERATION_FUNCTION_INTERFACE(g2xy,5)

SIV_OPERATION_FUNCTION_INTERFACE(g2y,1)
SIV_OPERATION_FUNCTION_INTERFACE(g2y,2)
SIV_OPERATION_FUNCTION_INTERFACE(g2y,3)
SIV_OPERATION_FUNCTION_INTERFACE(g2y,4)
SIV_OPERATION_FUNCTION_INTERFACE(g2y,5)

SIV_OPERATION_FUNCTION_INTERFACE(g2yy,1)
SIV_OPERATION_FUNCTION_INTERFACE(g2yy,2)
SIV_OPERATION_FUNCTION_INTERFACE(g2yy,3)
SIV_OPERATION_FUNCTION_INTERFACE(g2yy,4)
SIV_OPERATION_FUNCTION_INTERFACE(g2yy,5)

#define SIV_ACCESSOR_FUNCTION_INTERFACE(order)                            \
/**                                                                       \
 * Accesses the grayvalue of a SplineImageView of ##order degree          \
 * at a given position (inside the image/spline image view)               \
 *                                                                        \
 * \param siv The pointer to the SplineImageView                          \
 * \param x The x position                                                \
 * \param y The y position                                                \
 *                                                                        \
 * \return The grayvalue at position x,y of th given SplineImageView      \
 *          of order ##order.                                             \
 */                                                                       \
LIBEXPORT float vigra_splineimageview##order##_accessor_c(void * siv,     \
                                                          const double x, \
                                                          const double y);
SIV_ACCESSOR_FUNCTION_INTERFACE(1)
SIV_ACCESSOR_FUNCTION_INTERFACE(2)
SIV_ACCESSOR_FUNCTION_INTERFACE(3)
SIV_ACCESSOR_FUNCTION_INTERFACE(4)
SIV_ACCESSOR_FUNCTION_INTERFACE(5)




/************ ADDRESS BASED FUNCTIONS' INTERFACE *****************/

#define SIV_ADDRESS_CREATION_FUNCTION_INTERFACE(order)                                           \
/**                                                                                              \
 * Creates a SplineImageView for a given image band of ##order degree.                           \
 *                                                                                               \
 * \param arr_in Flat input array (band) of size width*height.                                   \
 * \param width The width of the flat array.                                                     \
 * \param height The height of the flat array.                                                   \
 *                                                                                               \
 * \return The adress to the created SplineImageView of order ##order                            \
 */                                                                                              \
LIBEXPORT unsigned long vigra_create_splineimageview##order##_address_c(const PixelType *arr_in, \
                                                                        const int width,         \
                                                                        const int height);
SIV_ADDRESS_CREATION_FUNCTION_INTERFACE(1)
SIV_ADDRESS_CREATION_FUNCTION_INTERFACE(2)
SIV_ADDRESS_CREATION_FUNCTION_INTERFACE(3)
SIV_ADDRESS_CREATION_FUNCTION_INTERFACE(4)
SIV_ADDRESS_CREATION_FUNCTION_INTERFACE(5)


#define SIV_DELETION_BY_ADDRESS_FUNCTION_INTERFACE(order)                                     \
/**                                                                                           \
 * Deletes a SplineImageView of ##order degree.                                               \
 *                                                                                            \
 * \param address The adress to the SplineImageView                                           \
 *                                                                                            \
 * \return Always 0.                                                                          \
 */                                                                                           \
LIBEXPORT int vigra_delete_splineimageview##order##_by_address_c(const unsigned long address);

SIV_DELETION_BY_ADDRESS_FUNCTION_INTERFACE(1)
SIV_DELETION_BY_ADDRESS_FUNCTION_INTERFACE(2)
SIV_DELETION_BY_ADDRESS_FUNCTION_INTERFACE(3)
SIV_DELETION_BY_ADDRESS_FUNCTION_INTERFACE(4)
SIV_DELETION_BY_ADDRESS_FUNCTION_INTERFACE(5)


#define SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(function, order)                                  \
/**                                                                                                   \
 * Accesses the ##function of a SplineImageView of ##order degree                                     \
 * at a given position (inside the image/spline image view)                                           \
 *                                                                                                    \
 * \param address The address to the SplineImageView                                                  \
 * \param x The x position                                                                            \
 * \param y The y position                                                                            \
 *                                                                                                    \
 * \return The result of the function ##function at position x,y of the                               \
 *         given SplineImageView of order ##order.                                                    \
 */                                                                                                   \
LIBEXPORT float vigra_splineimageview##order##_##function##_by_address_c(const unsigned long address, \
                                                                         const double x,              \
                                                                         const double y);

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx3,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx3,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx3,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx3,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dx3,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxxy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxxy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxxy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxxy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxxy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxyy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxyy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxyy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxyy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dxyy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy3,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy3,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy3,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy3,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dy3,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dyy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dyy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dyy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dyy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(dyy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2x,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2x,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2x,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2x,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2x,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2xy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2y,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2y,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2y,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2y,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2y,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2yy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2yy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2yy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2yy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION_INTERFACE(g2yy,5)


#define SIV_ACCESSOR_BY_ADDRESS_FUNCTION_INTERFACE(order)                                         \
/**                                                                                               \
 * Accesses the grayvalue of a SplineImageView of ##order degree                                  \
 * at a given position (inside the image/spline image view)                                       \
 *                                                                                                \
 * \param address The address to the SplineImageView                                              \
 * \param x The x position                                                                        \
 * \param y The y position                                                                        \
 *                                                                                                \
 * \return The grayvalue at position x,y of th given SplineImageView of order ##order.            \
 */                                                                                               \
LIBEXPORT float vigra_splineimageview##order##_accessor_by_address_c(const unsigned long address, \
                                                                     const double x,              \
                                                                     const double y);
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_INTERFACE(1)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_INTERFACE(2)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_INTERFACE(3)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_INTERFACE(4)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION_INTERFACE(5)

/**
 * @}
 */

#endif
