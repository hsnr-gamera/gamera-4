
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "contour.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_contour(void);
  }
#endif

                static PyObject* call_contour_top(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                FloatVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:contour_top"
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
return_arg = contour_top(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = contour_top(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = contour_top(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = contour_top(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = contour_top(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'contour_top' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = FloatVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_contour_left(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                FloatVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:contour_left"
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
return_arg = contour_left(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = contour_left(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = contour_left(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = contour_left(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = contour_left(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'contour_left' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = FloatVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_contour_bottom(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                FloatVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:contour_bottom"
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
return_arg = contour_bottom(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = contour_bottom(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = contour_bottom(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = contour_bottom(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = contour_bottom(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'contour_bottom' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = FloatVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_contour_right(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                FloatVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:contour_right"
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
return_arg = contour_right(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = contour_right(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = contour_right(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = contour_right(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = contour_right(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'contour_right' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = FloatVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_contour_samplepoints(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PointVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int percentage_arg;
                      int contour_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:contour_samplepoints"
                        ,
             &self_pyarg                        ,
             &percentage_arg                        ,
             &contour_arg                      ) <= 0)
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
return_arg = contour_samplepoints(*((OneBitImageView*)self_arg), percentage_arg, contour_arg);
break;
case CC:
return_arg = contour_samplepoints(*((Cc*)self_arg), percentage_arg, contour_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = contour_samplepoints(*((OneBitRleImageView*)self_arg), percentage_arg, contour_arg);
break;
case RLECC:
return_arg = contour_samplepoints(*((RleCc*)self_arg), percentage_arg, contour_arg);
break;
case MLCC:
return_arg = contour_samplepoints(*((MlCc*)self_arg), percentage_arg, contour_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'contour_samplepoints' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_contour_pavlidis(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PointVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:contour_pavlidis"
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
return_arg = contour_pavlidis(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = contour_pavlidis(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = contour_pavlidis(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = contour_pavlidis(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = contour_pavlidis(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'contour_pavlidis' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _contour_methods[] = {
                  {  "contour_top",
          call_contour_top, METH_VARARGS,
           "**contour_top** ()\n\nReturns a float vector containing the contour at the top of the\nimage.\n\nIf there are no black pixels in a given column, the value is set to\ninf."        },
                        {  "contour_left",
          call_contour_left, METH_VARARGS,
           "**contour_left** ()\n\nReturns a float vector containing the contour at the left of the\nimage.\n\nIf there are no black pixels in a given row, the value is set to\ninf."        },
                        {  "contour_bottom",
          call_contour_bottom, METH_VARARGS,
           "**contour_bottom** ()\n\nReturns a float vector containing the contour at the bottom of the\nimage.\n\nIf there are no black pixels in a given column, the value is set to\ninf."        },
                        {  "contour_right",
          call_contour_right, METH_VARARGS,
           "**contour_right** ()\n\nReturns a float vector containing the contour at the right of the\nimage.\n\nIf there are no black pixels in a given row, the value is set to\ninf."        },
                        {  "contour_samplepoints",
          call_contour_samplepoints, METH_VARARGS,
           "**contour_samplepoints** (int(1, 100) *percentage* = 25, ``Choice`` [outer_projection|full_contour] *contour* = outer_projection)\n\nReturns a point vector containing contour points of the given image.\n\n*percentage*:\n  return percentage of contour points. The points are selected approximately\n  equidistant on the contour.\n\n*contour*:\n  when 0 (\"outer_projection\"), the points returned by *contour_left* etc.\n  are used; when 1 (\"full_contour\") the points returned by *outline(1)*\n  are used.\n\nIn addition to the points determined by the percentage argument the result\nlist also contains the four extreme points (topmost, leftmost, bottommost,\nrightmost).\n\n.. code:: Python\n \n 	ccs = image.cc_analysis()\n 	points = []\n 	for cc in ccs:\n 	  for samplepoint in cc.contour_samplepoints(50):\n 	    points.append(samplepoint)"        },
                        {  "contour_pavlidis",
          call_contour_pavlidis, METH_VARARGS,
           "**contour_pavlidis** ()\n\nReturns a point list of the outer contour trace found with Pavlidis'\nalgorithm (T. Pavlidis: *Algorithms for Grapics and Image Processing.*\npp. 129-165, Springer, 1982).\n\nNote that this extracts only the first contour found, so this method\nshould be applied to a single connected component. If you have an\nimage with more than one connected component, do a CC analysis before,\nas in the following example:\n\n.. code:: Python\n\n  ccs = img.cc_analysis()\n  contours = []\n  for cc in ccs:\n    contours.append([Point(p.x + cc.offset_x, p.y + cc.offset_y) \\n                     for p in cc.contour_pavlidis()])"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_contourDef = {
        PyModuleDef_HEAD_INIT,
        "_contour",
        nullptr,
        -1,
        _contour_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__contour(void) {
    return PyModule_Create(&module_contourDef);
  }
  

