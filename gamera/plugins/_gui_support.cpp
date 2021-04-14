
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "gui_support.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_gui_support(void);
  }
#endif

                static PyObject* call_to_string(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_string"
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
return_arg = to_string(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_string(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_string(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_string(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_string(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = to_string(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = to_string(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
return_arg = to_string(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = to_string(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = to_string(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_string' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_to_buffer(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      PyObject* Buffer_arg;
PyObject* Buffer_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:to_buffer"
                        ,
             &self_pyarg                        ,
             &Buffer_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      Buffer_arg = Buffer_pyarg;      
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
to_buffer(*((OneBitImageView*)self_arg), Buffer_arg);
break;
case CC:
to_buffer(*((Cc*)self_arg), Buffer_arg);
break;
case ONEBITRLEIMAGEVIEW:
to_buffer(*((OneBitRleImageView*)self_arg), Buffer_arg);
break;
case RLECC:
to_buffer(*((RleCc*)self_arg), Buffer_arg);
break;
case MLCC:
to_buffer(*((MlCc*)self_arg), Buffer_arg);
break;
case GREYSCALEIMAGEVIEW:
to_buffer(*((GreyScaleImageView*)self_arg), Buffer_arg);
break;
case GREY16IMAGEVIEW:
to_buffer(*((Grey16ImageView*)self_arg), Buffer_arg);
break;
case RGBIMAGEVIEW:
to_buffer(*((RGBImageView*)self_arg), Buffer_arg);
break;
case FLOATIMAGEVIEW:
to_buffer(*((FloatImageView*)self_arg), Buffer_arg);
break;
case COMPLEXIMAGEVIEW:
to_buffer(*((ComplexImageView*)self_arg), Buffer_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_buffer' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                  Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_to_buffer_colorize(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      PyObject* Buffer_arg;
PyObject* Buffer_pyarg;
                      int red_arg;
                      int green_arg;
                      int blue_arg;
                      int invert_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOiiii:to_buffer_colorize"
                        ,
             &self_pyarg                        ,
             &Buffer_pyarg                        ,
             &red_arg                        ,
             &green_arg                        ,
             &blue_arg                        ,
             &invert_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      Buffer_arg = Buffer_pyarg;                                                              
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
to_buffer_colorize(*((OneBitImageView*)self_arg), Buffer_arg, red_arg, green_arg, blue_arg, invert_arg);
break;
case CC:
to_buffer_colorize(*((Cc*)self_arg), Buffer_arg, red_arg, green_arg, blue_arg, invert_arg);
break;
case ONEBITRLEIMAGEVIEW:
to_buffer_colorize(*((OneBitRleImageView*)self_arg), Buffer_arg, red_arg, green_arg, blue_arg, invert_arg);
break;
case RLECC:
to_buffer_colorize(*((RleCc*)self_arg), Buffer_arg, red_arg, green_arg, blue_arg, invert_arg);
break;
case MLCC:
to_buffer_colorize(*((MlCc*)self_arg), Buffer_arg, red_arg, green_arg, blue_arg, invert_arg);
break;
case GREYSCALEIMAGEVIEW:
to_buffer_colorize(*((GreyScaleImageView*)self_arg), Buffer_arg, red_arg, green_arg, blue_arg, invert_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_buffer_colorize' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, and GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                                          Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_color_ccs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int ignore_unlabeled_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:color_ccs"
                        ,
             &self_pyarg                        ,
             &ignore_unlabeled_arg                      ) <= 0)
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
return_arg = color_ccs(*((OneBitImageView*)self_arg), ignore_unlabeled_arg);
break;
case CC:
return_arg = color_ccs(*((Cc*)self_arg), ignore_unlabeled_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = color_ccs(*((OneBitRleImageView*)self_arg), ignore_unlabeled_arg);
break;
case RLECC:
return_arg = color_ccs(*((RleCc*)self_arg), ignore_unlabeled_arg);
break;
case MLCC:
return_arg = color_ccs(*((MlCc*)self_arg), ignore_unlabeled_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'color_ccs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_draw_cc(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* _00000000_arg;
PyObject* _00000000_pyarg;
                      int red_arg;
                      int green_arg;
                      int blue_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOiii:draw_cc"
                        ,
             &self_pyarg                        ,
             &_00000000_pyarg                        ,
             &red_arg                        ,
             &green_arg                        ,
             &blue_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(_00000000_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument '_00000000' must be an image");
          return 0;
        }
        _00000000_arg = ((Image*)((RectObject*)_00000000_pyarg)->m_x);
        image_get_fv(_00000000_pyarg, &_00000000_arg->features, &_00000000_arg->features_len);
                                                        
              try {
                      switch(get_image_combination(self_pyarg)) {
case RGBIMAGEVIEW:
switch(get_image_combination(_00000000_pyarg)) {
case ONEBITIMAGEVIEW:
draw_cc(*((RGBImageView*)self_arg), *((OneBitImageView*)_00000000_arg), red_arg, green_arg, blue_arg);
break;
case CC:
draw_cc(*((RGBImageView*)self_arg), *((Cc*)_00000000_arg), red_arg, green_arg, blue_arg);
break;
case ONEBITRLEIMAGEVIEW:
draw_cc(*((RGBImageView*)self_arg), *((OneBitRleImageView*)_00000000_arg), red_arg, green_arg, blue_arg);
break;
case RLECC:
draw_cc(*((RGBImageView*)self_arg), *((RleCc*)_00000000_arg), red_arg, green_arg, blue_arg);
break;
case MLCC:
draw_cc(*((RGBImageView*)self_arg), *((MlCc*)_00000000_arg), red_arg, green_arg, blue_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The '_00000000' argument of 'draw_cc' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(_00000000_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'draw_cc' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                        Py_XINCREF(Py_None);
          return Py_None;
                    }
      
          static PyMethodDef _gui_support_methods[] = {
                  {  "to_string",
          call_to_string, METH_VARARGS,
           "**to_string** ()\n\nEncodes the image into a 'string' required by wxImage.\n(i.e. 8-bit RGB triplets)."        },
                        {  "to_buffer",
          call_to_buffer, METH_VARARGS,
           "**to_buffer** (object *Buffer*)\n\nEncodes the image into a 'buffer' required by wx.Image.\n(i.e. 8-bit RGB triplets). If you need to convert a gamera image\n*scaled_image* to a wx.Bitmap, you can do so as follows:\n\n.. code:: Python\n    \n  wximg = wx.EmptyImage(scaled_image.ncols, scaled_image.nrows)\n  scaled_image.to_buffer(wximg.GetDataBuffer())\n  wxbmp = wx.BitmapFromImage(wximg)"        },
                        {  "to_buffer_colorize",
          call_to_buffer_colorize, METH_VARARGS,
           "**to_buffer_colorize** (object *Buffer*, int *red*, int *green*, int *blue*, ``bool`` *invert*)\n\nEncodes the image into a 'buffer' required by wxImage, and\napplies the given color to the foreground and background."        },
                        {  "color_ccs",
          call_color_ccs, METH_VARARGS,
           "**color_ccs** (``bool`` *ignore_unlabeled* = True)\n\nReturns an RGB image where each connected component of the\nimage is colored one of eight different colors.  This function can\nbe used to verify that ``cc_analysis`` is working correctly for your\nimage.\n\nIt should be noted that this coloring does not take care of\ncomponent adjacency. It may therefore happen that adjacent components\nobtain the same color. If this is not acceptable in your use case,\nhave a look at graph_color_ccs_ instead.\n\n.. _graph_color_ccs: color.html#graph-color-ccs\n\n*ignore_unlabeled*:\n  do not colorize unlabeled pixels (pixel value one), but leave them black\n\n.. note:: Connected component analysis must already be performed\n          on the image (using cc_analysis_, for example) in order\n          for this to work.\n      \n.. _cc_analysis: segmentation.html#cc-analysis\n\n**Example 1:**\n\n  .. image:: images/color_ccs.png"        },
                        {  "draw_cc",
          call_draw_cc, METH_VARARGS,
           "**draw_cc** (``Image`` [OneBit] *_00000000*, int *red*, int *green*, int *blue*)\n\nDraws a colored Cc over an already initialized wxImage buffer."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_gui_supportDef = {
        PyModuleDef_HEAD_INIT,
        "_gui_support",
        nullptr,
        -1,
        _gui_support_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__gui_support(void) {
    return PyModule_Create(&module_gui_supportDef);
  }
  

