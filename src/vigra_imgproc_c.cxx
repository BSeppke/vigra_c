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

#include "vigra_imgproc_c.h"
#include <iostream> //needed by labelVolume, which is needed by localMinMax
#include <vigra/resizeimage.hxx>
#include <vigra/affinegeometry.hxx>
#include <vigra/basicgeometry.hxx>
#include <vigra/multi_fft.hxx>
#include <vigra/correlation.hxx>
#include <vigra/multi_localminmax.hxx>


/**
 * @file
 * @brief Implemenation of image processing algorithms
 */

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
                                  const int resample_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape_in(width_in,height_in);
        vigra::Shape2 shape_out(width_out,height_out);
        ImageView img_in(shape_in, arr_in);
        ImageView img_out(shape_out, arr_out);
        
        switch(resample_method)
        {
            case 4:
                vigra::resizeImageSplineInterpolation(img_in, img_out, vigra::BSpline<4, float>());
                break;
            case 3:
                vigra::resizeImageSplineInterpolation(img_in, img_out, vigra::BSpline<3, float>());
                break;
            case 2:
                vigra::resizeImageSplineInterpolation(img_in, img_out, vigra::BSpline<2, float>());
                break;
            case 1:
                vigra::resizeImageLinearInterpolation(img_in, img_out);
                break;
            case 0:
                vigra::resizeImageNoInterpolation(img_in, img_out);
                break;
            default:
                return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
                                  const int resample_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if (resample_method == 4)
        {
            vigra::SplineImageView<4, float> spline4(img_in);
            vigra::rotateImage(spline4, img_out, angle);
        }
        else if (resample_method == 3)
        {
            vigra::SplineImageView<3, float> spline3(img_in);
            vigra::rotateImage(spline3, img_out, angle);
        }
        else if (resample_method == 2)
        {
            vigra::SplineImageView<2, float> spline2(img_in);
            vigra::rotateImage(spline2, img_out, angle);
        }
        else if (resample_method == 1)
        {
            vigra::SplineImageView<1, float> spline1(img_in);
            vigra::rotateImage(spline1, img_out, angle);
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
                                      const int resample_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::MultiArrayView<2, double, vigra::UnstridedArrayTag> mat(vigra::Shape2(3, 3), affineMatrix);
        
        if (resample_method == 4)
        {
            vigra::SplineImageView<4, float> spline4(img_in);
            vigra::affineWarpImage(spline4, img_out, mat);
        }
        else if (resample_method == 3)
        {
            vigra::SplineImageView<3, float> spline3(img_in);
            vigra::affineWarpImage(spline3, img_out, mat);
        }
        else if (resample_method == 2)
        {
            vigra::SplineImageView<2, float> spline2(img_in);
            vigra::affineWarpImage(spline2, img_out, mat);
        }
        else if (resample_method == 1)
        {
            vigra::SplineImageView<1, float> spline1(img_in);
            vigra::affineWarpImage(spline1, img_out, mat);
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
                                   const int reflect_method)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if(reflect_method>=1 && reflect_method <=3)
        {
            vigra::reflectImage(img_in, img_out,
                                static_cast<vigra::Reflect>(reflect_method));
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
                                       const int height)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img(shape, arr_in);
        ImageView img_real(shape, arr_real_out);
        ImageView img_imag(shape, arr_imag_out);
        vigra::MultiArray<2, vigra::FFTWComplex<PixelType> > fourier(shape);
        
        vigra::fourierTransform(img, fourier);
        moveDCToCenter(fourier);
        
        auto img_real_iter = img_real.begin(),
             img_imag_iter = img_imag.begin();
        
        for(auto f_iter= fourier.begin();
            f_iter != fourier.end();
            ++f_iter, ++img_real_iter, ++img_imag_iter)
        {
            *img_real_iter = f_iter->real();
            *img_imag_iter = f_iter->imag();
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
                                           const int template_height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr_in);
        vigra::Shape2 template_shape(template_width, template_height);
        ImageView templ(template_shape, arr_template_in);
        ImageView corr(shape, arr_out);
        
        //only allow odd templates (because results are in center coords)
        if( template_width % 2 == 0 || template_height %2 == 0)
        {
            return 2;
        }
        
        vigra::fastCrossCorrelation(img, templ, corr);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

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
                                                     const int template_height)
{
    try
    {
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr_in);
        
        //only allow odd templates (because results are in center coords)
        if( template_width % 2 == 0 || template_height %2 == 0)
        {
            return 2;
        }
        
        vigra::Shape2 template_shape(template_width, template_height);
        ImageView templ(template_shape, arr_template_in);
        ImageView corr(shape, arr_out);
        
        vigra::fastNormalizedCrossCorrelation(img, templ, corr);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

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
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 *
 * \return 0 if the local maxima finding was successful, 1 else.
 */
LIBEXPORT int vigra_localmaxima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const bool eight_connectivity)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::localMaxima(img_in, img_out,
                           vigra::LocalMinmaxOptions().neighborhood(
                                eight_connectivity ?
                                    vigra::IndirectNeighborhood :
                                    vigra::DirectNeighborhood));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
 * \param eight_connectivity If set to true, 8-conectivity is used, else 4.
 *
 * \return 0 if the local minima finding was successful, 1 else.
 */
LIBEXPORT int vigra_localminima_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const bool eight_connectivity)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::localMinima(img_in, img_out,
                           vigra::LocalMinmaxOptions().neighborhood(
                                eight_connectivity ?
                                    vigra::IndirectNeighborhood :
                                    vigra::DirectNeighborhood));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
                               const int lower)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape_in(width_in,height_in);
        ImageView img(shape_in, arr_in);
        
        int cut_w = right - left,
            cut_h = lower - upper;
        
        //Check for cuttof measures
        if(cut_w > 0 && cut_w <= width_in && cut_h > 0 && cut_h <= height_in)
        {
            vigra::Shape2 cut_shape_in(cut_w,cut_h);
            ImageView cut_img(cut_shape_in, arr_out);
            
            cut_img = img.subarray(vigra::Shape2(left, upper),
                                   vigra::Shape2(right, lower));
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

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
                                const int lower)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape_in(width_in,height_in);
        ImageView img(shape_in, arr_in);
        
        int padd_w = right + left + width_in,
        padd_h = lower + upper + height_in;
        
        //Check for padding measures
        if(padd_w >= width_in && padd_h >= height_in)
        {
            vigra::Shape2 padd_shape_in(padd_w, padd_h);
            ImageView padd_img(padd_shape_in, arr_out);
            
            padd_img.subarray(vigra::Shape2(left, upper),
                              vigra::Shape2(left+width_in, upper+height_in)) = img;
        }
        else
        {
            return 2;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}
