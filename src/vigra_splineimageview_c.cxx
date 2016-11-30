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

#include "vigra_splineimageview_c.h"
#include <vigra/splineimageview.hxx>


/**
 * @file
 * @brief Implementation of Spline Image Views on images
 */


/************ CONVENIENT TYPEDEFS *****************/
/** 
 * SplineImageView using B-Splines or first order
 */
typedef vigra::SplineImageView<1, float> SplineImageView1;
/** 
 * SplineImageView using B-Splines or second order
 */
typedef vigra::SplineImageView<2, float> SplineImageView2;
/** 
 * SplineImageView using B-Splines or third order
 */
typedef vigra::SplineImageView<3, float> SplineImageView3;
/** 
 * SplineImageView using B-Splines or fourth order
 */
typedef vigra::SplineImageView<4, float> SplineImageView4;
/** 
 * SplineImageView using B-Splines or fifth order
 */
typedef vigra::SplineImageView<5, float> SplineImageView5;




/************ POINTER BASED FUNCTIONS *****************/

/**
 * Defines a preprocessor macro for the spline image view access
 */
#define SIV_CREATION_FUNCTION(order)                                              \
/**
 * Creates a SplineImageView for a given image band of degree order.
 *
 * \param arr_in Flat input array (band) of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the flat array.
 *
 * \return a (void) pointer to the created SplineImageView of degree order.
 */                                                                               \
LIBEXPORT void * vigra_create_splineimageview##order##_c(const PixelType *arr_in, \
                                                         const int width,         \
                                                         const int height)	      \
{                                                                                 \
  ImageView img(vigra::Shape2(width, height), arr_in);							  \
  return new SplineImageView##order (img);								          \
}

SIV_CREATION_FUNCTION(1)
SIV_CREATION_FUNCTION(2)
SIV_CREATION_FUNCTION(3)
SIV_CREATION_FUNCTION(4)
SIV_CREATION_FUNCTION(5)


/**
 * Defines a preprocessor macro for the spline image view deletion
 */
#define SIV_DELETION_FUNCTION(order)                                  \
/**                                                                   \
 * Deletes a SplineImageView of ##order degree.                       \
 *                                                                    \
 * \param siv The pointer to the SplineImageView                      \
 *                                                                    \
 * \return Always 0.                                                  \
 */                                                                   \
LIBEXPORT int vigra_delete_splineimageview##order##_c(void * siv)     \
{                                                                     \
  SplineImageView##order * siv_ptr = (SplineImageView##order * ) siv; \
  delete siv_ptr;                                                     \
  return 0;                                                           \
}

SIV_DELETION_FUNCTION(1)
SIV_DELETION_FUNCTION(2)
SIV_DELETION_FUNCTION(3)
SIV_DELETION_FUNCTION(4)
SIV_DELETION_FUNCTION(5)


/**
 * Defines a preprocessor macro for the spline image view function access
 */
#define SIV_OPERATION_FUNCTION(function, order)                               \
/**
  Accesses the ##function of a SplineImageView of degree order
  at a given position (inside the image/spline image view)

  \param siv The pointer to the SplineImageView
  \param x The x position
  \param y The y position

  \return The result of the function at position x,y of the
          given SplineImageView of degree order.
 */                                                                           \
LIBEXPORT float vigra_splineimageview##order##_##function##_c(void * siv,     \
                                                              const double x, \
                                                              const double y) \
{                                                                             \
  SplineImageView##order * siv_ptr = (SplineImageView##order * ) siv;         \
	return siv_ptr -> function (x,y);                                         \
}

SIV_OPERATION_FUNCTION(dx,1)
SIV_OPERATION_FUNCTION(dx,2)
SIV_OPERATION_FUNCTION(dx,3)
SIV_OPERATION_FUNCTION(dx,4)
SIV_OPERATION_FUNCTION(dx,5)

SIV_OPERATION_FUNCTION(dx3,1)
SIV_OPERATION_FUNCTION(dx3,2)
SIV_OPERATION_FUNCTION(dx3,3)
SIV_OPERATION_FUNCTION(dx3,4)
SIV_OPERATION_FUNCTION(dx3,5)

SIV_OPERATION_FUNCTION(dxx,1)
SIV_OPERATION_FUNCTION(dxx,2)
SIV_OPERATION_FUNCTION(dxx,3)
SIV_OPERATION_FUNCTION(dxx,4)
SIV_OPERATION_FUNCTION(dxx,5)

SIV_OPERATION_FUNCTION(dxxy,1)
SIV_OPERATION_FUNCTION(dxxy,2)
SIV_OPERATION_FUNCTION(dxxy,3)
SIV_OPERATION_FUNCTION(dxxy,4)
SIV_OPERATION_FUNCTION(dxxy,5)

SIV_OPERATION_FUNCTION(dxy,1)
SIV_OPERATION_FUNCTION(dxy,2)
SIV_OPERATION_FUNCTION(dxy,3)
SIV_OPERATION_FUNCTION(dxy,4)
SIV_OPERATION_FUNCTION(dxy,5)

SIV_OPERATION_FUNCTION(dxyy,1)
SIV_OPERATION_FUNCTION(dxyy,2)
SIV_OPERATION_FUNCTION(dxyy,3)
SIV_OPERATION_FUNCTION(dxyy,4)
SIV_OPERATION_FUNCTION(dxyy,5)

SIV_OPERATION_FUNCTION(dy,1)
SIV_OPERATION_FUNCTION(dy,2)
SIV_OPERATION_FUNCTION(dy,3)
SIV_OPERATION_FUNCTION(dy,4)
SIV_OPERATION_FUNCTION(dy,5)

SIV_OPERATION_FUNCTION(dy3,1)
SIV_OPERATION_FUNCTION(dy3,2)
SIV_OPERATION_FUNCTION(dy3,3)
SIV_OPERATION_FUNCTION(dy3,4)
SIV_OPERATION_FUNCTION(dy3,5)

SIV_OPERATION_FUNCTION(dyy,1)
SIV_OPERATION_FUNCTION(dyy,2)
SIV_OPERATION_FUNCTION(dyy,3)
SIV_OPERATION_FUNCTION(dyy,4)
SIV_OPERATION_FUNCTION(dyy,5)

SIV_OPERATION_FUNCTION(g2,1)
SIV_OPERATION_FUNCTION(g2,2)
SIV_OPERATION_FUNCTION(g2,3)
SIV_OPERATION_FUNCTION(g2,4)
SIV_OPERATION_FUNCTION(g2,5)

SIV_OPERATION_FUNCTION(g2x,1)
SIV_OPERATION_FUNCTION(g2x,2)
SIV_OPERATION_FUNCTION(g2x,3)
SIV_OPERATION_FUNCTION(g2x,4)
SIV_OPERATION_FUNCTION(g2x,5)

SIV_OPERATION_FUNCTION(g2xx,1)
SIV_OPERATION_FUNCTION(g2xx,2)
SIV_OPERATION_FUNCTION(g2xx,3)
SIV_OPERATION_FUNCTION(g2xx,4)
SIV_OPERATION_FUNCTION(g2xx,5)

SIV_OPERATION_FUNCTION(g2xy,1)
SIV_OPERATION_FUNCTION(g2xy,2)
SIV_OPERATION_FUNCTION(g2xy,3)
SIV_OPERATION_FUNCTION(g2xy,4)
SIV_OPERATION_FUNCTION(g2xy,5)

SIV_OPERATION_FUNCTION(g2y,1)
SIV_OPERATION_FUNCTION(g2y,2)
SIV_OPERATION_FUNCTION(g2y,3)
SIV_OPERATION_FUNCTION(g2y,4)
SIV_OPERATION_FUNCTION(g2y,5)

SIV_OPERATION_FUNCTION(g2yy,1)
SIV_OPERATION_FUNCTION(g2yy,2)
SIV_OPERATION_FUNCTION(g2yy,3)
SIV_OPERATION_FUNCTION(g2yy,4)
SIV_OPERATION_FUNCTION(g2yy,5)

/**
 * Defines a preprocessor macro for the spline image view access interface
 */
#define SIV_ACCESSOR_FUNCTION(order)                                      \
/**
  Accesses the grayvalue of a SplineImageView of degree order
  at a given position (inside the image/spline image view)

  \param siv The pointer to the SplineImageView
  \param x The x position
  \param y The y position

  \return The grayvalue at position x,y of th given SplineImageView
           of degree order.
 */                                                                       \
LIBEXPORT float vigra_splineimageview##order##_accessor_c(void * siv,     \
                                                          const double x, \
                                                          const double y) \
{                                                                         \
  SplineImageView##order * siv_ptr = (SplineImageView##order * ) siv;     \
	return (* siv_ptr)(x,y);                                              \
}

SIV_ACCESSOR_FUNCTION(1)
SIV_ACCESSOR_FUNCTION(2)
SIV_ACCESSOR_FUNCTION(3)
SIV_ACCESSOR_FUNCTION(4)
SIV_ACCESSOR_FUNCTION(5)




/************ ADDRESS BASED FUNCTIONS *****************/

/**
 * Defines a preprocessor macro for the address-based spline image view creation
 */
#define SIV_ADDRESS_CREATION_FUNCTION(order)                                                     \
/**
  Creates a SplineImageView for a given image band of degree order.

  \param arr_in Flat input array (band) of size width*height.
  \param width The width of the flat array.
  \param height The height of the flat array.

   \return The adress to the created SplineImageView of degree order
 */                                                                                              \
LIBEXPORT unsigned long vigra_create_splineimageview##order##_address_c(const PixelType *arr_in, \
                                                                        const int width,         \
                                                                        const int height)	     \
{                                                                                                \
  ImageView img(vigra::Shape2(width, height), arr_in);                                           \
  SplineImageView##order* siv = new SplineImageView##order(img);                                 \
  return (unsigned long) siv;                                                                    \
}

SIV_ADDRESS_CREATION_FUNCTION(1)
SIV_ADDRESS_CREATION_FUNCTION(2)
SIV_ADDRESS_CREATION_FUNCTION(3)
SIV_ADDRESS_CREATION_FUNCTION(4)
SIV_ADDRESS_CREATION_FUNCTION(5)

/**
 * Defines a preprocessor macro for the address-based spline image view deletion
 */
#define SIV_DELETION_BY_ADDRESS_FUNCTION(order)                                               \
/**
  Deletes a SplineImageView of degree order.

  \param address The adress to the SplineImageView of degree order

  \return Always 0.
 */                                                                                           \
LIBEXPORT int vigra_delete_splineimageview##order##_by_address_c(const unsigned long address) \
{                                                                                             \
  SplineImageView##order * siv = (SplineImageView##order * ) address;                         \
  delete siv;                                                                                 \
  return 0;                                                                                   \
}

SIV_DELETION_BY_ADDRESS_FUNCTION(1)
SIV_DELETION_BY_ADDRESS_FUNCTION(2)
SIV_DELETION_BY_ADDRESS_FUNCTION(3)
SIV_DELETION_BY_ADDRESS_FUNCTION(4)
SIV_DELETION_BY_ADDRESS_FUNCTION(5)


/**
 * Defines a preprocessor macro for the address-based spline image view function access
 */
#define SIV_OPERATION_BY_ADDRESS_FUNCTION(function, order)                                            \
/**
  Accesses the function of a SplineImageView of degree order
  at a given position (inside the image/spline image view)

  \param address The address to the SplineImageView
  \param x The x position
  \param y The y position

  \return The result of function at position x,y of the
           given SplineImageView of degree order.
 */                                                                                                   \
LIBEXPORT float vigra_splineimageview##order##_##function##_by_address_c(const unsigned long address, \
                                                                         const double x,              \
                                                                         const double y)	          \
{                                                                                                     \
  SplineImageView##order * siv = (SplineImageView##order * ) address;                                 \
  return siv -> function (x,y);                                                                       \
}

SIV_OPERATION_BY_ADDRESS_FUNCTION(dx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dx3,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx3,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx3,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx3,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dx3,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dxx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dxxy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxxy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxxy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxxy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxxy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dxy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dxyy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxyy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxyy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxyy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dxyy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dy3,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy3,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy3,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy3,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dy3,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(dyy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dyy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dyy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dyy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(dyy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(g2,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(g2x,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2x,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2x,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2x,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2x,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xx,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xx,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xx,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xx,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xx,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2xy,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(g2y,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2y,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2y,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2y,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2y,5)

SIV_OPERATION_BY_ADDRESS_FUNCTION(g2yy,1)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2yy,2)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2yy,3)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2yy,4)
SIV_OPERATION_BY_ADDRESS_FUNCTION(g2yy,5)

/**
 * Defines a preprocessor macro for the address-based spline image view access
 */
#define SIV_ACCESSOR_BY_ADDRESS_FUNCTION(order)                                                   \
/**
  Accesses the grayvalue of a SplineImageView of degree order
  at a given position (inside the image/spline image view)

  \param address The address to the SplineImageView
  \param x The x position
  \param y The y position

  \return The grayvalue at position x,y of th given SplineImageView of degree order.
 */                                                                                               \
LIBEXPORT float vigra_splineimageview##order##_accessor_by_address_c(const unsigned long address, \
                                                                     const double x,              \
                                                                     const double y)	          \
{                                                                                                 \
  SplineImageView##order * siv = (SplineImageView##order *) address;                              \
  return (* siv)(x,y);                                                                            \
}

SIV_ACCESSOR_BY_ADDRESS_FUNCTION(1)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(2)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(3)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(4)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(5)
