#include "vigra/basicimage.hxx"
#include "vigra/basicimageview.hxx"
#include "vigra/flatmorphology.hxx"
#include "os_settings.hxx"

using namespace std;

LIBEXPORT int vigra_discerosion_c(const float *arr, const float *arr2,const  int width,const  int height,const  int radius){ 
    try
    {
      // create a gray scale image of appropriate size
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
            
	  vigra::BImage tmp(width, height),tmp2(width, height);
	  
	  vigra::copyImage(srcImageRange(img), destImage(tmp));
            
      vigra::discErosion(srcImageRange(tmp), destImage(tmp2), radius);
	  
	  vigra::copyImage(srcImageRange(tmp2), destImage(img2));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_discdilation_c(const float *arr, const float *arr2,const  int width,const  int height,const  int radius){ 
    try
    {
      // create a gray scale image of appropriate size
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
	  
	  vigra::BImage tmp(width, height),tmp2(width, height);
	  
	  vigra::copyImage(srcImageRange(img), destImage(tmp));
            
      vigra::discDilation(srcImageRange(tmp), destImage(tmp2), radius);
	  
	  vigra::copyImage(srcImageRange(tmp2), destImage(img2));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigraext_upwind_c(const float *arr, const float *arr2,  const float *arr3, const  int width,const  int height,const float weight){
	try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		vigra::BasicImageView<float> img3(arr3, width, height);
		
		float upper, lower, left, right, center, fx, fy;
		
		for(int y=0; y<height; ++y){
			for(int x=0; x<width; ++x){
				upper  = img(x,                 max(0,        y-1));
				lower  = img(x,                 min(height-1, y+1));
				left   = img(max(0,       x-1), y);
				right  = img(min(width-1, x+1), y);
				center = img(x,y);
				
				if(img2(x,y)<0){
					fx = max(max(right - center, left  - center), 0.0f);
					fy = max(max(lower - center, upper - center), 0.0f);
					img3(x,y) = center + weight*sqrt( fx*fx + fy*fy);
				}
				else{
					fx = max(max(center - right, center - left), 0.0f);
					fy = max(max(center - lower, center - upper), 0.0f);
					img3(x,y) = center - weight*sqrt( fx*fx + fy*fy);
				}				
			}
		}
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}


