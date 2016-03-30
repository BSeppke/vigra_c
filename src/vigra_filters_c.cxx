#include "vigra_filters_c.h"

#include "vigra/stdconvolution.hxx"
#include "vigra/multi_convolution.hxx"
#include "vigra/nonlineardiffusion.hxx" 
#include "vigra/distancetransform.hxx"
#include "vigra/tensorutilities.hxx"
#include "vigra/gradient_energy_tensor.hxx"
#include "vigra/boundarytensor.hxx"
#include "vigra/orientedtensorfilters.hxx"


//Helper function to generate a vigra::Kernel2D from a flat array
template<class T>
vigra::Kernel2D<T> kernel2dFromArray(const T* arr, const int width, const int height)
{
    //Create a view on the data
    vigra::Shape2 shape(width,height);
    vigra::MultiArrayView<2, T> k_img(shape, arr);
    
    //Allocate a temp. BasicImage<T> for initialization of the Kernel2D,
    //which shall be returned.
    vigra::BasicImage<T> temp_kernel(width, height);
    
    //Fill the temp image
    for(int y=0; y<height; ++y)
        for(int x=0; x<width; ++x)
            temp_kernel(x,y) = k_img(x,y);
    
    //Init a kernel based in that image
    vigra::Kernel2D<T> kernel;
    kernel.initExplicitly(temp_kernel);
    
    //and return it
    return kernel;
}


//Helper function to generate a vigra::Kernel1D from a flat array
template<class T>
vigra::Kernel1D<T> kernel1dFromArray(const T* arr, const int size)
{
    //Boundaries of the kernel
    int b = size/2;
    
    //Init the convolution kernel
    vigra::Kernel1D<T> kernel;
    kernel.initExplicitly(-b, b);
    
    //Fill the kernel with array data
    for(int i=0; i<size; ++i)
    {
        kernel[i-b] = arr[i];
    }
    
    //and return it
    return kernel;
}

LIBEXPORT int vigra_convolveimage_c(const PixelType *arr, PixelType *arr2, const double *kernel_arr, const int width, const int height, const int kernel_width, const int kernel_height)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
        
		//check if kernel dimensions are odd
		if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
			return 2;

		convolveImage(img,img2, kernel2dFromArray(kernel_arr, kernel_width, kernel_height));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_separableconvolveimage_c(const PixelType *arr, PixelType *arr2, const double *kernel_arr_h, const double *kernel_arr_v, const int width, const int height, const int kernel_width, const int kernel_height)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
		
		//check if kernel dimensions are odd
		if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
			return 2;
        
		convolveImage(img, img2, kernel1dFromArray(kernel_arr_h, kernel_width), kernel1dFromArray(kernel_arr_v, kernel_height));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiangradient_c(const PixelType *arr, const PixelType *arr2, const PixelType *arr3, const int width, const int height, const  float sigma)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
		ImageView img3(shape, arr3);
		
		vigra::gaussianGradient(img, img2, img3, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiangradientmagnitude_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const  float sigma)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
		
		vigra::gaussianGradientMagnitude(img, img2, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiansmoothing_c(const PixelType *arr , const PixelType *arr2, const int width, const int height, const  float sigma)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
            
        vigra::gaussianSmoothing(img, img2, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_laplacianofgaussian_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const  float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img(shape, arr);
        ImageView img2(shape, arr2);
            
        vigra::laplacianOfGaussian(img, img2, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_hessianmatrixofgaussian_c(const PixelType *arr, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width, const int height, const float scale)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
		
		vigra::hessianMatrixOfGaussian(img, img_xx,img_xy,img_yy, scale);
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_structuretensor_c(const PixelType *arr, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width, const int height, const float inner_scale, const float outer_scale)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
		
		vigra::structureTensor(img, img_xx,img_xy,img_yy, inner_scale, outer_scale);
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_boundarytensor_c(const PixelType *arr, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width, const int height, const float scale)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
		
		//create the temporary tensor
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
		
		vigra::boundaryTensor(img, tensor, scale);
		
        auto xx_iter = img_xx.begin(),
             xy_iter = img_xy.begin(),
             yy_iter = img_yy.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ xx_iter, ++xy_iter, ++yy_iter)
        {
            *xx_iter = t_iter->operator[](0);
            *xy_iter = t_iter->operator[](1);
            *yy_iter = t_iter->operator[](2);
        }
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_boundarytensor1_c(const PixelType *arr, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width, const int height, const float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
		
		//create the temporary tensor
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
		
		vigra::boundaryTensor1(img, tensor, scale);
		
        auto xx_iter = img_xx.begin(),
             xy_iter = img_xy.begin(),
             yy_iter = img_yy.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ xx_iter, ++xy_iter, ++yy_iter)
        {
            *xx_iter = t_iter->operator[](0);
            *xy_iter = t_iter->operator[](1);
            *yy_iter = t_iter->operator[](2);
        }
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gradientenergytensor_c(const PixelType *arr, const double *arr_derivKernel, const double *arr_smoothKernel, const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const int width, const int height, const int derivKernel_size, const int smoothKernel_size)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
		
		//create the temporary tensor
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
		
		vigra::Kernel1D<double> derivKernel, smoothKernel;
		
		derivKernel = derivKernel.initExplicitly(-derivKernel_size/2, derivKernel_size/2);
		for(int i=0; i<derivKernel_size; ++i){
			derivKernel[i+derivKernel_size/2] = arr_derivKernel[i];
		}
		
		smoothKernel = smoothKernel.initExplicitly(-smoothKernel_size/2, smoothKernel_size/2);
		for(int i=0; i<smoothKernel_size; ++i){
			smoothKernel[i+smoothKernel_size/2] = arr_smoothKernel[i];
		}
		
		vigra::gradientEnergyTensor(img, tensor, derivKernel, smoothKernel);
		
        auto xx_iter = img_xx.begin(),
             xy_iter = img_xy.begin(),
             yy_iter = img_yy.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ xx_iter, ++xy_iter, ++yy_iter)
        {
            *xx_iter = t_iter->operator[](0);
            *xy_iter = t_iter->operator[](1);
            *yy_iter = t_iter->operator[](2);
        }
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_tensoreigenrepresentation_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_lEV, const PixelType *arr_sEV, const PixelType *arr_ang, const int width, const int height)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
        
		ImageView img_lEV(shape, arr_lEV);
		ImageView img_sEV(shape, arr_sEV);
		ImageView img_ang(shape, arr_ang);
        
		//create the temporary tensor
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
		
        auto xx_iter = img_xx.begin(),
             xy_iter = img_xy.begin(),
             yy_iter = img_yy.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ xx_iter, ++xy_iter, ++yy_iter)
        {
            t_iter->operator[](0) = *xx_iter;
            t_iter->operator[](1) = *xy_iter;
            t_iter->operator[](2) = *yy_iter;
        }
        
		vigra::tensorEigenRepresentation(tensor, tensor);
				
        auto lEV_iter = img_lEV.begin(),
             sEV_iter = img_sEV.begin(),
             ang_iter = img_ang.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ lEV_iter, ++sEV_iter, ++ang_iter)
        {
            *lEV_iter = t_iter->operator[](0);
            *sEV_iter = t_iter->operator[](1);
            *ang_iter = t_iter->operator[](2);
        }
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_tensortrace_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_trace, const int width, const int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
        ImageView img_trace(shape, arr_trace);
		
		//create the temporary tensor
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
		
        auto xx_iter = img_xx.begin(),
             xy_iter = img_xy.begin(),
             yy_iter = img_yy.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ xx_iter, ++xy_iter, ++yy_iter)
        {
            t_iter->operator[](0) = *xx_iter;
            t_iter->operator[](1) = *xy_iter;
            t_iter->operator[](2) = *yy_iter;
        }
        
		vigra::tensorTrace(tensor, img_trace);
		
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_tensortoedgecorner_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_edgeness, const PixelType *arr_orientation, const PixelType *arr_cornerness, const int width, const int height)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
        
		ImageView img_edgeness(shape, arr_edgeness);
		ImageView img_orientation(shape, arr_orientation);
		ImageView img_cornerness(shape, arr_cornerness);
        
		//create the temporary tensor
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
		vigra::MultiArray<2, vigra::TinyVector<float, 2> > edgePart(width,height);
		
        auto xx_iter = img_xx.begin(),
             xy_iter = img_xy.begin(),
             yy_iter = img_yy.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ xx_iter, ++xy_iter, ++yy_iter)
        {
            t_iter->operator[](0) = *xx_iter;
            t_iter->operator[](1) = *xy_iter;
            t_iter->operator[](2) = *yy_iter;
        }
        
		vigra::tensorToEdgeCorner(tensor, edgePart, img_cornerness);
				
        auto edgeness_iter = img_edgeness.begin(),
             orientation_iter = img_orientation.begin();
        
        for(auto e_iter = edgePart.begin(); e_iter != edgePart.end(); ++e_iter, ++ edgeness_iter, ++orientation_iter)
        {
            *edgeness_iter = e_iter->operator[](0);
            *orientation_iter = e_iter->operator[](1);
        }
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}
LIBEXPORT int vigra_hourglassfilter_c(const PixelType *arr_xx, const PixelType *arr_xy, const PixelType *arr_yy, const PixelType *arr_hgxx, const PixelType *arr_hgxy, const PixelType *arr_hgyy, const int width, const int height, const float sigma, const float rho)
{
    try
        {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img_xx(shape, arr_xx);
		ImageView img_xy(shape, arr_xy);
		ImageView img_yy(shape, arr_yy);
        
		ImageView img_hgxx(shape, arr_hgxx);
		ImageView img_hgxy(shape, arr_hgxy);
		ImageView img_hgyy(shape, arr_hgyy);
        
		//create the temporary tensor
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
		vigra::MultiArray<2, vigra::TinyVector<float, 3> > hg_tensor(width,height);
		
        auto xx_iter = img_xx.begin(),
             xy_iter = img_xy.begin(),
             yy_iter = img_yy.begin();
        
        for(auto t_iter = tensor.begin(); t_iter != tensor.end(); ++t_iter, ++ xx_iter, ++xy_iter, ++yy_iter)
        {
            t_iter->operator[](0) = *xx_iter;
            t_iter->operator[](1) = *xy_iter;
            t_iter->operator[](2) = *yy_iter;
        }
        
		vigra::tensorEigenRepresentation(tensor, tensor);
		vigra::hourGlassFilter(tensor, hg_tensor, sigma, rho);
				
        auto hgxx_iter = img_hgxx.begin(),
             hgxy_iter = img_hgxy.begin(),
             hgyy_iter = img_hgyy.begin();
        
        for(auto hg_iter = hg_tensor.begin(); hg_iter != hg_tensor.end(); ++hg_iter, ++hgxx_iter, ++hgxy_iter, ++hgyy_iter)
        {
            *hgxx_iter = hg_iter->operator[](0);
            *hgxy_iter = hg_iter->operator[](1);
            *hgyy_iter = hg_iter->operator[](2);
        }
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiansharpening_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const float sharpening_factor, const float scale)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
		
		vigra::gaussianSharpening(img, img2, sharpening_factor, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_simplesharpening_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, float sharpening_factor)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
		
		vigra::simpleSharpening(img, img2, sharpening_factor);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_nonlineardiffusion_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const float edge_threshold, const float scale)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
		
		vigra::nonlinearDiffusion(img, img2,
								  vigra::DiffusivityFunctor<float>(edge_threshold), scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_distancetransform_c(const PixelType *arr, const PixelType *arr2, const int width, const int height, const float background_label, const int norm)
{
    try
    {
		// create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
		ImageView img(shape, arr);
		ImageView img2(shape, arr2);
		
		if(norm>=0 && norm <= 2)
			vigra::distanceTransform(   img, img2,
									 background_label,   norm);
		else
			return 2;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
