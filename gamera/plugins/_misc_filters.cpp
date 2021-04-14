
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "misc_filters.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_misc_filters(void);
  }
#endif

                static PyObject* call_mean(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int k_arg;
                      int border_treatment_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:mean"
                        ,
             &self_pyarg                        ,
             &k_arg                        ,
             &border_treatment_arg                      ) <= 0)
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
return_arg = mean(*((OneBitImageView*)self_arg), k_arg, border_treatment_arg);
break;
case CC:
return_arg = mean(*((Cc*)self_arg), k_arg, border_treatment_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = mean(*((OneBitRleImageView*)self_arg), k_arg, border_treatment_arg);
break;
case RLECC:
return_arg = mean(*((RleCc*)self_arg), k_arg, border_treatment_arg);
break;
case MLCC:
return_arg = mean(*((MlCc*)self_arg), k_arg, border_treatment_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = mean(*((GreyScaleImageView*)self_arg), k_arg, border_treatment_arg);
break;
case GREY16IMAGEVIEW:
return_arg = mean(*((Grey16ImageView*)self_arg), k_arg, border_treatment_arg);
break;
case FLOATIMAGEVIEW:
return_arg = mean(*((FloatImageView*)self_arg), k_arg, border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'mean' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_rank(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int rank_arg;
                      int k_arg;
                      int border_treatment_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiii:rank"
                        ,
             &self_pyarg                        ,
             &rank_arg                        ,
             &k_arg                        ,
             &border_treatment_arg                      ) <= 0)
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
return_arg = rank(*((OneBitImageView*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
case CC:
return_arg = rank(*((Cc*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = rank(*((OneBitRleImageView*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
case RLECC:
return_arg = rank(*((RleCc*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
case MLCC:
return_arg = rank(*((MlCc*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = rank(*((GreyScaleImageView*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
case GREY16IMAGEVIEW:
return_arg = rank(*((Grey16ImageView*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
case FLOATIMAGEVIEW:
return_arg = rank(*((FloatImageView*)self_arg), rank_arg, k_arg, border_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'rank' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_min_max_filter(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int k_arg;
                      int filter_arg;
                      int k_vertical_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiii:min_max_filter"
                        ,
             &self_pyarg                        ,
             &k_arg                        ,
             &filter_arg                        ,
             &k_vertical_arg                      ) <= 0)
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
return_arg = min_max_filter(*((OneBitImageView*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
case CC:
return_arg = min_max_filter(*((Cc*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = min_max_filter(*((OneBitRleImageView*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
case RLECC:
return_arg = min_max_filter(*((RleCc*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
case MLCC:
return_arg = min_max_filter(*((MlCc*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = min_max_filter(*((GreyScaleImageView*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
case GREY16IMAGEVIEW:
return_arg = min_max_filter(*((Grey16ImageView*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
case FLOATIMAGEVIEW:
return_arg = min_max_filter(*((FloatImageView*)self_arg), k_arg, filter_arg, k_vertical_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'min_max_filter' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_create_gabor_filter(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double orientation_arg;
                      double frequency_arg;
                      int direction_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oddi:create_gabor_filter"
                        ,
             &self_pyarg                        ,
             &orientation_arg                        ,
             &frequency_arg                        ,
             &direction_arg                      ) <= 0)
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
return_arg = create_gabor_filter(*((GreyScaleImageView*)self_arg), orientation_arg, frequency_arg, direction_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'create_gabor_filter' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_kfill(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int k_arg;
                      int iterations_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:kfill"
                        ,
             &self_pyarg                        ,
             &k_arg                        ,
             &iterations_arg                      ) <= 0)
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
return_arg = kfill(*((OneBitImageView*)self_arg), k_arg, iterations_arg);
break;
case CC:
return_arg = kfill(*((Cc*)self_arg), k_arg, iterations_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = kfill(*((OneBitRleImageView*)self_arg), k_arg, iterations_arg);
break;
case RLECC:
return_arg = kfill(*((RleCc*)self_arg), k_arg, iterations_arg);
break;
case MLCC:
return_arg = kfill(*((MlCc*)self_arg), k_arg, iterations_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'kfill' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_kfill_modified(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int k_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:kfill_modified"
                        ,
             &self_pyarg                        ,
             &k_arg                      ) <= 0)
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
return_arg = kfill_modified(*((OneBitImageView*)self_arg), k_arg);
break;
case CC:
return_arg = kfill_modified(*((Cc*)self_arg), k_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = kfill_modified(*((OneBitRleImageView*)self_arg), k_arg);
break;
case RLECC:
return_arg = kfill_modified(*((RleCc*)self_arg), k_arg);
break;
case MLCC:
return_arg = kfill_modified(*((MlCc*)self_arg), k_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'kfill_modified' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _misc_filters_methods[] = {
                  {  "mean",
          call_mean, METH_VARARGS,
           "**mean** (int *k* = 3, ``Choice`` [padwhite|reflect] *border_treatment* = reflect)\n\nWithin each *k* times *k* window, set the center pixel to the mean\nvalue of all pixels.\n\n*k* is the window size (must be odd), and *border_treatment* can\nbe 0 ('padwhite'), which sets window pixels outside the image to white,\nor 1 ('reflect'), for reflecting boundary conditions."        },
                        {  "rank",
          call_rank, METH_VARARGS,
           "**rank** (int *rank*, int *k* = 3, ``Choice`` [padwhite|reflect] *border_treatment* = reflect)\n\nWithin each *k* times *k* window, set the center pixel to the *r*-th ranked\nvalue.\n\nNote that for ``Onebit`` images, actually *rank(k*k - r + 1)* is computed instead\nof *rank(r)*. This has the effect that you do not need to worry whether\nyour image is a greyscale or onebit image: in all cases low values\nfor *r* will darken the image and high values will light it up.\n\n*rank* (1, 2, ..., *k* * *k*)\n  The rank of the windows pixels to select for the center. (k*k+1)/2 is\n  equivalent to the median.\n\n*k* (3, 5 ,7, ...)\n  The window size (must be odd).\n\n*border_treatment* (0, 1)\n  When 0 ('padwhite'), window pixels outside the image are set to white.\n  When 1 ('reflect'), reflecting boundary conditions are used."        },
                        {  "min_max_filter",
          call_min_max_filter, METH_VARARGS,
           "**min_max_filter** (int *k* = 3, ``Choice`` [min|max] *filter* = min, int *k_vertical* = 0)\n\nWithin each *k* times *k* window, set the center pixel to the minimum or\nmaximum value of all pixels inside the window.\n\n*k* is the window size (must be odd) and *filter* is the filter type\n(0 for min, 1 for max). When *k_vertical* is nonzero, the vertical size of\nthe window is set to *k_vertical* instead of *k*.\n\nThis function does the same as *rank(1,k,border_treatment=1)*, but is\nmuch faster because the runtime of *min_max_filter* is constant in\nthe window size. The same algorithm has been developed independently\nby van Herk and Gil and Werman. See\n\n  M. van Herk: *A fast algorithm for local minimum and maximum filters\n  on rectangular and octagonal kernels.* Pattern Recognition Letters 13,\n  pp. 517-521, 1992\n\n  J. Gil, M. Werman: *Computing 2-D min, median, and max filters.*\n  IEEE Transactions on Pattern Analysis and Machine Intelligence 15,\n  pp. 504-507, 1993"        },
                        {  "create_gabor_filter",
          call_create_gabor_filter, METH_VARARGS,
           "**create_gabor_filter** (float *orientation* = 45.00, float *frequency* = 0.38, int *direction* = 5)\n\nComputes the convolution of an image with a two dimensional Gabor\nfunction. The result is returned as a float image.\n\nThe *orientation* is given in radians, the other parameters are\nthe center *frequency* (for example 0.375 or smaller) and the two\nangular and radial sigmas of the gabor filter.\n\nThe energy of the filter is explicitly normalized to 1.0."        },
                        {  "kfill",
          call_kfill, METH_VARARGS,
           "**kfill** (int *k* = 3, int *iterations* = 1)\n\nRemoves salt and pepper noise in onebit images by applying the *kfill*\nfilter *iterations* times. Should before *iteration* times a run of\nthe kfill filter not change a single pixel, the iteration is stopped\nbeforehand.\n\nIn contrast to a rank or mean filter, kfill is designed in such\na way that it does not merge non touching connected components.\nTo this end, the border of the *k* times *k* mask is scanned for\nblack pixels and the center is not filled when this would connect\ndisjoint pixels on the border. A detailed description of the\nalgorithm can be found in\n\n   M. Seul, L. O'Gorman, M.J. Sammon: *Practical Algorithms for\n   Image Analysis.* Cambridge University Press, 2000\n\nThe present implementation does not use code from the book, but has\nbeen written from scratch."        },
                        {  "kfill_modified",
          call_kfill_modified, METH_VARARGS,
           "**kfill_modified** (int *k* = 3)\n\nRemoves salt and pepper noise in onebit images by applying a\nmodified version of the *kfill* filter proposed in the following\nreference:\n\n   K.Chinnasarn, Y.Rangsanseri, P.Thitimajshima:\n   *Removing Salt-and-Pepper Noise in Text/Graphics Images.*\n   Proceedings of The Asia-Pacific Conference on Circuits and Systems\n   (APCCAS'98), pp. 459-462, 1998\n\nFor *k* = 3, this algorithm is identical with the original kfill algorithm.\nFor larger *k* however, it fills the window core also when not all\npixels are of the same value. It should be noted that in this case,\nthe modified version does *not* take care\nof connectivity. In other words, it can result in joining previously\ndisconnected connected components, similar to a morphological closing\noperation, while at the same time small black speckles are removed."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_misc_filtersDef = {
        PyModuleDef_HEAD_INIT,
        "_misc_filters",
        nullptr,
        -1,
        _misc_filters_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__misc_filters(void) {
    return PyModule_Create(&module_misc_filtersDef);
  }
  

