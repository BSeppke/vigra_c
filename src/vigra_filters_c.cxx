#include "vigra/basicimageview.hxx"
#include "vigra/convolution.hxx"
#include "vigra/separableconvolution.hxx"
#include "vigra/nonlineardiffusion.hxx" 
#include "vigra/distancetransform.hxx"

#include "vigra/tensorutilities.hxx"
#include "vigra/gradient_energy_tensor.hxx"
#include "vigra/boundarytensor.hxx"
#include "vigra/orientedtensorfilters.hxx"

#include "os_settings.hxx"

LIBEXPORT int vigra_convolveimage_c(const float *arr, float *arr2, const double *kernel_arr,const int width,const  int height,const int kernel_width,const  int kernel_height){
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		vigra::BasicImageView<double> k(kernel_arr, kernel_width, kernel_height);
		
		//check if kernel dimensions are odd
		if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
			return 2;
		
		vigra::Diff2D k_ul(-kernel_width/2,-kernel_height/2), k_lr(kernel_width/2,kernel_height/2);
		vigra::BasicImageView<double>::Iterator kernel_center = k.upperLeft() + vigra::Diff2D(kernel_width/2, kernel_height/2);
		
		convolveImage(	img.upperLeft(), img.lowerRight(), img.accessor(),
					  img2.upperLeft(), img2.accessor(),
					  kernel_center, k.accessor(),
					  k_ul, k_lr, vigra::BORDER_TREATMENT_REFLECT);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_separableconvolveimage_c(const float *arr, float *arr2, const double *kernel_arr_h, const double *kernel_arr_v, const int width,const  int height,const int kernel_width,const  int kernel_height){
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		
		vigra::BasicImage<float> temp(width, height);

		//check if kernel dimensions are odd
		if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
			return 2;
		
		vigra::separableConvolveX(img.upperLeft(), img.lowerRight(), img.accessor(),
								  temp.upperLeft(), temp.accessor(), 
								  kernel_arr_h + kernel_width/2, vigra::StandardAccessor<double>(), -kernel_width/2, kernel_width/2, vigra::BORDER_TREATMENT_REFLECT);
		
		vigra::separableConvolveY(temp.upperLeft(), temp.lowerRight(), temp.accessor(),
								  img2.upperLeft(), img2.accessor(), 
								  kernel_arr_v + kernel_height/2, vigra::StandardAccessor<double>(),  -kernel_height/2, kernel_height/2, vigra::BORDER_TREATMENT_REFLECT);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_gaussiangradient_c(const float *arr, const float *arr2, const float *arr3, const  int width,const  int height,const  float sigma){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		vigra::BasicImageView<float> img3(arr3, width, height);
		
		vigra::gaussianGradient(srcImageRange(img), destImage(img2), destImage(img3), sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_gaussiangradientmagnitude_c(const float *arr, const float *arr2,const  int width,const  int height,const  float sigma){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		
		vigra::gaussianGradientMagnitude(srcImageRange(img), destImage(img2), sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_gaussiansmoothing_c(const float *arr ,const float *arr2,const  int width,const  int height,const  float sigma){ 
    try
    {
      // create a gray scale image of appropriate size
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
            
      vigra::gaussianSmoothing(srcImageRange(img), destImage(img2), sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_laplacianofgaussian_c(const float *arr, const float *arr2,const  int width,const int height,const  float scale){ 
    try
    {
      // create a gray scale image of appropriate size
      vigra::BasicImageView<float> img(arr, width, height);
      vigra::BasicImageView<float> img2(arr2, width, height);
            
      vigra::laplacianOfGaussian(srcImageRange(img), destImage(img2), scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_hessianmatrixofgaussian_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float scale){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		vigra::hessianMatrixOfGaussian(srcImageRange(img),
							   destImage(img_xx), destImage(img_xy), destImage(img_yy), scale);
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_structuretensor_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float inner_scale, const float outer_scale){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		vigra::structureTensor(srcImageRange(img),
							   destImage(img_xx), destImage(img_xy), destImage(img_yy), inner_scale, outer_scale);
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_boundarytensor_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float scale){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		//create the temporary tensor
		typedef vigra::TinyVector<float, 3> FVector3;
		vigra::FVector3Image tensor(width,height);
		
		vigra::boundaryTensor(srcImageRange(img), destImage(tensor), scale);
		
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(0), img_xx.upperLeft(), img_xx.accessor());
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(1), img_xy.upperLeft(), img_xy.accessor());
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(2), img_yy.upperLeft(), img_yy.accessor());
		
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_boundarytensor1_c(const float *arr, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const float scale){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		//create the temporary tensor
		typedef vigra::TinyVector<float, 3> FVector3;
		vigra::FVector3Image tensor(width,height);
		
		vigra::boundaryTensor1(srcImageRange(img), destImage(tensor), scale);
		
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(0), img_xx.upperLeft(), img_xx.accessor());
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(1), img_xy.upperLeft(), img_xy.accessor());
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(2), img_yy.upperLeft(), img_yy.accessor());
		
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_gradientenergytensor_c(const float *arr, const double *arr_derivKernel, const double *arr_smoothKernel, const float *arr_xx, const float *arr_xy, const float *arr_yy, const int width, const int height, const int derivKernel_size, const int smoothKernel_size){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		//create the temporary tensor
		typedef vigra::TinyVector<float, 3> FVector3;
		vigra::FVector3Image tensor(width,height);
		
		vigra::Kernel1D<double> derivKernel, smoothKernel;
		
		derivKernel = derivKernel.initExplicitly(-derivKernel_size/2, derivKernel_size/2);
		for(int i=0; i<derivKernel_size; ++i){
			derivKernel[i+derivKernel_size/2] = arr_derivKernel[i];
		}
		
		smoothKernel = smoothKernel.initExplicitly(-smoothKernel_size/2, smoothKernel_size/2);
		for(int i=0; i<smoothKernel_size; ++i){
			smoothKernel[i+smoothKernel_size/2] = arr_smoothKernel[i];
		}
		
		vigra::gradientEnergyTensor(srcImageRange(img), destImage(tensor),  derivKernel, smoothKernel);
		
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(0), img_xx.upperLeft(), img_xx.accessor());
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(1), img_xy.upperLeft(), img_xy.accessor());
		vigra::copyImage(tensor.upperLeft(), tensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(2), img_yy.upperLeft(), img_yy.accessor());
		
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_tensoreigenrepresentation_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_lEV, const float *arr_sEV, const float *arr_ang, const int width, const int height){ 
    try
    {
		typedef vigra::TinyVector<float, 3> FVector3;
		
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		vigra::BasicImageView<float> img_lEV(arr_lEV, width, height);
		vigra::BasicImageView<float> img_sEV(arr_sEV, width, height);
		vigra::BasicImageView<float> img_ang(arr_ang, width, height);
		
		vigra::FVector3Image tensor(width,height);
		vigra::FVector3Image eigen(width,height);
		
		vigra::copyImage(img_xx.upperLeft(), img_xx.lowerRight(), img_xx.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(0));
		vigra::copyImage(img_xy.upperLeft(), img_xy.lowerRight(), img_xy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(1));
		vigra::copyImage(img_yy.upperLeft(), img_yy.lowerRight(), img_yy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(2));
		
		vigra::tensorEigenRepresentation(srcImageRange(tensor), destImage(eigen));
		
		vigra::copyImage(eigen.upperLeft(), eigen.lowerRight(), vigra::VectorComponentAccessor<FVector3>(0), img_lEV.upperLeft(), img_lEV.accessor());
		vigra::copyImage(eigen.upperLeft(), eigen.lowerRight(), vigra::VectorComponentAccessor<FVector3>(1), img_sEV.upperLeft(), img_sEV.accessor());
		vigra::copyImage(eigen.upperLeft(), eigen.lowerRight(), vigra::VectorComponentAccessor<FVector3>(2), img_ang.upperLeft(), img_ang.accessor());
		
		
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_tensortrace_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_trace, const int width, const int height){ 
    try
    {
		typedef vigra::TinyVector<float, 3> FVector3;
		
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		vigra::BasicImageView<float> img_trace(arr_trace, width, height);
		
		vigra::FVector3Image tensor(width,height);
		
		vigra::copyImage(img_xx.upperLeft(), img_xx.lowerRight(), img_xx.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(0));
		vigra::copyImage(img_xy.upperLeft(), img_xy.lowerRight(), img_xy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(1));
		vigra::copyImage(img_yy.upperLeft(), img_yy.lowerRight(), img_yy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(2));
		
		vigra::tensorTrace(srcImageRange(tensor), destImage(img_trace));
		
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_tensortoedgecorner_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_edgeness, const float *arr_orientation, const float *arr_cornerness, const int width, const int height){ 
    try
    {
		typedef vigra::TinyVector<float, 3> FVector3;
		typedef vigra::TinyVector<float, 2> FVector2;
		
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		vigra::BasicImageView<float> img_edgeness(arr_edgeness,   width, height);
		vigra::BasicImageView<float> img_orientation(arr_orientation,   width, height);
		vigra::BasicImageView<float> img_cornerness(arr_cornerness, width, height);
		
		vigra::FVector3Image tensor(width,height);
		vigra::FVector2Image edgePart(width,height);
		
		vigra::copyImage(img_xx.upperLeft(), img_xx.lowerRight(), img_xx.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(0));
		vigra::copyImage(img_xy.upperLeft(), img_xy.lowerRight(), img_xy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(1));
		vigra::copyImage(img_yy.upperLeft(), img_yy.lowerRight(), img_yy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(2));
		
		vigra::tensorToEdgeCorner(srcImageRange(tensor), destImage(edgePart), destImage(img_cornerness));
		
		vigra::copyImage(edgePart.upperLeft(), edgePart.lowerRight(), vigra::VectorComponentAccessor<FVector2>(0), img_edgeness.upperLeft(), img_edgeness.accessor());
		vigra::copyImage(edgePart.upperLeft(), edgePart.lowerRight(), vigra::VectorComponentAccessor<FVector2>(1), img_orientation.upperLeft(), img_orientation.accessor());
				
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
LIBEXPORT int vigra_hourglassfilter_c(const float *arr_xx, const float *arr_xy, const float *arr_yy, const float *arr_hgxx, const float *arr_hgxy, const float *arr_hgyy, const int width, const int height, const float sigma, const float rho){ 
    try
    {
		typedef vigra::TinyVector<float, 3> FVector3;
		
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img_xx(arr_xx, width, height);
		vigra::BasicImageView<float> img_xy(arr_xy, width, height);
		vigra::BasicImageView<float> img_yy(arr_yy, width, height);
		
		vigra::BasicImageView<float> img_hgxx(arr_hgxx, width, height);
		vigra::BasicImageView<float> img_hgxy(arr_hgxy, width, height);
		vigra::BasicImageView<float> img_hgyy(arr_hgyy, width, height);
		
		vigra::FVector3Image tensor(width,height);
		vigra::FVector3Image smoothedTensor(width,height);
		
		vigra::copyImage(img_xx.upperLeft(), img_xx.lowerRight(), img_xx.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(0));
		vigra::copyImage(img_xy.upperLeft(), img_xy.lowerRight(), img_xy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(1));
		vigra::copyImage(img_yy.upperLeft(), img_yy.lowerRight(), img_yy.accessor(), tensor.upperLeft(), vigra::VectorComponentAccessor<FVector3>(2));
		
		vigra::hourGlassFilter(srcImageRange(tensor), destImage(smoothedTensor), sigma, rho);
		
		vigra::copyImage(smoothedTensor.upperLeft(), smoothedTensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(0), img_hgxx.upperLeft(), img_hgxx.accessor());
		vigra::copyImage(smoothedTensor.upperLeft(), smoothedTensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(1), img_hgxy.upperLeft(), img_hgxy.accessor());
		vigra::copyImage(smoothedTensor.upperLeft(), smoothedTensor.lowerRight(), vigra::VectorComponentAccessor<FVector3>(2), img_hgyy.upperLeft(), img_hgyy.accessor());
		
		
	}
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_gaussiansharpening_c(const float *arr, const float *arr2,const int width, const int height, const float sharpening_factor, const float scale){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		
		vigra::gaussianSharpening(srcImageRange(img), destImage(img2),sharpening_factor, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_simplesharpening_c(const float *arr, const float *arr2, const int width, const int height, float sharpening_factor){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		
		vigra::simpleSharpening(srcImageRange(img), destImage(img2),sharpening_factor);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}


LIBEXPORT int vigra_nonlineardiffusion_c(const float *arr, const float *arr2, const int width, const int height, const float edge_threshold, const float scale){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		
		vigra::nonlinearDiffusion(srcImageRange(img), destImage(img2),
								  vigra::DiffusivityFunctor<float>(edge_threshold), scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_distancetransform_c(const float *arr, const float *arr2, const int width, const int height, const float background_label, const int norm){ 
    try
    {
		// create a gray scale image of appropriate size
		vigra::BasicImageView<float> img(arr, width, height);
		vigra::BasicImageView<float> img2(arr2, width, height);
		
		if(norm>=0 && norm <= 2)
			vigra::distanceTransform(   srcImageRange(img), destImage(img2),
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
