
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "segmentation.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_segmentation(void);
  }
#endif

                static PyObject* call_cc_analysis(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::list<Image*>* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cc_analysis"
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
return_arg = cc_analysis(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = cc_analysis(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = cc_analysis(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = cc_analysis(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = cc_analysis(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cc_analysis' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = ImageList_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                      static PyObject* call_splitx(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::list<Image*>* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatVector* center_arg;
PyObject* center_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:splitx"
                        ,
             &self_pyarg                        ,
             &center_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      center_arg = FloatVector_from_python(center_pyarg);
      if (center_arg == NULL) return 0;
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = splitx(*((OneBitImageView*)self_arg), center_arg);
break;
case CC:
return_arg = splitx(*((Cc*)self_arg), center_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = splitx(*((OneBitRleImageView*)self_arg), center_arg);
break;
case RLECC:
return_arg = splitx(*((RleCc*)self_arg), center_arg);
break;
case MLCC:
return_arg = splitx(*((MlCc*)self_arg), center_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'splitx' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete center_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              
      return_pyarg = ImageList_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_splity(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::list<Image*>* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatVector* center_arg;
PyObject* center_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:splity"
                        ,
             &self_pyarg                        ,
             &center_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      center_arg = FloatVector_from_python(center_pyarg);
      if (center_arg == NULL) return 0;
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = splity(*((OneBitImageView*)self_arg), center_arg);
break;
case CC:
return_arg = splity(*((Cc*)self_arg), center_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = splity(*((OneBitRleImageView*)self_arg), center_arg);
break;
case RLECC:
return_arg = splity(*((RleCc*)self_arg), center_arg);
break;
case MLCC:
return_arg = splity(*((MlCc*)self_arg), center_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'splity' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete center_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              
      return_pyarg = ImageList_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                                        static PyObject* call_splitx_max(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::list<Image*>* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatVector* center_arg;
PyObject* center_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:splitx_max"
                        ,
             &self_pyarg                        ,
             &center_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      center_arg = FloatVector_from_python(center_pyarg);
      if (center_arg == NULL) return 0;
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = splitx_max(*((OneBitImageView*)self_arg), center_arg);
break;
case CC:
return_arg = splitx_max(*((Cc*)self_arg), center_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = splitx_max(*((OneBitRleImageView*)self_arg), center_arg);
break;
case RLECC:
return_arg = splitx_max(*((RleCc*)self_arg), center_arg);
break;
case MLCC:
return_arg = splitx_max(*((MlCc*)self_arg), center_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'splitx_max' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete center_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              
      return_pyarg = ImageList_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
      
          static PyMethodDef _segmentation_methods[] = {
                  {  "cc_analysis",
          call_cc_analysis, METH_VARARGS,
           "**cc_analysis** ()\n\nPerforms connected component analysis on the image.\n\nThis algorithm assumes 8-connected components, meaning any two\npixels are considered \"connected\" if they are adjacent in any\ndirection, including diagonally.\n\nThe original image will have all of its pixels \"labeled\" with a\nnumber representing each connected component.  This is so the\nconnected components can share data with their source image and\nmakes things much more efficient.\n\nReturns a list of ccs found in the image.  Since all the CC's\nshare the same data with the original image, changing the CC's\nwill affect the original.  If you do not want this behavior, use\nthe image_copy_ function on each of the CCs::\n\n  ccs = [x.image_copy() for x in ccs]\n\n.. _image_copy: utility.html#image-copy"        },
                                  {  "splitx",
          call_splitx, METH_VARARGS,
           "**splitx** (``FloatVector`` *center* = [0.5])\n\nSplits an image vertically.\n\nThe split point is determined automatically by finding a valley in\nthe projections near *center*.\n\nThis function is overloaded to work both with a single value\nand a list of splitting point candidates as input."        },
                        {  "splity",
          call_splity, METH_VARARGS,
           "**splity** (``FloatVector`` *center* = [0.5])\n\nSplits an image horizontally.\n\nThe split point is determined automatically by finding a valley in\nthe projections near *center*.\n\nThis function is overloaded to work both with a single value and a\nlist of splitting point candidates as input."        },
                                                                {  "splitx_max",
          call_splitx_max, METH_VARARGS,
           "**splitx_max** (``FloatVector`` *center* = [0.5])\n\nSplits an image vertically.\n\n    The split point is determined automatically by finding a peak in\n    the projections near *center*.\n\n    This function is overloaded to work both with a single value and a\n    list of splitting point candidates as input.\n    "        },
              { nullptr }
  };
  
  static struct PyModuleDef module_segmentationDef = {
        PyModuleDef_HEAD_INIT,
        "_segmentation",
        nullptr,
        -1,
        _segmentation_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__segmentation(void) {
    return PyModule_Create(&module_segmentationDef);
  }
  

