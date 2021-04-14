
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "geometry.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_geometry(void);
  }
#endif

                static PyObject* call_voronoi_from_labeled_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:voronoi_from_labeled_image"
                        ,
             &self_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = voronoi_from_labeled_image(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = voronoi_from_labeled_image(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = voronoi_from_labeled_image(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = voronoi_from_labeled_image(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = voronoi_from_labeled_image(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = voronoi_from_labeled_image(*((GreyScaleImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'voronoi_from_labeled_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, and GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = create_ImageObject(return_arg);              return return_pyarg;
            }
                              }
                static PyObject* call_voronoi_from_points(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      PointVector* points_arg;
PyObject* points_pyarg;
                      IntVector* labels_arg;
PyObject* labels_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOO:voronoi_from_points"
                        ,
             &self_pyarg                        ,
             &points_pyarg                        ,
             &labels_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      points_arg = PointVector_from_python(points_pyarg);
      if (points_arg == NULL) return 0;
                    
      labels_arg = IntVector_from_python(labels_pyarg);
      if (labels_arg == NULL) return 0;
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
voronoi_from_points(*((OneBitImageView*)self_arg), points_arg, labels_arg);
break;
case CC:
voronoi_from_points(*((Cc*)self_arg), points_arg, labels_arg);
break;
case ONEBITRLEIMAGEVIEW:
voronoi_from_points(*((OneBitRleImageView*)self_arg), points_arg, labels_arg);
break;
case RLECC:
voronoi_from_points(*((RleCc*)self_arg), points_arg, labels_arg);
break;
case MLCC:
voronoi_from_points(*((MlCc*)self_arg), points_arg, labels_arg);
break;
case GREYSCALEIMAGEVIEW:
voronoi_from_points(*((GreyScaleImageView*)self_arg), points_arg, labels_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'voronoi_from_points' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, and GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete points_arg;                  delete labels_arg;                          Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_labeled_region_neighbors(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int eight_connectivity_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:labeled_region_neighbors"
                        ,
             &self_pyarg                        ,
             &eight_connectivity_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = labeled_region_neighbors(*((OneBitImageView*)self_arg), eight_connectivity_arg);
break;
case CC:
return_arg = labeled_region_neighbors(*((Cc*)self_arg), eight_connectivity_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = labeled_region_neighbors(*((OneBitRleImageView*)self_arg), eight_connectivity_arg);
break;
case RLECC:
return_arg = labeled_region_neighbors(*((RleCc*)self_arg), eight_connectivity_arg);
break;
case MLCC:
return_arg = labeled_region_neighbors(*((MlCc*)self_arg), eight_connectivity_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'labeled_region_neighbors' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                              if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
                static PyObject* call_delaunay_from_points(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PyObject* return_arg;
PyObject* return_pyarg;
                                          PointVector* points_arg;
PyObject* points_pyarg;
                      IntVector* labels_arg;
PyObject* labels_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:delaunay_from_points"
                        ,
             &points_pyarg                        ,
             &labels_pyarg                      ) <= 0)
           return 0;
               
              
      points_arg = PointVector_from_python(points_pyarg);
      if (points_arg == NULL) return 0;
                    
      labels_arg = IntVector_from_python(labels_pyarg);
      if (labels_arg == NULL) return 0;
            
              try {
                      return_arg = delaunay_from_points(points_arg, labels_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete points_arg;                  delete labels_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
                static PyObject* call_graph_color_ccs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      ImageVector ccs_arg;
PyObject* ccs_pyarg;
                      PyObject* colors_arg;
PyObject* colors_pyarg;
                      int method_arg;
                      int unique_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOOii:graph_color_ccs"
                        ,
             &self_pyarg                        ,
             &ccs_pyarg                        ,
             &colors_pyarg                        ,
             &method_arg                        ,
             &unique_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
          const char* type_error_ccs = "Argument 'ccs' must be an iterable of images.";
          PyObject* ccs_pyarg_seq = PySequence_Fast(ccs_pyarg, type_error_ccs);
          if (ccs_pyarg_seq == NULL)
            return 0;
          int ccs_arg_size = PySequence_Fast_GET_SIZE(ccs_pyarg_seq);
          ccs_arg.resize(ccs_arg_size);
          for (int i=0; i < ccs_arg_size; ++i) {
            PyObject *element = PySequence_Fast_GET_ITEM(ccs_pyarg_seq, i);
            if (!is_ImageObject(element)) {
              PyErr_SetString(PyExc_TypeError, type_error_ccs);
              return 0;
            }
            ccs_arg[i] = std::pair<Image*, int>((Image*)(((RectObject*)element)->m_x), get_image_combination(element));
            image_get_fv(element, &ccs_arg[i].first->features,
                         &ccs_arg[i].first->features_len);
          }
          Py_DECREF(ccs_pyarg_seq);              colors_arg = colors_pyarg;                                  
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = graph_color_ccs(*((OneBitImageView*)self_arg), ccs_arg, colors_arg, method_arg, unique_arg);
break;
case CC:
return_arg = graph_color_ccs(*((Cc*)self_arg), ccs_arg, colors_arg, method_arg, unique_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = graph_color_ccs(*((OneBitRleImageView*)self_arg), ccs_arg, colors_arg, method_arg, unique_arg);
break;
case RLECC:
return_arg = graph_color_ccs(*((RleCc*)self_arg), ccs_arg, colors_arg, method_arg, unique_arg);
break;
case MLCC:
return_arg = graph_color_ccs(*((MlCc*)self_arg), ccs_arg, colors_arg, method_arg, unique_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'graph_color_ccs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                                    if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = create_ImageObject(return_arg);              return return_pyarg;
            }
                              }
                static PyObject* call_convex_hull_from_points(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PointVector* return_arg;
PyObject* return_pyarg;
                                          PointVector* points_arg;
PyObject* points_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:convex_hull_from_points"
                        ,
             &points_pyarg                      ) <= 0)
           return 0;
               
              
      points_arg = PointVector_from_python(points_pyarg);
      if (points_arg == NULL) return 0;
            
              try {
                      return_arg = convex_hull_from_points(points_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete points_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              
      return_pyarg = PointVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_convex_hull_as_points(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PointVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:convex_hull_as_points"
                        ,
             &self_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = convex_hull_as_points(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = convex_hull_as_points(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = convex_hull_as_points(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = convex_hull_as_points(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = convex_hull_as_points(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'convex_hull_as_points' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              
      return_pyarg = PointVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_convex_hull_as_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int filled_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:convex_hull_as_image"
                        ,
             &self_pyarg                        ,
             &filled_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = convex_hull_as_image(*((OneBitImageView*)self_arg), filled_arg);
break;
case CC:
return_arg = convex_hull_as_image(*((Cc*)self_arg), filled_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = convex_hull_as_image(*((OneBitRleImageView*)self_arg), filled_arg);
break;
case RLECC:
return_arg = convex_hull_as_image(*((RleCc*)self_arg), filled_arg);
break;
case MLCC:
return_arg = convex_hull_as_image(*((MlCc*)self_arg), filled_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'convex_hull_as_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                              if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = create_ImageObject(return_arg);              return return_pyarg;
            }
                              }
                static PyObject* call_max_empty_rect(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Rect* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:max_empty_rect"
                        ,
             &self_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = max_empty_rect(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = max_empty_rect(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = max_empty_rect(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = max_empty_rect(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = max_empty_rect(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'max_empty_rect' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            
      return_pyarg = create_RectObject(*return_arg);
      delete return_arg;            return return_pyarg;
                              }
                static PyObject* call_hough_lines(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PyObject* return_arg;
PyObject* return_pyarg;
                                          PointVector* points_arg;
PyObject* points_pyarg;
                      double theta_min_arg;
                      double theta_step_arg;
                      double theta_max_arg;
                      double rho_min_arg;
                      double rho_step_arg;
                      double rho_max_arg;
                      int n_lines_arg;
                      double threshold_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oddddddid:hough_lines"
                        ,
             &points_pyarg                        ,
             &theta_min_arg                        ,
             &theta_step_arg                        ,
             &theta_max_arg                        ,
             &rho_min_arg                        ,
             &rho_step_arg                        ,
             &rho_max_arg                        ,
             &n_lines_arg                        ,
             &threshold_arg                      ) <= 0)
           return 0;
               
              
      points_arg = PointVector_from_python(points_pyarg);
      if (points_arg == NULL) return 0;
                                                                                                                            
              try {
                      return_arg = hough_lines(points_arg, theta_min_arg, theta_step_arg, theta_max_arg, rho_min_arg, rho_step_arg, rho_max_arg, n_lines_arg, threshold_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete points_arg;                                                                                                                                                                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
      
          static PyMethodDef _geometry_methods[] = {
                  {  "voronoi_from_labeled_image",
          call_voronoi_from_labeled_image, METH_VARARGS,
           "**voronoi_from_labeled_image** ()\n\nComputes the area Voronoi tesselation from an image containing labeled\nCc's. In the returned onebit image, every pixel is labeled with the\nlabel value of the closest Cc in the input image.\n\nTo prepare the input image, you can use cc_analysis__. When the Cc's\nonly consist of single points, the area Voronoi tesselation is identical\nto the ordinary Voronoi tesselation.\n\n.. __: segmentation.html#cc-analysis\n\nThe implementation applies a watershed algorithm to the distance transform\nof the input image, a method known as *seeded region growing* (U. Köthe:\n*Primary Image Segmentation.* Proceedings 17th DAGM-Symposium, pp. 554-561,\nSpringer, 1995).\n\nThe example shown below is the image *voronoi_cells* as created with\nthe following code:\n\n.. code:: Python\n\n  # create an area Voronoi tesselation and\n  # mark the cells and their edges in color\n  ccs = image.cc_analysis()  # labels the image\n  voronoi = image.voronoi_from_labeled_image()\n  voronoi_cells = voronoi.color_ccs()\n  voronoi_cells.highlight(image, RGBPixel(0,0,0))\n  voronoi_edges = voronoi.labeled_region_edges()\n  voronoi_cells.highlight(voronoi_edges, RGBPixel(255,255,255))"        },
                        {  "voronoi_from_points",
          call_voronoi_from_points, METH_VARARGS,
           "**voronoi_from_points** ([object *points*], ``IntVector`` *labels*)\n\nComputes the Voronoi tesselation from a list of points and point labels.\nThe result is directly written to the input image. Each white pixel is\nlabeled with the label value of the closest point. Non white pixel in the\ninput image are not overwritten.\n\nThe arguments *points* and *labels* specify the points and labels, such\nthat ``labels[i]`` is the label of ``points[i]``. Note that the labels\nneed not necessarily all be different, which can be useful as an \napproximation of an area Voronoi tesselation.\n\nThe algorithm is very simple: it stores the points in a `kd-tree`_ and\nthen looks up the closest point for each image pixel. This has a runtime\nof *O(N log(n))*, where *N* is the number of image pixels and *n* is the\nnumber of points. For not too many points, this should be faster than the\nmorphological region growing approach of `voronoi_from_labeled_image`_.\n\n.. _`kd-tree`: kdtree.html\n.. _`voronoi_from_labeled_image`: #voronoi-from-labeled-image\n\nThe example shown below is the image *voronoi_edges* as created with\nthe following code:\n\n.. code:: Python\n\n  # create a Voronoi tesselation and mark\n  # the cell edges in a second image\n  points = [(10,10),(20,30),(32,22),(85,14),(40,70),(80,85)]\n  voronoi = Image((0,0),(90,90))\n  voronoi.voronoi_from_points(points,[i+2 for i in range(len(points))])\n  voronoi_edges = voronoi.labeled_region_edges()\n  for p in points:\n     voronoi_edges.set(p,1)"        },
                        {  "labeled_region_neighbors",
          call_labeled_region_neighbors, METH_VARARGS,
           "**labeled_region_neighbors** (``bool`` *eight_connectivity* = True)\n\nFor an image containing labeled regions, a list of all label pairs belonging\nto touching regions is returned. When *eight_connectivity* is ``True``\n(default), 8-connectivity is used for neighborship, otherwise\n4-connectivity is used.\n\nThis can be useful for building a Delaunay graph from a Voronoi tesselation\nas in the following example:\n\n.. code:: Python\n\n  #\n  # build Delaunay graph of neighboring (i.e. adjacent) Cc's\n  #\n\n  # create map label->Cc for faster lookup later\n  ccs = image.cc_analysis()\n  label_to_cc = {}\n  for c in ccs:\n     label_to_cc[c.label] = c\n\n  # compute area Voronoi tesselation and neighborship list\n  voronoi = image.voronoi_from_labeled_image()\n  labelpairs = voronoi.labeled_region_neighbors()\n\n  # build map of all neighbors for each label for fast lookup\n  neighbors = {}\n  for label in label_to_cc.keys():\n     neighbors[label] = []\n  for n in labelpairs:\n     neighbors[n[0]].append(n[1])\n     neighbors[n[1]].append(n[0])\n\n  # now, all neighbors to a given cc can be looked up with\n  neighbors_of_cc = [label_to_cc[label] for label in neighbors[cc.label]]"        },
                        {  "delaunay_from_points",
          call_delaunay_from_points, METH_VARARGS,
           "**delaunay_from_points** ([object *points*], ``IntVector`` *labels*)\n\nComputes the Delaunay triangulation directly from a list of points and\npoint labels. The result is a list which contains tuples of adjacent labels,\nwhere in each tuple the smaller label is given first.\n\nThe arguments *points* and *labels* specify the points and nonnegative\nlabels, such that ``labels[i]`` is the label of ``points[i]``. Note that\nthe labels need not necessarily all be different, which can be useful\nfor the computation of a neighborship graph from a set of connected\ncomponents.\n\nThe computation of the Delaunay triangulation is based on the Delaunay\ntree which is a randomized geometric data structure. It is\ndescribed in O. Devillers, S. Meiser, M. Teillaud:\n`Fully dynamic Delaunay triangulation in logarithmic expected time per operation.`__\nComputational Geometry: Theory and Applications 2, pp. 55-80, 1992.\n\n.. __: http://hal.inria.fr/inria-00090678\n\nThis can be useful for building a neighborhood graph as shown in the\nfollowing example:\n\n.. code:: Python\n\n  from gamera import graph\n  from gamera.plugins.geometry import delaunay_from_points\n  \n  points = [(10,10),(20,30),(32,22),(85,14),(40,70),(80,85)]\n  labels = range(len(points))\n  neighbors = delaunay_from_points(points, labels)\n  \n  g = graph.Graph(graph.UNDIRECTED)\n  for pair in neighbors:\n      g.add_edge(pair[0], pair[1])"        },
                        {  "graph_color_ccs",
          call_graph_color_ccs, METH_VARARGS,
           "**graph_color_ccs** ([object *ccs*], [RGBPixel *colors*] = None, ``Choice`` [CC center|20% contour points|voronoi diagram] *method* = 20% contour points, ``bool`` *unique* = False)\n\nReturns an RGB Image where each segment is colored with one of the colors\nfrom *colors* in such a way that neighboring segments have different\ncolors. Optionally, each segment can also be colored uniquely with\na color that is close to one of the given *colors*.\n\nReference:\n\n  C. Dalitz, T. Bolten, O. Christion:\n  `\"Color Visualization of 2D Segmentations.\"`__\n  International Conference on Information Visualization Theory\n  and Applications (IVAPP), pp. 567-572 (2013)\n\n.. __: http://lionel.kr.hsnr.de/~dalitz/data/publications/ivapp13-coloring.pdf\n\nThis function can be used to verify that the pagesegmentation \ne.g. ``runlength_smearing`` is working correctly for your image.\n\n\nArguments:\n\n*ccs*:\n    ImageList which contains ccs to be colored. Must be views on\n    the image on which this method is called.\n\n*colors*:\n    list of colors (instances of RGBPixel) which will be used for coloring.\n    When ``None``, the default set of seven colors given in the example\n    below is used.\n\n*method*:\n    Controls the calculation of the neighborhood graph:\n\n        0 = from the CC center points\n        (fastest, but can be inaccurate for large CC's)\n\n        1 = from a 20 percent sample of the contour points\n        (reasonable compromise between speed and accuracy)\n\n        2 = from the exact area Voronoi diagram\n        (can be slow on large images)\n\n*unique*:\n    When ``True``, each segment obtains a unique color that is\n    close to one of the colors in *colors* with the restriction\n    that neighboring segments obtain sufficiently different colors.\n    See the reference above for details.\n\nExample:\n\n.. code:: Python\n\n   ccs = imgage.cc_analysis()\n   colors = [ RGBPixel(150, 0, 0),\n              RGBPixel(0, 250, 0),\n              RGBPixel(0, 0, 255),\n              RGBPixel(250, 0, 255),\n              RGBPixel(50, 150, 50),\n              RGBPixel(0, 190, 255),\n              RGBPixel(230, 190, 20) ]\n   rgb = imgage.graph_color_ccs(ccs, colors, 1)\n\n.. note:: *colors* must not contain less than six colors."        },
                        {  "convex_hull_from_points",
          call_convex_hull_from_points, METH_VARARGS,
           "**convex_hull_from_points** ([object *points*])\n\nReturns the polygon vertices of the convex hull of the given list of\npoints.\n\nThe function uses Graham's scan algorithm as described e.g. in Cormen et al.:\n*Introduction to Algorithms.* 2nd ed., MIT Press, p. 949, 2001\n"        },
                        {  "convex_hull_as_points",
          call_convex_hull_as_points, METH_VARARGS,
           "**convex_hull_as_points** ()\n\nReturns the vertex points of the convex hull of all black pixels\nin the given image.\n\nActually not all black pixels are required for computing the convex hull,\nbut only the left and right contour pixels of the image. This follows\nfrom the fact that, when a point is invisible both from the left and the\nright, it lies on the connection axis between two visible points and thus\ncannot be a vertex point of the convex hull.\n   "        },
                        {  "convex_hull_as_image",
          call_convex_hull_as_image, METH_VARARGS,
           "**convex_hull_as_image** (``bool`` *filled* = False)\n\nReturns an image containing the polygon of the convex hull calculated\nby convex_hull_as_points_.\n\n.. _convex_hull_as_points: geometry.html#convex_hull_as_points\n   "        },
                        {  "max_empty_rect",
          call_max_empty_rect, METH_VARARGS,
           "**max_empty_rect** ()\n\nReturns the maximum area empty rect that fits into the image without\ncontaining any of the black image pixels. This problem is in the literature\ngenerally known as the *Largest Empty Rectangle Problem*.\n\nWhen the image does not contain a white pixel at all, an exception of type\n``RuntimeError`` is thrown. The coordinates of the returned rectangle are\nrelative to the upper left corner of the image.\n\nReference: D. Vandevoorde: `\"The Maximal Rectangle Problem.\"`__ Dr. Dobb's,\nApril 1998.\n\n.. __: http://www.drdobbs.com/database/184410529\n   "        },
                        {  "hough_lines",
          call_hough_lines, METH_VARARGS,
           "**hough_lines** ([object *points*], float *theta_min*, float *theta_step*, float *theta_max*, float *rho_min*, float *rho_step*, float *rho_max*, int *n_lines*, float *threshold*)\n\nFinds lines in a point set with the Hough transform. Lines are \nrepresented by the Hessian normal form, i.e. by the two parameters\n*theta* and *rho*, where *rho* is the distance of the line to the origin,\nand *theta* is the angle of normal; a horizontal line therefore\nhas *theta* = 90 degrees.\n\nThe found lines are returned as a list of tuples \n[(*votes*, *theta*, *rho*),...],\nwhere *votes* is the number of points from the point set belonging to\nthis line. The lines are sorted by *votes* in descending order. Which and\nhow many lines are returned is controlled with *threshold* and *n_lines*.\nThe angles *theta* are given in degrees.\n\nArguments:\n\n*points*:\n    The points from the point cloud.\n\n*theta_min*, *theta_step*, *theta_max*\n    Theta-quantization of the Hough space, i.e. the range of angles\n    to be tested. Angles are spezified in degrees.\n\n*rho_min*, *rho_step*, *rho_max*\n    Rho-quantization of the Hough space, i.e. the range of origin-distances\n    to be tested.\n\n*n_lines*\n    The number of highest votes lines that are returned. When set to\n    zero, all found lines are returned.\n\n*threshold*\n    Only lines with more votes (points) than *threshold* are returned."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_geometryDef = {
        PyModuleDef_HEAD_INIT,
        "_geometry",
        nullptr,
        -1,
        _geometry_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__geometry(void) {
    return PyModule_Create(&module_geometryDef);
  }
  

