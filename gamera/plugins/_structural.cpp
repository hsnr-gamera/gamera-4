
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "structural.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_structural(void);
  }
#endif

                static PyObject* call_polar_distance(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                FloatVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:polar_distance"
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
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((OneBitImageView*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((Cc*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((Cc*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((Cc*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((Cc*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((Cc*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((Cc*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((Cc*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((Cc*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((Cc*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((Cc*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((OneBitRleImageView*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((RleCc*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((RleCc*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((RleCc*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((RleCc*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((RleCc*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((RleCc*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((RleCc*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((RleCc*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((RleCc*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((RleCc*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((MlCc*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((MlCc*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((MlCc*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((MlCc*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((MlCc*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((MlCc*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((MlCc*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((MlCc*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((MlCc*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((MlCc*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((GreyScaleImageView*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((Grey16ImageView*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((RGBImageView*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((FloatImageView*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case COMPLEXIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((OneBitImageView*)other_arg));
break;
case CC:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((Cc*)other_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((OneBitRleImageView*)other_arg));
break;
case RLECC:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((RleCc*)other_arg));
break;
case MLCC:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((MlCc*)other_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((GreyScaleImageView*)other_arg));
break;
case GREY16IMAGEVIEW:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((Grey16ImageView*)other_arg));
break;
case RGBIMAGEVIEW:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((RGBImageView*)other_arg));
break;
case FLOATIMAGEVIEW:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((FloatImageView*)other_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = polar_distance(*((ComplexImageView*)self_arg), *((ComplexImageView*)other_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'polar_distance' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_polar_match(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        int return_arg;
PyObject* return_pyarg;
                                          double r1_arg;
                      double q1_arg;
                      double r2_arg;
                      double q2_arg;
      
                                      if (PyArg_ParseTuple(args,  "dddd:polar_match"
                        ,
             &r1_arg                        ,
             &q1_arg                        ,
             &r2_arg                        ,
             &q2_arg                      ) <= 0)
           return 0;
               
                                                              
              try {
                      return_arg = polar_match(r1_arg, q1_arg, r2_arg, q2_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                                    return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
                static PyObject* call_bounding_box_grouping_function(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        int return_arg;
PyObject* return_pyarg;
                                          Rect* a_arg;
PyObject* a_pyarg;
                      Rect* b_arg;
PyObject* b_pyarg;
                      int threshold_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:bounding_box_grouping_function"
                        ,
             &a_pyarg                        ,
             &b_pyarg                        ,
             &threshold_arg                      ) <= 0)
           return 0;
               
              
      if (!is_RectObject(a_pyarg)) {
        PyErr_SetString(PyExc_TypeError, "Argument 'a' must be a Rect");
        return 0;
      }
      a_arg = (((RectObject*)a_pyarg)->m_x);
                    
      if (!is_RectObject(b_pyarg)) {
        PyErr_SetString(PyExc_TypeError, "Argument 'b' must be a Rect");
        return 0;
      }
      b_arg = (((RectObject*)b_pyarg)->m_x);
                          
              try {
                      return_arg = bounding_box_grouping_function(a_arg, b_arg, threshold_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                  return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
                static PyObject* call_shaped_grouping_function(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        int return_arg;
PyObject* return_pyarg;
                                          Image* a_arg;
PyObject* a_pyarg;
                      Image* b_arg;
PyObject* b_pyarg;
                      int threshold_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:shaped_grouping_function"
                        ,
             &a_pyarg                        ,
             &b_pyarg                        ,
             &threshold_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(a_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'a' must be an image");
          return 0;
        }
        a_arg = ((Image*)((RectObject*)a_pyarg)->m_x);
        image_get_fv(a_pyarg, &a_arg->features, &a_arg->features_len);
                      if (!is_ImageObject(b_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'b' must be an image");
          return 0;
        }
        b_arg = ((Image*)((RectObject*)b_pyarg)->m_x);
        image_get_fv(b_pyarg, &b_arg->features, &b_arg->features_len);
                            
              try {
                      switch(get_image_combination(a_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(b_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = shaped_grouping_function(*((OneBitImageView*)a_arg), *((OneBitImageView*)b_arg), threshold_arg);
break;
case CC:
return_arg = shaped_grouping_function(*((OneBitImageView*)a_arg), *((Cc*)b_arg), threshold_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = shaped_grouping_function(*((OneBitImageView*)a_arg), *((OneBitRleImageView*)b_arg), threshold_arg);
break;
case RLECC:
return_arg = shaped_grouping_function(*((OneBitImageView*)a_arg), *((RleCc*)b_arg), threshold_arg);
break;
case MLCC:
return_arg = shaped_grouping_function(*((OneBitImageView*)a_arg), *((MlCc*)b_arg), threshold_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'b' argument of 'shaped_grouping_function' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(b_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(b_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = shaped_grouping_function(*((Cc*)a_arg), *((OneBitImageView*)b_arg), threshold_arg);
break;
case CC:
return_arg = shaped_grouping_function(*((Cc*)a_arg), *((Cc*)b_arg), threshold_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = shaped_grouping_function(*((Cc*)a_arg), *((OneBitRleImageView*)b_arg), threshold_arg);
break;
case RLECC:
return_arg = shaped_grouping_function(*((Cc*)a_arg), *((RleCc*)b_arg), threshold_arg);
break;
case MLCC:
return_arg = shaped_grouping_function(*((Cc*)a_arg), *((MlCc*)b_arg), threshold_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'b' argument of 'shaped_grouping_function' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(b_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(b_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = shaped_grouping_function(*((OneBitRleImageView*)a_arg), *((OneBitImageView*)b_arg), threshold_arg);
break;
case CC:
return_arg = shaped_grouping_function(*((OneBitRleImageView*)a_arg), *((Cc*)b_arg), threshold_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = shaped_grouping_function(*((OneBitRleImageView*)a_arg), *((OneBitRleImageView*)b_arg), threshold_arg);
break;
case RLECC:
return_arg = shaped_grouping_function(*((OneBitRleImageView*)a_arg), *((RleCc*)b_arg), threshold_arg);
break;
case MLCC:
return_arg = shaped_grouping_function(*((OneBitRleImageView*)a_arg), *((MlCc*)b_arg), threshold_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'b' argument of 'shaped_grouping_function' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(b_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(b_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = shaped_grouping_function(*((RleCc*)a_arg), *((OneBitImageView*)b_arg), threshold_arg);
break;
case CC:
return_arg = shaped_grouping_function(*((RleCc*)a_arg), *((Cc*)b_arg), threshold_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = shaped_grouping_function(*((RleCc*)a_arg), *((OneBitRleImageView*)b_arg), threshold_arg);
break;
case RLECC:
return_arg = shaped_grouping_function(*((RleCc*)a_arg), *((RleCc*)b_arg), threshold_arg);
break;
case MLCC:
return_arg = shaped_grouping_function(*((RleCc*)a_arg), *((MlCc*)b_arg), threshold_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'b' argument of 'shaped_grouping_function' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(b_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(b_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = shaped_grouping_function(*((MlCc*)a_arg), *((OneBitImageView*)b_arg), threshold_arg);
break;
case CC:
return_arg = shaped_grouping_function(*((MlCc*)a_arg), *((Cc*)b_arg), threshold_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = shaped_grouping_function(*((MlCc*)a_arg), *((OneBitRleImageView*)b_arg), threshold_arg);
break;
case RLECC:
return_arg = shaped_grouping_function(*((MlCc*)a_arg), *((RleCc*)b_arg), threshold_arg);
break;
case MLCC:
return_arg = shaped_grouping_function(*((MlCc*)a_arg), *((MlCc*)b_arg), threshold_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'b' argument of 'shaped_grouping_function' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(b_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'a' argument of 'shaped_grouping_function' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(a_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                  return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
                static PyObject* call_least_squares_fit(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PyObject* return_arg;
PyObject* return_pyarg;
                                          PointVector* points_arg;
PyObject* points_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:least_squares_fit"
                        ,
             &points_pyarg                      ) <= 0)
           return 0;
               
              
      points_arg = PointVector_from_python(points_pyarg);
      if (points_arg == NULL) return 0;
            
              try {
                      return_arg = least_squares_fit(points_arg);
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
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
                static PyObject* call_least_squares_fit_xy(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PyObject* return_arg;
PyObject* return_pyarg;
                                          PointVector* points_arg;
PyObject* points_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:least_squares_fit_xy"
                        ,
             &points_pyarg                      ) <= 0)
           return 0;
               
              
      points_arg = PointVector_from_python(points_pyarg);
      if (points_arg == NULL) return 0;
            
              try {
                      return_arg = least_squares_fit_xy(points_arg);
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
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
                static PyObject* call_edit_distance(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        int return_arg;
PyObject* return_pyarg;
                                          char* s1_arg;
                      char* s2_arg;
      
                                      if (PyArg_ParseTuple(args,  "ss:edit_distance"
                        ,
             &s1_arg                        ,
             &s2_arg                      ) <= 0)
           return 0;
               
                                  
              try {
                      return_arg = edit_distance(s1_arg, s2_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
      
          static PyMethodDef _structural_methods[] = {
                  {  "polar_distance",
          call_polar_distance, METH_VARARGS,
           "**polar_distance** (``Image`` [OneBit|GreyScale|Grey16|RGB|Float|Complex] *other*)\n\nReturns a tuple containing the normalized distance, polar\ndirection, and non-normalized polar distance to another glyph\n(based on center of bounding boxes)."        },
                        {  "polar_match",
          call_polar_match, METH_VARARGS,
           "**polar_match** (float *r1*, float *q1*, float *r2*, float *q2*)\n\n"        },
                        {  "bounding_box_grouping_function",
          call_bounding_box_grouping_function, METH_VARARGS,
           "**bounding_box_grouping_function** (``Rect`` *a*, ``Rect`` *b*, int *threshold*)\n\nGiven two rectangles *a*, *b*, and a given *threshold* distance\n(in pixels), returns ``True`` if the two rectangles are closer\nthan *threshold*."        },
                        {  "shaped_grouping_function",
          call_shaped_grouping_function, METH_VARARGS,
           "**shaped_grouping_function** (``Image`` [OneBit] *a*, ``Image`` [OneBit] *b*, int *threshold*)\n\nGiven two connected components *a*, *b*, and a given *threshold*\ndistance (in pixels), returns ``True`` if any pixel in *a* are\ncloser than *threshold* to any pixel in *b*."        },
                        {  "least_squares_fit",
          call_least_squares_fit, METH_VARARGS,
           "**least_squares_fit** ([object *points*])\n\nPerforms a least squares fit on a given list of points.\n\nThe result is a tuple of the form (*m*, *b*, *q*) where *m* is the\nslope of the line, *b* is the *y*-offset, and *q* is the gamma fit\nof the line to the points. (This assumes the same statistical\nsignificance for all points).\n\nSee Numerical Recipes in C, section 15.2__ for more information.\n\n.. __: http://www.library.cornell.edu/nr/bookcpdf/c15-2.pdf"        },
                        {  "least_squares_fit_xy",
          call_least_squares_fit_xy, METH_VARARGS,
           "**least_squares_fit_xy** ([object *points*])\n\nIdentical to *least_squares_fit* for line angles below 45 degrees.\nFor lines with a more vertical slope a least square fit of *x = my\n+ b* is done instead.\n\nThe result is a tuple of the form (*m*, *b*, *q*, *x_of_y*) where\n*m, b, q* are the same as in *least_squares_fit*, but the integer\nvalue *x_of_y* determines the actual meaning of the parameters *m*\nand *b*:\n\nWhen *x_of_y* is zero, *y = mx + b*. Otherwise *x = my + b*."        },
                        {  "edit_distance",
          call_edit_distance, METH_VARARGS,
           "**edit_distance** (str *s1*, str *s2*)\n\nComputes the edit distance (also known as *Levenshtein distance*) between\ntwo strings.\n\nThis counts the number of character substitutions, additions and deletions\nnecessary to transform one string into another. This plugin is a \nstraightforward implementation of the classic algorithm by Wagner \nand Fischer, which has runtime complexity *O(m*n)*, where *m* and *n* are\nthe lengths of the two strings.\n\nSee R.A. Wagner, M.J. Fischer: *The String-to-String Correction Problem.*\nJournal of the ACM 21, pp. 168-173, 1974."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_structuralDef = {
        PyModuleDef_HEAD_INIT,
        "_structural",
        nullptr,
        -1,
        _structural_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__structural(void) {
    return PyModule_Create(&module_structuralDef);
  }
  

