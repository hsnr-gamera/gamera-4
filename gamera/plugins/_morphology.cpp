
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "morphology.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_morphology(void);
  }
#endif

                static PyObject* call_erode_dilate(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int ntimes_arg;
                      int direction_arg;
                      int shape_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiii:erode_dilate"
                        ,
             &self_pyarg                        ,
             &ntimes_arg                        ,
             &direction_arg                        ,
             &shape_arg                      ) <= 0)
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
return_arg = erode_dilate(*((OneBitImageView*)self_arg), ntimes_arg, direction_arg, shape_arg);
break;
case CC:
return_arg = erode_dilate(*((Cc*)self_arg), ntimes_arg, direction_arg, shape_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = erode_dilate(*((OneBitRleImageView*)self_arg), ntimes_arg, direction_arg, shape_arg);
break;
case RLECC:
return_arg = erode_dilate(*((RleCc*)self_arg), ntimes_arg, direction_arg, shape_arg);
break;
case MLCC:
return_arg = erode_dilate(*((MlCc*)self_arg), ntimes_arg, direction_arg, shape_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = erode_dilate(*((GreyScaleImageView*)self_arg), ntimes_arg, direction_arg, shape_arg);
break;
case FLOATIMAGEVIEW:
return_arg = erode_dilate(*((FloatImageView*)self_arg), ntimes_arg, direction_arg, shape_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'erode_dilate' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, and FLOAT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
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
                            static PyObject* call_despeckle(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      int cc_size_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:despeckle"
                        ,
             &self_pyarg                        ,
             &cc_size_arg                      ) <= 0)
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
despeckle(*((OneBitImageView*)self_arg), cc_size_arg);
break;
case CC:
despeckle(*((Cc*)self_arg), cc_size_arg);
break;
case ONEBITRLEIMAGEVIEW:
despeckle(*((OneBitRleImageView*)self_arg), cc_size_arg);
break;
case RLECC:
despeckle(*((RleCc*)self_arg), cc_size_arg);
break;
case MLCC:
despeckle(*((MlCc*)self_arg), cc_size_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'despeckle' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                  Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_distance_transform(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int norm_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:distance_transform"
                        ,
             &self_pyarg                        ,
             &norm_arg                      ) <= 0)
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
return_arg = distance_transform(*((OneBitImageView*)self_arg), norm_arg);
break;
case CC:
return_arg = distance_transform(*((Cc*)self_arg), norm_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = distance_transform(*((OneBitRleImageView*)self_arg), norm_arg);
break;
case RLECC:
return_arg = distance_transform(*((RleCc*)self_arg), norm_arg);
break;
case MLCC:
return_arg = distance_transform(*((MlCc*)self_arg), norm_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'distance_transform' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
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
                static PyObject* call_dilate_with_structure(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* structuring_element_arg;
PyObject* structuring_element_pyarg;
                      Point origin_arg;
PyObject* origin_pyarg;
                      int only_border_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOOi:dilate_with_structure"
                        ,
             &self_pyarg                        ,
             &structuring_element_pyarg                        ,
             &origin_pyarg                        ,
             &only_border_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(structuring_element_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'structuring_element' must be an image");
          return 0;
        }
        structuring_element_arg = ((Image*)((RectObject*)structuring_element_pyarg)->m_x);
        image_get_fv(structuring_element_pyarg, &structuring_element_arg->features, &structuring_element_arg->features_len);
                      
      try {
         origin_arg = coerce_Point(origin_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'origin' must be a Point, or convertible to a Point");
         return 0;
      }
                          
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = dilate_with_structure(*((OneBitImageView*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case CC:
return_arg = dilate_with_structure(*((OneBitImageView*)self_arg), *((Cc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = dilate_with_structure(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case RLECC:
return_arg = dilate_with_structure(*((OneBitImageView*)self_arg), *((RleCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case MLCC:
return_arg = dilate_with_structure(*((OneBitImageView*)self_arg), *((MlCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'dilate_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = dilate_with_structure(*((Cc*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case CC:
return_arg = dilate_with_structure(*((Cc*)self_arg), *((Cc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = dilate_with_structure(*((Cc*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case RLECC:
return_arg = dilate_with_structure(*((Cc*)self_arg), *((RleCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case MLCC:
return_arg = dilate_with_structure(*((Cc*)self_arg), *((MlCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'dilate_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = dilate_with_structure(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case CC:
return_arg = dilate_with_structure(*((OneBitRleImageView*)self_arg), *((Cc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = dilate_with_structure(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case RLECC:
return_arg = dilate_with_structure(*((OneBitRleImageView*)self_arg), *((RleCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case MLCC:
return_arg = dilate_with_structure(*((OneBitRleImageView*)self_arg), *((MlCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'dilate_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = dilate_with_structure(*((RleCc*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case CC:
return_arg = dilate_with_structure(*((RleCc*)self_arg), *((Cc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = dilate_with_structure(*((RleCc*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case RLECC:
return_arg = dilate_with_structure(*((RleCc*)self_arg), *((RleCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case MLCC:
return_arg = dilate_with_structure(*((RleCc*)self_arg), *((MlCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'dilate_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = dilate_with_structure(*((MlCc*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case CC:
return_arg = dilate_with_structure(*((MlCc*)self_arg), *((Cc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = dilate_with_structure(*((MlCc*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg, only_border_arg);
break;
case RLECC:
return_arg = dilate_with_structure(*((MlCc*)self_arg), *((RleCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
case MLCC:
return_arg = dilate_with_structure(*((MlCc*)self_arg), *((MlCc*)structuring_element_arg), origin_arg, only_border_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'dilate_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'dilate_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
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
                static PyObject* call_erode_with_structure(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* structuring_element_arg;
PyObject* structuring_element_pyarg;
                      Point origin_arg;
PyObject* origin_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOO:erode_with_structure"
                        ,
             &self_pyarg                        ,
             &structuring_element_pyarg                        ,
             &origin_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(structuring_element_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'structuring_element' must be an image");
          return 0;
        }
        structuring_element_arg = ((Image*)((RectObject*)structuring_element_pyarg)->m_x);
        image_get_fv(structuring_element_pyarg, &structuring_element_arg->features, &structuring_element_arg->features_len);
                      
      try {
         origin_arg = coerce_Point(origin_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'origin' must be a Point, or convertible to a Point");
         return 0;
      }
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = erode_with_structure(*((OneBitImageView*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg);
break;
case CC:
return_arg = erode_with_structure(*((OneBitImageView*)self_arg), *((Cc*)structuring_element_arg), origin_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = erode_with_structure(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg);
break;
case RLECC:
return_arg = erode_with_structure(*((OneBitImageView*)self_arg), *((RleCc*)structuring_element_arg), origin_arg);
break;
case MLCC:
return_arg = erode_with_structure(*((OneBitImageView*)self_arg), *((MlCc*)structuring_element_arg), origin_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'erode_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = erode_with_structure(*((Cc*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg);
break;
case CC:
return_arg = erode_with_structure(*((Cc*)self_arg), *((Cc*)structuring_element_arg), origin_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = erode_with_structure(*((Cc*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg);
break;
case RLECC:
return_arg = erode_with_structure(*((Cc*)self_arg), *((RleCc*)structuring_element_arg), origin_arg);
break;
case MLCC:
return_arg = erode_with_structure(*((Cc*)self_arg), *((MlCc*)structuring_element_arg), origin_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'erode_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = erode_with_structure(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg);
break;
case CC:
return_arg = erode_with_structure(*((OneBitRleImageView*)self_arg), *((Cc*)structuring_element_arg), origin_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = erode_with_structure(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg);
break;
case RLECC:
return_arg = erode_with_structure(*((OneBitRleImageView*)self_arg), *((RleCc*)structuring_element_arg), origin_arg);
break;
case MLCC:
return_arg = erode_with_structure(*((OneBitRleImageView*)self_arg), *((MlCc*)structuring_element_arg), origin_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'erode_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = erode_with_structure(*((RleCc*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg);
break;
case CC:
return_arg = erode_with_structure(*((RleCc*)self_arg), *((Cc*)structuring_element_arg), origin_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = erode_with_structure(*((RleCc*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg);
break;
case RLECC:
return_arg = erode_with_structure(*((RleCc*)self_arg), *((RleCc*)structuring_element_arg), origin_arg);
break;
case MLCC:
return_arg = erode_with_structure(*((RleCc*)self_arg), *((MlCc*)structuring_element_arg), origin_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'erode_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(structuring_element_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = erode_with_structure(*((MlCc*)self_arg), *((OneBitImageView*)structuring_element_arg), origin_arg);
break;
case CC:
return_arg = erode_with_structure(*((MlCc*)self_arg), *((Cc*)structuring_element_arg), origin_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = erode_with_structure(*((MlCc*)self_arg), *((OneBitRleImageView*)structuring_element_arg), origin_arg);
break;
case RLECC:
return_arg = erode_with_structure(*((MlCc*)self_arg), *((RleCc*)structuring_element_arg), origin_arg);
break;
case MLCC:
return_arg = erode_with_structure(*((MlCc*)self_arg), *((MlCc*)structuring_element_arg), origin_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'structuring_element' argument of 'erode_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(structuring_element_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'erode_with_structure' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
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
      
          static PyMethodDef _morphology_methods[] = {
                  {  "erode_dilate",
          call_erode_dilate, METH_VARARGS,
           "**erode_dilate** (int(0, 10) *ntimes* = 1, ``Choice`` [dilate|erode] *direction*, ``Choice`` [rectangular|octagonal] *shape*)\n\nMorphologically erodes or dilates the image with a rectangular or\nocagonal structuring element. For onebit images, this is simply a\nwrapper for erode_with_structure_ or dilate_with_structure_ with\nspecial cases for the structuring element.\n\nThe returned image is of the same size as the input image, which means\nthat border pixels are not dilated beyond the image dimensions. If you\nalso want the border pixels to be dilated, apply pad_image_ to the input\nimage beforehand.\n\n.. _pad_image: utility.html#pad-image\n.. _erode_with_structure: #erode-with-structure\n.. _dilate_with_structure: #dilate-with-structure\n\n*ntimes*\n  The number of times to perform the operation.\n*direction*\n  dilate (0)\n    increase the presence of black\n  erode (1)\n    decrease the presence of black\n*shape*\n  rectangular (0)\n    use a 3x3 rectangular morphology operator\n  octagonal (1)\n    use octagonal morphology operator by alternately using\n    a 3x3 cross and a 3x3 square structuring element"        },
                                            {  "despeckle",
          call_despeckle, METH_VARARGS,
           "**despeckle** (int(1, 100) *cc_size*)\n\nRemoves connected components that are smaller than the given size.\n\n*size*\n  The maximum number of pixels in each connected component that\n  will be removed.\n\nThis approach to finding connected components uses a pseudo-recursive\ndescent, which gets around the hard limit of ~64k connected components\nper page in ``cc_analysis``.  Unfortunately, this approach is much\nslower as the connected components get large, so *size* should be\nkept relatively small.\n\n*size* == 1 is a special case and runs much faster, since it does not\nrequire recursion."        },
                        {  "distance_transform",
          call_distance_transform, METH_VARARGS,
           "**distance_transform** (``Choice`` [chessboard|manhattan|euclidean] *norm*)\n\nFor all black pixels, the distance to the nearest white pixel is calculated.\nIn the destination image, all pixels corresponding to black pixels in the\ninput image will be assigned the their distance value, all pixels\ncorresponding to white pixels will be assigned 0.  The result is returned\nas a Float image.\n\n*norm*:\n\n  0: use chessboard distance (L-infinity norm)\n\n  1: use Manhattan distance (L1 norm)\n\n  2: use Euclidean distance (L2 norm)"        },
                        {  "dilate_with_structure",
          call_dilate_with_structure, METH_VARARGS,
           "**dilate_with_structure** (``Image`` [OneBit] *structuring_element*, ``Point`` *origin*, ``bool`` *only_border* = False)\n\nPerforms a binary morphological dilation with the given structuring\nelement.\n\nNote that it is necessary to specify which point in the\nstructuring element shall be treated as origin. This allows for\narbitrary structuring elements. Examples:\n\n.. code:: Python\n\n  # same as image.dilate()\n  structure = Image(Point(0,0), Point(2,2), ONEBIT)\n  structure.fill(1)\n  image = image.dilate_with_structure(structure, Point(1,1))\n\n  # same as image.erode_dilate(3,0,0)\n  structure = Image(Point(0,0), Point(6,6), ONEBIT)\n  structure.fill(1)\n  image = image.dilate_with_structure(structure, Point(3,3))\n\nThe implementation is straightforward and can be slow for large\nstructuring elements. If you know that your structuring element is\nconnected and its origin is black, you can set *only_border* to\n``True``, because in this case only the border pixels in the image\nneed to be considered which can speed up the dilation for some\nimages (though not for all).\n\nThe returned image is of the same size as the input image, which means\nthat border pixels are not dilated beyond the image dimensions. If you\nalso want the border pixels to be dilated, apply pad_image_ to the input\nimage beforehand.\n\n.. _pad_image: utility.html#pad-image\n\nReferences:\n\n  A proof that only the contour pixels need to be dilated for\n  connected structuring elements containing their origin is given\n  by Luc Vincent in *Morphological Transformations of Binary\n  Images with Arbitrary Structuring Elements*, Signal Processing,\n  Vol. 22, No. 1, pp. 3-23, January 1991 (see theorem 2.13)"        },
                        {  "erode_with_structure",
          call_erode_with_structure, METH_VARARGS,
           "**erode_with_structure** (``Image`` [OneBit] *structuring_element*, ``Point`` *origin*)\n\nPerforms a binary morphological erosion with the given structuring\nelement.\n\nNote that it is necessary to specify which point in the\nstructuring element shall be treated as origin. This allows for\narbitrary structuring elements.\n\nBorder pixels at which the structuring element extends beyond the\nimage dimensions are whitened. In other words the image is padded\nwith white pixels before erosion.\n\nExample:\n\n.. code:: Python\n\n  # same as image.erode()\n  structure = Image(Point(0,0), Point(2,2), ONEBIT)\n  structure.fill(1)\n  image = image.erode_with_structure(structure, Point(1,1))"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_morphologyDef = {
        PyModuleDef_HEAD_INIT,
        "_morphology",
        nullptr,
        -1,
        _morphology_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__morphology(void) {
    return PyModule_Create(&module_morphologyDef);
  }
  

