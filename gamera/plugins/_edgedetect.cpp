
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "edgedetect.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_edgedetect(void);
  }
#endif

                static PyObject* call_difference_of_exponential_edge_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double scale_arg;
                      double gradient_threshold_arg;
                      int min_edge_length_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oddi:difference_of_exponential_edge_image"
                        ,
             &self_pyarg                        ,
             &scale_arg                        ,
             &gradient_threshold_arg                        ,
             &min_edge_length_arg                      ) <= 0)
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
return_arg = difference_of_exponential_edge_image(*((GreyScaleImageView*)self_arg), scale_arg, gradient_threshold_arg, min_edge_length_arg);
break;
case GREY16IMAGEVIEW:
return_arg = difference_of_exponential_edge_image(*((Grey16ImageView*)self_arg), scale_arg, gradient_threshold_arg, min_edge_length_arg);
break;
case FLOATIMAGEVIEW:
return_arg = difference_of_exponential_edge_image(*((FloatImageView*)self_arg), scale_arg, gradient_threshold_arg, min_edge_length_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'difference_of_exponential_edge_image' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_difference_of_exponential_crack_edge_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double scale_arg;
                      double gradient_threshold_arg;
                      int min_edge_length_arg;
                      int close_gaps_arg;
                      int beautify_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oddiii:difference_of_exponential_crack_edge_image"
                        ,
             &self_pyarg                        ,
             &scale_arg                        ,
             &gradient_threshold_arg                        ,
             &min_edge_length_arg                        ,
             &close_gaps_arg                        ,
             &beautify_arg                      ) <= 0)
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
return_arg = difference_of_exponential_crack_edge_image(*((GreyScaleImageView*)self_arg), scale_arg, gradient_threshold_arg, min_edge_length_arg, close_gaps_arg, beautify_arg);
break;
case GREY16IMAGEVIEW:
return_arg = difference_of_exponential_crack_edge_image(*((Grey16ImageView*)self_arg), scale_arg, gradient_threshold_arg, min_edge_length_arg, close_gaps_arg, beautify_arg);
break;
case FLOATIMAGEVIEW:
return_arg = difference_of_exponential_crack_edge_image(*((FloatImageView*)self_arg), scale_arg, gradient_threshold_arg, min_edge_length_arg, close_gaps_arg, beautify_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'difference_of_exponential_crack_edge_image' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_canny_edge_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double scale_arg;
                      double gradient_threshold_arg;
      
                                      if (PyArg_ParseTuple(args,  "Odd:canny_edge_image"
                        ,
             &self_pyarg                        ,
             &scale_arg                        ,
             &gradient_threshold_arg                      ) <= 0)
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
return_arg = canny_edge_image(*((GreyScaleImageView*)self_arg), scale_arg, gradient_threshold_arg);
break;
case GREY16IMAGEVIEW:
return_arg = canny_edge_image(*((Grey16ImageView*)self_arg), scale_arg, gradient_threshold_arg);
break;
case FLOATIMAGEVIEW:
return_arg = canny_edge_image(*((FloatImageView*)self_arg), scale_arg, gradient_threshold_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'canny_edge_image' can not have pixel type '%s'. Acceptable values are GREYSCALE, GREY16, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_labeled_region_edges(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int mark_both_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:labeled_region_edges"
                        ,
             &self_pyarg                        ,
             &mark_both_arg                      ) <= 0)
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
return_arg = labeled_region_edges(*((OneBitImageView*)self_arg), mark_both_arg);
break;
case CC:
return_arg = labeled_region_edges(*((Cc*)self_arg), mark_both_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = labeled_region_edges(*((OneBitRleImageView*)self_arg), mark_both_arg);
break;
case RLECC:
return_arg = labeled_region_edges(*((RleCc*)self_arg), mark_both_arg);
break;
case MLCC:
return_arg = labeled_region_edges(*((MlCc*)self_arg), mark_both_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = labeled_region_edges(*((GreyScaleImageView*)self_arg), mark_both_arg);
break;
case GREY16IMAGEVIEW:
return_arg = labeled_region_edges(*((Grey16ImageView*)self_arg), mark_both_arg);
break;
case RGBIMAGEVIEW:
return_arg = labeled_region_edges(*((RGBImageView*)self_arg), mark_both_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'labeled_region_edges' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, and RGB.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_outline(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int which_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:outline"
                        ,
             &self_pyarg                        ,
             &which_arg                      ) <= 0)
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
return_arg = outline(*((OneBitImageView*)self_arg), which_arg);
break;
case CC:
return_arg = outline(*((Cc*)self_arg), which_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = outline(*((OneBitRleImageView*)self_arg), which_arg);
break;
case RLECC:
return_arg = outline(*((RleCc*)self_arg), which_arg);
break;
case MLCC:
return_arg = outline(*((MlCc*)self_arg), which_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'outline' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _edgedetect_methods[] = {
                  {  "difference_of_exponential_edge_image",
          call_difference_of_exponential_edge_image, METH_VARARGS,
           "**difference_of_exponential_edge_image** (float(0.00, 1000000000000000052504760255204420248704468581108159154915854115511802457988908195786371375080447864043704443832883878176942523235360430575644792184786706982848387200926575803737830233794788090059368953234970799945081119038967640880074652742780142494579258788820056842838115669472196386865459400540160.00) *scale* = 0.80, float(0.00, 1000000000000000052504760255204420248704468581108159154915854115511802457988908195786371375080447864043704443832883878176942523235360430575644792184786706982848387200926575803737830233794788090059368953234970799945081119038967640880074652742780142494579258788820056842838115669472196386865459400540160.00) *gradient_threshold* = 4.00, int(0, 32000) *min_edge_length* = 0)\n\nEXPERIMENTAL\n\nDetect and mark edges in an edge image using the Shen/Castan\nzero-crossing detector.\n\nUses code from the VIGRA Computer Vision Library (Copyright\n1998-2007 by Ullrich Köthe).\n\n*scale*\n  The scale relates to the value b of the exponential filter.\n\n*gradient_threshold*\n	Whenever the gradient at a zero crossing is greater than the\n	given gradient_threshold, an edge point is marked in the\n	destination image on the darker side of the zero crossing (the\n	zero crossing occurs between pixels).\n\n*min_edge_length*\n	Removes all edges shorter than the number of pixels specified\n	(0 retains all edges).  Values near 10 are suggested."        },
                        {  "difference_of_exponential_crack_edge_image",
          call_difference_of_exponential_crack_edge_image, METH_VARARGS,
           "**difference_of_exponential_crack_edge_image** (float(0.00, 1000000000000000052504760255204420248704468581108159154915854115511802457988908195786371375080447864043704443832883878176942523235360430575644792184786706982848387200926575803737830233794788090059368953234970799945081119038967640880074652742780142494579258788820056842838115669472196386865459400540160.00) *scale* = 0.80, float(0.00, 1000000000000000052504760255204420248704468581108159154915854115511802457988908195786371375080447864043704443832883878176942523235360430575644792184786706982848387200926575803737830233794788090059368953234970799945081119038967640880074652742780142494579258788820056842838115669472196386865459400540160.00) *gradient_threshold* = 4.00, int(0, 32000) *min_edge_length* = 0, ``bool`` *close_gaps* = False, ``bool`` *beautify* = False)\n\nEXPERIMENTAL\n\n      Detect and mark edges in a crack edge image using the\n      Shen/Castan zero-crossing detector.\n\n      Uses code from the VIGRA Computer Vision Library (Copyright\n      1998-2007 by Ullrich Köthe).\n\n      *scale*\n	The scale relates to the value b of the exponential filter.\n\n      *gradient_threshold*\n	Whenever the gradient at a zero crossing is greater than the\n	given gradient threshold, an edge point is marked in the\n	destination image on the darker side of the zero crossing (the\n	zero crossing occurs between pixels).\n\n      *min_edge_length*\n	Removes all edges shorter than the number of pixels specified\n	(0 retains all edges).  Values near 10 are suggested.\n\n      *close_gaps*\n        Close one pixel wide gaps.\n\n      *beautify*\n        See the VIGRA Docs.\n      "        },
                        {  "canny_edge_image",
          call_canny_edge_image, METH_VARARGS,
           "**canny_edge_image** (float(0.00, 1000000000000000052504760255204420248704468581108159154915854115511802457988908195786371375080447864043704443832883878176942523235360430575644792184786706982848387200926575803737830233794788090059368953234970799945081119038967640880074652742780142494579258788820056842838115669472196386865459400540160.00) *scale* = 0.80, float(0.00, 1000000000000000052504760255204420248704468581108159154915854115511802457988908195786371375080447864043704443832883878176942523235360430575644792184786706982848387200926575803737830233794788090059368953234970799945081119038967640880074652742780142494579258788820056842838115669472196386865459400540160.00) *gradient_threshold* = 4.00)\n\nEXPERIMENTAL\n\n      Detect and mark edges in an edge image using Canny's algorithm.\n\n      Uses code from the VIGRA Computer Vision Library (Copyright\n      1998-2007 by Ullrich Köthe).\n\n      *scale*\n	The scale relates to the value b of the exponential filter.\n\n      *gradient_threshold*\n	This operator first calls cannyEdgelList() to generate an\n	edgel list for the given image. Than it scans this list and\n	selects edgels whose strength is above the given\n	gradient_threshold.\n      "        },
                        {  "labeled_region_edges",
          call_labeled_region_edges, METH_VARARGS,
           "**labeled_region_edges** (``bool`` *mark_both* = False)\n\nPixels with a label different from one of its neighboring pixels\nare marked black in the returned image.\n\nWhen *mark_both* is ``True``, both edges of the region border are\nmarked, resulting in a two pixel wide edge."        },
                        {  "outline",
          call_outline, METH_VARARGS,
           "**outline** (``Choice`` [outer|inner] *which* = outer)\n\nTraces the outline of the image.  When *which* is 0 (\"outer\"),\nthe result is obtained by dilating the image and then XOR'ing the\nresult with the original; when *which* is 1 (\"inner\"), the result\nis obtained by eroding the image and then XOR'ing the\nresult with the original."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_edgedetectDef = {
        PyModuleDef_HEAD_INIT,
        "_edgedetect",
        nullptr,
        -1,
        _edgedetect_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__edgedetect(void) {
    return PyModule_Create(&module_edgedetectDef);
  }
  

