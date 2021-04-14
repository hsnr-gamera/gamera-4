
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "transformation.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_transformation(void);
  }
#endif

                static PyObject* call_rotate(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double angle_arg;
                      PyObject* bgcolor_arg;
PyObject* bgcolor_pyarg;
                      int order_arg;
      
                                      if (PyArg_ParseTuple(args,  "OdOi:rotate"
                        ,
             &self_pyarg                        ,
             &angle_arg                        ,
             &bgcolor_pyarg                        ,
             &order_arg                      ) <= 0)
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
return_arg = rotate(*((OneBitImageView*)self_arg), angle_arg, pixel_from_python<OneBitPixel>::convert(bgcolor_pyarg), order_arg);
break;
case CC:
return_arg = rotate(*((Cc*)self_arg), angle_arg, pixel_from_python<OneBitPixel>::convert(bgcolor_pyarg), order_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = rotate(*((OneBitRleImageView*)self_arg), angle_arg, pixel_from_python<OneBitPixel>::convert(bgcolor_pyarg), order_arg);
break;
case RLECC:
return_arg = rotate(*((RleCc*)self_arg), angle_arg, pixel_from_python<OneBitPixel>::convert(bgcolor_pyarg), order_arg);
break;
case MLCC:
return_arg = rotate(*((MlCc*)self_arg), angle_arg, pixel_from_python<OneBitPixel>::convert(bgcolor_pyarg), order_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = rotate(*((GreyScaleImageView*)self_arg), angle_arg, pixel_from_python<GreyScalePixel>::convert(bgcolor_pyarg), order_arg);
break;
case GREY16IMAGEVIEW:
return_arg = rotate(*((Grey16ImageView*)self_arg), angle_arg, pixel_from_python<Grey16Pixel>::convert(bgcolor_pyarg), order_arg);
break;
case RGBIMAGEVIEW:
return_arg = rotate(*((RGBImageView*)self_arg), angle_arg, pixel_from_python<RGBPixel>::convert(bgcolor_pyarg), order_arg);
break;
case FLOATIMAGEVIEW:
return_arg = rotate(*((FloatImageView*)self_arg), angle_arg, pixel_from_python<FloatPixel>::convert(bgcolor_pyarg), order_arg);
break;
case COMPLEXIMAGEVIEW:
return_arg = rotate(*((ComplexImageView*)self_arg), angle_arg, pixel_from_python<ComplexPixel>::convert(bgcolor_pyarg), order_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'rotate' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_resize(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Dim dim_arg;
PyObject* dim_pyarg;
                      int interp_type_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:resize"
                        ,
             &self_pyarg                        ,
             &dim_pyarg                        ,
             &interp_type_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      if (!is_DimObject(dim_pyarg)) {
        PyErr_SetString(PyExc_TypeError, "Argument 'dim' must be a Dim object");
        return 0;
      }
      dim_arg = *((Dim*)((DimObject*)dim_pyarg)->m_x);                    
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = resize(*((OneBitImageView*)self_arg), dim_arg, interp_type_arg);
break;
case CC:
return_arg = resize(*((Cc*)self_arg), dim_arg, interp_type_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = resize(*((OneBitRleImageView*)self_arg), dim_arg, interp_type_arg);
break;
case RLECC:
return_arg = resize(*((RleCc*)self_arg), dim_arg, interp_type_arg);
break;
case MLCC:
return_arg = resize(*((MlCc*)self_arg), dim_arg, interp_type_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = resize(*((GreyScaleImageView*)self_arg), dim_arg, interp_type_arg);
break;
case GREY16IMAGEVIEW:
return_arg = resize(*((Grey16ImageView*)self_arg), dim_arg, interp_type_arg);
break;
case RGBIMAGEVIEW:
return_arg = resize(*((RGBImageView*)self_arg), dim_arg, interp_type_arg);
break;
case FLOATIMAGEVIEW:
return_arg = resize(*((FloatImageView*)self_arg), dim_arg, interp_type_arg);
break;
case COMPLEXIMAGEVIEW:
return_arg = resize(*((ComplexImageView*)self_arg), dim_arg, interp_type_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'resize' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_scale(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double scaling_arg;
                      int interp_type_arg;
      
                                      if (PyArg_ParseTuple(args,  "Odi:scale"
                        ,
             &self_pyarg                        ,
             &scaling_arg                        ,
             &interp_type_arg                      ) <= 0)
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
return_arg = scale(*((OneBitImageView*)self_arg), scaling_arg, interp_type_arg);
break;
case CC:
return_arg = scale(*((Cc*)self_arg), scaling_arg, interp_type_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = scale(*((OneBitRleImageView*)self_arg), scaling_arg, interp_type_arg);
break;
case RLECC:
return_arg = scale(*((RleCc*)self_arg), scaling_arg, interp_type_arg);
break;
case MLCC:
return_arg = scale(*((MlCc*)self_arg), scaling_arg, interp_type_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = scale(*((GreyScaleImageView*)self_arg), scaling_arg, interp_type_arg);
break;
case GREY16IMAGEVIEW:
return_arg = scale(*((Grey16ImageView*)self_arg), scaling_arg, interp_type_arg);
break;
case RGBIMAGEVIEW:
return_arg = scale(*((RGBImageView*)self_arg), scaling_arg, interp_type_arg);
break;
case FLOATIMAGEVIEW:
return_arg = scale(*((FloatImageView*)self_arg), scaling_arg, interp_type_arg);
break;
case COMPLEXIMAGEVIEW:
return_arg = scale(*((ComplexImageView*)self_arg), scaling_arg, interp_type_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'scale' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_shear_row(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      int row_arg;
                      int distance_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:shear_row"
                        ,
             &self_pyarg                        ,
             &row_arg                        ,
             &distance_arg                      ) <= 0)
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
shear_row(*((OneBitImageView*)self_arg), row_arg, distance_arg);
break;
case CC:
shear_row(*((Cc*)self_arg), row_arg, distance_arg);
break;
case ONEBITRLEIMAGEVIEW:
shear_row(*((OneBitRleImageView*)self_arg), row_arg, distance_arg);
break;
case RLECC:
shear_row(*((RleCc*)self_arg), row_arg, distance_arg);
break;
case MLCC:
shear_row(*((MlCc*)self_arg), row_arg, distance_arg);
break;
case GREYSCALEIMAGEVIEW:
shear_row(*((GreyScaleImageView*)self_arg), row_arg, distance_arg);
break;
case GREY16IMAGEVIEW:
shear_row(*((Grey16ImageView*)self_arg), row_arg, distance_arg);
break;
case RGBIMAGEVIEW:
shear_row(*((RGBImageView*)self_arg), row_arg, distance_arg);
break;
case FLOATIMAGEVIEW:
shear_row(*((FloatImageView*)self_arg), row_arg, distance_arg);
break;
case COMPLEXIMAGEVIEW:
shear_row(*((ComplexImageView*)self_arg), row_arg, distance_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'shear_row' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_shear_column(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      int column_arg;
                      int distance_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:shear_column"
                        ,
             &self_pyarg                        ,
             &column_arg                        ,
             &distance_arg                      ) <= 0)
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
shear_column(*((OneBitImageView*)self_arg), column_arg, distance_arg);
break;
case CC:
shear_column(*((Cc*)self_arg), column_arg, distance_arg);
break;
case ONEBITRLEIMAGEVIEW:
shear_column(*((OneBitRleImageView*)self_arg), column_arg, distance_arg);
break;
case RLECC:
shear_column(*((RleCc*)self_arg), column_arg, distance_arg);
break;
case MLCC:
shear_column(*((MlCc*)self_arg), column_arg, distance_arg);
break;
case GREYSCALEIMAGEVIEW:
shear_column(*((GreyScaleImageView*)self_arg), column_arg, distance_arg);
break;
case GREY16IMAGEVIEW:
shear_column(*((Grey16ImageView*)self_arg), column_arg, distance_arg);
break;
case RGBIMAGEVIEW:
shear_column(*((RGBImageView*)self_arg), column_arg, distance_arg);
break;
case FLOATIMAGEVIEW:
shear_column(*((FloatImageView*)self_arg), column_arg, distance_arg);
break;
case COMPLEXIMAGEVIEW:
shear_column(*((ComplexImageView*)self_arg), column_arg, distance_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'shear_column' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_mirror_horizontal(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:mirror_horizontal"
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
mirror_horizontal(*((OneBitImageView*)self_arg));
break;
case CC:
mirror_horizontal(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
mirror_horizontal(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
mirror_horizontal(*((RleCc*)self_arg));
break;
case MLCC:
mirror_horizontal(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
mirror_horizontal(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
mirror_horizontal(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
mirror_horizontal(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
mirror_horizontal(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
mirror_horizontal(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'mirror_horizontal' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_mirror_vertical(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:mirror_vertical"
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
mirror_vertical(*((OneBitImageView*)self_arg));
break;
case CC:
mirror_vertical(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
mirror_vertical(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
mirror_vertical(*((RleCc*)self_arg));
break;
case MLCC:
mirror_vertical(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
mirror_vertical(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
mirror_vertical(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
mirror_vertical(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
mirror_vertical(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
mirror_vertical(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'mirror_vertical' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_grey_convert(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      IntVector* newgrey_arg;
PyObject* newgrey_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:grey_convert"
                        ,
             &self_pyarg                        ,
             &newgrey_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      newgrey_arg = IntVector_from_python(newgrey_pyarg);
      if (newgrey_arg == NULL) return 0;
            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
return_arg = grey_convert(*((GreyScaleImageView*)self_arg), newgrey_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'grey_convert' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete newgrey_arg;                                      if (return_arg== nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              return_pyarg = create_ImageObject(return_arg);              return return_pyarg;
            }
                              }
      
          static PyMethodDef _transformation_methods[] = {
                  {  "rotate",
          call_rotate, METH_VARARGS,
           "**rotate** (float(-180.00, 180.00) *angle*, Pixel *bgcolor* = None, int(1, 3) *order* = 1)\n\nRotates an image.\n\n*angle*\n  The angle of rotation (in degrees)\n\n*bgcolor*\n  The color to use for pixels outside of the original image bounds.\n  When *bgcolor* is ``None``, white is used.\n\n*order*\n  The order of the spline used for interpolation.  Must be between 1 - 3."        },
                        {  "resize",
          call_resize, METH_VARARGS,
           "**resize** (``Dim`` *dim*, ``Choice`` [None|Linear|Spline] *interp_type*)\n\nReturns a resized copy of an image. In addition to size, the type\nof interpolation can be specified, with a tradeoff between speed\nand quality.\n\nIf you need to maintain the aspect ratio of the original image,\nconsider using scale_ instead.\n\n*dim*\n  The size of the resulting image.\n\n*interp_type* [None|Linear|Spline]\n  The type of interpolation used to resize the image.  Each option\n  is progressively higher quality, yet slower.\n\n.. _scale: #scale"        },
                        {  "scale",
          call_scale, METH_VARARGS,
           "**scale** (float *scaling*, ``Choice`` [None|Linear|Spline] *interp_type*)\n\nReturns a scaled copy of the image. In addition to scale, the type\nof interpolation can be specified, with a tradeoff between speed\nand quality.\n\nIf you need to change the aspect ratio of the original image,\nconsider using resize_ instead.\n\n*scale*\n  A scaling factor.  Values greater than 1 will result in a larger image.\n  Values less than 1 will result in a smaller image.\n\n*interp_type* [None|Linear|Spline]\n  The type of interpolation used to resize the image.  Each option is\n  progressively higher quality, yet slower.\n\n.. _resize: #resize"        },
                        {  "shear_row",
          call_shear_row, METH_VARARGS,
           "**shear_row** (int *row*, int *distance*)\n\nShears a given row by a given amount.\n\n*row*\n  The row number to shear.\n\n*distance*\n  The number of pixels to move the row.  Positive values\n  move the row to the right.  Negative values move the row\n  to the left."        },
                        {  "shear_column",
          call_shear_column, METH_VARARGS,
           "**shear_column** (int *column*, int *distance*)\n\nShears a given column by a given amount.\n\n*column*\n  The column number to shear.\n\n*distance*\n  The number of pixels to move the column.  Positive values\n  move the column downward.  Negative values move the column\n  upward."        },
                        {  "mirror_horizontal",
          call_mirror_horizontal, METH_VARARGS,
           "**mirror_horizontal** ()\n\nFlips the image across the horizontal (*x*) axis."        },
                        {  "mirror_vertical",
          call_mirror_vertical, METH_VARARGS,
           "**mirror_vertical** ()\n\nFlips the image across the vertical (*y*) axis."        },
                        {  "grey_convert",
          call_grey_convert, METH_VARARGS,
           "**grey_convert** (``IntVector`` *newgrey*)\n\nConverts grey values to the new values provided in the vector *newgrey*,\ni.e. *val* is replaced by *newgrey[val]*.\n\nAs this is only implemented for greyscale images, the vector *newgrey*\nmust be of size 256 and all entries must be in [0,255]."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_transformationDef = {
        PyModuleDef_HEAD_INIT,
        "_transformation",
        nullptr,
        -1,
        _transformation_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__transformation(void) {
    return PyModule_Create(&module_transformationDef);
  }
  

