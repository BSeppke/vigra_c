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
        ImageView img(shape, arr_in);
        
        if(rescale_range)
        {
            vigra::exportImage(img, filename);
        }
        else
        {
            vigra::MultiArray<2, unsigned char> img8bit(shape);
            auto img8Bit_iter = img8bit.begin();
        
            for(auto img_iter = img.begin(); img_iter != img.end(); ++img_iter, ++img8Bit_iter)
            {
                *img8Bit_iter = vigra::max(vigra::min(*img_iter, 255.0f), 0.0f);
            }
            
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
        
        if(rescale_range)
        {
            for(auto img_iter = img.begin(); img_iter != img.end(); ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
            {
                img_iter->red() = *red_iter;
                img_iter->green() = *green_iter;
                img_iter->blue() = *blue_iter;
            }
            // export the image, which has just been filled
            vigra::exportImage(img, filename);
        }
        else
        {
            for(auto img_iter = img.begin(); img_iter != img.end(); ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
            {
                img_iter->red() = vigra::max(vigra::min(*red_iter, 255.0f), 0.0f);
                img_iter->green() = vigra::max(vigra::min(*green_iter, 255.0f), 0.0f);
                img_iter->blue() = vigra::max(vigra::min(*blue_iter, 255.0f), 0.0f);
            }
            
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
        
        if(rescale_range)
        {
            for(auto img_iter = img.begin(); img_iter != img.end(); ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
            {
                img_iter->red() = *red_iter;
                img_iter->green() = *green_iter;
                img_iter->blue() = *blue_iter;
            }
           
            // export the image, which has just been filled
            vigra::exportImageAlpha(img, img_alpha, filename);
        }
        else
        {
            for(auto img_iter = img.begin(); img_iter != img.end(); ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
            {
                img_iter->red() = vigra::max(vigra::min(*red_iter, 255.0f), 0.0f);
                img_iter->green() = vigra::max(vigra::min(*green_iter, 255.0f), 0.0f);
                img_iter->blue() = vigra::max(vigra::min(*blue_iter, 255.0f), 0.0f);
            }
            
            for(auto img_iter = img_alpha.begin(); img_iter != img_alpha.end(); ++img_iter)
            {
                *img_iter = vigra::max(vigra::min(*img_iter, 255.0f), 0.0f);
            }
           
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


LIBEXPORT int vigra_has_hdf5_c()
{
    #ifdef HAS_HDF5
        return 1;
    #else
        return 0;
    #endif
}

#ifdef HAS_HDF5
#include <vigra/hdf5impex.hxx>

LIBEXPORT int vigra_hdf5_numdimensions_c(const char* filename, const char* pathInFile)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::HDF5ImportInfo info(filename, pathInFile);

        return info.numDimensions();
    }
    catch (vigra::StdException & e)
    {
        return 0;
    }
}

LIBEXPORT int vigra_hdf5_shape_c(const char * filename, const char* pathInFile, int* shape_arr, const int dimensions)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::HDF5ImportInfo info(filename, pathInFile);

        if (info.numDimensions() != dimensions)
        {
            return 1;
        }
        for(int i=0; i!=dimensions; ++i)
        {
            shape_arr[i] = info.shapeOfDimension(i);
        }
        return 0;
    }
    catch (vigra::StdException & e)
    {
        return 2;
    }
}

LIBEXPORT int vigra_hdf5_importarray_c(const char * filename, const char* pathInFile, float* flat_arr, int* shape_arr, const int dimensions)
{
    try
    {
        vigra::HDF5ImportInfo info(filename, pathInFile);
        
        if(info.numDimensions() != dimensions)
        {
            return 1;
        }
        
        bool dimMatch = true;
        for(int dim=0; dim != dimensions; ++dim)
        {
         dimMatch = dimMatch && (info.shapeOfDimension(dim) == shape_arr[dim]);
        }
        
        if(!dimMatch)
        {
            return 1;
        }
        
        switch(info.numDimensions())
        {
            case 1:
            {
                vigra::MultiArrayShape<1>::type shape(info.shape().begin());
                vigra::MultiArrayView<1, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 2:
            {
                vigra::MultiArrayShape<2>::type shape(info.shape().begin());
                vigra::MultiArrayView<2, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 3:
            {
                vigra::MultiArrayShape<3>::type shape(info.shape().begin());
                vigra::MultiArrayView<3, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 4:
            {
                vigra::MultiArrayShape<4>::type shape(info.shape().begin());
                vigra::MultiArrayView<4, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 5:
            {
                vigra::MultiArrayShape<5>::type shape(info.shape().begin());
                vigra::MultiArrayView<5, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 6:
            {
                vigra::MultiArrayShape<6>::type shape(info.shape().begin());
                vigra::MultiArrayView<6, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 7:
            {
                vigra::MultiArrayShape<7>::type shape(info.shape().begin());
                vigra::MultiArrayView<7, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 8:
            {
                vigra::MultiArrayShape<8>::type shape(info.shape().begin());
                vigra::MultiArrayView<8, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            case 9:
            {
                vigra::MultiArrayShape<9>::type shape(info.shape().begin());
                vigra::MultiArrayView<9, float> array(shape, flat_arr);
                readHDF5(info, array);
                return 0;
            }
            default:
                return 1;
        }
    }
    catch (vigra::StdException & e)
    {
        return 2;
    }
}

LIBEXPORT int vigra_hdf5_exportarray_c(float* flat_arr, int* shape_arr, const int dimensions, const char * filename, const char* pathInFile)
{
    try
    {
        switch(dimensions)
        {
            case 1:
            {
                vigra::MultiArrayShape<1>::type shape(shape_arr);
                vigra::MultiArrayView<1, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 2:
            {
                vigra::MultiArrayShape<2>::type shape(shape_arr);
                vigra::MultiArrayView<2, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 3:
            {
                vigra::MultiArrayShape<3>::type shape(shape_arr);
                vigra::MultiArrayView<3, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 4:
            {
                vigra::MultiArrayShape<4>::type shape(shape_arr);
                vigra::MultiArrayView<4, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 5:
            {
                vigra::MultiArrayShape<5>::type shape(shape_arr);
                vigra::MultiArrayView<5, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 6:
            {
                vigra::MultiArrayShape<6>::type shape(shape_arr);
                vigra::MultiArrayView<6, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 7:
            {
                vigra::MultiArrayShape<7>::type shape(shape_arr);
                vigra::MultiArrayView<7, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 8:
            {
                vigra::MultiArrayShape<8>::type shape(shape_arr);
                vigra::MultiArrayView<8, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            case 9:
            {
                vigra::MultiArrayShape<9>::type shape(shape_arr);
                vigra::MultiArrayView<9, float> array(shape, flat_arr);
                writeHDF5(filename, pathInFile, array);
                return 0;
            }
            default:
                return 1;
        }
    }
    catch (vigra::StdException & e)
    {
        return 2;
    }
}
#endif
