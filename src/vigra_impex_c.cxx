#include "vigra_impex_c.h"

#include "vigra/impex.hxx"


LIBEXPORT int vigra_importgrayimage_c(const PixelType *arr_out, int width, int height, const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::ImageImportInfo info(filename);
        
        if(info.width() == width && info.height() == height)
        {
            if( info.isGrayscale())
            {
                // create a gray scale image of appropriate size
                vigra::Shape2 shape(width, height);
                ImageView img(shape, arr_out);
                
                // import the image just read
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

LIBEXPORT int vigra_exportgrayimage_c(const PixelType *arr_in, int width, int height, const char * filename)
{
    try
    {
        // create a gray scale image of appropriate size
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

LIBEXPORT int vigra_importrgbimage_c(const PixelType *arr_r_out, const PixelType *arr_g_out, const PixelType *arr_b_out, int width, int height, const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
        vigra::ImageImportInfo info(filename);
        
        if( info.width() == width && info.height() == height)
        {
            if( info.isColor())
            {
                // create a gray scale image of appropriate size
                vigra::MultiArray<2, vigra::RGBValue<PixelType> > img(info.width(), info.height());
                
                // import the image just read
                importImage(info, img);
                
                //write the color channels to the different arrays
                vigra::Shape2 shape(width, height);
                ImageView img_red(shape, arr_r_out);
                ImageView img_green(shape, arr_g_out);
                ImageView img_blue(shape, arr_b_out);
                
                auto red_iter   = img_red.begin(),
                     green_iter = img_green.begin(),
                     blue_iter  = img_blue.begin();
                
                for(auto img_iter = img.begin();img_iter != img.end(); ++img_iter, ++red_iter, ++green_iter, ++blue_iter)
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

LIBEXPORT int vigra_exportrgbimage_c(const PixelType *arr_r_in, const PixelType *arr_g_in, const PixelType *arr_b_in, int width, int height, const char * filename)
{
    try
    {
        // create a floating (32-bit) color image of appropriate size
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

LIBEXPORT int get_width_c(const char * filename)
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

LIBEXPORT int get_height_c(const char * filename)
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

LIBEXPORT int get_numbands_c(const char * filename)
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
