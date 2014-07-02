#include "vigra_splineimageview_c.h"

#include <vigra/splineimageview.hxx>


typedef vigra::SplineImageView<1, float> SplineImageView1;
typedef vigra::SplineImageView<2, float> SplineImageView2;
typedef vigra::SplineImageView<3, float> SplineImageView3;
typedef vigra::SplineImageView<4, float> SplineImageView4;
typedef vigra::SplineImageView<5, float> SplineImageView5;

/************ POINTER BASED FUNCTIONS *****************/

#define SIV_CREATION_FUNCTION(splineDegree) \
LIBEXPORT void * vigra_create_splineimageview##splineDegree##_c (const float *arr, const int width, const int height)	\
{																														\
    vigra::BasicImageView<float> img(arr, width, height);																\
    return new SplineImageView##splineDegree (srcImageRange(img));														\
}

SIV_CREATION_FUNCTION(1)
SIV_CREATION_FUNCTION(2)
SIV_CREATION_FUNCTION(3)
SIV_CREATION_FUNCTION(4)
SIV_CREATION_FUNCTION(5)


#define SIV_DELETION_FUNCTION(splineDegree) \
LIBEXPORT int vigra_delete_splineimageview##splineDegree##_c (void * siv)               \
{                                                                                       \
    SplineImageView##splineDegree * siv_ptr  = (SplineImageView##splineDegree * ) siv;  \
    delete siv;                                                                         \
    return 0;                                                                           \
}

SIV_DELETION_FUNCTION(1)
SIV_DELETION_FUNCTION(2)
SIV_DELETION_FUNCTION(3)
SIV_DELETION_FUNCTION(4)
SIV_DELETION_FUNCTION(5)



#define SIV_OPERATION_FUNCTION(function, splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_##function##_c (void * siv, double x, double y)	\
{                                                                                                       \
    SplineImageView##splineDegree * siv_ptr  = (SplineImageView##splineDegree * ) siv;                  \
	return siv_ptr -> function (x,y);                                                                   \
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


#define SIV_ACCESSOR_FUNCTION(splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_accessor_c(void * siv, double x, double y)    \
{                                                                                                   \
    SplineImageView##splineDegree * siv_ptr  = (SplineImageView##splineDegree * ) siv;              \
	return (* siv_ptr)(x,y);                                                                        \
}

SIV_ACCESSOR_FUNCTION(1)
SIV_ACCESSOR_FUNCTION(2)
SIV_ACCESSOR_FUNCTION(3)
SIV_ACCESSOR_FUNCTION(4)
SIV_ACCESSOR_FUNCTION(5)



/************ ADDRESS BASED FUNCTIONS *****************/


#define SIV_ADDRESS_CREATION_FUNCTION(splineDegree) \
LIBEXPORT vigra::UInt64 vigra_create_splineimageview##splineDegree##_address_c (const float *arr, const int width, const int height)	\
{                                                                                                                                       \
    vigra::BasicImageView<float> img(arr, width, height);                                                                               \
    SplineImageView##splineDegree* siv = new SplineImageView##splineDegree (srcImageRange(img));                                        \
    return (vigra::UInt64) siv;                                                                                                         \
}

SIV_ADDRESS_CREATION_FUNCTION(1)
SIV_ADDRESS_CREATION_FUNCTION(2)
SIV_ADDRESS_CREATION_FUNCTION(3)
SIV_ADDRESS_CREATION_FUNCTION(4)
SIV_ADDRESS_CREATION_FUNCTION(5)

#define SIV_DELETION_BY_ADDRESS_FUNCTION(splineDegree) \
LIBEXPORT int vigra_delete_splineimageview##splineDegree##_by_address_c (vigra::UInt64 address)	\
{                                                                                               \
    SplineImageView##splineDegree * siv = (SplineImageView##splineDegree * ) address;           \
    delete siv;                                                                                 \
    return 0;                                                                                   \
}

SIV_DELETION_BY_ADDRESS_FUNCTION(1)
SIV_DELETION_BY_ADDRESS_FUNCTION(2)
SIV_DELETION_BY_ADDRESS_FUNCTION(3)
SIV_DELETION_BY_ADDRESS_FUNCTION(4)
SIV_DELETION_BY_ADDRESS_FUNCTION(5)


#define SIV_OPERATION_BY_ADDRESS_FUNCTION(function, splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_##function##_by_address_c (vigra::UInt64 address, double x, double y)	\
{                                                                                                                           \
    SplineImageView##splineDegree * siv = (SplineImageView##splineDegree * ) address;                                       \
    return siv -> function (x,y);                                                                                           \
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


#define SIV_ACCESSOR_BY_ADDRESS_FUNCTION(splineDegree) \
LIBEXPORT float vigra_splineimageview##splineDegree##_accessor_by_address_c(vigra::UInt64 address, double x, double y)	\
{                                                                                                                       \
    SplineImageView##splineDegree * siv = (SplineImageView##splineDegree *) address;                                    \
    return (* siv)(x,y);                                                                                                \
}

SIV_ACCESSOR_BY_ADDRESS_FUNCTION(1)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(2)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(3)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(4)
SIV_ACCESSOR_BY_ADDRESS_FUNCTION(5)
