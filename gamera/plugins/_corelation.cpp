
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "corelation.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_corelation(void);
  }
#endif

                static PyObject* call_corelation_weighted(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                double return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* template_arg;
PyObject* template_pyarg;
                      Point offset_arg;
PyObject* offset_pyarg;
                      double bb_arg;
                      double bw_arg;
                      double wb_arg;
                      double ww_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOOdddd:corelation_weighted"
                        ,
             &self_pyarg                        ,
             &template_pyarg                        ,
             &offset_pyarg                        ,
             &bb_arg                        ,
             &bw_arg                        ,
             &wb_arg                        ,
             &ww_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(template_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'template' must be an image");
          return 0;
        }
        template_arg = ((Image*)((RectObject*)template_pyarg)->m_x);
        image_get_fv(template_pyarg, &template_arg->features, &template_arg->features_len);
                      
      try {
         offset_arg = coerce_Point(offset_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'offset' must be a Point, or convertible to a Point");
         return 0;
      }
                                                                    
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_weighted(*((OneBitImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case CC:
return_arg = corelation_weighted(*((OneBitImageView*)self_arg), *((Cc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_weighted(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case RLECC:
return_arg = corelation_weighted(*((OneBitImageView*)self_arg), *((RleCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case MLCC:
return_arg = corelation_weighted(*((OneBitImageView*)self_arg), *((MlCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_weighted' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_weighted(*((Cc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case CC:
return_arg = corelation_weighted(*((Cc*)self_arg), *((Cc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_weighted(*((Cc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case RLECC:
return_arg = corelation_weighted(*((Cc*)self_arg), *((RleCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case MLCC:
return_arg = corelation_weighted(*((Cc*)self_arg), *((MlCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_weighted' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_weighted(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case CC:
return_arg = corelation_weighted(*((OneBitRleImageView*)self_arg), *((Cc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_weighted(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case RLECC:
return_arg = corelation_weighted(*((OneBitRleImageView*)self_arg), *((RleCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case MLCC:
return_arg = corelation_weighted(*((OneBitRleImageView*)self_arg), *((MlCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_weighted' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_weighted(*((RleCc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case CC:
return_arg = corelation_weighted(*((RleCc*)self_arg), *((Cc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_weighted(*((RleCc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case RLECC:
return_arg = corelation_weighted(*((RleCc*)self_arg), *((RleCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case MLCC:
return_arg = corelation_weighted(*((RleCc*)self_arg), *((MlCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_weighted' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_weighted(*((MlCc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case CC:
return_arg = corelation_weighted(*((MlCc*)self_arg), *((Cc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_weighted(*((MlCc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case RLECC:
return_arg = corelation_weighted(*((MlCc*)self_arg), *((RleCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case MLCC:
return_arg = corelation_weighted(*((MlCc*)self_arg), *((MlCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_weighted' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_weighted(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case CC:
return_arg = corelation_weighted(*((GreyScaleImageView*)self_arg), *((Cc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_weighted(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case RLECC:
return_arg = corelation_weighted(*((GreyScaleImageView*)self_arg), *((RleCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
case MLCC:
return_arg = corelation_weighted(*((GreyScaleImageView*)self_arg), *((MlCc*)template_arg), offset_arg, bb_arg, bw_arg, wb_arg, ww_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_weighted' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'corelation_weighted' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, and GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                                                                        return_pyarg = PyFloat_FromDouble((double)return_arg);            return return_pyarg;
                              }
                static PyObject* call_corelation_sum(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                double return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* template_arg;
PyObject* template_pyarg;
                      Point offset_arg;
PyObject* offset_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOO:corelation_sum"
                        ,
             &self_pyarg                        ,
             &template_pyarg                        ,
             &offset_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(template_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'template' must be an image");
          return 0;
        }
        template_arg = ((Image*)((RectObject*)template_pyarg)->m_x);
        image_get_fv(template_pyarg, &template_arg->features, &template_arg->features_len);
                      
      try {
         offset_arg = coerce_Point(offset_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'offset' must be a Point, or convertible to a Point");
         return 0;
      }
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum(*((OneBitImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum(*((OneBitImageView*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum(*((OneBitImageView*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum(*((OneBitImageView*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum(*((Cc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum(*((Cc*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum(*((Cc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum(*((Cc*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum(*((Cc*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum(*((OneBitRleImageView*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum(*((OneBitRleImageView*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum(*((OneBitRleImageView*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum(*((RleCc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum(*((RleCc*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum(*((RleCc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum(*((RleCc*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum(*((RleCc*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum(*((MlCc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum(*((MlCc*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum(*((MlCc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum(*((MlCc*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum(*((MlCc*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum(*((GreyScaleImageView*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum(*((GreyScaleImageView*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum(*((GreyScaleImageView*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'corelation_sum' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, and GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                return_pyarg = PyFloat_FromDouble((double)return_arg);            return return_pyarg;
                              }
                static PyObject* call_corelation_sum_squares(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                double return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* template_arg;
PyObject* template_pyarg;
                      Point offset_arg;
PyObject* offset_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOO:corelation_sum_squares"
                        ,
             &self_pyarg                        ,
             &template_pyarg                        ,
             &offset_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(template_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'template' must be an image");
          return 0;
        }
        template_arg = ((Image*)((RectObject*)template_pyarg)->m_x);
        image_get_fv(template_pyarg, &template_arg->features, &template_arg->features_len);
                      
      try {
         offset_arg = coerce_Point(offset_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'offset' must be a Point, or convertible to a Point");
         return 0;
      }
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum_squares(*((OneBitImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum_squares(*((OneBitImageView*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum_squares(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum_squares(*((OneBitImageView*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum_squares(*((OneBitImageView*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum_squares' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum_squares(*((Cc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum_squares(*((Cc*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum_squares(*((Cc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum_squares(*((Cc*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum_squares(*((Cc*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum_squares' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum_squares(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum_squares(*((OneBitRleImageView*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum_squares(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum_squares(*((OneBitRleImageView*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum_squares(*((OneBitRleImageView*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum_squares' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum_squares(*((RleCc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum_squares(*((RleCc*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum_squares(*((RleCc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum_squares(*((RleCc*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum_squares(*((RleCc*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum_squares' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum_squares(*((MlCc*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum_squares(*((MlCc*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum_squares(*((MlCc*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum_squares(*((MlCc*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum_squares(*((MlCc*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum_squares' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(template_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = corelation_sum_squares(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case CC:
return_arg = corelation_sum_squares(*((GreyScaleImageView*)self_arg), *((Cc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = corelation_sum_squares(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case RLECC:
return_arg = corelation_sum_squares(*((GreyScaleImageView*)self_arg), *((RleCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
case MLCC:
return_arg = corelation_sum_squares(*((GreyScaleImageView*)self_arg), *((MlCc*)template_arg), offset_arg, ProgressBar((char *)"Correlating"));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'template' argument of 'corelation_sum_squares' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(template_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'corelation_sum_squares' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, and GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                return_pyarg = PyFloat_FromDouble((double)return_arg);            return return_pyarg;
                              }
      
          static PyMethodDef _corelation_methods[] = {
                  {  "corelation_weighted",
          call_corelation_weighted, METH_VARARGS,
           "**corelation_weighted** (``Image`` [OneBit] *template*, ``Point`` *offset*, float *bb*, float *bw*, float *wb*, float *ww*)\n\nReturns a floating-point value for how well an image is corelated\nto another image placed at a given origin (*x*, *y*).  Uses the\nweighted reward/penalty method.\n\n*template*\n  The template image.\n\n*offset*\n  The displacement of the template on the image.\n\n*bb*, *bw*, *wb*, *ww*\n  The rewards and penalties for different combinations of pixels.\n  The first letter in the argument name indicates the color of the\n  template; the second letter indicates the color of the source\n  image.  For instance, the value of *bw* will be applied to the\n  result when the template pixel is black and the source image\n  pixel is white.\n\n+--------+--------+------------------+\n| Image  |        | Template         |\n|        +--------+---------+--------+\n|        |        | black   | white  |\n|        +--------+---------+--------+\n|        | black  | *bb*    | *wb*   |\n|        +--------+---------+--------+\n|        | white  | *bw*    | *ww*   |\n+--------+--------+---------+--------+"        },
                        {  "corelation_sum",
          call_corelation_sum, METH_VARARGS,
           "**corelation_sum** (``Image`` [OneBit] *template*, ``Point`` *offset*)\n\nReturns a floating-point value for how well an image is corelated\nto another image placed at a given origin (*x*, *y*).  Uses the\nsum of absolute distance method.  A higher value indicates more\ncorelation.\n\n*template*\n  The template image.\n\n*offset*\n  The displacement of the template on the image."        },
                        {  "corelation_sum_squares",
          call_corelation_sum_squares, METH_VARARGS,
           "**corelation_sum_squares** (``Image`` [OneBit] *template*, ``Point`` *offset*)\n\nReturns a floating-point value for how well an image is corelated\nto another image placed at a given origin (*x*, *y*).  Uses the\nsum of squares method.  A higher value indicates more corelation.\n\n*template*\n  The template image.\n*offset*\n  The displacement of the template on the image."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_corelationDef = {
        PyModuleDef_HEAD_INIT,
        "_corelation",
        nullptr,
        -1,
        _corelation_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__corelation(void) {
    return PyModule_Create(&module_corelationDef);
  }
  

