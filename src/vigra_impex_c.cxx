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

#include "vigra_impex_c.h"
#include <vigra/impex.hxx>
#include <vigra/impexalpha.hxx>


/**
 * @file
 * @brief Implementation of image import and export
 */

LIBEXPORT int vigra_importgrayimage_c(const PixelType * arr_out,
                                      const int width,
                                      const int height,
                                      const char * filename)
{
    try
    {
        //read image given as first argument
        //file type is determined automatically
        vigra::ImageImportInfo info(filename);
        
        if(info.width() == width && info.height() == height)
        {
            if(info.isGrayscale())
            {
                //Create gray scale image views for the arrays
                vigra::Shape2 shape(width, height);
                ImageView img(shape, arr_out);
                
                //import the image just read
                importImage(info, img);
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 3;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_importrgbimage_c(const PixelType * arr_r_out,
                                     const PixelType * arr_g_out,
                                     const PixelType * arr_b_out,
                                     const int width,
                                     const int height,
                                     const char * filename)
{
    try
    {
        //read image given as first argument
        //file type is determined automatically
        vigra::ImageImportInfo info(filename);
        
        if(info.width() == width && info.height() == height)
        {
            if(info.isColor())
            {
                //Create gray scale image views for the arrays
                vigra::MultiArray<2, vigra::RGBValue<PixelType> > img(info.width(), info.height());
                
                //import the image just read
                importImage(info, img);
                
                //write the color channels to the different arrays
                vigra::Shape2 shape(width, height);
                ImageView img_red(shape, arr_r_out);
                ImageView img_green(shape, arr_g_out);
                ImageView img_blue(shape, arr_b_out);
                
                auto red_iter   = img_red.begin(),
                     green_iter = img_green.begin(),
                     blue_iter  = img_blue.begin();
                
                for(auto img_iter = img.begin();
                    img_iter != img.end();
                    ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
                {
                    *red_iter = img_iter->red();
                    *green_iter = img_iter->green();
                    *blue_iter = img_iter->blue();
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 3;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_importrgbaimage_c(const PixelType * arr_r_out,
                                      const PixelType * arr_g_out,
                                      const PixelType * arr_b_out,
                                      const PixelType * arr_a_out,
                                      const int width,
                                      const int height,
                                      const char * filename)
{
    try
    {
        //read image given as first argument
        //file type is determined automatically
        vigra::ImageImportInfo info(filename);
        
        if(info.width() == width && info.height() == height)
        {
            if(info.isColor() && info.numExtraBands())
            {
                //Create gray scale image views for the arrays
                vigra::Shape2 shape(width, height);
                vigra::MultiArray<2, vigra::RGBValue<PixelType> > img(shape);
                ImageView img_alpha(shape, arr_a_out);
                
                //import the image just read into rgb-temp image and alpha arr
                importImageAlpha(info, img, img_alpha);
                
                //write the color channels to the different arrays
                ImageView img_red(shape, arr_r_out);
                ImageView img_green(shape, arr_g_out);
                ImageView img_blue(shape, arr_b_out);
                
                auto red_iter   = img_red.begin(),
                     green_iter = img_green.begin(),
                     blue_iter  = img_blue.begin();
                
                for(auto img_iter = img.begin();
                    img_iter != img.end();
                    ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
                {
                    *red_iter = img_iter->red();
                    *green_iter = img_iter->green();
                    *blue_iter = img_iter->blue();
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 3;
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_exportgrayimage_c(const PixelType * arr_in,
                                      const int width,
                                      const int height,
                                      const char * filename,
                                      bool rescale_range)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView out(shape, arr_in);
        
        if(rescale_range)
        {
            vigra::exportImage(out, filename);
        }
        else
        {
            vigra::MultiArray<2, unsigned char> img8bit(out);
            vigra::exportImage(img8bit, filename);
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_exportrgbimage_c(const PixelType * arr_r_in,
                                     const PixelType * arr_g_in,
                                     const PixelType * arr_b_in,
                                     const int width,
                                     const int height,
                                     const char * filename,
                                     bool rescale_range)
{
    try
    {
        //create a floating (32-bit) color image of appropriate size
        vigra::MultiArray<2, vigra::RGBValue<PixelType> > img(width, height);
        
        //write the color channels from the different arrays
        vigra::Shape2 shape_in(width,height);
        ImageView img_red(shape_in, arr_r_in);
        ImageView img_green(shape_in, arr_g_in);
        ImageView img_blue(shape_in, arr_b_in);
        
        auto red_iter = img_red.begin(),
             green_iter = img_green.begin(),
             blue_iter = img_blue.begin();
        
        for(auto img_iter = img.begin(); img_iter != img.end(); ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
        {
            img_iter->red() = *red_iter;
            img_iter->green() = *green_iter;
            img_iter->blue() = *blue_iter;
        }
        
        if(rescale_range)
        {
            // export the image, which has just been filled
            vigra::exportImage(img, filename);
        }
        else
        {
            vigra::MultiArray<2, vigra::RGBValue<unsigned char> > img8bit(img);
            vigra::exportImage(img8bit, filename);
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_exportrgbaimage_c(const PixelType * arr_r_in,
                                      const PixelType * arr_g_in,
                                      const PixelType * arr_b_in,
                                      const PixelType * arr_a_in,
                                      const int width,
                                      const int height,
                                      const char * filename,
                                      bool rescale_range)
{
    try
    {
        //create a floating (32-bit) color image of appropriate size
        vigra::MultiArray<2, vigra::RGBValue<PixelType> > img(width, height);
        
        //write the color channels from the different arrays
        vigra::Shape2 shape_in(width,height);
        ImageView img_red(shape_in, arr_r_in);
        ImageView img_green(shape_in, arr_g_in);
        ImageView img_blue(shape_in, arr_b_in);
        ImageView img_alpha(shape_in, arr_a_in);
        
        auto red_iter = img_red.begin(),
             green_iter = img_green.begin(),
             blue_iter = img_blue.begin();
        
        for(auto img_iter = img.begin(); img_iter != img.end(); ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
        {
            img_iter->red() = *red_iter;
            img_iter->green() = *green_iter;
            img_iter->blue() = *blue_iter;
        }
        
        if(rescale_range)
        {
            // export the image, which has just been filled
            vigra::exportImageAlpha(img, img_alpha, filename);
        }
        else
        {
            vigra::MultiArray<2, vigra::RGBValue<unsigned char> > img8bit(img);
            vigra::exportImageAlpha(img8bit, img_alpha, filename);
        }
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_imagewidth_c(const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::ImageImportInfo info(filename);
        return info.width();
    }
    catch (vigra::StdException & e)
    {
        return 0;
    }
}

LIBEXPORT int vigra_imageheight_c(const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::ImageImportInfo info(filename);
        return info.height();
    }
    catch (vigra::StdException & e)
    {
        return 0;
    }
}

LIBEXPORT int vigra_imagenumbands_c(const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::ImageImportInfo info(filename);
        return info.numBands();
    }
    catch (vigra::StdException & e)
    {
        return 0;
    }
}

LIBEXPORT int vigra_imagenumextrabands_c(const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::ImageImportInfo info(filename);
        return info.numExtraBands();
    }
    catch (vigra::StdException & e)
    {
        return 0;
    }
}
