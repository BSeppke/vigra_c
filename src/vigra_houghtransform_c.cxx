/************************************************************************/
/*                                                                      */
/*               Copyright 2020-2022 by Benjamin Seppke                 */
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

#include "vigra_houghtransform_c.h"
#include <iostream>
#include "vigra_ext/houghtransform.hxx"



/**
 * @file
 * @brief Implementation of hough transfrom for lines
 */

LIBEXPORT void* vigra_houghtransform_lines_c(const PixelType * arr_in,
                                        const int width,
                                        const int height,
                                        const int angles,
                                        const int min_supporters)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        
        using namespace vigra_ext;
        HoughLineTransform hlt(angles, shape);
        hlt.fillAccumulator(img_in);
        
        std::vector<HoughLine> paramLines =  hlt.extractLines(min_supporters);
        std::sort(paramLines.begin(), paramLines.end());
        
        std::vector<HoughLine>* persistentResult = new std::vector<HoughLine>(paramLines.size());
        std::copy(paramLines.begin(), paramLines.end(), persistentResult->begin());
        return persistentResult;
    }
    catch (vigra::StdException & e)
    {
        return nullptr;
    }
    return nullptr;
}

int vigra_houghtransform_get_line_count_c(const void * hough_lines)
{
    try
    {
        using namespace vigra_ext;
        
        const std::vector<HoughLine>* persistentResult = reinterpret_cast<const std::vector<HoughLine>*>(hough_lines);
        return persistentResult->size();
    }
    catch (vigra::StdException & e)
    {
        return 0;
    }
    return 0;
}

int vigra_houghtransform_get_lines_c(const void * hough_lines,
    PixelType * arr_out,
    const int width,
    const int height)
{
    try
    {
        using namespace vigra_ext;
        
        const std::vector<HoughLine>* persistentResult = reinterpret_cast<const std::vector<HoughLine>*>(hough_lines);
        
        if ((width != 3) || (height != persistentResult->size()))
        {
            return 1;
        }
        
        //Create gray scale image for the  line array
        vigra::Shape2 shape(width,height);
        ImageView img_out(shape, arr_out);
        
        for (int y=0; y!= height; ++y)
        {
            img_out(0,y) = persistentResult->at(y).angle;
            img_out(1,y) = persistentResult->at(y).distance;
            img_out(2,y) = persistentResult->at(y).weight;
        }
    }
    catch (vigra::StdException & e)
    {
        return 2;
    }
    return 0;
}

int vigra_houghtransform_delete_lines_c(void * hough_lines)
{
    try
    {
        using namespace vigra_ext;
        
        std::vector<HoughLine>* persistentResult = reinterpret_cast<std::vector<HoughLine>*>(hough_lines);
        delete persistentResult;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}

/**
 * @file
 * @brief Implementation of hough transfrom for circles
 */

LIBEXPORT void* vigra_houghtransform_cicles_c(const PixelType * arr_in,
                                        const int width,
                                        const int height,
                                        const int min_radius,
                                        const int max_radius,
                                        const int min_supporters)
{
    try
    {
        //Create gray scale image views for the arrays
        vigra::Shape2 shape(width,height);
        ImageView img_in(shape, arr_in);
        
        using namespace vigra_ext;
        HoughCircleTransform hct(min_radius, max_radius, shape);
        hct.fillAccumulator(img_in);
        
        std::vector<HoughCircle> paramCircles =  hct.extractCircles(min_supporters);
        std::sort(paramCircles.begin(), paramCircles.end());
        
        std::vector<HoughCircle>* persistentResult = new std::vector<HoughCircle>(paramCircles.size());
        std::copy(paramCircles.begin(), paramCircles.end(), persistentResult->begin());
        return persistentResult;
        
    }
    catch (vigra::StdException & e)
    {
        return nullptr;
    }
    return nullptr;
}

int vigra_houghtransform_get_circle_count_c(const void * hough_cicles)
{
    try
    {
        using namespace vigra_ext;
        
        const std::vector<HoughCircle>* persistentResult = reinterpret_cast<const std::vector<HoughCircle>*>(hough_cicles);
        return persistentResult->size();
    }
    catch (vigra::StdException & e)
    {
        return 0;
    }
    return 0;
}

int vigra_houghtransform_get_circles_c(const void * hough_circles,
    PixelType * arr_out,
    const int width,
    const int height)
{
    try
    {
        using namespace vigra_ext;
        
        const std::vector<HoughCircle>* persistentResult = reinterpret_cast<const std::vector<HoughCircle>*>(hough_circles);
        
        if ((width != 4) || (height != persistentResult->size()))
        {
            return 1;
        }
        
        //Create gray scale image for the  line array
        vigra::Shape2 shape(width, height);
        ImageView img_out(shape, arr_out);
        
        for (int y=0; y!= img_out.height(); ++y)
        {
            img_out(0,y) = persistentResult->at(y).pos_x;
            img_out(1,y) = persistentResult->at(y).pos_y;
            img_out(2,y) = persistentResult->at(y).radius;
            img_out(3,y) = persistentResult->at(y).weight;
        }
    }
    catch (vigra::StdException & e)
    {
        return 2;
    }
    return 0;
}

int vigra_houghtransform_delete_circles_c(void * hough_circles)
{
    try
    {
        using namespace vigra_ext;
        
        std::vector<HoughCircle>* persistentResult = reinterpret_cast<std::vector<HoughCircle>*>(hough_circles);
        delete persistentResult;
    }
    catch (vigra::StdException & e)
    {
        return 1;
    }
    return 0;
}
