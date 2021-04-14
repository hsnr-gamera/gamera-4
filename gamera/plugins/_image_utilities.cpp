
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "image_utilities.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_image_utilities(void);
  }
#endif

                      static PyObject* call_image_copy(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int storage_format_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:image_copy"
                        ,
             &self_pyarg                        ,
             &storage_format_arg                      ) <= 0)
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
return_arg = image_copy(*((OneBitImageView*)self_arg), storage_format_arg);
break;
case CC:
return_arg = image_copy(*((Cc*)self_arg), storage_format_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = image_copy(*((OneBitRleImageView*)self_arg), storage_format_arg);
break;
case RLECC:
return_arg = image_copy(*((RleCc*)self_arg), storage_format_arg);
break;
case MLCC:
return_arg = image_copy(*((MlCc*)self_arg), storage_format_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = image_copy(*((GreyScaleImageView*)self_arg), storage_format_arg);
break;
case GREY16IMAGEVIEW:
return_arg = image_copy(*((Grey16ImageView*)self_arg), storage_format_arg);
break;
case RGBIMAGEVIEW:
return_arg = image_copy(*((RGBImageView*)self_arg), storage_format_arg);
break;
case FLOATIMAGEVIEW:
return_arg = image_copy(*((FloatImageView*)self_arg), storage_format_arg);
break;
case COMPLEXIMAGEVIEW:
return_arg = image_copy(*((ComplexImageView*)self_arg), storage_format_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'image_copy' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_histogram(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                FloatVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:histogram"
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
case GREYSCALEIMAGEVIEW:
return_arg = histogram(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = histogram(*((Grey16ImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'histogram' can not have pixel type '%s'. Acceptable values are GREYSCALE, and GREY16.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_union_images(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          ImageVector list_of_images_arg;
PyObject* list_of_images_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:union_images"
                        ,
             &list_of_images_pyarg                      ) <= 0)
           return 0;
               
              
          const char* type_error_list_of_images = "Argument 'list_of_images' must be an iterable of images.";
          PyObject* list_of_images_pyarg_seq = PySequence_Fast(list_of_images_pyarg, type_error_list_of_images);
          if (list_of_images_pyarg_seq == NULL)
            return 0;
          int list_of_images_arg_size = PySequence_Fast_GET_SIZE(list_of_images_pyarg_seq);
          list_of_images_arg.resize(list_of_images_arg_size);
          for (int i=0; i < list_of_images_arg_size; ++i) {
            PyObject *element = PySequence_Fast_GET_ITEM(list_of_images_pyarg_seq, i);
            if (!is_ImageObject(element)) {
              PyErr_SetString(PyExc_TypeError, type_error_list_of_images);
              return 0;
            }
            list_of_images_arg[i] = std::pair<Image*, int>((Image*)(((RectObject*)element)->m_x), get_image_combination(element));
            image_get_fv(element, &list_of_images_arg[i].first->features,
                         &list_of_images_arg[i].first->features_len);
          }
          Py_DECREF(list_of_images_pyarg_seq);      
              try {
                      return_arg = union_images(list_of_images_arg);
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
                static PyObject* call_fill_white(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:fill_white"
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
fill_white(*((OneBitImageView*)self_arg));
break;
case CC:
fill_white(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
fill_white(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
fill_white(*((RleCc*)self_arg));
break;
case MLCC:
fill_white(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
fill_white(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
fill_white(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
fill_white(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
fill_white(*((FloatImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'fill_white' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_fill(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      PyObject* value_arg;
PyObject* value_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:fill"
                        ,
             &self_pyarg                        ,
             &value_pyarg                      ) <= 0)
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
fill(*((OneBitImageView*)self_arg), pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case CC:
fill(*((Cc*)self_arg), pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
fill(*((OneBitRleImageView*)self_arg), pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case RLECC:
fill(*((RleCc*)self_arg), pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case MLCC:
fill(*((MlCc*)self_arg), pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case GREYSCALEIMAGEVIEW:
fill(*((GreyScaleImageView*)self_arg), pixel_from_python<GreyScalePixel>::convert(value_pyarg));
break;
case GREY16IMAGEVIEW:
fill(*((Grey16ImageView*)self_arg), pixel_from_python<Grey16Pixel>::convert(value_pyarg));
break;
case RGBIMAGEVIEW:
fill(*((RGBImageView*)self_arg), pixel_from_python<RGBPixel>::convert(value_pyarg));
break;
case FLOATIMAGEVIEW:
fill(*((FloatImageView*)self_arg), pixel_from_python<FloatPixel>::convert(value_pyarg));
break;
case COMPLEXIMAGEVIEW:
fill(*((ComplexImageView*)self_arg), pixel_from_python<ComplexPixel>::convert(value_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'fill' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                  Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_pad_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int top_arg;
                      int right_arg;
                      int bottom_arg;
                      int left_arg;
                      PyObject* value_arg;
PyObject* value_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OiiiiO:pad_image"
                        ,
             &self_pyarg                        ,
             &top_arg                        ,
             &right_arg                        ,
             &bottom_arg                        ,
             &left_arg                        ,
             &value_pyarg                      ) <= 0)
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
return_arg = pad_image(*((OneBitImageView*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case CC:
return_arg = pad_image(*((Cc*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = pad_image(*((OneBitRleImageView*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case RLECC:
return_arg = pad_image(*((RleCc*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case MLCC:
return_arg = pad_image(*((MlCc*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = pad_image(*((GreyScaleImageView*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<GreyScalePixel>::convert(value_pyarg));
break;
case GREY16IMAGEVIEW:
return_arg = pad_image(*((Grey16ImageView*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<Grey16Pixel>::convert(value_pyarg));
break;
case RGBIMAGEVIEW:
return_arg = pad_image(*((RGBImageView*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<RGBPixel>::convert(value_pyarg));
break;
case FLOATIMAGEVIEW:
return_arg = pad_image(*((FloatImageView*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<FloatPixel>::convert(value_pyarg));
break;
case COMPLEXIMAGEVIEW:
return_arg = pad_image(*((ComplexImageView*)self_arg), top_arg, right_arg, bottom_arg, left_arg, pixel_from_python<ComplexPixel>::convert(value_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'pad_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_pad_image_default(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          Image* _00000001_arg;
PyObject* _00000001_pyarg;
                      int top_arg;
                      int right_arg;
                      int bottom_arg;
                      int left_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiiii:pad_image_default"
                        ,
             &_00000001_pyarg                        ,
             &top_arg                        ,
             &right_arg                        ,
             &bottom_arg                        ,
             &left_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(_00000001_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument '_00000001' must be an image");
          return 0;
        }
        _00000001_arg = ((Image*)((RectObject*)_00000001_pyarg)->m_x);
        image_get_fv(_00000001_pyarg, &_00000001_arg->features, &_00000001_arg->features_len);
                                                                      
              try {
                      switch(get_image_combination(_00000001_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = pad_image_default(*((OneBitImageView*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case CC:
return_arg = pad_image_default(*((Cc*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = pad_image_default(*((OneBitRleImageView*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case RLECC:
return_arg = pad_image_default(*((RleCc*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case MLCC:
return_arg = pad_image_default(*((MlCc*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = pad_image_default(*((GreyScaleImageView*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case GREY16IMAGEVIEW:
return_arg = pad_image_default(*((Grey16ImageView*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case RGBIMAGEVIEW:
return_arg = pad_image_default(*((RGBImageView*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case FLOATIMAGEVIEW:
return_arg = pad_image_default(*((FloatImageView*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
case COMPLEXIMAGEVIEW:
return_arg = pad_image_default(*((ComplexImageView*)_00000001_arg), top_arg, right_arg, bottom_arg, left_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The '_00000001' argument of 'pad_image_default' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(_00000001_pyarg));
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
                static PyObject* call_trim_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      PyObject* PixelValue_arg;
PyObject* PixelValue_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:trim_image"
                        ,
             &self_pyarg                        ,
             &PixelValue_pyarg                      ) <= 0)
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
return_arg = trim_image(*((OneBitImageView*)self_arg), pixel_from_python<OneBitPixel>::convert(PixelValue_pyarg));
break;
case CC:
return_arg = trim_image(*((Cc*)self_arg), pixel_from_python<OneBitPixel>::convert(PixelValue_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = trim_image(*((OneBitRleImageView*)self_arg), pixel_from_python<OneBitPixel>::convert(PixelValue_pyarg));
break;
case RLECC:
return_arg = trim_image(*((RleCc*)self_arg), pixel_from_python<OneBitPixel>::convert(PixelValue_pyarg));
break;
case MLCC:
return_arg = trim_image(*((MlCc*)self_arg), pixel_from_python<OneBitPixel>::convert(PixelValue_pyarg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = trim_image(*((GreyScaleImageView*)self_arg), pixel_from_python<GreyScalePixel>::convert(PixelValue_pyarg));
break;
case GREY16IMAGEVIEW:
return_arg = trim_image(*((Grey16ImageView*)self_arg), pixel_from_python<Grey16Pixel>::convert(PixelValue_pyarg));
break;
case RGBIMAGEVIEW:
return_arg = trim_image(*((RGBImageView*)self_arg), pixel_from_python<RGBPixel>::convert(PixelValue_pyarg));
break;
case FLOATIMAGEVIEW:
return_arg = trim_image(*((FloatImageView*)self_arg), pixel_from_python<FloatPixel>::convert(PixelValue_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'trim_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_invert(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:invert"
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
invert(*((OneBitImageView*)self_arg));
break;
case CC:
invert(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
invert(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
invert(*((RleCc*)self_arg));
break;
case MLCC:
invert(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
invert(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
invert(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
invert(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'invert' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, and RGB.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_clip_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Rect* other_arg;
PyObject* other_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:clip_image"
                        ,
             &self_pyarg                        ,
             &other_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      if (!is_RectObject(other_pyarg)) {
        PyErr_SetString(PyExc_TypeError, "Argument 'other' must be a Rect");
        return 0;
      }
      other_arg = (((RectObject*)other_pyarg)->m_x);
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = clip_image(*((OneBitImageView*)self_arg), other_arg);
break;
case CC:
return_arg = clip_image(*((Cc*)self_arg), other_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = clip_image(*((OneBitRleImageView*)self_arg), other_arg);
break;
case RLECC:
return_arg = clip_image(*((RleCc*)self_arg), other_arg);
break;
case MLCC:
return_arg = clip_image(*((MlCc*)self_arg), other_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = clip_image(*((GreyScaleImageView*)self_arg), other_arg);
break;
case GREY16IMAGEVIEW:
return_arg = clip_image(*((Grey16ImageView*)self_arg), other_arg);
break;
case RGBIMAGEVIEW:
return_arg = clip_image(*((RGBImageView*)self_arg), other_arg);
break;
case FLOATIMAGEVIEW:
return_arg = clip_image(*((FloatImageView*)self_arg), other_arg);
break;
case COMPLEXIMAGEVIEW:
return_arg = clip_image(*((ComplexImageView*)self_arg), other_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'clip_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_mask(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* mask_arg;
PyObject* mask_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:mask"
                        ,
             &self_pyarg                        ,
             &mask_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(mask_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'mask' must be an image");
          return 0;
        }
        mask_arg = ((Image*)((RectObject*)mask_pyarg)->m_x);
        image_get_fv(mask_pyarg, &mask_arg->features, &mask_arg->features_len);
              
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(mask_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = mask(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)mask_arg));
break;
case CC:
return_arg = mask(*((GreyScaleImageView*)self_arg), *((Cc*)mask_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = mask(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)mask_arg));
break;
case RLECC:
return_arg = mask(*((GreyScaleImageView*)self_arg), *((RleCc*)mask_arg));
break;
case MLCC:
return_arg = mask(*((GreyScaleImageView*)self_arg), *((MlCc*)mask_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'mask' argument of 'mask' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(mask_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(mask_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = mask(*((RGBImageView*)self_arg), *((OneBitImageView*)mask_arg));
break;
case CC:
return_arg = mask(*((RGBImageView*)self_arg), *((Cc*)mask_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = mask(*((RGBImageView*)self_arg), *((OneBitRleImageView*)mask_arg));
break;
case RLECC:
return_arg = mask(*((RGBImageView*)self_arg), *((RleCc*)mask_arg));
break;
case MLCC:
return_arg = mask(*((RGBImageView*)self_arg), *((MlCc*)mask_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'mask' argument of 'mask' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(mask_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'mask' can not have pixel type '%s'. Acceptable values are GREYSCALE, and RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_nested_list_to_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          PyObject* nested_list_arg;
PyObject* nested_list_pyarg;
                      int image_type_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:nested_list_to_image"
                        ,
             &nested_list_pyarg                        ,
             &image_type_arg                      ) <= 0)
           return 0;
               
              nested_list_arg = nested_list_pyarg;                    
              try {
                      return_arg = nested_list_to_image(nested_list_arg, image_type_arg);
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
                static PyObject* call_to_nested_list(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_nested_list"
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
return_arg = to_nested_list(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_nested_list(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_nested_list(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_nested_list(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_nested_list(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = to_nested_list(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = to_nested_list(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
return_arg = to_nested_list(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = to_nested_list(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = to_nested_list(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_nested_list' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                      static PyObject* call_mse(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                double return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* _00000002_arg;
PyObject* _00000002_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:mse"
                        ,
             &self_pyarg                        ,
             &_00000002_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(_00000002_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument '_00000002' must be an image");
          return 0;
        }
        _00000002_arg = ((Image*)((RectObject*)_00000002_pyarg)->m_x);
        image_get_fv(_00000002_pyarg, &_00000002_arg->features, &_00000002_arg->features_len);
              
              try {
                      switch(get_image_combination(self_pyarg)) {
case RGBIMAGEVIEW:
switch(get_image_combination(_00000002_pyarg)) {
case RGBIMAGEVIEW:
return_arg = mse(*((RGBImageView*)self_arg), *((RGBImageView*)_00000002_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The '_00000002' argument of 'mse' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(_00000002_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'mse' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                              return_pyarg = PyFloat_FromDouble((double)return_arg);            return return_pyarg;
                              }
                static PyObject* call_reset_onebit_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:reset_onebit_image"
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
reset_onebit_image(*((OneBitImageView*)self_arg));
break;
case CC:
reset_onebit_image(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
reset_onebit_image(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
reset_onebit_image(*((RleCc*)self_arg));
break;
case MLCC:
reset_onebit_image(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'reset_onebit_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_ccs_from_labeled_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::list<Image*>* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:ccs_from_labeled_image"
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
return_arg = ccs_from_labeled_image(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = ccs_from_labeled_image(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = ccs_from_labeled_image(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = ccs_from_labeled_image(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = ccs_from_labeled_image(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'ccs_from_labeled_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_min_max_location(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* mask_arg;
PyObject* mask_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:min_max_location"
                        ,
             &self_pyarg                        ,
             &mask_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(mask_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'mask' must be an image");
          return 0;
        }
        mask_arg = ((Image*)((RectObject*)mask_pyarg)->m_x);
        image_get_fv(mask_pyarg, &mask_arg->features, &mask_arg->features_len);
              
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(mask_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = min_max_location(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)mask_arg));
break;
case CC:
return_arg = min_max_location(*((GreyScaleImageView*)self_arg), *((Cc*)mask_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = min_max_location(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)mask_arg));
break;
case RLECC:
return_arg = min_max_location(*((GreyScaleImageView*)self_arg), *((RleCc*)mask_arg));
break;
case MLCC:
return_arg = min_max_location(*((GreyScaleImageView*)self_arg), *((MlCc*)mask_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'mask' argument of 'min_max_location' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(mask_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(mask_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = min_max_location(*((Grey16ImageView*)self_arg), *((OneBitImageView*)mask_arg));
break;
case CC:
return_arg = min_max_location(*((Grey16ImageView*)self_arg), *((Cc*)mask_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = min_max_location(*((Grey16ImageView*)self_arg), *((OneBitRleImageView*)mask_arg));
break;
case RLECC:
return_arg = min_max_location(*((Grey16ImageView*)self_arg), *((RleCc*)mask_arg));
break;
case MLCC:
return_arg = min_max_location(*((Grey16ImageView*)self_arg), *((MlCc*)mask_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'mask' argument of 'min_max_location' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(mask_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(mask_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = min_max_location(*((FloatImageView*)self_arg), *((OneBitImageView*)mask_arg));
break;
case CC:
return_arg = min_max_location(*((FloatImageView*)self_arg), *((Cc*)mask_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = min_max_location(*((FloatImageView*)self_arg), *((OneBitRleImageView*)mask_arg));
break;
case RLECC:
return_arg = min_max_location(*((FloatImageView*)self_arg), *((RleCc*)mask_arg));
break;
case MLCC:
return_arg = min_max_location(*((FloatImageView*)self_arg), *((MlCc*)mask_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'mask' argument of 'min_max_location' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(mask_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'min_max_location' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_min_max_location_nomask(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:min_max_location_nomask"
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
case GREYSCALEIMAGEVIEW:
return_arg = min_max_location_nomask(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = min_max_location_nomask(*((Grey16ImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = min_max_location_nomask(*((FloatImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'min_max_location_nomask' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _image_utilities_methods[] = {
                            {  "image_copy",
          call_image_copy, METH_VARARGS,
           "**image_copy** (``Choice`` [DENSE|RLE] *storage_format*)\n\nCopies an image along with all of its underlying data.  Since the data is\ncopied, changes to the new image do not affect the original image.\n\n*storage_format*\n  specifies the compression type for the returned copy:\n\nDENSE (0)\n  no compression\nRLE (1)\n  run-length encoding compression"        },
                        {  "histogram",
          call_histogram, METH_VARARGS,
           "**histogram** ()\n\nCompute the histogram of the pixel values in the given image.\nReturns a Python array of doubles, with each value being a\npercentage.\n\nIf the GUI is being used, the histogram is displayed.\n\n.. image:: images/histogram.png"        },
                        {  "union_images",
          call_union_images, METH_VARARGS,
           "**union_images** ([object *list_of_images*])\n\nReturns an image that is the union of the given list of connected\ncomponents."        },
                        {  "fill_white",
          call_fill_white, METH_VARARGS,
           "**fill_white** ()\n\nFills the entire image with white."        },
                        {  "fill",
          call_fill, METH_VARARGS,
           "**fill** (Pixel *value*)\n\nFills the entire image with value.\n\n*value*\n  A pixel value.  This value may be any value the pixel type can support."        },
                        {  "pad_image",
          call_pad_image, METH_VARARGS,
           "**pad_image** (int *top*, int *right*, int *bottom*, int *left*, Pixel *value*)\n\nPads an image with any value. When no pixel value is given, the value \ncorresponding to the color *white* is used.\n\n*top*\n  Padding on the top.\n\n*right*\n  Padding on the right.\n\n*bottom*\n  Padding on the bottom.\n\n*left*\n  Padding on the left.\n\n*value*\n  An optional pixel value of the pixel type of the image.\n  When omitted or set to ``None``, the color white is used for padding."        },
                        {  "pad_image_default",
          call_pad_image_default, METH_VARARGS,
           "**pad_image_default** (``Image`` [OneBit|GreyScale|Grey16|RGB|Float|Complex] *_00000001*, int *top*, int *right*, int *bottom*, int *left*)\n\nPads an image with the default pixel value white"        },
                        {  "trim_image",
          call_trim_image, METH_VARARGS,
           "**trim_image** (Pixel *PixelValue* = None)\n\nReturns minimal view so that outside of the view only Pixels with\n*PixelValue* exists. When no *PixelValue* is given, white is used."        },
                        {  "invert",
          call_invert, METH_VARARGS,
           "**invert** ()\n\nInverts the image."        },
                        {  "clip_image",
          call_clip_image, METH_VARARGS,
           "**clip_image** (``Rect`` *other*)\n\nCrops an image so that the bounding box includes only the\nintersection of it and another image.  Returns a zero-sized image\nif the two images do not intersect."        },
                        {  "mask",
          call_mask, METH_VARARGS,
           "**mask** (``Image`` [OneBit] *mask*)\n\nMasks an image using the given ONEBIT image.  Parts of the ONEBIT\nimage that are white will be changed to white in the resulting\nimage.\n\nThe images must be the same size."        },
                        {  "nested_list_to_image",
          call_nested_list_to_image, METH_VARARGS,
           "**nested_list_to_image** (object *nested_list*, ``Choice`` [ONEBIT|GREYSCALE|GREY16|RGB|FLOAT] *image_type*)\n\nConverts a nested Python list to an Image.  Is the inverse of\n``to_nested_list``.\n\n*nested_list*\n  A nested Python list in row-major order.  If the list is a flat list,\n  an image with a single row will be created.\n\n*image_type*\n  The resulting image type.  Should be one of the integer Image type\n  constants (ONEBIT, GREYSCALE, GREY16, RGB, FLOAT).  If image_type\n  is not provided or less than 0, the image type will be determined\n  by auto-detection from the list.  The following list shows the mapping\n  from Python type to image type:\n\n  - int -> GREYSCALE\n  - float -> FLOAT\n  - RGBPixel -> RGB\n\nTo obtain other image types, the type number must be explicitly passed.\n\nNOTE: This will not scale very well and should only be used\nfor small images, such as convolution kernels.\n\nExamples:\n\n.. code:: Python\n\n  # Sobel kernel (implicitly will be a FLOAT image)\n  kernel = nested_list_to_image([[0.125, 0.0, -0.125],\n                                 [0.25 , 0.0, -0.25 ],\n                                 [0.125, 0.0, -0.125]])\n\n  # Single row image (note that nesting is optional)\n  image = nested_list_to_image([RGBPixel(255, 0, 0),\n                                RGBPixel(0, 255, 0),\n                                RGBPixel(0, 0, 255)])"        },
                        {  "to_nested_list",
          call_to_nested_list, METH_VARARGS,
           "**to_nested_list** ()\n\nConverts an image to a nested Python list.\nThis method is the inverse of ``nested_list_to_image``.\n\nThe following table describes how each image type is converted to\nPython types:\n\n  - ONEBIT -> int\n  - GREYSCALE -> int\n  - GREY16 -> int\n  - RGB -> RGBPixel\n  - FLOAT -> float\n\nNOTE: This will not scale very well and should only be used for\nsmall images, such as convolution kernels."        },
                                  {  "mse",
          call_mse, METH_VARARGS,
           "**mse** (``Image`` [RGB] *_00000002*)\n\nCalculates the mean square error between two images."        },
                        {  "reset_onebit_image",
          call_reset_onebit_image, METH_VARARGS,
           "**reset_onebit_image** ()\n\nResets all black pixel values in a onebit image to one.  This\ncan be necessary e.g. after a CC analysis which sets black\npixels to some other label value."        },
                        {  "ccs_from_labeled_image",
          call_ccs_from_labeled_image, METH_VARARGS,
           "**ccs_from_labeled_image** ()\n\nReturns all ``Cc``'s represented by unique labels in the given\nonebit image. The bounding boxes are computed as tight as possible.\n\nThis is mostly useful for reading manually labeled groundtruth\ndata from color PNG files in combination with the plugin\ncolors_to_labels_. Example:\n\n.. code:: Python\n\n  labeled = rgb.colors_to_labels()\n  ccs = labeled.ccs_from_labeled_image()\n\n.. _colors_to_labels: color.html#colors-to-labels"        },
                        {  "min_max_location",
          call_min_max_location, METH_VARARGS,
           "**min_max_location** (``Image`` [OneBit] *mask* = None)\n\nReturns the minimum and maximum pixel value and their location\nin an image. When the min/max value occurs at several locations, only the\nlocation that is closest to the bottom right corner is returned.\n\nOnly those pixels are examined that are black in the provided *mask*. \nWhen no *mask* is given, the entire image is examined. The mask can\nbe useful, e.g., to find the lightest and darkest value in the original\ngreyscale image belonging to a Cc, as in the following example:\n\n    .. code:: Python\n\n      onebit = grey.to_onebit()\n      ccs = onebit.cc_analysis()\n      # compute min/max of first cc in original greyscale image\n      (pmin, vmin, pmax, vmax) = grey.min_max_location(ccs[0])\n\nThe return value is a tuple of the form *(pmin, vmin, pmax, vmax)* where\n*pmin* and *pmax* are the point of the minimum and maximum, respectively,\nand *vmin* and *vmax* the corresponding pixel values.\n"        },
                        {  "min_max_location_nomask",
          call_min_max_location_nomask, METH_VARARGS,
           "**min_max_location_nomask** ()\n\nThis is only a helper function for overloading min_max_location.\nIt is not needed on the Python side, but only on the C++ side due to\nthe plugin wrapping mechanism of Gamera.\n"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_image_utilitiesDef = {
        PyModuleDef_HEAD_INIT,
        "_image_utilities",
        nullptr,
        -1,
        _image_utilities_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__image_utilities(void) {
    return PyModule_Create(&module_image_utilitiesDef);
  }
  

