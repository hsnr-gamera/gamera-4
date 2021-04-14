
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "binarization.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_binarization(void);
  }
#endif

                static PyObject* call_image_mean(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                double return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:image_mean"
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
return_arg = image_mean(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = image_mean(*((Grey16ImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = image_mean(*((FloatImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'image_mean' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            return_pyarg = PyFloat_FromDouble((double)return_arg);            return return_pyarg;
                              }
                static PyObject* call_image_variance(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                double return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:image_variance"
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
return_arg = image_variance(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = image_variance(*((Grey16ImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = image_variance(*((FloatImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'image_variance' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            return_pyarg = PyFloat_FromDouble((double)return_arg);            return return_pyarg;
                              }
                static PyObject* call_mean_filter(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int region_size_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:mean_filter"
                        ,
             &self_pyarg                        ,
             &region_size_arg                      ) <= 0)
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
return_arg = mean_filter(*((GreyScaleImageView*)self_arg), region_size_arg);
break;
case GREY16IMAGEVIEW:
return_arg = mean_filter(*((Grey16ImageView*)self_arg), region_size_arg);
break;
case FLOATIMAGEVIEW:
return_arg = mean_filter(*((FloatImageView*)self_arg), region_size_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'mean_filter' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_variance_filter(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* means_arg;
PyObject* means_pyarg;
                      int region_size_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:variance_filter"
                        ,
             &self_pyarg                        ,
             &means_pyarg                        ,
             &region_size_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(means_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'means' must be an image");
          return 0;
        }
        means_arg = ((Image*)((RectObject*)means_pyarg)->m_x);
        image_get_fv(means_pyarg, &means_arg->features, &means_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(means_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = variance_filter(*((GreyScaleImageView*)self_arg), *((FloatImageView*)means_arg), region_size_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'means' argument of 'variance_filter' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(means_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(means_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = variance_filter(*((Grey16ImageView*)self_arg), *((FloatImageView*)means_arg), region_size_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'means' argument of 'variance_filter' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(means_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(means_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = variance_filter(*((FloatImageView*)self_arg), *((FloatImageView*)means_arg), region_size_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'means' argument of 'variance_filter' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(means_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'variance_filter' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_wiener_filter(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int region_size_arg;
                      double noise_variance_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oid:wiener_filter"
                        ,
             &self_pyarg                        ,
             &region_size_arg                        ,
             &noise_variance_arg                      ) <= 0)
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
return_arg = wiener_filter(*((GreyScaleImageView*)self_arg), region_size_arg, noise_variance_arg);
break;
case GREY16IMAGEVIEW:
return_arg = wiener_filter(*((Grey16ImageView*)self_arg), region_size_arg, noise_variance_arg);
break;
case FLOATIMAGEVIEW:
return_arg = wiener_filter(*((FloatImageView*)self_arg), region_size_arg, noise_variance_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'wiener_filter' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_niblack_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int region_size_arg;
                      double sensitivity_arg;
                      int lower_bound_arg;
                      int upper_bound_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oidii:niblack_threshold"
                        ,
             &self_pyarg                        ,
             &region_size_arg                        ,
             &sensitivity_arg                        ,
             &lower_bound_arg                        ,
             &upper_bound_arg                      ) <= 0)
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
return_arg = niblack_threshold(*((GreyScaleImageView*)self_arg), region_size_arg, sensitivity_arg, lower_bound_arg, upper_bound_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'niblack_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_sauvola_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int region_size_arg;
                      double sensitivity_arg;
                      int dynamic_range_arg;
                      int lower_bound_arg;
                      int upper_bound_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oidiii:sauvola_threshold"
                        ,
             &self_pyarg                        ,
             &region_size_arg                        ,
             &sensitivity_arg                        ,
             &dynamic_range_arg                        ,
             &lower_bound_arg                        ,
             &upper_bound_arg                      ) <= 0)
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
return_arg = sauvola_threshold(*((GreyScaleImageView*)self_arg), region_size_arg, sensitivity_arg, dynamic_range_arg, lower_bound_arg, upper_bound_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'sauvola_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_gatos_background(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* binarization_arg;
PyObject* binarization_pyarg;
                      int region_size_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:gatos_background"
                        ,
             &self_pyarg                        ,
             &binarization_pyarg                        ,
             &region_size_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(binarization_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'binarization' must be an image");
          return 0;
        }
        binarization_arg = ((Image*)((RectObject*)binarization_pyarg)->m_x);
        image_get_fv(binarization_pyarg, &binarization_arg->features, &binarization_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(binarization_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = gatos_background(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)binarization_arg), region_size_arg);
break;
case CC:
return_arg = gatos_background(*((GreyScaleImageView*)self_arg), *((Cc*)binarization_arg), region_size_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = gatos_background(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)binarization_arg), region_size_arg);
break;
case RLECC:
return_arg = gatos_background(*((GreyScaleImageView*)self_arg), *((RleCc*)binarization_arg), region_size_arg);
break;
case MLCC:
return_arg = gatos_background(*((GreyScaleImageView*)self_arg), *((MlCc*)binarization_arg), region_size_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'binarization' argument of 'gatos_background' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(binarization_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'gatos_background' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_gatos_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* background_arg;
PyObject* background_pyarg;
                      Image* binarization_arg;
PyObject* binarization_pyarg;
                      double q_arg;
                      double p1_arg;
                      double p2_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOOddd:gatos_threshold"
                        ,
             &self_pyarg                        ,
             &background_pyarg                        ,
             &binarization_pyarg                        ,
             &q_arg                        ,
             &p1_arg                        ,
             &p2_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(background_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'background' must be an image");
          return 0;
        }
        background_arg = ((Image*)((RectObject*)background_pyarg)->m_x);
        image_get_fv(background_pyarg, &background_arg->features, &background_arg->features_len);
                      if (!is_ImageObject(binarization_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'binarization' must be an image");
          return 0;
        }
        binarization_arg = ((Image*)((RectObject*)binarization_pyarg)->m_x);
        image_get_fv(binarization_pyarg, &binarization_arg->features, &binarization_arg->features_len);
                                                        
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(background_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(binarization_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = gatos_threshold(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)background_arg), *((OneBitImageView*)binarization_arg), q_arg, p1_arg, p2_arg);
break;
case CC:
return_arg = gatos_threshold(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)background_arg), *((Cc*)binarization_arg), q_arg, p1_arg, p2_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = gatos_threshold(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)background_arg), *((OneBitRleImageView*)binarization_arg), q_arg, p1_arg, p2_arg);
break;
case RLECC:
return_arg = gatos_threshold(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)background_arg), *((RleCc*)binarization_arg), q_arg, p1_arg, p2_arg);
break;
case MLCC:
return_arg = gatos_threshold(*((GreyScaleImageView*)self_arg), *((GreyScaleImageView*)background_arg), *((MlCc*)binarization_arg), q_arg, p1_arg, p2_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'binarization' argument of 'gatos_threshold' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(binarization_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'background' argument of 'gatos_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(background_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'gatos_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_white_rohrer_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int x_lookahead_arg;
                      int y_lookahead_arg;
                      int bias_mode_arg;
                      int bias_factor_arg;
                      int f_factor_arg;
                      int g_factor_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiiiiii:white_rohrer_threshold"
                        ,
             &self_pyarg                        ,
             &x_lookahead_arg                        ,
             &y_lookahead_arg                        ,
             &bias_mode_arg                        ,
             &bias_factor_arg                        ,
             &f_factor_arg                        ,
             &g_factor_arg                      ) <= 0)
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
return_arg = white_rohrer_threshold(*((GreyScaleImageView*)self_arg), x_lookahead_arg, y_lookahead_arg, bias_mode_arg, bias_factor_arg, f_factor_arg, g_factor_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'white_rohrer_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                      static PyObject* call_brink_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:brink_threshold"
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
return_arg = brink_threshold(*((GreyScaleImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'brink_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _binarization_methods[] = {
                  {  "image_mean",
          call_image_mean, METH_VARARGS,
           "**image_mean** ()\n\nReturns the mean over all pixels of an image as a FLOAT."        },
                        {  "image_variance",
          call_image_variance, METH_VARARGS,
           "**image_variance** ()\n\nReturns the variance over all pixels of an image as a FLOAT."        },
                        {  "mean_filter",
          call_mean_filter, METH_VARARGS,
           "**mean_filter** (int *region size* = 5)\n\nReturns the regional mean of an image as a FLOAT.\n\n*region_size*\n  The size of the region in which to calculate a mean."        },
                        {  "variance_filter",
          call_variance_filter, METH_VARARGS,
           "**variance_filter** (``Image`` [Float] *means*, int *region size* = 5)\n\nReturns the regional variance of an image as a FLOAT.\n\n*means*\n  Pre-calculated means for each region.\n\n*region_size*\n  The size of the region in which to calculate the variance."        },
                        {  "wiener_filter",
          call_wiener_filter, METH_VARARGS,
           "**wiener_filter** (int *region size* = 5, float *noise variance* = -1.00)\n\nAdaptive Wiener filter for de-noising.\n\nSee:\n\nJ. Lim. 2001. *Two-Dimensional Signal Processing.* Englewood\nCliffs: Prentice Hall.\n\n*region_size*\n  The size of the region within which to calculate the filter\n  coefficients.\n\n*noise_variance* \n  Variance of the noise in the image. If negative, estimated\n  automatically as the median of local variances."        },
                        {  "niblack_threshold",
          call_niblack_threshold, METH_VARARGS,
           "**niblack_threshold** (int *region size* = 15, float *sensitivity* = -0.20, int(0, 255) *lower bound* = 20, int(0, 255) *upper bound* = 150)\n\nCreates a binary image using Niblack's adaptive algorithm.\n\nNiblack, W. 1986. *An Introduction to Digital Image Processing.* Englewood\nCliffs, NJ: Prentice Hall.\n\nLike the QGAR library, there are two extra global thresholds for\nthe lightest and darkest regions.\n\n*region_size*\n  The size of the region in which to calculate a threshold.\n\n*sensitivity*\n  The sensitivity weight on the variance.\n\n*lower bound*\n  A global threshold beneath which all pixels are considered black.\n\n*upper bound*\n  A global threshold above which all pixels are considered white."        },
                        {  "sauvola_threshold",
          call_sauvola_threshold, METH_VARARGS,
           "**sauvola_threshold** (int *region size* = 15, float *sensitivity* = 0.50, int(1, 255) *dynamic range* = 128, int(0, 255) *lower bound* = 20, int(0, 255) *upper bound* = 150)\n\nCreates a binary image using Sauvola's adaptive algorithm.\n\nSauvola, J. and M. Pietikainen. 2000. Adaptive document image\nbinarization.  *Pattern Recognition* 33: 225--236.\n\nLike the QGAR library, there are two extra global thresholds for\nthe lightest and darkest regions.\n\n*region_size*\n  The size of the region in which to calculate a threshold.\n\n*sensitivity*\n  The sensitivity weight on the adjusted variance.\n\n*dynamic_range*\n  The dynamic range of the variance.\n\n*lower bound*\n  A global threshold beneath which all pixels are considered black.\n\n*upper bound*\n  A global threshold above which all pixels are considered white."        },
                        {  "gatos_background",
          call_gatos_background, METH_VARARGS,
           "**gatos_background** (``Image`` [OneBit] *binarization*, int *region size* = 15)\n\nEstimates the background of an image according to Gatos et al.'s\nmethod. See:\n\nGatos, Basilios, Ioannis Pratikakis, and Stavros\nJ. Perantonis. 2004. An adaptive binarization technique for low\nquality historical documents. *Lecture Notes in Computer\nScience* 3163: 102--113.\n\n*region_size* \n  Region size for interpolation.\n\n*binarization*\n  A preliminary binarization of the image."        },
                        {  "gatos_threshold",
          call_gatos_threshold, METH_VARARGS,
           "**gatos_threshold** (``Image`` [GreyScale] *background*, ``Image`` [OneBit] *binarization*, float *q* = 0.60, float *p1* = 0.50, float *p2* = 0.80)\n\nThresholds an image according to Gatos et al.'s method. See:\n\nGatos, Basilios, Ioannis Pratikakis, and Stavros\nJ. Perantonis. 2004. An adaptive binarization technique for low\nquality historical documents. *Lecture Notes in Computer\nScience* 3163: 102-113.\n\n*background*\n  Estimated background of the image.\n\n*binarization*\n  A preliminary binarization of the image.\n\nUse the default settings for the other parameters unless you know\nwhat you are doing."        },
                        {  "white_rohrer_threshold",
          call_white_rohrer_threshold, METH_VARARGS,
           "**white_rohrer_threshold** (int *x lookahead* = 8, int *y lookahead* = 1, int *bias mode* = 0, int *bias factor* = 100, int *f factor* = 100, int *g factor* = 100)\n\nCreates a binary image using White and Rohrer's dynamic thresholding\nalgorithm. It is the first of the two algorithms described in:\n\nJ. M. White and G. D. Rohrer. 1983. Image thresholding for optical\ncharacter recognition and other applications requiring character\nimage extraction.  *IBM J. Res. Dev.* 27(4), pp. 400-411\n\nThe algorithm uses a 'running' average instead of true average of\nthe gray values in the neighborhood.  The lookahead parameter\ngives the number of lookahead pixels used in the biased running\naverage that is used in deciding the threshold at each pixel\nlocation.\n\n*x_lookahead*\n  the number of lookahead pixels in the horizontal direction for\n  computing the running average. White and Rohrer suggest a value\n  of 8 for a 240 dpi scanning resolution.\n\n*y_lookahead*\n  number of lines used for further averaging from the horizontal\n  averages.\n\nThe other parameters are for calculating biased running average.\nWithout bias the thresholding decision would be determined by\nnoise fluctuations in uniform areas.\n\nThis implementation uses code from XITE__.\n\n.. __: http://www.ifi.uio.no/forskning/grupper/dsb/Software/Xite/\n\n.. note::\n\n   Permission to use, copy, modify and distribute this software\n   and its documentation for any purpose and without fee is hereby\n   granted, provided that this copyright notice appear in all\n   copies and that both that copyright notice and this permission\n   notice appear in supporting documentation and that the name of\n   B-lab, Department of Informatics or University of Oslo not be\n   used in advertising or publicity pertaining to distribution of\n   the software without specific, written prior permission.\n\n   B-LAB DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,\n   INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND\n   FITNESS, IN NO EVENT SHALL B-LAB BE LIABLE FOR ANY SPECIAL,\n   INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER\n   RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN\n   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,\n   ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF\n   THIS SOFTWARE."        },
                                  {  "brink_threshold",
          call_brink_threshold, METH_VARARGS,
           "**brink_threshold** ()\n\nCalculates threshold for image with Brink and Pendock's minimum-cross    \nentropy method and returns corrected image. It is best used for binarising\nimages with dark, near-black foreground and significant bleed-through.\nTo that end, it generally predicts lower thresholds than other\nthresholding algorithms.\n\nReference: A.D. Brink, N.E. Pendock: Minimum cross-entropy threshold selection.\nPattern Recognition 29 (1), 1996. 179-188."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_binarizationDef = {
        PyModuleDef_HEAD_INIT,
        "_binarization",
        nullptr,
        -1,
        _binarization_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__binarization(void) {
    return PyModule_Create(&module_binarizationDef);
  }
  

