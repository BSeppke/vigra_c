#ifndef VIGRA_KERNELUTILS_H
#define VIGRA_KERNELUTILS_H

#include <vigra/stdconvolution.hxx>
#include <vigra/multi_convolution.hxx>

/**
 * Internal helper function to generate a vigra::Kernel2D from a flat array.
 * The template argument determines the data type of the array and the resulting
 * Kernel2D.
 *
 * \param arr_in Flat input array of size width*height.
 * \param width The width of the flat array.
 * \param height The height of the height of the flat array.
 *
 * \return The result of the given array as a vigra::Kernel2D.
 */
template<class T>
vigra::Kernel2D<T> kernel2dFromArray(const T * arr_in,
                                     const int width,
                                     const int height)
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

/**
 * Internal helper function to generate a vigra::Kernel1D from a flat array.
 * The template argument determines the data type of the array and the resulting
 * Kernel1D.
 *
 * \param arr_in Flat input array of size size.
 * \param size The size of the flat array.
 *
 * \return The result of the given array as a vigra::Kernel1D.
 */
template<class T>
vigra::Kernel1D<T> kernel1dFromArray(const T * arr_in,
                                     const int size)
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

#endif
