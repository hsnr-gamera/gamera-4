
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "convolution.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_convolution(void);
  }
#endif

                static PyObject* call_convolve(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* kernel_arg;
PyObject* kernel_pyarg;
                      int border_treatment_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:convolve"
                        ,
             &self_pyarg                        ,
             &kernel_pyarg                        ,
             &border_treatment_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(kernel_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'kernel' must be an image");
          return 0;
        }
        kernel_arg = ((Image*)((RectObject*)kernel_pyarg)->m_x);
        image_get_fv(kernel_pyarg, &kernel_arg->features, &kernel_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(kernel_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve(*((GreyScaleImageView*)self_arg), *((FloatImageView*)kernel_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel' argument of 'convolve' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(kernel_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve(*((Grey16ImageView*)self_arg), *((FloatImageView*)kernel_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel' argument of 'convolve' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(kernel_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve(*((RGBImageView*)self_arg), *((FloatImageView*)kernel_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel' argument of 'convolve' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(kernel_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve(*((FloatImageView*)self_arg), *((FloatImageView*)kernel_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel' argument of 'convolve' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_pyarg));
return 0;
}
break;
case COMPLEXIMAGEVIEW:
switch(get_image_combination(kernel_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve(*((ComplexImageView*)self_arg), *((FloatImageView*)kernel_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel' argument of 'convolve' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'convolve' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                      static PyObject* call_convolve_x(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* kernel_x_arg;
PyObject* kernel_x_pyarg;
                      int border_treatment_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:convolve_x"
                        ,
             &self_pyarg                        ,
             &kernel_x_pyarg                        ,
             &border_treatment_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(kernel_x_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'kernel_x' must be an image");
          return 0;
        }
        kernel_x_arg = ((Image*)((RectObject*)kernel_x_pyarg)->m_x);
        image_get_fv(kernel_x_pyarg, &kernel_x_arg->features, &kernel_x_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(kernel_x_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_x(*((GreyScaleImageView*)self_arg), *((FloatImageView*)kernel_x_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_x' argument of 'convolve_x' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_x_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(kernel_x_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_x(*((Grey16ImageView*)self_arg), *((FloatImageView*)kernel_x_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_x' argument of 'convolve_x' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_x_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(kernel_x_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_x(*((RGBImageView*)self_arg), *((FloatImageView*)kernel_x_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_x' argument of 'convolve_x' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_x_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(kernel_x_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_x(*((FloatImageView*)self_arg), *((FloatImageView*)kernel_x_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_x' argument of 'convolve_x' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_x_pyarg));
return 0;
}
break;
case COMPLEXIMAGEVIEW:
switch(get_image_combination(kernel_x_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_x(*((ComplexImageView*)self_arg), *((FloatImageView*)kernel_x_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_x' argument of 'convolve_x' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_x_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'convolve_x' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_convolve_y(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* kernel_y_arg;
PyObject* kernel_y_pyarg;
                      int border_treatment_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:convolve_y"
                        ,
             &self_pyarg                        ,
             &kernel_y_pyarg                        ,
             &border_treatment_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(kernel_y_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'kernel_y' must be an image");
          return 0;
        }
        kernel_y_arg = ((Image*)((RectObject*)kernel_y_pyarg)->m_x);
        image_get_fv(kernel_y_pyarg, &kernel_y_arg->features, &kernel_y_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case GREYSCALEIMAGEVIEW:
switch(get_image_combination(kernel_y_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_y(*((GreyScaleImageView*)self_arg), *((FloatImageView*)kernel_y_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_y' argument of 'convolve_y' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_y_pyarg));
return 0;
}
break;
case GREY16IMAGEVIEW:
switch(get_image_combination(kernel_y_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_y(*((Grey16ImageView*)self_arg), *((FloatImageView*)kernel_y_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_y' argument of 'convolve_y' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_y_pyarg));
return 0;
}
break;
case RGBIMAGEVIEW:
switch(get_image_combination(kernel_y_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_y(*((RGBImageView*)self_arg), *((FloatImageView*)kernel_y_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_y' argument of 'convolve_y' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_y_pyarg));
return 0;
}
break;
case FLOATIMAGEVIEW:
switch(get_image_combination(kernel_y_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_y(*((FloatImageView*)self_arg), *((FloatImageView*)kernel_y_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_y' argument of 'convolve_y' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_y_pyarg));
return 0;
}
break;
case COMPLEXIMAGEVIEW:
switch(get_image_combination(kernel_y_pyarg)) {
case FLOATIMAGEVIEW:
return_arg = convolve_y(*((ComplexImageView*)self_arg), *((FloatImageView*)kernel_y_arg), border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'kernel_y' argument of 'convolve_y' can not have pixel type '%s'. Acceptable value is FLOAT.", get_pixel_type_name(kernel_y_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'convolve_y' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_GaussianKernel(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          double standard_deviation_arg;
      
                                      if (PyArg_ParseTuple(args,  "d:GaussianKernel"
                        ,
             &standard_deviation_arg                      ) <= 0)
           return 0;
               
                    
              try {
                      return_arg = GaussianKernel(standard_deviation_arg);
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
                static PyObject* call_GaussianDerivativeKernel(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          double standard_deviation_arg;
                      int order_arg;
      
                                      if (PyArg_ParseTuple(args,  "di:GaussianDerivativeKernel"
                        ,
             &standard_deviation_arg                        ,
             &order_arg                      ) <= 0)
           return 0;
               
                                  
              try {
                      return_arg = GaussianDerivativeKernel(standard_deviation_arg, order_arg);
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
                static PyObject* call_BinomialKernel(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          int radius_arg;
      
                                      if (PyArg_ParseTuple(args,  "i:BinomialKernel"
                        ,
             &radius_arg                      ) <= 0)
           return 0;
               
                    
              try {
                      return_arg = BinomialKernel(radius_arg);
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
                static PyObject* call_AveragingKernel(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          int radius_arg;
      
                                      if (PyArg_ParseTuple(args,  "i:AveragingKernel"
                        ,
             &radius_arg                      ) <= 0)
           return 0;
               
                    
              try {
                      return_arg = AveragingKernel(radius_arg);
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
                static PyObject* call_SymmetricGradientKernel(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                          
                                 
      
              try {
                                    return_arg=
                        SymmetricGradientKernel();
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
                static PyObject* call_SimpleSharpeningKernel(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          double sharpening_factor_arg;
      
                                      if (PyArg_ParseTuple(args,  "d:SimpleSharpeningKernel"
                        ,
             &sharpening_factor_arg                      ) <= 0)
           return 0;
               
                    
              try {
                      return_arg = SimpleSharpeningKernel(sharpening_factor_arg);
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
                                          
          static PyMethodDef _convolution_methods[] = {
                  {  "convolve",
          call_convolve, METH_VARARGS,
           "**convolve** (``Image`` [Float] *kernel*, ``Choice`` [avoid|clip|repeat|reflect|wrap] *border_treatment* = clip)\n\nConvolves an image with a given kernel.\n\nUses code from the Vigra library (Copyright 1998-2007 by Ullrich\nKöthe).\n\n*kernel*\n  A kernel for the convolution.  The kernel may either be a FloatImage\n  or a nested Python list of floats.\n\n*border_treatment*\n  Specifies how to treat the borders of the image.  Must be one of\n  the following:\n\n  - BORDER_TREATMENT_AVOID (0)\n\n    do not operate on a pixel where the kernel does not fit in the image\n\n  - BORDER_TREATMENT_CLIP (1)\n\n    clip kernel at image border. The kernel entries are renormalized\n    so that the total kernel sum is not changed (this is only useful\n    if the kernel is >= 0 everywhere).\n\n  - BORDER_TREATMENT_REPEAT (2)\n\n    repeat the nearest valid pixel\n\n  - BORDER_TREATMENT_REFLECT (3)\n  \n    reflect image at last row/column\n\n  - BORDER_TREATMENT_WRAP (4)\n\n    wrap image around (periodic boundary conditions)\n\nExample usage:\n\n.. code:: Python\n\n  # Using a custom kernel\n  img2 = image.convolve([[0.125, 0.0, -0.125],\n                         [0.25 , 0.0, -0.25 ],\n                         [0.125, 0.0, -0.125]])\n\n  # Using one of the included kernel generators\n  img2 = image.convolve(GaussianKernel(3.0))"        },
                                  {  "convolve_x",
          call_convolve_x, METH_VARARGS,
           "**convolve_x** (``Image`` [Float] *kernel_x*, ``Choice`` [avoid|clip|repeat|reflect|wrap] *border_treatment* = clip)\n\nConvolves an image in the X directions with a 1D kernel.  This is\nequivalent to what the Vigra library calls \"Separable\nConvolution\".\n\nUses code from the Vigra library (Copyright 1998-2007 by Ullrich\nKöthe).\n\n*kernel_x*\n  A kernel for the convolution in the *x* direction.  The kernel\n  may either be a FloatImage or a nested Python list of floats.\n  It must consist of only a single row.\n\n*border_treatment*\n  Specifies how to treat the borders of the image.  See\n  ``convolve`` for information about *border_treatment* values."        },
                        {  "convolve_y",
          call_convolve_y, METH_VARARGS,
           "**convolve_y** (``Image`` [Float] *kernel_y*, ``Choice`` [avoid|clip|repeat|reflect|wrap] *border_treatment* = clip)\n\nConvolves an image in the X directions with a 1D kernel.  This is\nequivalent to what the Vigra library calls \"Separable Convolution\".\n\nUses code from the Vigra library (Copyright 1998-2007 by Ullrich\nKöthe).\n\n*kernel_y*\n  A kernel for the convolution in the *x* direction.  The kernel\n  may either be a FloatImage or a nested Python list of floats.\n  It must consist of only a single row.\n\n*border_treatment*\n  Specifies how to treat the borders of the image.  See\n  ``convolve`` for information about *border_treatment* values."        },
                        {  "GaussianKernel",
          call_GaussianKernel, METH_VARARGS,
           "**GaussianKernel** (float *standard_deviation* = 1.00)\n\nInit as a Gaussian function. The radius of the kernel is always\n3*standard_deviation.\n\n*standard_deviation*\n  The standard deviation of the Gaussian kernel."        },
                        {  "GaussianDerivativeKernel",
          call_GaussianDerivativeKernel, METH_VARARGS,
           "**GaussianDerivativeKernel** (float *standard_deviation* = 1.00, int *order* = 1)\n\nInit as a Gaussian derivative of order 'order'.  The radius of the\nkernel is always 3*std_dev.\n\n*standard_deviation*\n  The standard deviation of the Gaussian kernel.\n\n*order*\n  The order of the Gaussian kernel."        },
                        {  "BinomialKernel",
          call_BinomialKernel, METH_VARARGS,
           "**BinomialKernel** (int *radius* = 3)\n\nCreates a binomial filter kernel for use with separable\nconvolution of a given radius.\n\n*radius*\n  The radius of the kernel."        },
                        {  "AveragingKernel",
          call_AveragingKernel, METH_VARARGS,
           "**AveragingKernel** (int *radius* = 3)\n\nCreates an Averaging filter kernel for use with separable\nconvolution.  The window size is (2*radius+1) * (2*radius+1).\n\n*radius*\n  The radius of the kernel."        },
                        {  "SymmetricGradientKernel",
          call_SymmetricGradientKernel, METH_VARARGS,
           "**SymmetricGradientKernel** ()\n\nInit as a symmetric gradient filter of the form [ 0.5, 0.0, -0.5]"        },
                        {  "SimpleSharpeningKernel",
          call_SimpleSharpeningKernel, METH_VARARGS,
           "**SimpleSharpeningKernel** (float *sharpening_factor* = 0.50)\n\nCreates a kernel for simple sharpening."        },
                                                                          { nullptr }
  };
  
  static struct PyModuleDef module_convolutionDef = {
        PyModuleDef_HEAD_INIT,
        "_convolution",
        nullptr,
        -1,
        _convolution_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__convolution(void) {
    return PyModule_Create(&module_convolutionDef);
  }
  

