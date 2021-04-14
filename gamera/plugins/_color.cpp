
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "color.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_color(void);
  }
#endif

                static PyObject* call_hue(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:hue"
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
case RGBIMAGEVIEW:
return_arg = hue(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'hue' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_saturation(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:saturation"
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
case RGBIMAGEVIEW:
return_arg = saturation(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'saturation' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_value(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:value"
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
case RGBIMAGEVIEW:
return_arg = value(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'value' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_cyan(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cyan"
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
case RGBIMAGEVIEW:
return_arg = cyan(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cyan' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_magenta(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:magenta"
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
case RGBIMAGEVIEW:
return_arg = magenta(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'magenta' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_yellow(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:yellow"
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
case RGBIMAGEVIEW:
return_arg = yellow(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'yellow' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_cie_x(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cie_x"
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
case RGBIMAGEVIEW:
return_arg = cie_x(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cie_x' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_cie_y(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cie_y"
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
case RGBIMAGEVIEW:
return_arg = cie_y(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cie_y' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_cie_z(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cie_z"
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
case RGBIMAGEVIEW:
return_arg = cie_z(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cie_z' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_cie_Lab_L(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cie_Lab_L"
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
case RGBIMAGEVIEW:
return_arg = cie_Lab_L(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cie_Lab_L' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_cie_Lab_a(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cie_Lab_a"
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
case RGBIMAGEVIEW:
return_arg = cie_Lab_a(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cie_Lab_a' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_cie_Lab_b(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:cie_Lab_b"
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
case RGBIMAGEVIEW:
return_arg = cie_Lab_b(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'cie_Lab_b' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_red(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:red"
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
case RGBIMAGEVIEW:
return_arg = red(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'red' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_green(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:green"
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
case RGBIMAGEVIEW:
return_arg = green(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'green' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_blue(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:blue"
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
case RGBIMAGEVIEW:
return_arg = blue(*((RGBImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'blue' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_false_color(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int colormap_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:false_color"
                        ,
             &self_pyarg                        ,
             &colormap_arg                      ) <= 0)
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
return_arg = false_color(*((GreyScaleImageView*)self_arg), colormap_arg);
break;
case FLOATIMAGEVIEW:
return_arg = false_color(*((FloatImageView*)self_arg), colormap_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'false_color' can not have pixel type '%s'. Acceptable values are GREYSCALE, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_colors_to_labels(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      PyObject* rgb_to_label_arg;
PyObject* rgb_to_label_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:colors_to_labels"
                        ,
             &self_pyarg                        ,
             &rgb_to_label_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      rgb_to_label_arg = rgb_to_label_pyarg;      
              try {
                      switch(get_image_combination(self_pyarg)) {
case RGBIMAGEVIEW:
return_arg = colors_to_labels(*((RGBImageView*)self_arg), rgb_to_label_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'colors_to_labels' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _color_methods[] = {
                  {  "hue",
          call_hue, METH_VARARGS,
           "**hue** ()\n\nReturns a FLOAT image where each pixel is a hue value in HSV space\nin range [0, 1).  Since the hue space is cyclic, the shortest\n*distance* between 1 and 0 is 0."        },
                        {  "saturation",
          call_saturation, METH_VARARGS,
           "**saturation** ()\n\nReturns a FLOAT image where each pixel is a saturation value in\nHSV space in range [0, 1]."        },
                        {  "value",
          call_value, METH_VARARGS,
           "**value** ()\n\nReturns a FLOAT image where each pixel is the value in\nHSV space in range [0, 1].  For more information, Google for HSV color\nspace."        },
                        {  "cyan",
          call_cyan, METH_VARARGS,
           "**cyan** ()\n\nReturns a GREYSCALE image where each pixel is the cyan component\nof the RGB original."        },
                        {  "magenta",
          call_magenta, METH_VARARGS,
           "**magenta** ()\n\nReturns a GREYSCALE image where each pixel is the magenta\ncomponent of the RGB original."        },
                        {  "yellow",
          call_yellow, METH_VARARGS,
           "**yellow** ()\n\nReturns a GREYSCALE image where each pixel is the yellow component\nof the RGB original."        },
                        {  "cie_x",
          call_cie_x, METH_VARARGS,
           "**cie_x** ()\n\nReturns a FLOAT image where each pixel is a *x* value in the `CIE\n1964 Colorimetric`__ system in range [0, 1).\n\n.. __: http://www.isc.tamu.edu/~astro/color/cie_xyz1964.html"        },
                        {  "cie_y",
          call_cie_y, METH_VARARGS,
           "**cie_y** ()\n\nReturns a FLOAT image where each pixel is a *y* value in the `CIE\n1964 Colorimetric`__ system in range [0, 1).\n\n.. __: http://www.isc.tamu.edu/~astro/color/cie_xyz1964.html"        },
                        {  "cie_z",
          call_cie_z, METH_VARARGS,
           "**cie_z** ()\n\nReturns a FLOAT image where each pixel is a *z* value in the `CIE\n1964 Colorimetric`__ system in range [0, 1).\n\n.. __: http://www.isc.tamu.edu/~astro/color/cie_xyz1964.html"        },
                        {  "cie_Lab_L",
          call_cie_Lab_L, METH_VARARGS,
           "**cie_Lab_L** ()\n\nReturns a FLOAT image where each pixel is an *L* value in the \nCIE L*a*b* color space. For an introduction to the different color\nspaces, see A. Ford and A. Roberts: `Color Space Concersions`__ (1998).\n\nThe present conversion uses the RGB to Lab conversion routine from VIGRA.\n\n.. __: http://www.poynton.com/PDFs/coloureq.pdf"        },
                        {  "cie_Lab_a",
          call_cie_Lab_a, METH_VARARGS,
           "**cie_Lab_a** ()\n\nReturns a FLOAT image where each pixel is an *a* value in the \nCIE L*a*b* color space. For an introduction to the different color\nspaces, see A. Ford and A. Roberts: `Color Space Concersions`__ (1998).\n\nThe present conversion uses the RGB to Lab conversion routine from VIGRA.\n\n.. __: http://www.poynton.com/PDFs/coloureq.pdf"        },
                        {  "cie_Lab_b",
          call_cie_Lab_b, METH_VARARGS,
           "**cie_Lab_b** ()\n\nReturns a FLOAT image where each pixel is a *b* value in the \nCIE L*a*b* color space. For an introduction to the different color\nspaces, see A. Ford and A. Roberts: `Color Space Concersions`__ (1998).\n\nThe present conversion uses the RGB to Lab conversion routine from VIGRA.\n\n.. __: http://www.poynton.com/PDFs/coloureq.pdf"        },
                        {  "red",
          call_red, METH_VARARGS,
           "**red** ()\n\nReturns a GREYSCALE image where each pixel is the red component of\nthe RGB original."        },
                        {  "green",
          call_green, METH_VARARGS,
           "**green** ()\n\nReturns a GREYSCALE image where each pixel is the green component\nof the original."        },
                        {  "blue",
          call_blue, METH_VARARGS,
           "**blue** ()\n\nReturns a GREYSCALE image where each pixel is the blue component\nof the RGB original."        },
                        {  "false_color",
          call_false_color, METH_VARARGS,
           "**false_color** (``Choice`` [diverging|rainbow] *colormap* = diverging)\n\nReturns a false color representation of the given image.\nThis can help visualize greyscale images that are not *real*\nimages but are representations of other kinds of data.\n\nThe option *colormap* specifies how the values are converted:\n\n 0: diverging colormap after Moreland with blue representing low, white representing mean, and red representing high values\n\n 1: rainbow colormap with blue representing low, green representing mean, and red representing high values\n\nNote that float images are scaled to the range [0,1], which means\nthat the highest value is always colored red and the lowest value blue.\nFor greyscale image no range stretching is done, so if you want this,\nyou must first convert the image to a float image.\n\nReference: K. Moreland:\n`Diverging Color Maps for Scientific Visualization.`__\n5th International Symposium on Visual Computing, 2009\n\n__ http://www.kennethmoreland.com/color-maps/"        },
                        {  "colors_to_labels",
          call_colors_to_labels, METH_VARARGS,
           "**colors_to_labels** (dict *rgb_to_label*)\n\nConverts an RGB image to a labeled onebit image.\n\nEach RGB color is replaced by the label specified in the mapping\n*rgb_to_label*. RGB values not listed in *rgb_to_label* are white\nin the returned onebit image. When no mapping *rgb_to_label* is\nprovided, each different RGB color is replaced by a unique label.\n\nThis is mostly useful for reading manually labeled groundtruth\ndata from color PNG files. Example:\n\n.. code:: Python\n\n  # map red to label 3, and green to label 5\n  labeled = rgb.colors_to_labels( {RGBPixel(255,0,0): 3, RGBPixel(0,255,0): 5} )\n\nA typical use case of this plugin is in combination\nwith ccs_from_labeled_image_.\n\n.. _ccs_from_labeled_image: utility.html#ccs-from-labeled-image"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_colorDef = {
        PyModuleDef_HEAD_INIT,
        "_color",
        nullptr,
        -1,
        _color_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__color(void) {
    return PyModule_Create(&module_colorDef);
  }
  

