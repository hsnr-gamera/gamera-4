
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "thinning.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_thinning(void);
  }
#endif

                static PyObject* call_thin_zs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:thin_zs"
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
return_arg = thin_zs(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = thin_zs(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = thin_zs(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = thin_zs(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = thin_zs(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'thin_zs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_thin_hs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:thin_hs"
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
return_arg = thin_hs(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = thin_hs(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = thin_hs(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = thin_hs(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = thin_hs(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'thin_hs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                                  static PyObject* call_thin_lc(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:thin_lc"
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
return_arg = thin_lc(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = thin_lc(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = thin_lc(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = thin_lc(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = thin_lc(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'thin_lc' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _thinning_methods[] = {
                  {  "thin_zs",
          call_thin_zs, METH_VARARGS,
           "**thin_zs** ()\n\nThins (skeletonizes) a ONEBIT image using the Zhang and Suen\nalgorithm.\n\nThe resulting skeleton is not a medial axis transformation, and\nthe ends of the skeleton will not extend to the edges of the\noriginal image.\n\nT. Y. Zhang and C. Y. Suen. 1984.  A Fast Parallel Algorithm for\nThinning Digital Patterns., *Communications of ACM*, 2(3).\n\nR. C. Gonzalez and P. Wintz. 1987 *Digital Image Processing.*,\n2. edition. 398-402."        },
                        {  "thin_hs",
          call_thin_hs, METH_VARARGS,
           "**thin_hs** ()\n\nDerives the medial axis transformation from a ONEBIT image using the\nHaralick and Shapiro algorithm.\n\nUnlike thin_zs_ and thin_lc_, this function performs a medial axis\ntransformation, and the ends of the skeleton extend to the corners of\nthe original image.\n\nConsider using thin_hs_large_image_ instead, for faster performance on\nlarge images with a lot of connected components.\n\nR. M. Haralick and L. G. Shapiro. 1992.  *Computer and Robot Vision*,\nVol. 1, Chapter 5 (especially 5.10.1).  Reading, MA: Addison-Wesley."        },
                                                      {  "thin_lc",
          call_thin_lc, METH_VARARGS,
           "**thin_lc** ()\n\nThins (skeletonizes) a ONEBIT image using the Lee and Chen\nalgorithm.\n\nThis function is a simple extension to the Zhang and Suen\nalgorithm in thin_zs_ that ensure that no two pixels are more than\n4-connected.\n\nThe resulting skeleton is not a medial axis transformation, and\nthe ends of the skeleton will not extend to the edges of the\noriginal image.\n\nH.-J. Lee and B. Chen. 1992.  Recognition of handwritten Chinese\ncharacters via short line segments. *Pattern Recognition*. 25(5)\n543-552."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_thinningDef = {
        PyModuleDef_HEAD_INIT,
        "_thinning",
        nullptr,
        -1,
        _thinning_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__thinning(void) {
    return PyModule_Create(&module_thinningDef);
  }
  

