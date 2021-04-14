
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "image_conversion.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_image_conversion(void);
  }
#endif

                static PyObject* call_to_rgb(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_rgb"
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
return_arg = to_rgb(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_rgb(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_rgb(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_rgb(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_rgb(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = to_rgb(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = to_rgb(*((Grey16ImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = to_rgb(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = to_rgb(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_rgb' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_to_greyscale(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_greyscale"
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
return_arg = to_greyscale(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_greyscale(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_greyscale(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_greyscale(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_greyscale(*((MlCc*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = to_greyscale(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
return_arg = to_greyscale(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = to_greyscale(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = to_greyscale(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_greyscale' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_to_grey16(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_grey16"
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
return_arg = to_grey16(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_grey16(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_grey16(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_grey16(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_grey16(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = to_grey16(*((GreyScaleImageView*)self_arg));
break;
case RGBIMAGEVIEW:
return_arg = to_grey16(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = to_grey16(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = to_grey16(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_grey16' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_to_float(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_float"
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
return_arg = to_float(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_float(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_float(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_float(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_float(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = to_float(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = to_float(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
return_arg = to_float(*((RGBImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = to_float(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_float' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                            static PyObject* call_to_complex(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_complex"
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
return_arg = to_complex(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_complex(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_complex(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_complex(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_complex(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = to_complex(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = to_complex(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
return_arg = to_complex(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = to_complex(*((FloatImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_complex' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_extract_real(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:extract_real"
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
case COMPLEXIMAGEVIEW:
return_arg = extract_real(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'extract_real' can not have pixel type '%s'. Acceptable value is COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_extract_imaginary(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:extract_imaginary"
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
case COMPLEXIMAGEVIEW:
return_arg = extract_imaginary(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'extract_imaginary' can not have pixel type '%s'. Acceptable value is COMPLEX.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _image_conversion_methods[] = {
                  {  "to_rgb",
          call_to_rgb, METH_VARARGS,
           "**to_rgb** ()\n\nConverts the given image to an RGB image according to the following rules:\n\n- for ONEBIT images, 0 is mapped to (255,255,255) and everything else to (0,0,0)\n- for GREYSCALE and GREY16 images, R=G=B\n- for FLOAT images, the range [min,max] is linearly mapped to the 256 grey values\n\nNote, converting an image to one of the same type performs a copy operation."        },
                        {  "to_greyscale",
          call_to_greyscale, METH_VARARGS,
           "**to_greyscale** ()\n\nConverts the given image to a GREYSCALE image according to the\nfollowing rules:\n\n- for ONEBIT images, 0 is mapped to 255 and everything else to 0.\n- for FLOAT images, the range [min,max] is linearly scaled to [0,255]\n- for GREY16 images, the range [0,max] is linearly scaled to [0,255]\n- for RGB images, the luminance is used, which is defined in VIGRA as 0.3*R + 0.59*G + 0.11*B\n\nConverting an image to one of the same type performs a copy operation."        },
                        {  "to_grey16",
          call_to_grey16, METH_VARARGS,
           "**to_grey16** ()\n\nConverts the given image to a GREY16 image according to the\nfollowing rules:\n\n- for ONEBIT images, 0 is mapped to 65535 and everything else to 0.\n- for FLOAT images, the range [min,max] is linearly scaled to [0,65535]\n- for GREYSCALE images, pixel values are copied unchanged\n- for RGB images, the luminance is used, which is defined in VIGRA as 0.3*R + 0.59*G + 0.11*B. This results only in a value range [0,255]\n\nConverting an image to one of the same type performs a copy operation."        },
                        {  "to_float",
          call_to_float, METH_VARARGS,
           "**to_float** ()\n\nConverts the given image to a FLOAT image according to the following\nrules:\n\n- for ONEBIT images, 0 is mapped to 0.0 and everything else to 1.0\n- for GREYSCALE and GREY16 images, pixel values are copied unchanged\n- for RGB images, the luminance is used, which is defined in VIGRA as 0.3*R + 0.59*G + 0.11*B\n\nConverting an image to one of the same type performs a copy operation."        },
                                            {  "to_complex",
          call_to_complex, METH_VARARGS,
           "**to_complex** ()\n\nConverts the given image to a COMPLEX image.\n\nNote, converting an image to one of the same type performs a copy operation."        },
                        {  "extract_real",
          call_extract_real, METH_VARARGS,
           "**extract_real** ()\n\nReturns a Float image containing only the real values in the given\ncomplex image."        },
                        {  "extract_imaginary",
          call_extract_imaginary, METH_VARARGS,
           "**extract_imaginary** ()\n\nReturns a Float image containing only the imaginary values in the\ngiven complex image."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_image_conversionDef = {
        PyModuleDef_HEAD_INIT,
        "_image_conversion",
        nullptr,
        -1,
        _image_conversion_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__image_conversion(void) {
    return PyModule_Create(&module_image_conversionDef);
  }
  

