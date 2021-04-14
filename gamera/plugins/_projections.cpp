
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "projections.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_projections(void);
  }
#endif

                static PyObject* call_projection_rows(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                IntVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:projection_rows"
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
return_arg = projection_rows(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = projection_rows(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = projection_rows(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = projection_rows(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = projection_rows(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'projection_rows' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = IntVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_projection_cols(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                IntVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:projection_cols"
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
return_arg = projection_cols(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = projection_cols(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = projection_cols(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = projection_cols(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = projection_cols(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'projection_cols' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = IntVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                      static PyObject* call_projection_skewed_rows(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatVector* Rotation_angles_arg;
PyObject* Rotation_angles_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:projection_skewed_rows"
                        ,
             &self_pyarg                        ,
             &Rotation_angles_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      Rotation_angles_arg = FloatVector_from_python(Rotation_angles_pyarg);
      if (Rotation_angles_arg == NULL) return 0;
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = projection_skewed_rows(*((OneBitImageView*)self_arg), Rotation_angles_arg);
break;
case CC:
return_arg = projection_skewed_rows(*((Cc*)self_arg), Rotation_angles_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = projection_skewed_rows(*((OneBitRleImageView*)self_arg), Rotation_angles_arg);
break;
case RLECC:
return_arg = projection_skewed_rows(*((RleCc*)self_arg), Rotation_angles_arg);
break;
case MLCC:
return_arg = projection_skewed_rows(*((MlCc*)self_arg), Rotation_angles_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'projection_skewed_rows' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete Rotation_angles_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
                static PyObject* call_projection_skewed_cols(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatVector* Rotation_angles_arg;
PyObject* Rotation_angles_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:projection_skewed_cols"
                        ,
             &self_pyarg                        ,
             &Rotation_angles_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      Rotation_angles_arg = FloatVector_from_python(Rotation_angles_pyarg);
      if (Rotation_angles_arg == NULL) return 0;
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = projection_skewed_cols(*((OneBitImageView*)self_arg), Rotation_angles_arg);
break;
case CC:
return_arg = projection_skewed_cols(*((Cc*)self_arg), Rotation_angles_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = projection_skewed_cols(*((OneBitRleImageView*)self_arg), Rotation_angles_arg);
break;
case RLECC:
return_arg = projection_skewed_cols(*((RleCc*)self_arg), Rotation_angles_arg);
break;
case MLCC:
return_arg = projection_skewed_cols(*((MlCc*)self_arg), Rotation_angles_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'projection_skewed_cols' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete Rotation_angles_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
                  
          static PyMethodDef _projections_methods[] = {
                  {  "projection_rows",
          call_projection_rows, METH_VARARGS,
           "**projection_rows** ()\n\nCompute the horizontal projections of an image.  This computes the\nnumber of pixels in each row."        },
                        {  "projection_cols",
          call_projection_cols, METH_VARARGS,
           "**projection_cols** ()\n\nCompute the vertical projections of an image.  This computes the\nnumber of pixels in each column."        },
                                  {  "projection_skewed_rows",
          call_projection_skewed_rows, METH_VARARGS,
           "**projection_skewed_rows** (``FloatVector`` *Rotation angles*)\n\nComputes all horizontal projections of an image skewed by a list\nof angles. For more details and an example see\nprojection_skewed_cols_.\n\nNote that unlike rotate_ the image size is not extended. Image\nregions moved outside the original image size are simply clipped,\nwhich restricts this method to small angles.\n\n.. _projection_skewed_cols: #projection_skewed_cols"        },
                        {  "projection_skewed_cols",
          call_projection_skewed_cols, METH_VARARGS,
           "**projection_skewed_cols** (``FloatVector`` *Rotation angles*)\n\nComputes all vertical projections of an image skewed by a list of\nangles. As in rotate_, angles are measured clockwise and in\ndegrees.  Thus a rotate followed by a projection_cols would be\nconceptually the same, albeit considerably slower.\n\nThis function is overloaded to work both with a single angle and a\nlist of angles as input. In the first case a single projection\nvector is returned, in the second a list of projections\nvectors. This is explained in the following example:\n\n.. code:: Python\n\n  # called twice with a single angle as input\n  proj1 = img.projection_skewed_cols(0.5)\n  proj2 = img.projection_skewed_cols(1.0)\n\n  # the same result with one function call\n  projlist = img.projection_skewed_cols([0.5,1.0])\n  proj1 = projlist[0]\n  proj2 = projlist[1]\n\nNote that unlike rotate_ the image size is not extended. Image\nregions moved outside the original image size are simply clipped,\nwhich restricts this method to small angles.\n\n.. _rotate: transformation.html#rotate"        },
                                  { nullptr }
  };
  
  static struct PyModuleDef module_projectionsDef = {
        PyModuleDef_HEAD_INIT,
        "_projections",
        nullptr,
        -1,
        _projections_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__projections(void) {
    return PyModule_Create(&module_projectionsDef);
  }
  

