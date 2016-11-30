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

#include "vigra_impex_c.h"
#include <vigra/impex.hxx>
#include <vigra/impexalpha.hxx>


/**
 * @file
 * @brief Implementation of image import and export
 */

/**
 * Import of a grayscale image from filesystem into a single band array.
 * This function checks if an image exists on file system and if it is grayscale.
 * If so, it is imported into the given flat array, which needs already to 
 * be allocated at correct size (width*hight).
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

/**
 * Import of an RGB image from filesystem into three single band arrays.
 * This function checks if an image exists on file system and if it is RGB.
 * If so, it is imported into the three given flat arrays, which needs already to
 * be allocated at correct size (width*hight each).
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

/**
 * Import of an ARGB image from filesystem into four single band arrays.
 * This function checks if an image exists on file system and if it is RGB with
 * at least one additional alpha band.
 * If so, it is imported into the four given flat arrays, which needs already to
 * be allocated at correct size (width*hight each).
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

/**
 * Export of a grayscale image from a single band array to file system.
 * This function writes the given band as a grayvalue image to the file system.
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
                                      const char * filename)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView out(shape, arr_in);
        
        // import the image just read
        vigra::exportImage(out, filename);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

/**
 * Export of an RGB image from three single band arrays to file system.
 * This function writes the given bands as a RGB image to the file system.
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
                                     const char * filename)
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
        
        // export the image, which has just been filled
        vigra::exportImage(img, filename);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

/**
 * Export of an RGBA image from four single band arrays to file system.
 * This function writes the given bands as a RGBA image to the file system.
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
                                      const char * filename)
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
        
        // export the image, which has just been filled
        vigra::exportImageAlpha(img, img_alpha, filename);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

/**
 * This function returns the image width of a given filename without importing
 * the data of that image from filesystem.
 *
 * \param filename the file name of the image
 *
 * \return 0,   if an error occured or the image has no width,
 *         else the width of the image.
 */
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

/**
 * This function returns the image height of a given filename without importing
 * the data of that image from filesystem.
 *
 * \param filename the file name of the image
 *
 * \return 0,   if an error occured or the image has no height,
 *         else the height of the image.
 */
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

/**
 * This function returns the number of bands of an image of a given filename 
 * without importing the data of that image from filesystem.
 *
 * \param filename the file name of the image
 *
 * \return 0,    if an error occured or the image has no bands,
 *         else  the number of bands of the image.
 */
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

/**
 * This function returns the number of addiation (alpha-)bands of an image of a
 * given filename without importing the data of that image from filesystem.
 *
 * \param filename the file name of the image
 *
 * \return 0,   if an error occured or there are no additional bands,
 *         else the number of extra bands of the image.
 */
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
