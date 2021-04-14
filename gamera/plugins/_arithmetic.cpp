
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "arithmetic.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_arithmetic(void);
  }
#endif

                static PyObject* call_add_images(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
                      int in_place_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:add_images"
                        ,
             &self_pyarg                        ,
             &other_pyarg                        ,
             &in_place_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(other_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'other' must be an image");
          return 0;
        }
        other_arg = ((Image*)((RectObject*)other_pyarg)->m_x);
        image_get_fv(other_pyarg, &other_arg->features, &other_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREYSCALEIMAGEVIEW:
return_arg = add_images(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'add_images' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREY16IMAGEVIEW:
return_arg = add_images(*((Grey16ImageView*)self_arg), *((Grey16ImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'add_images' can not have pixel type '%s'. Acceptable value is GREY16.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case RGBIMAGEVIEW:
return_arg = add_images(*((RGBImageView*)self_arg), *((RGBImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'add_images' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = add_images(*((FloatImageView*)self_arg), *((FloatImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'add_images' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case COMPLEXIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case COMPLEXIMAGEVIEW:
return_arg = add_images(*((ComplexImageView*)self_arg), *((ComplexImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'add_images' can not have pixel type '%s'. Acceptable value is COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'add_images' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_subtract_images(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
                      int in_place_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:subtract_images"
                        ,
             &self_pyarg                        ,
             &other_pyarg                        ,
             &in_place_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(other_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'other' must be an image");
          return 0;
        }
        other_arg = ((Image*)((RectObject*)other_pyarg)->m_x);
        image_get_fv(other_pyarg, &other_arg->features, &other_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = subtract_images(*((OneBitImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = subtract_images(*((OneBitImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = subtract_images(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = subtract_images(*((OneBitImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = subtract_images(*((OneBitImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = subtract_images(*((Cc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = subtract_images(*((Cc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = subtract_images(*((Cc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = subtract_images(*((Cc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = subtract_images(*((Cc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = subtract_images(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = subtract_images(*((OneBitRleImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = subtract_images(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = subtract_images(*((OneBitRleImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = subtract_images(*((OneBitRleImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = subtract_images(*((RleCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = subtract_images(*((RleCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = subtract_images(*((RleCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = subtract_images(*((RleCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = subtract_images(*((RleCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = subtract_images(*((MlCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = subtract_images(*((MlCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = subtract_images(*((MlCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = subtract_images(*((MlCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = subtract_images(*((MlCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREYSCALEIMAGEVIEW:
return_arg = subtract_images(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREY16IMAGEVIEW:
return_arg = subtract_images(*((Grey16ImageView*)self_arg), *((Grey16ImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable value is GREY16.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case RGBIMAGEVIEW:
return_arg = subtract_images(*((RGBImageView*)self_arg), *((RGBImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = subtract_images(*((FloatImageView*)self_arg), *((FloatImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case COMPLEXIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case COMPLEXIMAGEVIEW:
return_arg = subtract_images(*((ComplexImageView*)self_arg), *((ComplexImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'subtract_images' can not have pixel type '%s'. Acceptable value is COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'subtract_images' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_multiply_images(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
                      int in_place_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:multiply_images"
                        ,
             &self_pyarg                        ,
             &other_pyarg                        ,
             &in_place_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(other_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'other' must be an image");
          return 0;
        }
        other_arg = ((Image*)((RectObject*)other_pyarg)->m_x);
        image_get_fv(other_pyarg, &other_arg->features, &other_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREYSCALEIMAGEVIEW:
return_arg = multiply_images(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'multiply_images' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREY16IMAGEVIEW:
return_arg = multiply_images(*((Grey16ImageView*)self_arg), *((Grey16ImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'multiply_images' can not have pixel type '%s'. Acceptable value is GREY16.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case RGBIMAGEVIEW:
return_arg = multiply_images(*((RGBImageView*)self_arg), *((RGBImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'multiply_images' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = multiply_images(*((FloatImageView*)self_arg), *((FloatImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'multiply_images' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case COMPLEXIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case COMPLEXIMAGEVIEW:
return_arg = multiply_images(*((ComplexImageView*)self_arg), *((ComplexImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'multiply_images' can not have pixel type '%s'. Acceptable value is COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'multiply_images' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_divide_images(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
                      int in_place_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:divide_images"
                        ,
             &self_pyarg                        ,
             &other_pyarg                        ,
             &in_place_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(other_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'other' must be an image");
          return 0;
        }
        other_arg = ((Image*)((RectObject*)other_pyarg)->m_x);
        image_get_fv(other_pyarg, &other_arg->features, &other_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREYSCALEIMAGEVIEW:
return_arg = divide_images(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'divide_images' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case GREY16IMAGEVIEW:
return_arg = divide_images(*((Grey16ImageView*)self_arg), *((Grey16ImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'divide_images' can not have pixel type '%s'. Acceptable value is GREY16.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = divide_images(*((FloatImageView*)self_arg), *((FloatImageView*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'divide_images' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'divide_images' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _arithmetic_methods[] = {
                  {  "add_images",
          call_add_images, METH_VARARGS,
           "**add_images** (``Image`` [GreyScale|Grey16|Float|RGB|Complex] *other*, ``bool`` *in_place* = False)\n\nAdds the corresponding pixels of two images together.\n\nThe two images must be the same type.\n\nSince it would be difficult to determine what exactly to do if the\nimages are a different size, the two images must be the same size.\nUse .subimage on either image to crop appropriately if necessary\nfor your specific case.\n\n*in_place*\n  If true, the operation will be performed in-place, changing the\n  contents of the current image."        },
                        {  "subtract_images",
          call_subtract_images, METH_VARARGS,
           "**subtract_images** (``Image`` [OneBit|GreyScale|Grey16|RGB|Float|Complex] *other*, ``bool`` *in_place* = False)\n\nAdds the pixels of another image from the current image.\n\nThe two images must be the same type.\n\nSince it would be difficult to determine what exactly to do if the\nimages are a different size, the two images must be the same size.\nUse .subimage on either image to crop appropriately if necessary\nfor your specific case.\n\n*in_place*\n  If true, the operation will be performed in-place, changing the\n  contents of the current image."        },
                        {  "multiply_images",
          call_multiply_images, METH_VARARGS,
           "**multiply_images** (``Image`` [GreyScale|Grey16|Float|RGB|Complex] *other*, ``bool`` *in_place* = False)\n\nMultiplies the corresponding pixels of two images together.\n\nNote that this does not work on labeled ONEBIT images, because all\npixel values in the returned image are reset to one or zero in this case.\n\nSince it would be difficult to determine what exactly to do if the\nimages are a different size, the two images must be the same size.\nUse .subimage on either image to crop appropriately if necessary\nfor your specific case.\n\n*in_place*\n  If true, the operation will be performed in-place, changing the\n  contents of the current image."        },
                        {  "divide_images",
          call_divide_images, METH_VARARGS,
           "**divide_images** (``Image`` [GreyScale|Grey16|Float] *other*, ``bool`` *in_place* = False)\n\nDivides the pixels of the current image by the pixels of another\nimage.\n\nThe two images must be the same type.\n\nSince it would be difficult to determine what exactly to do if the\nimages are a different size, the two images must be the same size.\nUse .subimage on either image to crop appropriately if necessary\nfor your specific case.\n\n*in_place*\n  If true, the operation will be performed in-place, changing the\n  contents of the current image."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_arithmeticDef = {
        PyModuleDef_HEAD_INIT,
        "_arithmetic",
        nullptr,
        -1,
        _arithmetic_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__arithmetic(void) {
    return PyModule_Create(&module_arithmeticDef);
  }
  

