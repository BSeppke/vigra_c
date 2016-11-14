#include "vigra_filters_c.h"

#include <vigra/stdconvolution.hxx>
#include <vigra/multi_convolution.hxx>
#include <vigra/nonlineardiffusion.hxx>
#include <vigra/distancetransform.hxx>
#include <vigra/tensorutilities.hxx>
#include <vigra/gradient_energy_tensor.hxx>
#include <vigra/boundarytensor.hxx>
#include <vigra/orientedtensorfilters.hxx>
#include <vigra/shockfilter.hxx>


//Helper function to generate a vigra::Kernel2D from a flat array
template<class T>
vigra::Kernel2D<T> kernel2dFromArray(const T* arr_in, const int width, const int height)
{
    //Create a view on the data
    vigra::Shape2 shape(width,height);
    vigra::MultiArrayView<2, T, vigra::UnstridedArrayTag> k_img_in(shape, arr_in);
    
    //Allocate a temp. BasicImage<T> for initialization of the Kernel2D,
    //which shall be returned.
    vigra::BasicImage<T> temp_kernel(width, height);
    
    //Fill the temp image
    for(int y=0; y<height; ++y)
        for(int x=0; x<width; ++x)
            temp_kernel(x,y) = k_img_in(x,y);
    
    //Init a kernel based in that image
    vigra::Kernel2D<T> kernel;
    kernel.initExplicitly(temp_kernel);
    
    //and return it
    return kernel;
}


//Helper function to generate a vigra::Kernel1D from a flat array
template<class T>
vigra::Kernel1D<T> kernel1dFromArray(const T* arr_in, const int size)
{
    //Boundaries of the kernel
    int b = size/2;
    
    //Init the convolution kernel
    vigra::Kernel1D<T> kernel;
    kernel.initExplicitly(-b, b);
    
    //Fill the kernel with array data
    for(int i=0; i<size; ++i)
    {
        kernel[i-b] = arr_in[i];
    }
    
    //and return it
    return kernel;
}

LIBEXPORT int vigra_convolveimage_c(const PixelType *arr_in, const double *kernel_arr_in, const PixelType *arr_out, const int width, const int height, const int kernel_width, const int kernel_height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        //check if kernel dimensions are odd
        if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
            return 2;
        
        vigra::convolveImage(img_in, img_out, kernel2dFromArray(kernel_arr_in, kernel_width, kernel_height));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_separableconvolveimage_c(const PixelType *arr_in, const double *kernel_arr_h, const double *kernel_arr_v, const PixelType *arr_out, const int width, const int height, const int kernel_width, const int kernel_height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        //check if kernel dimensions are odd
        if ( (kernel_width % 2)==0 || (kernel_height % 2)==0)
            return 2;
        
        vigra::convolveImage(img_in, img_out, kernel1dFromArray(kernel_arr_h, kernel_width), kernel1dFromArray(kernel_arr_v, kernel_height));
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiangradient_c(const PixelType *arr_in, const PixelType *arr_gx_out, const PixelType *arr_gy_out, const int width, const int height, const float sigma)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_gx(shape, arr_gx_out);
        ImageView img_gy(shape, arr_gy_out);
        
        vigra::gaussianGradient(img_in, img_gx, img_gy, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiangradientmagnitude_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float sigma)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::gaussianGradientMagnitude(img_in, img_out, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_gaussiansmoothing_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float sigma)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::gaussianSmoothing(img_in, img_out, sigma);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_laplacianofgaussian_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::laplacianOfGaussian(img_in, img_out, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_hessianmatrixofgaussian_c(const PixelType *arr_in, const PixelType *arr_xx_out, const PixelType *arr_xy_out, const PixelType *arr_yy_out, const int width, const int height, const float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_xx(shape, arr_xx_out);
        ImageView img_xy(shape, arr_xy_out);
        ImageView img_yy(shape, arr_yy_out);
        
        vigra::hessianMatrixOfGaussian(img_in, img_xx,img_xy,img_yy, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_structuretensor_c(const PixelType *arr_in, const PixelType *arr_xx_out, const PixelType *arr_xy_out, const PixelType *arr_yy_out, const int width, const int height, const float inner_scale, const float outer_scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_xx(shape, arr_xx_out);
        ImageView img_xy(shape, arr_xy_out);
        ImageView img_yy(shape, arr_yy_out);
        
        vigra::structureTensor(img_in, img_xx,img_xy,img_yy, inner_scale, outer_scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    
    return 0;
}

LIBEXPORT int vigra_boundarytensor_c(const PixelType *arr_in, const PixelType *arr_xx_out, const PixelType *arr_xy_out, const PixelType *arr_yy_out, const int width, const int height, const float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_xx(shape, arr_xx_out);
        ImageView img_xy(shape, arr_xy_out);
        ImageView img_yy(shape, arr_yy_out);
        
        //create the temporary tensor
        vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
        
        vigra::boundaryTensor(img_in, tensor, scale);
        
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

LIBEXPORT int vigra_boundarytensor1_c(const PixelType *arr_in, const PixelType *arr_xx_out, const PixelType *arr_xy_out, const PixelType *arr_yy_out, const int width, const int height, const float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_xx(shape, arr_xx_out);
        ImageView img_xy(shape, arr_xy_out);
        ImageView img_yy(shape, arr_yy_out);
        
        //create the temporary tensor
        vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
        
        vigra::boundaryTensor1(img_in, tensor, scale);
        
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

LIBEXPORT int vigra_gradientenergytensor_c(const PixelType *arr_in, const double *arr_derivKernel_in, const double *arr_smoothKernel_in, const PixelType *arr_xx_out, const PixelType *arr_xy_out, const PixelType *arr_yy_out, const int width, const int height, const int derivKernel_size, const int smoothKernel_size)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_xx(shape, arr_xx_out);
        ImageView img_xy(shape, arr_xy_out);
        ImageView img_yy(shape, arr_yy_out);
        
        //create the temporary tensor
        vigra::MultiArray<2, vigra::TinyVector<float, 3> > tensor(width,height);
        
        vigra::Kernel1D<double> derivKernel, smoothKernel;
        
        derivKernel = derivKernel.initExplicitly(-derivKernel_size/2, derivKernel_size/2);
        for(int i=0; i<derivKernel_size; ++i)
        {
            derivKernel[i+derivKernel_size/2] = arr_derivKernel_in[i];
        }
        
        smoothKernel = smoothKernel.initExplicitly(-smoothKernel_size/2, smoothKernel_size/2);
        for(int i=0; i<smoothKernel_size; ++i)
        {
            smoothKernel[i+smoothKernel_size/2] = arr_smoothKernel_in[i];
        }
        
        vigra::gradientEnergyTensor(img_in, tensor, derivKernel, smoothKernel);
        
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

LIBEXPORT int vigra_tensoreigenrepresentation_c(const PixelType *arr_xx_in, const PixelType *arr_xy_in, const PixelType *arr_yy_in, const PixelType *arr_lEV_out, const PixelType *arr_sEV_out, const PixelType *arr_ang_out, const int width, const int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_xx(shape, arr_xx_in);
        ImageView img_xy(shape, arr_xy_in);
        ImageView img_yy(shape, arr_yy_in);
        
        ImageView img_lEV(shape, arr_lEV_out);
        ImageView img_sEV(shape, arr_sEV_out);
        ImageView img_ang(shape, arr_ang_out);
        
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

LIBEXPORT int vigra_tensortrace_c(const PixelType *arr_xx_in, const PixelType *arr_xy_in, const PixelType *arr_yy_in, const PixelType *arr_trace_out, const int width, const int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_xx(shape, arr_xx_in);
        ImageView img_xy(shape, arr_xy_in);
        ImageView img_yy(shape, arr_yy_in);
        ImageView img_trace(shape, arr_trace_out);
        
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

LIBEXPORT int vigra_tensortoedgecorner_c(const PixelType *arr_xx_in, const PixelType *arr_xy_in, const PixelType *arr_yy_in, const PixelType *arr_edgeness_out, const PixelType *arr_orientation_out, const PixelType *arr_cornerness_out, const int width, const int height)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_xx(shape, arr_xx_in);
        ImageView img_xy(shape, arr_xy_in);
        ImageView img_yy(shape, arr_yy_in);
        
        ImageView img_edgeness(shape, arr_edgeness_out);
        ImageView img_orientation(shape, arr_orientation_out);
        ImageView img_cornerness(shape, arr_cornerness_out);
        
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
LIBEXPORT int vigra_hourglassfilter_c(const PixelType *arr_xx_in, const PixelType *arr_xy_in, const PixelType *arr_yy_in, const PixelType *arr_hgxx_out, const PixelType *arr_hgxy_out, const PixelType *arr_hgyy_out, const int width, const int height, const float sigma, const float rho)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_xx(shape, arr_xx_in);
        ImageView img_xy(shape, arr_xy_in);
        ImageView img_yy(shape, arr_yy_in);
        
        ImageView img_hgxx(shape, arr_hgxx_out);
        ImageView img_hgxy(shape, arr_hgxy_out);
        ImageView img_hgyy(shape, arr_hgyy_out);
        
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

LIBEXPORT int vigra_gaussiansharpening_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float sharpening_factor, const float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::gaussianSharpening(img_in, img_out, sharpening_factor, scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_simplesharpening_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, float sharpening_factor)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::simpleSharpening(img_in, img_out, sharpening_factor);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_nonlineardiffusion_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float edge_threshold, const float scale)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        vigra::nonlinearDiffusion(img_in, img_out,
                                  vigra::DiffusivityFunctor<float>(edge_threshold), scale);
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

LIBEXPORT int vigra_distancetransform_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float background_label, const int norm)
{
    try
    {
        // create a gray scale image of appropriate size
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

LIBEXPORT int vigra_shockfilter_c(const PixelType *arr_in, const PixelType *arr_out, const int width, const int height, const float sigma, const float rho, const float upwind_factor_h, const int iterations)
{
    try
    {
        // create a gray scale image of appropriate size
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        ImageView img_out(shape, arr_out);
        
        if(iterations>=0)
            vigra::shockFilter(img_in, img_out, sigma, rho, upwind_factor_h, iterations);
        else
            return 2;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
