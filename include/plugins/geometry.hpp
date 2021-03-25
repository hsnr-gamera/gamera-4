/*
 * Copyright (C) 2009-2015 Christoph Dalitz
 *               2010      Oliver Christen
 *               2011      Christian Brandt
 *               2012      David Kolanus
 *               2015      Manuel Jeltsch
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


#ifndef cd30112009_geometry
#define cd30112009_geometry

#include <map>
#include <set>
#include <stack>
#include <algorithm>
#include "gamera.hpp"
#include "vigra/distancetransform.hxx"
#include "vigra/seededregiongrowing.hxx"
#include "geostructs/kdtree.hpp"
#include "geostructs/delaunaytree.hpp"
#include "graph/graph.hpp"
#include "graph/graphdataderived.hpp"
#include "graph/node.hpp"
#include "plugins/contour.hpp"
#include "plugins/draw.hpp"


using namespace Gamera::Kdtree;
using namespace Gamera::Delaunaytree;
using namespace Gamera::GraphApi;
using namespace std;

namespace Gamera {

  // this implementation is based on a sample program included
  // in the VIGRA library by Ulrich Koethe
  template<class T>
  Image* voronoi_from_labeled_image(const T& src, bool white_edges=false) {
    typedef typename T::value_type value_type;
    typedef typename ImageFactory<T>::data_type data_type;
    typedef typename ImageFactory<T>::view_type view_type;
    // vigra's seeded region growing only works on greyscale images
    Grey16ImageData* voronoi_data = new Grey16ImageData(src.size(), src.origin());
    Grey16ImageView* voronoi = new Grey16ImageView(*voronoi_data);
    size_t x,y;
    value_type val, maxlabel;
    map<value_type, bool> all_labels;

    maxlabel = 0;
    for (y=0; y<src.nrows(); ++y) {
      for (x=0; x<src.ncols(); ++x) {
        val = src.get(Point(x,y));
        if (val > 0) {
          voronoi->set(Point(x,y),val);
          all_labels.insert(make_pair(val,true));
          if (val > maxlabel) maxlabel = val;
        } else {
          voronoi->set(Point(x,y),0);
        }
      }
    }
    if (all_labels.size() <= 2) {
      delete voronoi;
      delete voronoi_data;
      throw std::runtime_error("Black pixels must be labeled for Voronoi tesselation.");
    }

    FloatImageData* dist_data = new FloatImageData(src.size(), src.origin());
    FloatImageView* dist = new FloatImageView(*dist_data);

    try {
      // The Voronoi tesselation is done by a watershed segmentation
      // on the distance transform image, which is quite a bit overhead.
      // The algorithm should be significantly faster when the Voronoi
      // cells are computed directly similar to a distance transform.
      // TODO: implement this based on VIGRA's distance transform code
      vigra::distanceTransform(src_image_range(src), dest_image(*dist), 0, 2);
      vigra::ArrayOfRegionStatistics<vigra::SeedRgDirectValueFunctor<float> > 
        statistics((size_t)maxlabel);
      if (white_edges) {
        vigra::seededRegionGrowing(src_image_range(*dist), src_image(*voronoi),
                                   dest_image(*voronoi), statistics, KeepContours);
      } else {
        vigra::seededRegionGrowing(src_image_range(*dist), src_image(*voronoi),
                                   dest_image(*voronoi), statistics, CompleteGrow);
      }
    } catch (std::exception e) {
      delete dist;
      delete dist_data;
      delete voronoi;
      delete voronoi_data;
      throw;
    }

    // distance image no longer needed
    delete dist;
    delete dist_data;

    // copy over result to return value
    data_type* result_data = new data_type(voronoi->size(), voronoi->origin());
    view_type* result = new view_type(*result_data);
    for (y=0; y<voronoi->nrows(); ++y) {
      for (x=0; x<voronoi->ncols(); ++x) {
        result->set(Point(x,y),(value_type)voronoi->get(Point(x,y)));
      }
    }

    // greyscale image no longer needed
    delete voronoi;
    delete voronoi_data;

    return result;
  }


  template<class T>
  void voronoi_from_points(T& src, const PointVector* points, IntVector* labels) {

    // some plausi checks
    if (points->empty())
      throw std::runtime_error("points must not be empty.");
    if (points->size() != labels->size())
      throw std::runtime_error("Number of points must match the number of labels.");

    size_t i,x,y;

    // build kd-tree from points
    KdNodeVector nodes,neighbors;
    CoordPoint p(2);
    for (i=0; i<points->size(); i++) {
      p[0] = (*points)[i].x();
      p[1] = (*points)[i].y();
      KdNode n(p);
      n.data = &((*labels)[i]);
      nodes.push_back(n);
    }
    KdTree tree(&nodes);

    // label all pixels with nearest neighbor label
    for (y=0; y<src.nrows(); ++y) {
      for (x=0; x<src.ncols(); ++x) {
        if (src.get(Point(x,y)) == 0) {
          p[0] = x; p[1] = y;
          tree.k_nearest_neighbors(p, 1, &neighbors);
          src.set(Point(x,y),*((int*)(neighbors[0].data)));
        }
      }
    }
  }


  // returns list of neighboring label pairs
  template<class T>
  PyObject* labeled_region_neighbors(const T& src, bool eight_connectivity=true) {
    size_t x,y,max_x,max_y;

    typedef typename T::value_type value_type;
    max_x = src.ncols()-1;
    max_y = src.nrows()-1;

    // map for storing neighborship relations; to avoid duplicates,
    // we store for each label only *smaller* neighboring labels
    // note that we must use 'int' insetad of 'value_type' because
    // some versions of gcc do not like nested templates
    typedef set<value_type> set_type;
    typedef map<value_type,set_type> map_type;
    map_type neighbors;

    // check bulk of image
    value_type label1,label2;
    //set<value_type> emptyset;
    set_type emptyset;
    for (y=0; y<max_y; ++y) {
      for (x=0; x<max_x; ++x) {
        label1 = src.get(Point(x,y));
        label2 = src.get(Point(x+1,y));
        if (label1 > label2) {
          if (neighbors.find(label1) == neighbors.end())
            neighbors[label1] = emptyset;
          neighbors[label1].insert(label2);
        }
        else if (label2 > label1) {
          if (neighbors.find(label2) == neighbors.end())
            neighbors[label2] = emptyset;
          neighbors[label2].insert(label1);
        }
        label2 = src.get(Point(x,y+1));
        if (label1 > label2) {
          if (neighbors.find(label1) == neighbors.end())
            neighbors[label1] = emptyset;
          neighbors[label1].insert(label2);
        }
        else if (label2 > label1) {
          if (neighbors.find(label2) == neighbors.end())
            neighbors[label2] = emptyset;
          neighbors[label2].insert(label1);
        }
        if (eight_connectivity) {
          label2 = src.get(Point(x+1,y+1));
          if (label1 > label2) {
            if (neighbors.find(label1) == neighbors.end())
              neighbors[label1] = emptyset;
            neighbors[label1].insert(label2);
          }
          else if (label2 > label1) {
            if (neighbors.find(label2) == neighbors.end())
              neighbors[label2] = emptyset;
            neighbors[label2].insert(label1);
          }
        }
      }
    }
    // check last row
    for (x=0; x<max_x; ++x) {
      label1 = src.get(Point(x,max_y));
      label2 = src.get(Point(x+1,max_y));
      if (label1 > label2) {
        if (neighbors.find(label1) == neighbors.end())
          neighbors[label1] = emptyset;
        neighbors[label1].insert(label2);
      }
      else if (label2 > label1) {
        if (neighbors.find(label2) == neighbors.end())
          neighbors[label2] = emptyset;
        neighbors[label2].insert(label1);
      }
    }
    // check last column
    for (y=0; y<max_y; ++y) {
      label1 = src.get(Point(max_x,y));
      label2 = src.get(Point(max_x,y+1));
      if (label1 > label2) {
        if (neighbors.find(label1) == neighbors.end())
          neighbors[label1] = emptyset;
        neighbors[label1].insert(label2);
      }
      else if (label2 > label1) {
        if (neighbors.find(label2) == neighbors.end())
          neighbors[label2] = emptyset;
        neighbors[label2].insert(label1);
      }
    }
    //printf("emptyset.size(): %i\n", emptyset.size());

    // copy result over to return value
    PyObject *retval, *entry, *entry1, *entry2;
    retval = PyList_New(0);
    typename map_type::iterator it1;
    typename set_type::iterator it2;
    for (it1=neighbors.begin(); it1!=neighbors.end(); it1++) {
      entry1 = Py_BuildValue("i", (int)it1->first);
      //printf("Neighbors of %i:", (int)it1->first);
      for (it2=it1->second.begin(); it2!=it1->second.end(); it2++) {
        // beware that PyList_SetItem 'steals' a reference,
        // while PyList_append increases the reference
        entry = PyList_New(2);
        Py_XINCREF(entry1);
        PyList_SetItem(entry, 0, entry1);
        entry2 = Py_BuildValue("i", (int)*it2);
        //printf(" %i", (int)*it2);
        PyList_SetItem(entry, 1, entry2);
        PyList_Append(retval, entry);
        Py_XDECREF(entry);
      }
      //printf("\n");
      Py_XDECREF(entry1);
    }
    return retval;
  }


  //-----------------------------------------------------------------------
  // functions for Delaunay triangulation
  //-----------------------------------------------------------------------
  void delaunay_from_points_cpp(PointVector *pv, IntVector *lv, std::map<int,std::set<int> > *result) {

    // some plausi checks
	if (pv->empty()) {
      throw std::runtime_error("No points for triangulation given.");
    }
    if (pv->size() < 3) {
      throw std::runtime_error("At least three points are required.");
    }
    if (pv->size() != lv->size()) {
      throw std::runtime_error("Number of points must match the number of labels.");
    }

    DelaunayTree dt;
    PointVector::iterator pv_it;
    IntVector::iterator lv_it;
    std::vector<Vertex*> vertices;
    std::vector<Vertex*>::iterator it;

    result->clear();

    pv_it = pv->begin();
    lv_it = lv->begin();

    int x, y;
    while(pv_it != pv->end() && lv_it != lv->end()) {
      x = (*pv_it).x();
      y = (*pv_it).y();
      vertices.push_back(new Vertex(x, y, (*lv_it)));
      ++pv_it;
      ++lv_it;
    }
    random_shuffle(vertices.begin(), vertices.end());
    dt.addVertices(&vertices);
    dt.neighboringLabels(result);
    for(it = vertices.begin() ; it != vertices.end() ; ++it) {
      delete *it;
    }
  }
  
  PyObject* delaunay_from_points(PointVector *pv, IntVector *lv) {
  	PyObject *list, *entry, *label1, *label2;
    std::map<int,std::set<int> > neighbors;
    std::map<int,std::set<int> >::iterator nit1;
    std::set<int>::iterator nit2;
  	
	delaunay_from_points_cpp(pv, lv, &neighbors);
    list = PyList_New(0);
    for (nit1=neighbors.begin(); nit1!=neighbors.end(); ++nit1) {
      for (nit2=nit1->second.begin(); nit2!=nit1->second.end(); nit2++) {
        entry = PyList_New(2);
        label1 = Py_BuildValue("i", nit1->first);
        label2 = Py_BuildValue("i", *nit2);
        PyList_SetItem(entry, 0, label1);
        PyList_SetItem(entry, 1, label2);
        PyList_Append(list, entry);
        Py_XDECREF(entry);
      }
    }

  	return list;
  }


  //-----------------------------------------------------------------------
  // functions for graph coloring of Cc's with different colors
  //-----------------------------------------------------------------------
  typedef std::map<unsigned int, Image*> LabelCcMap;
  template<class T>
  Graph *graph_from_ccs(T &image, ImageVector &ccs, int method) {
    Graph *graph = new Graph(FLAG_UNDIRECTED);
    graph->make_singly_connected();

    PointVector *pv = new PointVector();
    IntVector *iv = new IntVector();
    ImageVector::iterator iter;

    if( method == 0 || method == 1 ) {
      if( method == 0 ) {
        // method == 0 --> from the CC center points
        for( iter = ccs.begin(); iter != ccs.end(); iter++) {
          Cc* cc = static_cast<Cc*>((*iter).first);
          pv->push_back( cc->center() );
          iv->push_back( cc->label() );
        }        
      }
      else if( method == 1) {
        // method == 1 --> from a 20 percent sample of the contour points
        for( iter = ccs.begin(); iter != ccs.end(); iter++) {
          Cc* cc = static_cast<Cc*>((*iter).first);
          PointVector *cc_pv = contour_samplepoints(*cc, 20);
          PointVector::iterator point_vec_iter;
          for( point_vec_iter = cc_pv->begin(); point_vec_iter != cc_pv->end(); point_vec_iter++ ) {
            pv->push_back(*point_vec_iter);
            iv->push_back(cc->label());
          }
          delete cc_pv;
        }
      }

      // Build the graph
      std::map<int,std::set<int> > neighbors;
      std::map<int,std::set<int> >::iterator nit1;
      std::set<int>::iterator nit2;
      delaunay_from_points_cpp(pv, iv, &neighbors);
      for (nit1=neighbors.begin(); nit1!=neighbors.end(); ++nit1) {
        for (nit2=nit1->second.begin(); nit2!=nit1->second.end(); nit2++) {
           GraphDataLong* a_p = new GraphDataLong(nit1->first);
           GraphDataLong* b_p = new GraphDataLong(*nit2);
           bool del_a = !graph->add_node(a_p);
           bool del_b = !graph->add_node(b_p);
           graph->add_edge(a_p, b_p); 
           if(del_a)
              delete a_p;
           if(del_b)
              delete b_p;
        }
      }
    }
    else if( method == 2 ) {
      // method == 2 --> from the exact area Voronoi diagram
      typedef typename ImageFactory<T>::view_type view_type;
      Image *voronoi       = voronoi_from_labeled_image(image);
      PyObject *labelpairs = labeled_region_neighbors( *((view_type*) voronoi) );
      for (int i = 0; i < PyList_Size(labelpairs); i++) {
        PyObject *adj_list = PyList_GetItem(labelpairs, i);
        PyObject *region1 = PyList_GetItem(adj_list, 0);
        PyObject *region2 = PyList_GetItem(adj_list, 1);
        GraphDataLong* a_p = new GraphDataLong(PyLong_AsLong(region1));
        GraphDataLong* b_p = new GraphDataLong(PyLong_AsLong(region2));
        bool del_a = !graph->add_node(a_p);
        bool del_b = !graph->add_node(b_p);
        graph->add_edge(a_p, b_p); 
        if(del_a)
           delete a_p;
        if(del_b)
           delete b_p;
      }
      delete voronoi->data();
      delete voronoi;
      Py_XDECREF(labelpairs);
    }
    else {
      throw std::runtime_error("Unknown method for construction the neighborhood graph");
    }

    delete pv;
    delete iv;
    return graph;
  }

  // two helper classes for color cluster generation
  class RgbColor4Heap {
  public:
    RGBPixel color;
    double distance;
    RgbColor4Heap(const RGBPixel& c, double d) {color = c; distance = d;}
  };
  class Compare_RgbColor4Heap {
  public:
    bool operator()(const RgbColor4Heap &n, const RgbColor4Heap &m) {
      return (n.distance > m.distance);
    }
  };

  void generate_color_cluster(const RGBPixel* center, size_t ncolors, std::vector<RGBPixel>* cluster) {

    // some local helper functions and classes
    struct local {
      static void rgbneighbors(const RGBPixel& p, std::vector<RGBPixel>* nns) {
        nns->clear();
        int r,g,b;
        int minr, ming, minb;
        int maxr, maxg, maxb;
        if (p.red()<255)   maxr = +1; else maxr = 0;
        if (p.green()<255) maxg = +1; else maxg = 0;
        if (p.blue()<255)  maxb = +1; else maxb = 0;
        if (p.red()>0)   minr = -1; else minr = 0;
        if (p.green()>0) ming = -1; else ming = 0;
        if (p.blue()>0)  minb = -1; else minb = 0;
        for (r=minr; r<=maxr; r++)
          for (g=ming; g<=maxg; g++)
            for (b=minb; b<=maxb; b++)
              if (!(r == 0 && g == 0 && b==0))
                nns->push_back(RGBPixel((int)p.red()+r,p.green()+g,p.blue()+b));
      }
      static double rgbdistance(const RGBPixel& p1, const RGBPixel& p2) {
        return (p1.red()-(double)p2.red())*(p1.red()-(double)p2.red()) +
          (p1.green()-(double)p2.green())*(p1.green()-(double)p2.green()) +
          (p1.blue()-(double)p2.blue())*(p1.blue()-(double)p2.blue());
      }
    };

    // here starts the function code
    cluster->clear();
    if (ncolors < 1) return;
    cluster->push_back(*center);
    if (ncolors < 2) return;

    RGBPixel color;
    size_t i,j;
    // set of selected colors for quick check for existence
    std::set<RGBPixel> selectedcolors;
    selectedcolors.insert(*center);
    // neighbors of new point
    std::vector<RGBPixel> neighbors;
    // queue of color candidates
    std::priority_queue<RgbColor4Heap, std::vector<RgbColor4Heap>, Compare_RgbColor4Heap> candidateheap;
    local::rgbneighbors(*center, &neighbors);
    for (i=0; i<neighbors.size(); i++) {
      candidateheap.push(RgbColor4Heap(neighbors[i],local::rgbdistance(*center, neighbors[i])));
      selectedcolors.insert(neighbors[i]);
    }

    for (i=1; i<ncolors; i++) {
      //printf("neighbors: %i, candidates: %i\n", neighbors.size(), candidateheap.size()); fflush(stdout);
      if (candidateheap.empty()) {
        throw std::runtime_error("no new color candidates found");
      }
      color = candidateheap.top().color;
      candidateheap.pop();
      cluster->push_back(color);
      // add neighbors of new color to candidates
      local::rgbneighbors(color, &neighbors);
      for (j=0; j<neighbors.size(); j++) {
        if (selectedcolors.find(neighbors[j]) == selectedcolors.end()) {
          candidateheap.push(RgbColor4Heap(neighbors[j],local::rgbdistance(*center,neighbors[j])));
          selectedcolors.insert(neighbors[j]);
        }
      }
    }

  }

  template<class T>
  RGBImageView* graph_color_ccs(T &image, ImageVector &ccs, PyObject *colors, int method, bool unique=false) {
    Graph *graph = NULL;
    std::vector<RGBPixel*> RGBColors;
    size_t ncolors;
    std::vector<std::vector<RGBPixel>*> colorclusters;
    std::vector<RGBPixel>* cluster;

    // check input parameters
    if( ccs.size() == 0 ) {
      throw std::runtime_error("graph_color_ccs: no CCs given.");
    }
    if( !PyList_Check(colors) ) {
      throw std::runtime_error("graph_color_ccs: colors is no list");
    }
    if( PyList_Size(colors) < 6 ) {
      throw std::runtime_error("graph_color_ccs: coloring algorithm only works "
            "with more than five colors");
    }
    ncolors = PyList_Size(colors);
    std::vector<size_t> colorcount(ncolors, 0);

    // extract the colors
    for(size_t i = 0; i < ncolors; i++) {
      PyObject *Py_RGBPixel = PyList_GetItem(colors, i);
      RGBPixel *RGBPixel    = ((RGBPixelObject*) Py_RGBPixel )->m_x;
      RGBColors.push_back(RGBPixel);
    }

    // special case: only one cc (=> no edges in graph)
    if (ccs.size() == 1) {
      TypeIdImageFactory<RGB, DENSE>::image_type *coloredImage = 
        TypeIdImageFactory<RGB, DENSE>::create(image.origin(), image.dim());
      unsigned int label = static_cast<Cc*>(ccs.begin()->first)->label();
      for (size_t y = 0; y < image.nrows(); y++) {
        for(size_t x = 0; x < image.ncols(); x++) {
          if (image.get(Point(x,y))){
            if (image.get(Point(x,y)) == label)
              coloredImage->set(Point(x,y), *RGBColors[0]);
            else
              coloredImage->set(Point(x,y), RGBPixel(0,0,0));
          }
        }
      }
      return coloredImage;
    }

    // build the graph from the given ccs
    graph = graph_from_ccs(image, ccs, method);

    // color the graph
    graph->colorize(ncolors);

    // for unique coloring, generate color clusters around each color
    if (unique) {
      // count color frequencies
      NodePtrIterator *nit = graph->get_nodes();
      Node *n;
      while((n=nit->next()) != NULL) {
        colorcount[graph->get_color(n)] += 1;
      }
      delete nit;
      // generate color clusters
      for (size_t i=0; i<ncolors; i++) {
        cluster = new std::vector<RGBPixel>;
        generate_color_cluster(RGBColors[i], colorcount[i], cluster);
        colorclusters.push_back(cluster);
        //for (size_t i=0; i<cluster->size(); i++) {
        //  RGBPixel p = cluster->at(i);
        //  printf("(%i,%i,%i)\n", p.red(), p.green(), p.blue());
        //}
      }
    }

    // Create the return image
    // Ccs not passed to the function are set black in the result
    typedef TypeIdImageFactory<RGB, DENSE> RGBViewFactory;
    
    RGBViewFactory::image_type *coloredImage = 
       RGBViewFactory::create(image.origin(), image.dim());
    
    int label;
    std::map<int,RGBPixel> labelcolor;
    for( size_t y = 0; y < image.nrows(); y++) {
      for( size_t x = 0; x < image.ncols(); x++ ) {
        label = image.get(Point(x,y));
        if( label != 0 ) {
          try {
             GraphDataLong d(label);
             Node* n = graph->get_node(&d);
             unsigned int c = graph->get_color(n); // throws exception when not found
             if (unique) {
               if (labelcolor.find(label) == labelcolor.end()) {
                 if (colorclusters[c]->empty())
                   throw std::runtime_error("no color found for label");
                 labelcolor[label] = colorclusters[c]->back();
                 colorclusters[c]->pop_back();
               }
               coloredImage->set(Point(x,y), labelcolor[label]);
             }
             else {
               coloredImage->set(Point(x,y), *RGBColors[c]);
             }
          }
          catch( std::runtime_error runtimeError ) {
            coloredImage->set(Point(x,y), RGBPixel(0,0,0));
          }
        }
      }
    }


    // clean up
    NodePtrIterator* it = graph->get_nodes();
    Node* n;
    while((n = it->next()) != NULL) {
      delete dynamic_cast<GraphDataLong*>(n->_value);
    }
    delete it;
    delete graph;
    if (unique) {
      for (size_t i=0; i<ncolors; i++)
        delete colorclusters[i];
    }

    return coloredImage;
  }

  //------------------------------------------------------------------
  // convex hull computation with Graham's scan algorithm.
  // See Cormen et al.: Introduction to Algorithms. 2nd ed., p. 949
  //------------------------------------------------------------------

  inline bool greater_distance(const Point& origin, const Point& p1, const Point& p2) {
    double dx2 = (double)p2.x() - origin.x();
    double dx1 = (double)p1.x() - origin.x();
    double dy2 = (double)p2.y() - origin.y();
    double dy1 = (double)p1.y() - origin.y();
    if (dy1*dy1+dx1*dx1 > dy2*dy2+dx2*dx2) {
      return true;
    }
    return false;
  }

  // positive when p0p1 clockwise oriented compared to p0p2
  // zero when all points collinear
  inline double clockwise_orientation(const Point& p0, const Point& p1, const Point& p2) {
    return ((double)p1.x() - p0.x())*((double)p2.y() - p0.y()) -
      ((double)p2.x() - p0.x())*((double)p1.y() - p0.y());
  }

  inline double polar_angle(Point center, Point p2) {
    double dx = double(p2.x()) - center.x();
    double dy = double(p2.y()) - center.y();
    return atan2(dy, dx);
  };

  // see Cormen et al.: Introduction to Algorithms.
  // 2nd ed., MIT Press, p. 949, 2001
  PointVector* convex_hull_from_points(PointVector *points) {
     if (points->empty()) {
        return new PointVector;
     }
     //get leftmost and top point and save it in (*points)[0]
     size_t min_x = points->at(0).x();
     size_t min_y = points->at(0).y();
     size_t min_i = 0;
     size_t i;
     for(i=0; i < points->size(); i++) {
        if (points->at(i).x() < min_x) {
            min_x = points->at(i).x();
            min_y = points->at(i).y();
            min_i = i;
        } else if (points->at(i).x() == min_x && points->at(i).y() < min_y) {
            min_x = points->at(i).x();
            min_y = points->at(i).y();
            min_i = i;
        }
     }
     std::swap( points->at(0), points->at(min_i));


      //sort by polar in polarmap. If more than one point,
      //remove all but the one farthest from origin
     Point origin = points->at(0);
     std::map<double, Point> stack_polarangle;
     std::map<double, Point>::iterator found;
     double polarangle;
     Point p;

     for(PointVector::iterator it = points->begin()+1; it != points->end();it++) {
        p = *it;
        polarangle = polar_angle(origin, p);
        found = stack_polarangle.find(polarangle);
        //use nearest
        if(found == stack_polarangle.end()){
           stack_polarangle[polarangle] = p;
        }
        else if(greater_distance(origin, p, found->second)) {
           stack_polarangle[polarangle] = p;
    	}
     }


     // start with graham scan
     PointVector* retVector = new PointVector;
     std::map<double, Point>::iterator pointIt;
     pointIt = stack_polarangle.begin();

     retVector->push_back(origin); 	        // push point[0]

     // points represent a single point
     if (pointIt == stack_polarangle.end()) {
       return retVector;
     }

     retVector->push_back(pointIt->second); // push point[1]
     pointIt++;

     // points represent a line
     if (pointIt == stack_polarangle.end()) {
       return retVector;
     }

     retVector->push_back(pointIt->second); // push point[2]
     pointIt++;


     //pointIt starts at point[3]
     for( ; pointIt != stack_polarangle.end(); pointIt++) {
        p = pointIt->second;
        while(retVector->size() > 2 && clockwise_orientation(*(retVector->end()-2),*(retVector->end()-1), p) <= 0.0) {
			retVector->pop_back();
        }
        retVector->push_back(p);
     }

     return retVector;
  }


  template<class T>
  PointVector* convex_hull_as_points(const T& src) {
    PointVector *contour_points = new PointVector();
    PointVector::iterator found;

    FloatVector *left = contour_left(src);
    FloatVector *right = contour_right(src);
    FloatVector::iterator it;
    size_t y;
    std::set<Point> pointset;

    for(it = left->begin(), y=0; it != left->end() ; it++, y++) {
      if( *it != std::numeric_limits<double>::infinity() ) {
        contour_points->push_back(Point((coord_t)*it,y));
        pointset.insert(Point((coord_t)*it,y));
      }
    }
    for(it = right->begin(), y=0; it != right->end() ; it++, y++) {
      if( *it != std::numeric_limits<double>::infinity() ) {
        if(pointset.count(Point((coord_t)src.ncols()-*it,y))==0)
          contour_points->push_back(Point((coord_t)src.ncols()-*it,y));
      }
    }
    PointVector *output = convex_hull_from_points(contour_points);

    delete left;
    delete right;
    delete contour_points;

    return output;
  }

  template<class T>
    Image* convex_hull_as_image(const T& src, bool filled) {
    //typedef typename T::value_type value_type;
    
    //typedef typename ImageFactory<OneBitImageView>::view_type view_type;
    OneBitImageData* res_data = new OneBitImageData(src.size(),src.origin());
    OneBitImageView* res = new OneBitImageView(*res_data,src.origin(),src.size());

    PointVector* hullpoints = convex_hull_as_points(src);
    for (size_t i=1; i< hullpoints->size(); i++)
      draw_line(*res,hullpoints->at(i-1),hullpoints->at(i),black(*res));
    draw_line(*res,hullpoints->back(),hullpoints->front(),black(*res));

    delete hullpoints;

    if (filled) {
      size_t x,y,from,to;
      for (y=0; y<res->nrows(); y++) {
        from = to = res->ncols();
        from = 0;
        while (from < res->ncols() && is_white(res->get(Point(from,y))))
          from++;
        if (from >= res->ncols()-1) continue;
        to = res->ncols()-1;
        while (to > 0 && is_white(res->get(Point(to,y))))
          to--;
        for (x=from+1; x<to; x++)
          res->set(Point(x,y),black(*res));
      }
    }

    return res;
  }

  // based upon a sample program kindly provided by Daveed Vandevoorde
  template<class T>
  Rect* max_empty_rect(const T& src) {
    size_t x,y,open_width,x0;
    unsigned int w0,area,best_area;
    std::vector<unsigned int> c(src.ncols()+1,0);
    std::stack<unsigned int> s;
    Point best_ul(0,0);
    Point best_lr(0,0);
    best_area = 0;

	for (y=0; y<src.nrows(); ++y) {
      open_width = 0;
      // update cache
      for (x=0; x<src.ncols(); ++x) {
		if (is_black(src.get(Point(x,y)))) {
          c[x] = 0;
        } else {
          ++c[x];
        }
      }
      for (x=0; x<=src.ncols(); ++x) {
        if (c[x]>open_width) { // open new rectangle?
          s.push(x);
          s.push(open_width);
          open_width = c[x];
        } // "else" optional here 
        else if (c[x]<open_width) { // close rectangle(s)? 
          do {
            w0 = s.top(); s.pop();
            x0 = s.top(); s.pop();
            area = open_width*(x-x0);
            if (area>best_area) {
              best_area = area;
              best_ul = Point(x0, y-open_width+1);
              best_lr = Point(x-1, y);
            }
            open_width = w0;
          } while (c[x]<open_width);
          open_width = c[x];
          if (open_width!=0) {
            s.push(x0);
            s.push(w0);
          }
        }
      }
	}
    if (is_black(src.get(best_lr))) {
      throw std::runtime_error("max_empty_rect: image has no white pixels.");
    }
    Rect* result = new Rect(best_ul,best_lr);
    return result;
  }


  PyObject* hough_lines(const PointVector* points, 
                        double min_theta, double step_theta, double max_theta, 
                        double min_rho, double step_rho, double max_rho,
                        unsigned int n_lines=0, float threshold=1) {
    if(!(min_theta < max_theta && step_theta != 0 && (max_theta - min_theta) / step_theta >= 1)) {
      throw std::invalid_argument("Invalid arguments! The following assertion failed: min_theta < max_theta && step_theta != 0 && (max_theta - min_theta) / step_theta >= 1");
    }
    if(!(min_rho < max_rho && step_rho != 0 && (max_rho - min_rho) / step_rho >= 1)) {
      throw std::invalid_argument("Invalid arguments! The following assertion failed: min_rho < max_rho && step_rho != 0 && (max_rho - min_rho) / step_rho >= 1");
    }

    unsigned int window = 2; // step width for local maxima
    bool smooth = true;      // whether cells shall vote for neighbors too
    
    if(min_theta < 0) {
      min_theta = 0;
    }
    if(max_theta > M_PI) {
      max_theta = M_PI;
    }
    if(threshold <=0) {
      threshold = 1;
    }
    // compute accumulator / votings in parameter space
    int theta_size = (max_theta - min_theta) / step_theta;
    int rho_size = (max_rho - min_rho) / step_rho;
    
    std::vector<std::vector<double> > houghSpace(theta_size, std::vector<double>(rho_size));

    std::vector<double> sin_theta(houghSpace.size()), cos_theta(houghSpace.size());
    for(unsigned int theta = 0; theta < houghSpace.size(); theta++) {
      sin_theta[theta] = sin((min_theta + (theta * step_theta))*M_PI/180.0);
      cos_theta[theta] = cos((min_theta + (theta * step_theta))*M_PI/180.0);
    }

    PointVector::const_iterator p;
    for (p = points->begin(); p != points->end(); p++) {
      for(unsigned int theta = 0; theta < houghSpace.size(); theta++) { // from index of min_theta to index of max_theta
        // compute hessesche normalform:
        // cos(alpha) * x + sin(alpha) * y = d
        double rho = cos_theta[theta] * p->x() + sin_theta[theta] * p->y();

        double di = (rho - min_rho) / step_rho; // get index
        di = (di > 0.0) ? floor(di + 0.5) : ceil(di - 0.5); // round
        if(di >= 0 && di < houghSpace[0].size()) { // if d >= d_min AND d<=d_max
          houghSpace[theta][di]++;
          if(smooth) { // compensate quantization error in d by onedirectional smoothing
            double rho_error = rho - ((di * step_rho) + min_rho); // distance between point and line after quantization, which in a perfect world would be 0
            if(rho_error > 0) {
              di++;
              if(di < houghSpace[0].size()) {
                houghSpace[theta][di] += abs(rho_error) / (step_rho / 2);
              }
            } else if(rho_error < 0) {
              di--;
              if(di >= 0) {
                houghSpace[theta][di] += abs(rho_error) / (step_rho / 2);
              }
            }
          }
        }
      }
    }

    // vector of Votes
    typedef std::vector<std::pair<double, std::pair<double, double> > > VectorType;
    VectorType lines;
    
    // find local maxima greater than threshold
    unsigned int mintheta, minrho, maxtheta, maxrho;
    if (window > houghSpace.size() || window > houghSpace[0].size())
      window = std::min(houghSpace.size(), houghSpace[0].size());
    for(unsigned int theta = 0; theta < houghSpace.size(); theta++) {
      if (theta <= window) mintheta = 0; else mintheta = theta - window;
      if (theta >= houghSpace.size()-window) maxtheta = houghSpace.size()-1; else maxtheta = theta + window;
      for(unsigned int rho = 0; rho < houghSpace[0].size(); rho++) {
        if (rho <= window) minrho = 0; else minrho = rho - window;
        if (rho >= houghSpace[0].size()-window) maxrho = houghSpace[0].size()-1; else maxrho = rho + window;
        double val = houghSpace[theta][rho];
        for(unsigned int dt = mintheta; val > 0.0 && dt <= maxtheta; dt++) {
          for(unsigned int dr = minrho; val > 0.0 && dr <= maxrho; dr++) {
            if (val < houghSpace[dt][dr]) val = 0.0;
          }
        }
        if (val > threshold)
          lines.push_back(std::pair<double, std::pair<double, double> > (val, std::pair<double, double>(theta * step_theta, (rho * step_rho) + (min_rho))));
      }
    }
    

    if(lines.size() == 0) {
      return NULL;
    }
    if(n_lines > 0 && lines.size() > n_lines) {
      // partition, so that nth line is on correct position
      std::nth_element(lines.begin(), lines.begin() + lines.size() - n_lines, lines.end()); // backward nth_element
      // cut off lines with less votes than nth line
      VectorType(lines.begin() + lines.size() - n_lines, lines.end()).swap(lines); // backwards resize()
    }
    // sort remaining lines in descending order
    std::sort(lines.rbegin(), lines.rend());

    PyObject *retval, *entry;
    retval = PyList_New(lines.size());    
    for(unsigned int i=0; i<lines.size(); i++) {
      entry = Py_BuildValue( "fff", lines[i].first, lines[i].second.first * 180 / M_PI, lines[i].second.second);
      PyList_SetItem(retval, i, entry);
    }
    return retval;
  }


} // namespace Gamera
#endif

