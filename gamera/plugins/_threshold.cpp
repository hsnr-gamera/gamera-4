
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "threshold.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_threshold(void);
  }
#endif

                static PyObject* call_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int threshold_arg;
                      int storage_format_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:threshold"
                        ,
             &self_pyarg                        ,
             &threshold_arg                        ,
             &storage_format_arg                      ) <= 0)
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
return_arg = threshold(*((GreyScaleImageView*)self_arg), threshold_arg, storage_format_arg);
break;
case GREY16IMAGEVIEW:
return_arg = threshold(*((Grey16ImageView*)self_arg), threshold_arg, storage_format_arg);
break;
case FLOATIMAGEVIEW:
return_arg = threshold(*((FloatImageView*)self_arg), threshold_arg, storage_format_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'threshold' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_otsu_find_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                int return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:otsu_find_threshold"
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
return_arg = otsu_find_threshold(*((GreyScaleImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'otsu_find_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
                static PyObject* call_otsu_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int storage_format_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:otsu_threshold"
                        ,
             &self_pyarg                        ,
             &storage_format_arg                      ) <= 0)
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
return_arg = otsu_threshold(*((GreyScaleImageView*)self_arg), storage_format_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'otsu_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_tsai_moment_preserving_find_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                int return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:tsai_moment_preserving_find_threshold"
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
return_arg = tsai_moment_preserving_find_threshold(*((GreyScaleImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'tsai_moment_preserving_find_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
                static PyObject* call_tsai_moment_preserving_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int storage_format_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:tsai_moment_preserving_threshold"
                        ,
             &self_pyarg                        ,
             &storage_format_arg                      ) <= 0)
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
return_arg = tsai_moment_preserving_threshold(*((GreyScaleImageView*)self_arg), storage_format_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'tsai_moment_preserving_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_abutaleb_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int storage_format_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:abutaleb_threshold"
                        ,
             &self_pyarg                        ,
             &storage_format_arg                      ) <= 0)
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
return_arg = abutaleb_threshold(*((GreyScaleImageView*)self_arg), storage_format_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'abutaleb_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_bernsen_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int storage_format_arg;
                      int region_size_arg;
                      int contrast_limit_arg;
                      int doubt_to_black_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiiii:bernsen_threshold"
                        ,
             &self_pyarg                        ,
             &storage_format_arg                        ,
             &region_size_arg                        ,
             &contrast_limit_arg                        ,
             &doubt_to_black_arg                      ) <= 0)
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
return_arg = bernsen_threshold(*((GreyScaleImageView*)self_arg), storage_format_arg, region_size_arg, contrast_limit_arg, doubt_to_black_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'bernsen_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_djvu_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double smoothness_arg;
                      int max_block_size_arg;
                      int min_block_size_arg;
                      int block_factor_arg;
      
                                      if (PyArg_ParseTuple(args,  "Odiii:djvu_threshold"
                        ,
             &self_pyarg                        ,
             &smoothness_arg                        ,
             &max_block_size_arg                        ,
             &min_block_size_arg                        ,
             &block_factor_arg                      ) <= 0)
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
return_arg = djvu_threshold(*((RGBImageView*)self_arg), smoothness_arg, max_block_size_arg, min_block_size_arg, block_factor_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'djvu_threshold' can not have pixel type '%s'. Acceptable value is RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_soft_threshold(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int t_arg;
                      double sigma_arg;
                      int dist_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oidi:soft_threshold"
                        ,
             &self_pyarg                        ,
             &t_arg                        ,
             &sigma_arg                        ,
             &dist_arg                      ) <= 0)
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
return_arg = soft_threshold(*((GreyScaleImageView*)self_arg), t_arg, sigma_arg, dist_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'soft_threshold' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_soft_threshold_find_sigma(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                double return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int t_arg;
                      int dist_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:soft_threshold_find_sigma"
                        ,
             &self_pyarg                        ,
             &t_arg                        ,
             &dist_arg                      ) <= 0)
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
return_arg = soft_threshold_find_sigma(*((GreyScaleImageView*)self_arg), t_arg, dist_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'soft_threshold_find_sigma' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                return_pyarg = PyFloat_FromDouble((double)return_arg);            return return_pyarg;
                              }
      
          static PyMethodDef _threshold_methods[] = {
                  {  "threshold",
          call_threshold, METH_VARARGS,
           "**threshold** (int *threshold*, ``Choice`` [dense|rle] *storage format*)\n\nCreates a binary image by splitting along a given global threshold value.\n\nPixels that are greater than the given value become white.\nPixels less than or equal to the given value become black.\n\n*storage_format* (optional)\n  specifies the compression type for the result:\n\n  DENSE (0)\n    no compression\n  RLE (1)\n    run-length encoding compression."        },
                        {  "otsu_find_threshold",
          call_otsu_find_threshold, METH_VARARGS,
           "**otsu_find_threshold** ()\n\nFinds a threshold point using the Otsu algorithm. Reference:\n\nN. Otsu: *A Threshold Selection Method from Grey-Level\nHistograms.* IEEE Transactions on Systems, Man, and Cybernetics\n(9), pp. 62-66 (1979)"        },
                        {  "otsu_threshold",
          call_otsu_threshold, METH_VARARGS,
           "**otsu_threshold** (``Choice`` [dense|rle] *storage format*)\n\nCreates a binary image by splitting along a threshold value\ndetermined using the Otsu algorithm.\n\nEquivalent to ``image.threshold(image.otsu_find_threshold())``.\n\n*storage_format* (optional)\n  specifies the compression type for the result:\n  \n  DENSE (0)\n    no compression\n  RLE (1)\n    run-length encoding compression"        },
                        {  "tsai_moment_preserving_find_threshold",
          call_tsai_moment_preserving_find_threshold, METH_VARARGS,
           "**tsai_moment_preserving_find_threshold** ()\n\nFinds a threshold point using the Tsai Moment Preserving threshold\nalgorithm. Reference:\n\nW.H. Tsai: *Moment-Preserving Thresholding: A New Approach.*\nComputer Vision Graphics and Image Processing (29), pp. 377-393\n(1985)"        },
                        {  "tsai_moment_preserving_threshold",
          call_tsai_moment_preserving_threshold, METH_VARARGS,
           "**tsai_moment_preserving_threshold** (``Choice`` [dense|rle] *storage format*)\n\nCreates a binary image by splitting along a threshold value\ndetermined using the Tsai Moment Preserving Threshold algorithm.\n\nEquivalent to\n``image.threshold(image.tsai_moment_preserving_find_threshold())``.\n\n*storage_format* (optional)\n  specifies the compression type for the result:\n\n  DENSE (0)\n    no compression\n  RLE (1)\n    run-length encoding compression"        },
                        {  "abutaleb_threshold",
          call_abutaleb_threshold, METH_VARARGS,
           "**abutaleb_threshold** (``Choice`` [dense|rle] *storage format*)\n\nCreates a binary image by using the Abutaleb locally-adaptive\nthresholding algorithm.\n\n*storage_format* (optional)\n  specifies the compression type for the result:\n\n  DENSE (0)\n    no compression\n  RLE (1)\n    run-length encoding compression"        },
                        {  "bernsen_threshold",
          call_bernsen_threshold, METH_VARARGS,
           "**bernsen_threshold** (``Choice`` [dense|rle] *storage format*, int(1, 50) *region size* = 11, int(0, 255) *contrast limit* = 80, ``bool`` *doubt_to_black* = False)\n\nCreates a binary image by using the Bernsen algorithm.\n\nEach point is thresholded by the mean between the maximum and minimum\nvalue in the surrounding region of size *region_size*. When the difference\nbetween maximum and minimum is below *contrast_limit* the pixel is set\nto black in case of *doubt_to_black* = ``True``, otherwise to white.\n\nReference: J. Bernsen: *Dynamic thresholding of grey-level images.* \nProc. 8th International Conference on Pattern Recognition (ICPR8),\npp. 1251-1255, 1986.\n\n*storage_format*\n  specifies the compression type for the result:\n\n  DENSE (0)\n    no compression\n  RLE (1)\n    run-length encoding compression\n\n*region_size*\n  The size of each region in which to calculate a threshold\n\n*contrast_limit*\n  The minimum amount of contrast required to threshold.\n\n*doubt_to_black*\n  When ``True``, 'doubtful' values are set to black, otherwise to white."        },
                        {  "djvu_threshold",
          call_djvu_threshold, METH_VARARGS,
           "**djvu_threshold** (float(0.00, 1.00) *smoothness* = 0.20, int *max_block_size* = 512, int *min_block_size* = 64, int(1, 8) *block_factor* = 2)\n\nCreates a binary image by using the DjVu thresholding algorithm.\n\nSee Section 5.1 in:\n\n  Bottou, L., P. Haffner, P. G. Howard, P. Simard, Y. Bengio and\n  Y. LeCun.  1998.  High Quality Document Image Compression with\n  DjVu.  AT&T Labs, Lincroft, NJ.\n\n  http://research.microsoft.com/~patrice/PDF/jei.pdf\n\nThis implementation features an additional extension to the\nalgorithm described above.  Once the background and foreground\ncolors are determined for each block, the image is thresholded by\ninterpolating the foreground and background colors between the\nblocks.  This prevents \"blockiness\" along boundaries of strong\ncolor change.\n\n*smoothness*\n  The amount of effect that parent blocks have on their children\n  blocks.  Higher values will result in more smoothness between\n  blocks.  Expressed as a percentage between 0.0 and 1.0.\n\n*max_block_size*\n  The size of the largest block to determine a threshold.\n\n*min_block_size*\n  The size of the smallest block to determine a threshold.\n\n*block_factor*\n  The number of child blocks (in each direction) per parent block.\n  For instance, a *block_factor* of 2 results in 4 children per\n  parent."        },
                        {  "soft_threshold",
          call_soft_threshold, METH_VARARGS,
           "**soft_threshold** (int *t* = None, float *sigma* = 0.00, ``Choice`` [logistic|normal|uniform] *dist* = logistic)\n\nDoes a greyscale transformation that \"smears out\" the threshold *t* by a\nchoosable amount *sigma*. This has the effect of a \"soft\" thresholding.\n\nEach grey value *x* is transformed to *F(x,t,sigma)*, where *F*\nis the CDF probability distribution with mean *t* and variance\n*sigma^2*. The parameter *dist* determines the type of probability\ndistribution: 0 = logistic, 1 = normal (gaussian), 2 = uniform.\n\nAs the choice *sigma* = 0 is useless (it is the same as normal\nthresholding), this special value is reserved for an automatic selection\nof *sigma* with soft_threshold_find_sigma__.\n\n.. __: #soft-threshold-find-sigma\n\nWhen *t* is not given, it is automatically computed with\notsu_find_threshold__.\n\n.. __: #otsu-find-threshold\n\nReference: C. Dalitz: `\"Soft Thresholding for Visual Image Enhancement.\"`__\nTechnischer Bericht Nr. 2014-01, Hochschule Niederrhein,\nFachbereich Elektrotechnik und Informatik, 2014\n\n.. __: http://www.hsnr.de/fileadmin/dateien/fb03/gruppen/technische-berichte/fb03-tb-2014-01.pdf"        },
                        {  "soft_threshold_find_sigma",
          call_soft_threshold_find_sigma, METH_VARARGS,
           "**soft_threshold_find_sigma** (int *t* = None, ``Choice`` [logistic|normal|uniform] *dist* = logistic)\n\nFor the CDF probability distribution given by *dist*\n(0 = logistic, 1 = normal (gaussian), 2 = uniform), sigma is\ndetermined such that *F(m,t,sigma)* = 0.99, where *m* is the mean grey\nvalue of all pixels with a grey value greater than *t*.\n\nReference: C. Dalitz: `\"Soft Thresholding for Visual Image Enhancement.\"`__\nTechnischer Bericht Nr. 2014-01, Hochschule Niederrhein,\nFachbereich Elektrotechnik und Informatik, 2014\n\n.. __: http://www.hsnr.de/fileadmin/dateien/fb03/gruppen/technische-berichte/fb03-tb-2014-01.pdf"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_thresholdDef = {
        PyModuleDef_HEAD_INIT,
        "_threshold",
        nullptr,
        -1,
        _threshold_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__threshold(void) {
    return PyModule_Create(&module_thresholdDef);
  }
  

