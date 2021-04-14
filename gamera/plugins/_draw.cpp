
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "draw.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_draw(void);
  }
#endif

                static PyObject* call_draw_line(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatPoint start_arg;
PyObject* start_pyarg;
                      FloatPoint end_arg;
PyObject* end_pyarg;
                      PyObject* value_arg;
PyObject* value_pyarg;
                      double thickness_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOOOd:draw_line"
                        ,
             &self_pyarg                        ,
             &start_pyarg                        ,
             &end_pyarg                        ,
             &value_pyarg                        ,
             &thickness_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         start_arg = coerce_FloatPoint(start_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'start' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                    
      try {
         end_arg = coerce_FloatPoint(end_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'end' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                                        
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
draw_line(*((OneBitImageView*)self_arg), start_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case CC:
draw_line(*((Cc*)self_arg), start_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case ONEBITRLEIMAGEVIEW:
draw_line(*((OneBitRleImageView*)self_arg), start_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case RLECC:
draw_line(*((RleCc*)self_arg), start_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case MLCC:
draw_line(*((MlCc*)self_arg), start_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case GREYSCALEIMAGEVIEW:
draw_line(*((GreyScaleImageView*)self_arg), start_arg, end_arg, pixel_from_python<GreyScalePixel>::convert(value_pyarg), thickness_arg);
break;
case GREY16IMAGEVIEW:
draw_line(*((Grey16ImageView*)self_arg), start_arg, end_arg, pixel_from_python<Grey16Pixel>::convert(value_pyarg), thickness_arg);
break;
case RGBIMAGEVIEW:
draw_line(*((RGBImageView*)self_arg), start_arg, end_arg, pixel_from_python<RGBPixel>::convert(value_pyarg), thickness_arg);
break;
case FLOATIMAGEVIEW:
draw_line(*((FloatImageView*)self_arg), start_arg, end_arg, pixel_from_python<FloatPixel>::convert(value_pyarg), thickness_arg);
break;
case COMPLEXIMAGEVIEW:
draw_line(*((ComplexImageView*)self_arg), start_arg, end_arg, pixel_from_python<ComplexPixel>::convert(value_pyarg), thickness_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'draw_line' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                        Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_draw_bezier(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatPoint start_arg;
PyObject* start_pyarg;
                      FloatPoint c1_arg;
PyObject* c1_pyarg;
                      FloatPoint c2_arg;
PyObject* c2_pyarg;
                      FloatPoint end_arg;
PyObject* end_pyarg;
                      PyObject* value_arg;
PyObject* value_pyarg;
                      double accuracy_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOOOOOd:draw_bezier"
                        ,
             &self_pyarg                        ,
             &start_pyarg                        ,
             &c1_pyarg                        ,
             &c2_pyarg                        ,
             &end_pyarg                        ,
             &value_pyarg                        ,
             &accuracy_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         start_arg = coerce_FloatPoint(start_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'start' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                    
      try {
         c1_arg = coerce_FloatPoint(c1_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'c1' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                    
      try {
         c2_arg = coerce_FloatPoint(c2_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'c2' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                    
      try {
         end_arg = coerce_FloatPoint(end_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'end' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                                        
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
draw_bezier(*((OneBitImageView*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), accuracy_arg);
break;
case CC:
draw_bezier(*((Cc*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), accuracy_arg);
break;
case ONEBITRLEIMAGEVIEW:
draw_bezier(*((OneBitRleImageView*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), accuracy_arg);
break;
case RLECC:
draw_bezier(*((RleCc*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), accuracy_arg);
break;
case MLCC:
draw_bezier(*((MlCc*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), accuracy_arg);
break;
case GREYSCALEIMAGEVIEW:
draw_bezier(*((GreyScaleImageView*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<GreyScalePixel>::convert(value_pyarg), accuracy_arg);
break;
case GREY16IMAGEVIEW:
draw_bezier(*((Grey16ImageView*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<Grey16Pixel>::convert(value_pyarg), accuracy_arg);
break;
case RGBIMAGEVIEW:
draw_bezier(*((RGBImageView*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<RGBPixel>::convert(value_pyarg), accuracy_arg);
break;
case FLOATIMAGEVIEW:
draw_bezier(*((FloatImageView*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<FloatPixel>::convert(value_pyarg), accuracy_arg);
break;
case COMPLEXIMAGEVIEW:
draw_bezier(*((ComplexImageView*)self_arg), start_arg, c1_arg, c2_arg, end_arg, pixel_from_python<ComplexPixel>::convert(value_pyarg), accuracy_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'draw_bezier' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                                                            Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_draw_marker(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatPoint location_arg;
PyObject* location_pyarg;
                      int size_arg;
                      int style_arg;
                      PyObject* value_arg;
PyObject* value_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOiiO:draw_marker"
                        ,
             &self_pyarg                        ,
             &location_pyarg                        ,
             &size_arg                        ,
             &style_arg                        ,
             &value_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         location_arg = coerce_FloatPoint(location_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'location' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                                                      
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
draw_marker(*((OneBitImageView*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case CC:
draw_marker(*((Cc*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
draw_marker(*((OneBitRleImageView*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case RLECC:
draw_marker(*((RleCc*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case MLCC:
draw_marker(*((MlCc*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case GREYSCALEIMAGEVIEW:
draw_marker(*((GreyScaleImageView*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<GreyScalePixel>::convert(value_pyarg));
break;
case GREY16IMAGEVIEW:
draw_marker(*((Grey16ImageView*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<Grey16Pixel>::convert(value_pyarg));
break;
case RGBIMAGEVIEW:
draw_marker(*((RGBImageView*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<RGBPixel>::convert(value_pyarg));
break;
case FLOATIMAGEVIEW:
draw_marker(*((FloatImageView*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<FloatPixel>::convert(value_pyarg));
break;
case COMPLEXIMAGEVIEW:
draw_marker(*((ComplexImageView*)self_arg), location_arg, size_arg, style_arg, pixel_from_python<ComplexPixel>::convert(value_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'draw_marker' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                        Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_draw_hollow_rect(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatPoint ul_arg;
PyObject* ul_pyarg;
                      FloatPoint lr_arg;
PyObject* lr_pyarg;
                      PyObject* value_arg;
PyObject* value_pyarg;
                      double thickness_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOOOd:draw_hollow_rect"
                        ,
             &self_pyarg                        ,
             &ul_pyarg                        ,
             &lr_pyarg                        ,
             &value_pyarg                        ,
             &thickness_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         ul_arg = coerce_FloatPoint(ul_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'ul' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                    
      try {
         lr_arg = coerce_FloatPoint(lr_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'lr' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                                        
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
draw_hollow_rect(*((OneBitImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case CC:
draw_hollow_rect(*((Cc*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case ONEBITRLEIMAGEVIEW:
draw_hollow_rect(*((OneBitRleImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case RLECC:
draw_hollow_rect(*((RleCc*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case MLCC:
draw_hollow_rect(*((MlCc*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg);
break;
case GREYSCALEIMAGEVIEW:
draw_hollow_rect(*((GreyScaleImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<GreyScalePixel>::convert(value_pyarg), thickness_arg);
break;
case GREY16IMAGEVIEW:
draw_hollow_rect(*((Grey16ImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<Grey16Pixel>::convert(value_pyarg), thickness_arg);
break;
case RGBIMAGEVIEW:
draw_hollow_rect(*((RGBImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<RGBPixel>::convert(value_pyarg), thickness_arg);
break;
case FLOATIMAGEVIEW:
draw_hollow_rect(*((FloatImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<FloatPixel>::convert(value_pyarg), thickness_arg);
break;
case COMPLEXIMAGEVIEW:
draw_hollow_rect(*((ComplexImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<ComplexPixel>::convert(value_pyarg), thickness_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'draw_hollow_rect' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                        Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_draw_filled_rect(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatPoint ul_arg;
PyObject* ul_pyarg;
                      FloatPoint lr_arg;
PyObject* lr_pyarg;
                      PyObject* value_arg;
PyObject* value_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOOO:draw_filled_rect"
                        ,
             &self_pyarg                        ,
             &ul_pyarg                        ,
             &lr_pyarg                        ,
             &value_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         ul_arg = coerce_FloatPoint(ul_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'ul' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                    
      try {
         lr_arg = coerce_FloatPoint(lr_pyarg);
      } catch (const std::invalid_argumen&t e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'lr' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                          
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
draw_filled_rect(*((OneBitImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case CC:
draw_filled_rect(*((Cc*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
draw_filled_rect(*((OneBitRleImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case RLECC:
draw_filled_rect(*((RleCc*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case MLCC:
draw_filled_rect(*((MlCc*)self_arg), ul_arg, lr_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg));
break;
case GREYSCALEIMAGEVIEW:
draw_filled_rect(*((GreyScaleImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<GreyScalePixel>::convert(value_pyarg));
break;
case GREY16IMAGEVIEW:
draw_filled_rect(*((Grey16ImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<Grey16Pixel>::convert(value_pyarg));
break;
case RGBIMAGEVIEW:
draw_filled_rect(*((RGBImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<RGBPixel>::convert(value_pyarg));
break;
case FLOATIMAGEVIEW:
draw_filled_rect(*((FloatImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<FloatPixel>::convert(value_pyarg));
break;
case COMPLEXIMAGEVIEW:
draw_filled_rect(*((ComplexImageView*)self_arg), ul_arg, lr_arg, pixel_from_python<ComplexPixel>::convert(value_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'draw_filled_rect' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                      Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_flood_fill(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      Point start_arg;
PyObject* start_pyarg;
                      PyObject* color_arg;
PyObject* color_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOO:flood_fill"
                        ,
             &self_pyarg                        ,
             &start_pyarg                        ,
             &color_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         start_arg = coerce_Point(start_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'start' must be a Point, or convertible to a Point");
         return 0;
      }
                          
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
flood_fill(*((OneBitImageView*)self_arg), start_arg, pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case CC:
flood_fill(*((Cc*)self_arg), start_arg, pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
flood_fill(*((OneBitRleImageView*)self_arg), start_arg, pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case RLECC:
flood_fill(*((RleCc*)self_arg), start_arg, pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case MLCC:
flood_fill(*((MlCc*)self_arg), start_arg, pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case GREYSCALEIMAGEVIEW:
flood_fill(*((GreyScaleImageView*)self_arg), start_arg, pixel_from_python<GreyScalePixel>::convert(color_pyarg));
break;
case RGBIMAGEVIEW:
flood_fill(*((RGBImageView*)self_arg), start_arg, pixel_from_python<RGBPixel>::convert(color_pyarg));
break;
case FLOATIMAGEVIEW:
flood_fill(*((FloatImageView*)self_arg), start_arg, pixel_from_python<FloatPixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'flood_fill' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_remove_border(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:remove_border"
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
remove_border(*((OneBitImageView*)self_arg));
break;
case CC:
remove_border(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
remove_border(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
remove_border(*((RleCc*)self_arg));
break;
case MLCC:
remove_border(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'remove_border' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_highlight(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* cc_arg;
PyObject* cc_pyarg;
                      PyObject* color_arg;
PyObject* color_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOO:highlight"
                        ,
             &self_pyarg                        ,
             &cc_pyarg                        ,
             &color_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(cc_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'cc' must be an image");
          return 0;
        }
        cc_arg = ((Image*)((RectObject*)cc_pyarg)->m_x);
        image_get_fv(cc_pyarg, &cc_arg->features, &cc_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(cc_pyarg)) {
case ONEBITIMAGEVIEW:
highlight(*((OneBitImageView*)self_arg), *((OneBitImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case CC:
highlight(*((OneBitImageView*)self_arg), *((Cc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
highlight(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case RLECC:
highlight(*((OneBitImageView*)self_arg), *((RleCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case MLCC:
highlight(*((OneBitImageView*)self_arg), *((MlCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'cc' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(cc_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(cc_pyarg)) {
case ONEBITIMAGEVIEW:
highlight(*((Cc*)self_arg), *((OneBitImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case CC:
highlight(*((Cc*)self_arg), *((Cc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
highlight(*((Cc*)self_arg), *((OneBitRleImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case RLECC:
highlight(*((Cc*)self_arg), *((RleCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case MLCC:
highlight(*((Cc*)self_arg), *((MlCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'cc' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(cc_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(cc_pyarg)) {
case ONEBITIMAGEVIEW:
highlight(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case CC:
highlight(*((OneBitRleImageView*)self_arg), *((Cc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
highlight(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case RLECC:
highlight(*((OneBitRleImageView*)self_arg), *((RleCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case MLCC:
highlight(*((OneBitRleImageView*)self_arg), *((MlCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'cc' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(cc_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(cc_pyarg)) {
case ONEBITIMAGEVIEW:
highlight(*((RleCc*)self_arg), *((OneBitImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case CC:
highlight(*((RleCc*)self_arg), *((Cc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
highlight(*((RleCc*)self_arg), *((OneBitRleImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case RLECC:
highlight(*((RleCc*)self_arg), *((RleCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case MLCC:
highlight(*((RleCc*)self_arg), *((MlCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'cc' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(cc_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(cc_pyarg)) {
case ONEBITIMAGEVIEW:
highlight(*((MlCc*)self_arg), *((OneBitImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case CC:
highlight(*((MlCc*)self_arg), *((Cc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
highlight(*((MlCc*)self_arg), *((OneBitRleImageView*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case RLECC:
highlight(*((MlCc*)self_arg), *((RleCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
case MLCC:
highlight(*((MlCc*)self_arg), *((MlCc*)cc_arg), pixel_from_python<OneBitPixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'cc' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(cc_pyarg));
return 0;
}
break;
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(cc_pyarg)) {
case ONEBITIMAGEVIEW:
highlight(*((GreyScaleImageView*)self_arg), *((OneBitImageView*)cc_arg), pixel_from_python<GreyScalePixel>::convert(color_pyarg));
break;
case CC:
highlight(*((GreyScaleImageView*)self_arg), *((Cc*)cc_arg), pixel_from_python<GreyScalePixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
highlight(*((GreyScaleImageView*)self_arg), *((OneBitRleImageView*)cc_arg), pixel_from_python<GreyScalePixel>::convert(color_pyarg));
break;
case RLECC:
highlight(*((GreyScaleImageView*)self_arg), *((RleCc*)cc_arg), pixel_from_python<GreyScalePixel>::convert(color_pyarg));
break;
case MLCC:
highlight(*((GreyScaleImageView*)self_arg), *((MlCc*)cc_arg), pixel_from_python<GreyScalePixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'cc' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(cc_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(cc_pyarg)) {
case ONEBITIMAGEVIEW:
highlight(*((RGBImageView*)self_arg), *((OneBitImageView*)cc_arg), pixel_from_python<RGBPixel>::convert(color_pyarg));
break;
case CC:
highlight(*((RGBImageView*)self_arg), *((Cc*)cc_arg), pixel_from_python<RGBPixel>::convert(color_pyarg));
break;
case ONEBITRLEIMAGEVIEW:
highlight(*((RGBImageView*)self_arg), *((OneBitRleImageView*)cc_arg), pixel_from_python<RGBPixel>::convert(color_pyarg));
break;
case RLECC:
highlight(*((RGBImageView*)self_arg), *((RleCc*)cc_arg), pixel_from_python<RGBPixel>::convert(color_pyarg));
break;
case MLCC:
highlight(*((RGBImageView*)self_arg), *((MlCc*)cc_arg), pixel_from_python<RGBPixel>::convert(color_pyarg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'cc' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(cc_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'highlight' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, and RGB.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_draw_circle(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatPoint c_arg;
PyObject* c_pyarg;
                      double r_arg;
                      PyObject* value_arg;
PyObject* value_pyarg;
                      double thickness_arg;
                      double accuracy_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOdOdd:draw_circle"
                        ,
             &self_pyarg                        ,
             &c_pyarg                        ,
             &r_arg                        ,
             &value_pyarg                        ,
             &thickness_arg                        ,
             &accuracy_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         c_arg = coerce_FloatPoint(c_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'c' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                                                                    
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
draw_circle(*((OneBitImageView*)self_arg), c_arg, r_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case CC:
draw_circle(*((Cc*)self_arg), c_arg, r_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case ONEBITRLEIMAGEVIEW:
draw_circle(*((OneBitRleImageView*)self_arg), c_arg, r_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case RLECC:
draw_circle(*((RleCc*)self_arg), c_arg, r_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case MLCC:
draw_circle(*((MlCc*)self_arg), c_arg, r_arg, pixel_from_python<OneBitPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case GREYSCALEIMAGEVIEW:
draw_circle(*((GreyScaleImageView*)self_arg), c_arg, r_arg, pixel_from_python<GreyScalePixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case GREY16IMAGEVIEW:
draw_circle(*((Grey16ImageView*)self_arg), c_arg, r_arg, pixel_from_python<Grey16Pixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case RGBIMAGEVIEW:
draw_circle(*((RGBImageView*)self_arg), c_arg, r_arg, pixel_from_python<RGBPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case FLOATIMAGEVIEW:
draw_circle(*((FloatImageView*)self_arg), c_arg, r_arg, pixel_from_python<FloatPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
case COMPLEXIMAGEVIEW:
draw_circle(*((ComplexImageView*)self_arg), c_arg, r_arg, pixel_from_python<ComplexPixel>::convert(value_pyarg), thickness_arg, accuracy_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'draw_circle' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                                          Py_XINCREF(Py_None);
          return Py_None;
                    }
            
          static PyMethodDef _draw_methods[] = {
                  {  "draw_line",
          call_draw_line, METH_VARARGS,
           "**draw_line** (``FloatPoint`` *start*, ``FloatPoint`` *end*, Pixel *value*, float *thickness*)\n\nDraws a straight line between two points.\n\nCoordinates are absolute and *not* relative to the offset of the image.\nTherefore, if the image offset is (5, 5), a line at (5, 5) will be\nin the upper left hand corner of the image.\n\n*a*:\n  The start ``FloatPoint``.\n\n*b*:\n  The end ``FloatPoint``.\n\n*value*:\n  The pixel value to set for the line.\n\n*thickness* = 1.0:\n  The thickness of the line (in pixels)\n\nThe implementation is based on the classic Bresenham algorithm, as described\nin J. E. Bresenham: *Algorithm for computer control of a digital plotter.*\nIBM Systems Journal 4, pp. 25-30 (1965)."        },
                        {  "draw_bezier",
          call_draw_bezier, METH_VARARGS,
           "**draw_bezier** (``FloatPoint`` *start*, ``FloatPoint`` *c1*, ``FloatPoint`` *c2*, ``FloatPoint`` *end*, Pixel *value*, float *accuracy* = 0.10)\n\nDraws a cubic bezier curve\n\nCoordinates are absolute and *not* relative to the offset of the image.\nTherefore, if the image offset is (5, 5), a curve at (5, 5) will be in\nthe upper left hand corner of the image.\n\n*start*:\n  The start ``FloatPoint``.\n\n*c1*:\n  The control point associated with the start point.\n\n*c2*\n  The control point associated with the end point.\n\n*end*\n  The end ``FloatPoint``.\n\n*value*:\n  The pixel value to set for the curve.\n\n*accuracy* = ``0.1``:\n  The rendering accuracy (in pixels)"        },
                        {  "draw_marker",
          call_draw_marker, METH_VARARGS,
           "**draw_marker** (``FloatPoint`` *location*, int *size* = 5, ``Choice`` [+|x|hollow_square|filled_square] *style* = +, Pixel *value*)\n\nDraws a marker at a given point.\n\nCoordinates are absolute and *not* relative to the offset of the image.\nTherefore, if the image offset is (5, 5), a marker at (5, 5)\nwill be in the upper left hand corner of the image.\n\n*a*\n  The position of the marker.\n\n*size*\n  The size of the marker (number of pixels)\n\n*style*\n  PLUS + (0)\n\n  X + (1)\n\n  HOLLOW_SQUARE (2)\n\n  FILLED_SQUARE (3)\n\n*value*\n  The pixel value to set for the line."        },
                        {  "draw_hollow_rect",
          call_draw_hollow_rect, METH_VARARGS,
           "**draw_hollow_rect** (``FloatPoint`` *ul*, ``FloatPoint`` *lr*, Pixel *value*, float *thickness*)\n\nDraws a hollow rectangle.\n\nCoordinates are absolute and *not* relative to the offset of the image.\nTherefore, if the image offset is (5, 5), a rectangle at (5, 5) will be\nin the upper left hand corner of the image.\n\nThe coordinates can be specified either by two FloatPoints or one\nRect:\n\n  **draw_hollow_rect** (FloatPoint(*x1*, *y1*), FloatPoint(*x2*,\n  *y2*), *value*, *thickness* = 1.0)\n\n  **draw_hollow_rect** (Rect *rect*, *value*, *thickness* = 1.0)\n\n*value*:\n  The pixel value to set for the lines.\n\n*thickness* = 1.0:\n  The thickness of the outline"        },
                        {  "draw_filled_rect",
          call_draw_filled_rect, METH_VARARGS,
           "**draw_filled_rect** (``FloatPoint`` *ul*, ``FloatPoint`` *lr*, Pixel *value*)\n\nDraws a filled rectangle.\n\nCoordinates are absolute and *not* relative to the offset of the image.\nTherefore, if the image offset is (5, 5), a rectangle at (5, 5) will\nbe in the upper left hand corner of the image.\n\nThe coordinates can be specified either by four integers, two\nFloatPoints, or one Rect:\n\n**draw_filled_rect** (FloatPoint(*x1*, *y1*), FloatPoint(*x2*,\n*y2*), *value*)\n\n**draw_filled_rect** (Rect *rect*, *value*)"        },
                        {  "flood_fill",
          call_flood_fill, METH_VARARGS,
           "**flood_fill** (``Point`` *start*, Pixel *color*)\n\nFlood fills from the given point using the given color.  This is similar\nto the \"bucket\" tool found in many paint programs.\n\nThe coordinates can be specified either by two integers or one Point:\n\n*a*:\n  The start ``Point``.\n\n*color*:\n  The pixel value to set for the rectangle."        },
                        {  "remove_border",
          call_remove_border, METH_VARARGS,
           "**remove_border** ()\n\nThis is a special case of the flood_fill algorithm that is designed\nto remove dark borders produced by photocopiers or flatbed scanners\naround the border of the image."        },
                        {  "highlight",
          call_highlight, METH_VARARGS,
           "**highlight** (``Image`` [OneBit] *cc*, Pixel *color*)\n\nHighlights all pixels on an image in given color that are black in the\npassed connected component. The connected component can be part of a\ndifferent image, it must however lie within the image region.\n\n*cc*\n  A one-bit connected component from the image\n\n*color*\n  A color value (RGBPixel, 0-255, or [0|1], depending on the image\n  type) used to color the *cc*."        },
                        {  "draw_circle",
          call_draw_circle, METH_VARARGS,
           "**draw_circle** (``FloatPoint`` *c*, float *r*, Pixel *value*, float *thickness*, float *accuracy*)\n\nDraws a center centered at *c* with radius *r*.\n\nCoordinates are absolute and *not* relative to the offset of the image.\nTherefore, if the image offset is (5, 5), a line at (5, 5) will be\nin the upper left hand corner of the image.\n\n*c*:\n  The center of the circle\n\n*r*:\n  The radius of the circle\n\n*value*:\n  The pixel value to set for the line.\n\n*thickness* = 1.0:\n  The thickness of the circle (in pixels)\n\n*accuracy* = 0.1:\n  The accuracy of the circle drawing\n\n  Based on the \"approximating a circle with Bezier curves\" approach.\n  http://www.whizkidtech.redprince.net/bezier/circle/"        },
                        { nullptr }
  };
  
  static struct PyModuleDef module_drawDef = {
        PyModuleDef_HEAD_INIT,
        "_draw",
        nullptr,
        -1,
        _draw_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__draw(void) {
    return PyModule_Create(&module_drawDef);
  }
  

