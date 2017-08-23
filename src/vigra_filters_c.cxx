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

#include "vigra_filters_c.h"
#include "vigra_kernelutils_c.h"
#include <vigra/medianfilter.hxx>
#include <vigra/nonlineardiffusion.hxx>
#include <vigra/shockfilter.hxx>
#include <vigra/multi_convolution.hxx>


/**
 * @file
 * @brief Implementation of image filters
 */

LIBEXPORT int vigra_convolveimage_c(const PixelType * arr_in,
                                    const double * kernel_arr_in,
                                    const PixelType * arr_out,
                                    const int width,
                                    const int height,
                                    const int kernel_width,
                                    const int kernel_height,
                                    const int border_treatment)
{
    if(border_treatment < 0 || border_treatment > 5)
    {
        //Illegal border treatment mode!
        return 3;
    }
    
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        //check if kernel dimensions are odd
        if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
            return 2;
        
        vigra::convolveImage(img_in, img_out,
                             kernel2dFromArray(kernel_arr_in,
                                               kernel_width, kernel_height,
                                               (vigra::BorderTreatmentMode)border_treatment));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_separableconvolveimage_c(const PixelType * arr_in,
                                             const double * kernel_h_arr_in,
                                             const double * kernel_v_arr_in,
                                             const PixelType * arr_out,
                                             const int width,
                                             const int height,
                                             const int kernel_width,
                                             const int kernel_height,
                                             const int border_treatment)
{
    if(border_treatment < 0 || border_treatment > 5)
    {
        //Illegal border treatment mode!
        return 3;
    }
    
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        //Check if kernel dimensions are odd
        if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
            return 2;
        
        vigra::convolveImage(img_in, img_out,
                             kernel1dFromArray(kernel_h_arr_in,
                                               kernel_width,
                                               (vigra::BorderTreatmentMode)border_treatment),
                             kernel1dFromArray(kernel_v_arr_in,
                                               kernel_height,
                                               (vigra::BorderTreatmentMode)border_treatment));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiangradient_c(const PixelType * arr_in,
                                       const PixelType * arr_gx_out,
                                       const PixelType * arr_gy_out,
                                       const int width,
                                       const int height,
                                       const float sigma)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_gx(shape, arr_gx_out);
        ImageView img_gy(shape, arr_gy_out);
        
        vigra::gaussianGradient(img_in, img_gx, img_gy, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiangradientmagnitude_c(const PixelType * arr_in,
                                                const PixelType * arr_out,
                                                const int width,
                                                const int height,
                                                const float sigma)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::gaussianGradientMagnitude(img_in, img_out, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiansmoothing_c(const PixelType * arr_in,
                                        const PixelType * arr_out,
                                        const int width,
                                        const int height,
                                        const float sigma)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::gaussianSmoothing(img_in, img_out, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_laplacianofgaussian_c(const PixelType * arr_in,
                                          const PixelType * arr_out,
                                          const int width,
                                          const int height,
                                          const float scale)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::laplacianOfGaussian(img_in, img_out, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_hessianmatrixofgaussian_c(const PixelType * arr_in,
                                              const PixelType * arr_xx_out,
                                              const PixelType * arr_xy_out,
                                              const PixelType * arr_yy_out,
                                              const int width,
                                              const int height,
                                              const float scale)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_xx(shape, arr_xx_out);
        ImageView img_xy(shape, arr_xy_out);
        ImageView img_yy(shape, arr_yy_out);
        
        vigra::hessianMatrixOfGaussian(img_in, img_xx,img_xy,img_yy, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiansharpening_c(const PixelType * arr_in,
                                         const PixelType * arr_out,
                                         const int width,
                                         const int height,
                                         const float sharpening_factor,
                                         const float scale)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::gaussianSharpening(img_in, img_out, sharpening_factor, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_simplesharpening_c(const PixelType * arr_in,
                                       const PixelType * arr_out,
                                       const int width,
                                       const int height,
                                       float sharpening_factor)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::simpleSharpening(img_in, img_out, sharpening_factor);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_medianfilter_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int window_width,
                                   const int window_height)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::medianFilter(img_in, img_out,
							vigra::Diff2D(window_width, window_height),
							vigra::BORDER_TREATMENT_ZEROPAD);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_nonlineardiffusion_c(const PixelType * arr_in,
                                         const PixelType * arr_out,
                                         const int width,
                                         const int height,
                                         const float edge_threshold,
                                         const float scale)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::nonlinearDiffusion(img_in, img_out,
                                  vigra::DiffusivityFunctor<float>(edge_threshold), scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_shockfilter_c(const PixelType *arr_in,
                                  const PixelType *arr_out,
                                  const int width,
                                  const int height,
                                  const float sigma,
                                  const float rho,
                                  const float upwind_factor_h,
                                  const int iterations)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if(iterations>=0)
            vigra::shockFilter(img_in, img_out, sigma, rho, upwind_factor_h, iterations);
        else
            return 2;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
