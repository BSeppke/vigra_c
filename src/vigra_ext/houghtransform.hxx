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
/*                                                                      *//************************************************************************/

#ifndef HOUGHTRANSFORM_HXX
#define HOUGHTRANSFORM_HXX

#include <iostream>
#include <vigra/multi_array.hxx>
#include <vigra/multi_localminmax.hxx>
#include <vigra/multi_math.hxx>

namespace vigra_ext
{

// Default Type for parametric lines:
class HoughLine
{
public:
    HoughLine()
    : angle(0),
      distance(0),
      weight(0)
    {
    }
    HoughLine(double a, double d, double w)
    : angle(a),
      distance(d),
      weight(w)
    {
    }
    HoughLine(const HoughLine& other)
    : angle(other.angle),
      distance(other.distance),
      weight(other.weight)
    {
    }
    
    bool operator<(const HoughLine& rhs)  const
    {
        return weight < rhs.weight;
    }
    
    double angle;     //angle in radians
    double distance;  //distance from image center
    double weight;    //weight/strength of line
};


class HoughLineTransform
{

public:
    HoughLineTransform(int angles, const vigra::Shape2 & shape)
    : m_angles(angles),
      m_maxDistance(vigra::round(shape.magnitude()/2)),
      m_cx(shape[0]/2),
      m_cy(shape[1]/2)
    {
        //Prepare Look-up tables
        prepareLUTs();
        m_accumulator.reshape(vigra::Shape2(m_angles,2*m_maxDistance));
    }

    int angles() const
    {
        return m_angles;
    }

    int maxDistance() const
    {
        return m_maxDistance;
    }
    
    const vigra::MultiArrayView<2, unsigned long> accumulator() const
    {
        return m_accumulator;
    }
    
    template<class T>
    const vigra::MultiArrayView<2,unsigned long> fillAccumulator(const vigra::MultiArrayView<2,T> & img)
    {
        for(int y=0; y!=img.height(); y++)
        {
            for(int x=0; x!=img.width(); x++)
            {
                if(img(x,y) != vigra::NumericTraits<T>::zero())
                {
                    for(int i=0; i!=m_angles; i++)
                    {
                        int d = vigra::round(m_maxDistance+m_cosines[i]*(x-m_cx) + m_sines[i]*(y-m_cy));
                        m_accumulator(i, d)++;
                    }
                }
            }
        }
        return m_accumulator;
    }
    
    void clearAccumulator()
    {
        m_accumulator=0;
    }
    
    template<class T>
    std::vector<HoughLine> extractLines(const vigra::MultiArrayView<2,T> & img, int min_supporters = 50)
    {
        clearAccumulator();
        fillAccumulator(img);
        return extractLines(min_supporters);
    }
    
    std::vector<HoughLine> extractLines(int min_supporters = 50)
    {
        std::vector<HoughLine> paramLines;
        
        // extract local maxima
        vigra::MultiArray<2, unsigned long> houghSpace_max(m_accumulator.shape());
        vigra::localMaxima( m_accumulator,
                            houghSpace_max,
                            vigra::LocalMinmaxOptions().neighborhood(vigra::DirectNeighborhood).allowAtBorder());
        
        // weight local maxima with supporters
        using namespace vigra::multi_math;
        houghSpace_max = houghSpace_max*m_accumulator;
        
        // extract valid lines by means of their parameters
        // (angle [Radians], d [Pixels])
        for(int d=0; d!=houghSpace_max.height(); d++)
        {
            for(int a=0; a!=houghSpace_max.width(); a++)
            {
                int weight = houghSpace_max(a,d);
                
                if(weight >= min_supporters)
                {
                    paramLines.push_back( HoughLine(
                                                M_PI*a/houghSpace_max.width(),
                                                d-houghSpace_max.height()/2.0,
                                                weight));
                }
            }
        }
        return paramLines;
    }

protected:
    void prepareLUTs()
    {
        //Prepare Look-up tables
        m_sines.resize(m_angles);
        m_cosines.resize(m_angles);
        
        double fac=M_PI/m_angles;
        double angle;
    
        for(int i=0; i!=m_angles; i++)
        {
            angle=fac*i;
            m_sines[i]   = sin(angle);
            m_cosines[i] = cos(angle);
        }
    }

    int m_angles;
    int m_maxDistance;

    std::vector<double> m_sines;
    std::vector<double> m_cosines;
    int m_cx;
    int m_cy;

    vigra::MultiArray<2, unsigned long> m_accumulator;
};

// Default Type for parametric lines:
class HoughCircle
{
public:
    HoughCircle()
    : pos_x(0),
      pos_y(0),
      radius(0),
      weight(0)
    {
    }
    HoughCircle(double a, double b, double r, double w)
    : pos_x(a),
      pos_y(b),
      radius(r),
      weight(w)
    {
    }
    HoughCircle(const HoughCircle & other)
    : pos_x(other.pos_x),
      pos_y(other.pos_y),
      radius(other.radius),
      weight(other.weight)
    {
    }
    
    bool operator<(const HoughCircle& rhs)  const
    {
        return weight < rhs.weight;
    }
    
    
    double pos_x;  //x position
    double pos_y;  //y position
    double radius; //radius
    double weight; //weight/strength of line
};


class HoughCircleTransform
{

public:
    HoughCircleTransform(int min_radius, int max_radius, const vigra::Shape2 & shape)
    : m_minRadius(min_radius),
      m_maxRadius(max_radius)
    {
        //Prepare Look-up tables
        prepareLUTs();
        m_accumulator.reshape(vigra::Shape3(shape[0]+2*m_maxRadius, shape[1]+2*m_maxRadius, m_maxRadius-m_minRadius));
    }

    int minRadius() const
    {
        return m_minRadius;
    }

    int maxRadius() const
    {
        return m_maxRadius;
    }
    
    const vigra::MultiArrayView<3, unsigned long> accumulator() const
    {
        return m_accumulator;
    }
        
    template<class T>
    const vigra::MultiArrayView<3,unsigned long> fillAccumulator(const vigra::MultiArrayView<2,T> & img)
    {
        for(int y=0; y!=img.height(); y++)
        {
            for(int x=0; x!=img.width(); x++)
            {
                if(img(x,y) != vigra::NumericTraits<T>::zero())
                {
                    int r=0;
                    for(const std::vector<vigra::Shape2> & circleCoords : m_circlesCoords)
                    {
                        for(const vigra::Shape2 & coords : circleCoords)
                        {
                            m_accumulator(x + coords[0],
                                          y + coords[1],
                                          r)++;
                        }
                        r++;
                    }
                }
            }
        }
        return m_accumulator;
    }
    
    void clearAccumulator()
    {
        m_accumulator=0;
    }
    
    template<class T>
    std::vector<HoughCircle> extractCircles(const vigra::MultiArrayView<2,T> & img, float min_supporters = 0.5)
    {
        clearAccumulator();
        fillAccumulator(img);
        return extractCircles(min_supporters);
    }
    
    
    std::vector<HoughCircle> extractCircles(float min_supporters = 0.5)
    {
        std::vector<HoughCircle> paramCircles;
        
        // extract local maxima
        vigra::MultiArray<3, unsigned long> houghSpace_max(m_accumulator.shape());
        vigra::localMaxima(m_accumulator,
                    houghSpace_max,
                vigra::LocalMinmaxOptions().neighborhood(vigra::DirectNeighborhood).allowAtBorder());
        
        // weight local maxima with supporters
        using namespace vigra::multi_math;
        houghSpace_max = houghSpace_max*m_accumulator;
        
        // extract valid circles by means of their parameters
        // (pos_x, pos_y, radius [Pixels])
        for(int r=0; r!=houghSpace_max.shape()[2]; r++)
        {
            for(int y=0; y!=houghSpace_max.shape()[1]; y++)
            {
                for(int x=0; x!=houghSpace_max.shape()[0]; x++)
                {
                    double weight = houghSpace_max(x,y,r)/(2*M_PI*(r+m_minRadius));
                    
                    if(weight >= min_supporters)
                    {
                        paramCircles.push_back( HoughCircle(
                                                    x-m_maxRadius,
                                                    y-m_maxRadius,
                                                    r+m_minRadius,
                                                    weight));
                    }
                }
            }
        }
        return paramCircles;
    }

protected:
    void prepareLUTs()
    {
        //Prepare Look-up tables
        for(int r=m_minRadius; r!=m_maxRadius; r++)
        {
            int circum = vigra::round(2*M_PI*r);
            std::vector<vigra::Shape2> circleCoords(circum);
            
            double fac=2.0*M_PI/circum;
            double angle;
            
            for(int i=0; i!=circum; ++i)
            {
                angle = fac*i;
                circleCoords[i][0] = m_maxRadius-r*cos(angle);
                circleCoords[i][1] = m_maxRadius-r*sin(angle);
            }
            m_circlesCoords.push_back(circleCoords);
        }
    }
    
    int m_minRadius;
    int m_maxRadius;

    std::vector< std::vector<vigra::Shape2> > m_circlesCoords;

    vigra::MultiArray<3, unsigned long> m_accumulator;
};

} // namespace vigra_ext

#endif //#define HOUGH_TRANSFORM_HXX
