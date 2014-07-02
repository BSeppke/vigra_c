#include "vigra_impex_c.h"

#include "vigra/impex.hxx"
#include "vigra/basicimageview.hxx"
#include "vigra/copyimage.hxx"

LIBEXPORT int vigra_importgrayimage_c(float *arr, int width, int height, const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
		vigra::ImageImportInfo info(filename);
		if(info.width() == width && info.height() == height){
			if( info.isGrayscale()) {
				// create a gray scale image of appropriate size
				vigra::BasicImageView<float> in(arr, info.width(), info.height());
            
				// import the image just read
				importImage(info, destImage(in));
			}
			else {
				return 2;
			}
		}
		else{
			return 3;
		}
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
LIBEXPORT int vigra_exportgrayimage_c(const float *arr, int width, int height, const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
		vigra::ImageExportInfo info(filename);
		
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> out(arr, width, height);
		
		// import the image just read
		vigra::exportImage(srcImageRange(out), info);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_importrgbimage_c(float *arr_r, float *arr_g, float *arr_b, int width, int height, const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
		vigra::ImageImportInfo info(filename);
		if( info.width() == width && info.height() == height){
			if( info.isColor()) {
				// create a gray scale image of appropriate size
				vigra::BasicImage<vigra::RGBValue<float> > in(info.width(), info.height());
				
				// import the image just read
				importImage(info, destImage(in));
				
				//write the color channels to the different arrays
				vigra::BasicImageView<float>   redView(arr_r, info.width(), info.height());
				vigra::BasicImageView<float> greenView(arr_g, info.width(), info.height());
				vigra::BasicImageView<float>  blueView(arr_b, info.width(), info.height());
				
				vigra::copyImage( in.upperLeft(), in.lowerRight(), vigra::RedAccessor<vigra::RGBValue<float> >(),   redView.upperLeft(),   vigra::BasicImageView<float>::Accessor());
				vigra::copyImage( in.upperLeft(), in.lowerRight(), vigra::GreenAccessor<vigra::RGBValue<float> >(), greenView.upperLeft(), vigra::BasicImageView<float>::Accessor());
				vigra::copyImage( in.upperLeft(), in.lowerRight(), vigra::BlueAccessor<vigra::RGBValue<float> >(),  blueView.upperLeft(),  vigra::BasicImageView<float>::Accessor());
			}
			else
			{
				return 2;
			}
		}
		else {
			return 3;
		}
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_exportrgbimage_c(const float *arr_r, const float *arr_g, const float *arr_b, int width, int height, const char * filename)
{
    try
    {
        // read image given as first argument
        // file type is determined automatically
		vigra::ImageExportInfo info(filename);
		
		// create a floating (32-bit) color image of appropriate size
		vigra::BasicImage<vigra::RGBValue<float> > out(width, height);
		
		//write the color channels to the different arrays
		vigra::BasicImageView<float>   redView(arr_r, width, height);
		vigra::BasicImageView<float> greenView(arr_g, width, height);
		vigra::BasicImageView<float>  blueView(arr_b, width, height);
		
		vigra::copyImage( redView.upperLeft(),   redView.lowerRight(),   vigra::BasicImageView<float>::Accessor(), out.upperLeft(), vigra::RedAccessor<vigra::RGBValue<float> >()  );
		vigra::copyImage( greenView.upperLeft(), greenView.lowerRight(), vigra::BasicImageView<float>::Accessor(), out.upperLeft(), vigra::GreenAccessor<vigra::RGBValue<float> >());
		vigra::copyImage( blueView.upperLeft(),  blueView.lowerRight(),  vigra::BasicImageView<float>::Accessor(), out.upperLeft(), vigra::BlueAccessor<vigra::RGBValue<float> >());
		
		// import the image just read
		vigra::exportImage(srcImageRange(out), info);
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