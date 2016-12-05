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

#ifndef VIGRA_KERNELUTILS_H
#define VIGRA_KERNELUTILS_H

#include <vigra/stdconvolution.hxx>
#include <vigra/multi_array.hxx>

/**
 * @file
 * @brief Header-only file for Kernel conversion utilities
 *
 * @defgroup kernelutils Kernel utilities
 * @{
 *    @brief Contains internal helpers (not exported by VIGRA_C) to convert arrays to kernels (Header-only file).
 */
 
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
    
    int w2 = width/2;
    int h2 = height/2;
    
    vigra::Kernel2D<T> kernel;
    kernel.initExplicitly(vigra::Shape2(-w2, -h2), vigra::Shape2(w2, h2));

    //Fill the kernel with array data
    for(int y=0; y<height; ++y)
    {
        for(int x=0; x<width; ++x)
        {
            kernel(x-w2,y-h2) = k_img_in(x,y);
        }
    }
    
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

/**
 * @}
 */
 
#endif
