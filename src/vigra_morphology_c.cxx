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

#include "vigra_morphology_c.h"
#include <vigra/flatmorphology.hxx>
#include <vigra/distancetransform.hxx>
#include <vigra/shockfilter.hxx>


/**
 * @file
 * @brief Implementation of morphological operators
 */

LIBEXPORT int vigra_distancetransform_c(const PixelType * arr_in,
                                        const PixelType * arr_out,
                                        const int width,
                                        const int height,
                                        const float background_label,
                                        const int norm)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if(norm>=0 && norm <= 2)
            vigra::distanceTransform(img_in, img_out, background_label, norm);
        else
            return 2;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_discerosion_c(const PixelType * arr_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const int radius)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::MultiArray<2, unsigned char> b_img = img_in;
        vigra::discErosion(b_img, img_out, radius);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_discdilation_c(const PixelType * arr_in,
                                   const PixelType * arr_out,
                                   const int width,
                                   const int height,
                                   const int radius)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::MultiArray<2, unsigned char> b_img = img_in;
        vigra::discDilation(b_img, img_out, radius);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_upwindimage_c(const PixelType * arr_in,
                                  const PixelType * arr_fac_in,
                                  const PixelType * arr_out,
                                  const int width,
                                  const int height,
                                  const float weight)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width, height);
        ImageView img_in(shape, arr_in);
        ImageView img_fac_in(shape, arr_fac_in);
        ImageView img_out(shape, arr_out);
        
        vigra::upwindImage(img_in, img_fac_in, img_out, weight);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
