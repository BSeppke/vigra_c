#include "vigra_impex_c.h"

#include "vigra/impex.hxx"


LIBEXPORT int vigra_importgrayimage_c(PixelType *arr, int width, int height, const char * filename)
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
                vigra::Shape2 shape(width,height);
                ImageView in(shape, arr);
                
                // import the image just read
                importImage(info, in);
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

LIBEXPORT int vigra_exportgrayimage_c(const PixelType *arr, int width, int height, const char * filename)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView out(shape, arr);
        
        // import the image just read
        vigra::exportImage(out, filename);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_importrgbimage_c(PixelType *arr_r, PixelType *arr_g, PixelType *arr_b, int width, int height, const char * filename)
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
                vigra::MultiArray<2, vigra::RGBValue<PixelType> > in(info.width(), info.height());
                
                // import the image just read
                importImage(info, in);
                
                //write the color channels to the different arrays
                vigra::Shape2 shape(width,height);
                ImageView img_red(shape, arr_r);
                ImageView img_green(shape, arr_g);
                ImageView img_blue(shape, arr_b);
                
                auto red_iter = img_red.begin(),
                green_iter = img_green.begin(),
                blue_iter = img_blue.begin();
                
                for(auto in_iter = in.begin();in_iter != in.end(); ++in_iter, ++red_iter, ++green_iter, ++blue_iter)
                {
                    *red_iter = in_iter->red();
                    *green_iter = in_iter->green();
                    *blue_iter = in_iter->blue();
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

LIBEXPORT int vigra_exportrgbimage_c(const PixelType *arr_r, const PixelType *arr_g, const PixelType *arr_b, int width, int height, const char * filename)
{
    try
    {
        // create a floating (32-bit) color image of appropriate size
        vigra::MultiArray<2, vigra::RGBValue<PixelType> > out(width, height);
        
        //write the color channels from the different arrays
        vigra::Shape2 shape(width,height);
        ImageView img_red(shape, arr_r);
        ImageView img_green(shape, arr_g);
        ImageView img_blue(shape, arr_b);
        
        auto red_iter = img_red.begin(),
        green_iter = img_green.begin(),
        blue_iter = img_blue.begin();
        
        for(auto out_iter = out.begin(); out_iter != out.end(); ++out_iter, ++red_iter, ++green_iter, ++blue_iter)
        {
            out_iter->red() = *red_iter;
            out_iter->green() = *green_iter;
            out_iter->blue() = *blue_iter;
        }
        
        // export the image, which has just been filled
        vigra::exportImage(out, filename);
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
