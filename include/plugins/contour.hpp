/*
 *
 * Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, Karl MacMillan
 *               2010      Oliver Christen, Christoph Dalitz
 *               2011      Andreas Leuschner, Christoph Dalitz
 *               2013      Christian Brandt
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef mgd10222004_contours
#define mgd10222004_contours


#include "gamera.hpp"
#include "plugins/edgedetect.hpp"

namespace Gamera {
template<class T>
FloatVector* contour_top(const T& m) {
    FloatVector* output = new FloatVector(m.ncols());
    try {
        for (size_t c = 0; c != m.ncols(); ++c) {
            size_t r = 0;
            for (; r != m.nrows(); ++r)
                if (is_black(m.get(Point(c, r))))
                    break;
            double result;
            if (r >= m.nrows())
                result = std::numeric_limits<double>::infinity();
            else
                result = (double)r;
            (*output)[c] = result;
        }
    } catch (std::exception e) {
        delete output;
        throw;
    }
    return output;
}

template<class T>
FloatVector* contour_bottom(const T& m) {
    FloatVector* output = new FloatVector(m.ncols());
    try {
        for (size_t c = 0; c != m.ncols(); ++c) {
            long r = m.nrows() - 1;
            for (; r >= 0; --r)
                if (is_black(m.get(Point(c, r))))
                    break;
            double result;
            if (r < 0)
                result = std::numeric_limits<double>::infinity();
            else
                result = (double)(m.nrows() - r);
            (*output)[c] = result;
        }
    } catch (std::exception e) {
    	std::cerr << e.what() << std::endl;
        delete output;
        throw;
    }
    return output;
}

template<class T>
FloatVector* contour_left(const T& m) {
    FloatVector* output = new FloatVector(m.nrows());
    try {
        for (size_t r = 0; r != m.nrows(); ++r) {
            size_t c = 0;
            for (; c != m.ncols(); ++c)
                if (is_black(m.get(Point(c, r))))
                    break;
            double result;
            if (c >= m.ncols())
                result = std::numeric_limits<double>::infinity();
            else
                result = (double)c;
            (*output)[r] = result;
        }
    } catch (std::exception e) {
        delete output;
        throw;
    }
    return output;
}

template<class T>
FloatVector* contour_right(const T& m) {
    FloatVector* output = new FloatVector(m.nrows());
    try {
        for (size_t r = 0; r != m.nrows(); ++r) {
            long c = m.ncols() - 1;
            for (; c >= 0; --c)
                if (is_black(m.get(Point(c, r))))
                    break;
            double result;
            if (c < 0)
                result = std::numeric_limits<double>::infinity();
            else
                result = (double)(m.ncols() - c);
            (*output)[r] = result;
        }
    } catch (std::exception e) {
        delete output;
        throw;
    }
    return output;
}

// etxraction of sample points from the contour
// author: Oliver Christen
template<class T>
PointVector * contour_samplepoints(const T& cc, int percentage, int contourtype=0) {
    PointVector *output = new PointVector();
    PointVector *contour_points = new PointVector();
    PointVector::iterator found;
    int x, y, i;
    float d;

    unsigned int top_d = std::numeric_limits<unsigned int>::max() ;
    unsigned int top_max_x = 0;
    unsigned int top_max_y = 0;

    unsigned int right_d = std::numeric_limits<unsigned int>::max();
    unsigned int right_max_x = 0;
    unsigned int right_max_y = 0;

    unsigned int bottom_d = std::numeric_limits<unsigned int>::max();
    unsigned int bottom_max_x = 0;
    unsigned int bottom_max_y = 0;

    unsigned int left_d = std::numeric_limits<unsigned int>::max();
    unsigned int left_max_x = 0;
    unsigned int left_max_y = 0;

    if (contourtype == 0) {
      FloatVector *top = contour_top(cc);
      FloatVector *right = contour_right(cc);
      FloatVector *bottom = contour_bottom(cc);
      FloatVector *left = contour_left(cc);
      FloatVector::iterator it;


      // top
      i = 0;
      for(it = top->begin() ; it != top->end() ; it++, i++) {
        if( *it == std::numeric_limits<double>::infinity() ) {
          continue;
        }
        d = *it;
        x = cc.offset_x() + i;
        y = cc.offset_y() + d;
        if( d < top_d) {
          top_d = d;
          top_max_x = x;
          top_max_y = y;
        }
        found = find(contour_points->begin(), contour_points->end(), Point(x,y));
        if(found == contour_points->end()) {
          contour_points->push_back( Point(x,y) );
        }
      }
      // right
      i = 0;
      for(it = right->begin() ; it != right->end() ; it++, i++) {
        if( *it == std::numeric_limits<double>::infinity() ) {
          continue;
        }
        d = *it;
        x = cc.offset_x() + cc.ncols() - d;
        y = cc.offset_y() + i;
        if( d < right_d) {
          right_d = d;
          right_max_x = x;
          right_max_y = y;
        }
        found = find(contour_points->begin(), contour_points->end(), Point(x,y));
        if(found == contour_points->end()) {
          contour_points->push_back( Point(x,y) );
        }
      }
      // bottom
      i = 0;
      for(it = bottom->begin() ; it != bottom->end() ; it++, i++) {
        if( *it == std::numeric_limits<double>::infinity() ) {
          continue;
        }
        d = *it;
        x = cc.offset_x() + i;
        y = cc.offset_y() + cc.nrows() - d;
        if( d <= bottom_d) {
          bottom_d = d;
          bottom_max_x = x;
          bottom_max_y = y;
        }
        found = find(contour_points->begin(), contour_points->end(), Point(x,y));
        if(found == contour_points->end()) {
          contour_points->push_back( Point(x,y) );
        }
      }
      // left
      i = 0;
      for(it = left->begin() ; it != left->end() ; it++, i++) {
        if( *it == std::numeric_limits<double>::infinity() ) {
          continue;
        }
        d = *it;
        x = cc.offset_x() + d;
        y = cc.offset_y() + i;
        if( d <= left_d) {
          left_d = d;
          left_max_x = x;
          left_max_y = y;
        }
        found = find(contour_points->begin(), contour_points->end(), Point(x,y));
        if(found == contour_points->end()) {
          contour_points->push_back( Point(x,y) );
        }
      }
      delete top;
      delete right;
      delete bottom;
      delete left;
    }
    else { // contourtype == 1
      typedef typename ImageFactory<T>::view_type view_type;
      view_type* tmp = outline(cc, 1);
      for (size_t y=0; y < tmp->nrows(); y++) {
        for (size_t x=0; x < tmp->ncols(); x++) {
          if (is_black(tmp->get(Point(x,y)))) {
            contour_points->push_back(Point(cc.offset_x()+x, cc.offset_y()+y));
            if (x < left_d) {
              left_d = x;
              left_max_x = cc.offset_x() + x;
              left_max_y = cc.offset_y() + y;
            }
            if (cc.ncols()-x < right_d) {
              right_d = cc.ncols()-x;
              right_max_x = cc.offset_x() + x;
              right_max_y = cc.offset_y() + y;
            }
            if (y < top_d) {
              top_d = y;
              top_max_x = cc.offset_x() + x;
              top_max_y = cc.offset_y() + y;
            }
            if (cc.nrows()-y < bottom_d) {
              bottom_d = cc.nrows() - y;
              bottom_max_x = cc.offset_x() + x;
              bottom_max_y = cc.offset_y() + y;
            }
          }
        }
      }
      delete tmp->data();
      delete tmp;
    }

    // add only every 100/percentage-th point
    double delta = 100.0/percentage;
    double step = 0.0;
    unsigned int offset = 0; // to avoid overflow and rounding errors
    unsigned int ii = 0;
    while (ii < contour_points->size()) {
        output->push_back( (*contour_points)[ii] );
        step += delta;
        if (step > 100.0) {
            step -= 100.0;
            offset += 100;
        }
        ii = offset + (unsigned int)step;
    }

    // add the four outer extreme points ...
    // ... top
    if (top_d != std::numeric_limits<unsigned int>::max()) {
        found = find(output->begin(), output->end(), Point(top_max_x, top_max_y));
        if(found == output->end()) {
            output->push_back( Point(top_max_x, top_max_y) );
        }
    }
    // ... right
    if (right_d != std::numeric_limits<unsigned int>::max()) {
        found = find(output->begin(), output->end(), Point(right_max_x, right_max_y));
        if(found == output->end()) {
            output->push_back( Point(right_max_x, right_max_y) );
        }
    }
    // ... bottom
    if (bottom_d != std::numeric_limits<unsigned int>::max()) {
        found = find(output->begin(), output->end(), Point(bottom_max_x, bottom_max_y));
        if(found == output->end()) {
            output->push_back( Point(bottom_max_x, bottom_max_y) );
        }
    }
    // ... left
    if (left_d != std::numeric_limits<unsigned int>::max()) {
        found = find(output->begin(), output->end(), Point(left_max_x, left_max_y));
        if(found == output->end()) {
            output->push_back( Point(left_max_x, left_max_y) );
        }
    }

    delete contour_points;

    return output;
}

// contour extraction with Pavlidis' algorithm
// author: Andreas Leuschner
template<class T>
PointVector* contour_pavlidis(T &m) {

    PointVector* v_contour = new PointVector();

    // neighbor mask:
    //   5  6  7
    //   4  P  0
    //   3  2  1
    int mask[8][2];
    //	 X            Y
    mask[0][0] = 1;    mask[0][1] = 0;
    mask[1][0] = 1;    mask[1][1] = -1;
    mask[2][0] = 0;    mask[2][1] = -1;
    mask[3][0] = -1;   mask[3][1] = -1;
    mask[4][0] = -1;   mask[4][1] = 0;
    mask[5][0] = -1;   mask[5][1] = 1;
    mask[6][0] = 0;    mask[6][1] = 1;
    mask[7][0] = 1;    mask[7][1] = 1;

    // find startpixel
    unsigned int x = 0;
    unsigned int y = 0;
    bool found=false;
    for(x = 0; x < m.ncols() && !found; x++) {
        for(y = 0; y < m.nrows() && !found; y++) {
            if(is_black(m.get(Point(x,y)))) {
                v_contour->push_back(Point(x,y));
                found = true;
            }
        }
    }
    if (!found)
      return v_contour;

	// extract contour
    Point p_Right;
    Point p_Middle;
    Point p_Left;
    unsigned int newX_R;
    unsigned int newY_R;
    unsigned int newX_M;
    unsigned int newY_M;
    unsigned int newX_L;
    unsigned int newY_L;
    found = false;
    bool first = true;
    int n = 0;
    int s = 6;
    int third = 0;

    int run = 1;
    while ( first == true || !((*v_contour)[n].x() == (*v_contour)[0].x() &&
            (*v_contour)[n].y() == (*v_contour)[0].y())
          ) {
        found = false;
        while(found == false && third < 3) {
            third++;

            newX_R = (*v_contour)[n].x() + mask[ (s-1+8)%8 ][0];
            newY_R = (*v_contour)[n].y() + mask[ (s-1+8)%8 ][1];

            newX_M = (*v_contour)[n].x() + mask[ (s)%8 ][0];
            newY_M = (*v_contour)[n].y() + mask[ (s)%8 ][1];

            newX_L = (*v_contour)[n].x() + mask[ (s+1)%8 ][0];
            newY_L = (*v_contour)[n].y() + mask[ (s+1)%8 ][1];

            if((newX_R < m.ncols() && newY_R < m.nrows()) ||
                    (newX_M < m.ncols() && newY_M < m.nrows()) ||
                    (newX_L < m.ncols() && newY_L < m.nrows())) {

                p_Right.x( newX_R );
                p_Right.y( newY_R );
                p_Middle.x( newX_M );
                p_Middle.y( newY_M );
                p_Left.x( newX_L );
                p_Left.y( newY_L );
                if (newX_R < m.ncols() && newY_R < m.nrows() && is_black(m.get(p_Right))) {
                    v_contour->push_back(p_Right);
                    found = true;
                    n++;
                    s = (s+8 - 2) % 8;
                }
                else if(newX_M < m.ncols() && newY_M < m.nrows() && is_black(m.get(p_Middle))) {
                    v_contour->push_back(p_Middle);
                    found = true;
                    n++;
                }
                else if(newX_L < m.ncols() && newY_L < m.nrows() && is_black(m.get(p_Left))) {
                    v_contour->push_back(p_Left);
                    found = true;
                    n++;
                }
                else {
                    s = (s + 2)%8;
                }
            }
            else {
                s = (s + 2) %8;
            }
        }
		
		third = 0;
        first = false;
        run++;
    }
    
	if (v_contour->size() > 1) {
        v_contour->pop_back(); // start pixel is doublette
	}

    return v_contour;
}

}
#endif
