
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "logical.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_logical(void);
  }
#endif

                static PyObject* call_and_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
                      int in_place_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:and_image"
                        ,
             &self_pyarg                        ,
             &other_pyarg                        ,
             &in_place_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(other_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'other' must be an image");
          return 0;
        }
        other_arg = ((Image*)((RectObject*)other_pyarg)->m_x);
        image_get_fv(other_pyarg, &other_arg->features, &other_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = and_image(*((OneBitImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = and_image(*((OneBitImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = and_image(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = and_image(*((OneBitImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = and_image(*((OneBitImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'and_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = and_image(*((Cc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = and_image(*((Cc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = and_image(*((Cc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = and_image(*((Cc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = and_image(*((Cc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'and_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = and_image(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = and_image(*((OneBitRleImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = and_image(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = and_image(*((OneBitRleImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = and_image(*((OneBitRleImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'and_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = and_image(*((RleCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = and_image(*((RleCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = and_image(*((RleCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = and_image(*((RleCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = and_image(*((RleCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'and_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = and_image(*((MlCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = and_image(*((MlCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = and_image(*((MlCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = and_image(*((MlCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = and_image(*((MlCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'and_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'and_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_or_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
                      int in_place_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:or_image"
                        ,
             &self_pyarg                        ,
             &other_pyarg                        ,
             &in_place_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(other_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'other' must be an image");
          return 0;
        }
        other_arg = ((Image*)((RectObject*)other_pyarg)->m_x);
        image_get_fv(other_pyarg, &other_arg->features, &other_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = or_image(*((OneBitImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = or_image(*((OneBitImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = or_image(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = or_image(*((OneBitImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = or_image(*((OneBitImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'or_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = or_image(*((Cc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = or_image(*((Cc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = or_image(*((Cc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = or_image(*((Cc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = or_image(*((Cc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'or_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = or_image(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = or_image(*((OneBitRleImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = or_image(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = or_image(*((OneBitRleImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = or_image(*((OneBitRleImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'or_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = or_image(*((RleCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = or_image(*((RleCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = or_image(*((RleCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = or_image(*((RleCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = or_image(*((RleCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'or_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = or_image(*((MlCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = or_image(*((MlCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = or_image(*((MlCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = or_image(*((MlCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = or_image(*((MlCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'or_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'or_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_xor_image(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      Image* other_arg;
PyObject* other_pyarg;
                      int in_place_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOi:xor_image"
                        ,
             &self_pyarg                        ,
             &other_pyarg                        ,
             &in_place_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      if (!is_ImageObject(other_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'other' must be an image");
          return 0;
        }
        other_arg = ((Image*)((RectObject*)other_pyarg)->m_x);
        image_get_fv(other_pyarg, &other_arg->features, &other_arg->features_len);
                            
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = xor_image(*((OneBitImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = xor_image(*((OneBitImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = xor_image(*((OneBitImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = xor_image(*((OneBitImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = xor_image(*((OneBitImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'xor_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = xor_image(*((Cc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = xor_image(*((Cc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = xor_image(*((Cc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = xor_image(*((Cc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = xor_image(*((Cc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'xor_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = xor_image(*((OneBitRleImageView*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = xor_image(*((OneBitRleImageView*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = xor_image(*((OneBitRleImageView*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = xor_image(*((OneBitRleImageView*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = xor_image(*((OneBitRleImageView*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'xor_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = xor_image(*((RleCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = xor_image(*((RleCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = xor_image(*((RleCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = xor_image(*((RleCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = xor_image(*((RleCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'xor_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(other_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = xor_image(*((MlCc*)self_arg), *((OneBitImageView*)other_arg), in_place_arg);
break;
case CC:
return_arg = xor_image(*((MlCc*)self_arg), *((Cc*)other_arg), in_place_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = xor_image(*((MlCc*)self_arg), *((OneBitRleImageView*)other_arg), in_place_arg);
break;
case RLECC:
return_arg = xor_image(*((MlCc*)self_arg), *((RleCc*)other_arg), in_place_arg);
break;
case MLCC:
return_arg = xor_image(*((MlCc*)self_arg), *((MlCc*)other_arg), in_place_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'other' argument of 'xor_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(other_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'xor_image' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _logical_methods[] = {
                  {  "and_image",
          call_and_image, METH_VARARGS,
           "**and_image** (``Image`` [OneBit] *other*, ``bool`` *in_place* = False)\n\nPerform the AND operation on two images.\n\nSince it would be difficult to determine what exactly to do if the images\nare a different size, the two images must be the same size.\n\n*in_place*\n  If true, the operation will be performed in-place, changing the\n  contents of the current image.\n\nSee or_image_ for some usage examples."        },
                        {  "or_image",
          call_or_image, METH_VARARGS,
           "**or_image** (``Image`` [OneBit] *other*, ``bool`` *in_place* = False)\n\nPerform the OR operation on two images.\n\nSince it would be difficult to determine what exactly to do if the\nimages are a different size, the two images must be the same size.\n\n*in_place*\n  If true, the operation will be performed in-place, changing the\n  contents of the current image.\n\nUsage examples:\n\nUsing logical functions in different ways will generally involve\ncreating temporary subimages for regions of interest.  Subimages are\nvery lightweight objects that keep track of a bounding box and refer\nto the underlying data, therefore creating/destroying a number of\nthese on the fly should not have a significant impact on\nperformance.\n\nPadding an image.\n\n.. code:: Python\n\n  def pad_image(image, padding):\n    new_image = Image(0, 0,\n                      image.nrows + padding * 2, image.ncols + padding * 2,\n                      ONEBIT, DENSE)\n    new_image.subimage((padding, padding), Dim(image.nrows, image.ncols)).or_image(image, True)\n    return new_image\n\nStamping an image over a larger image.  Use subimage to change the\ndestination of the stamp.\n\n.. code:: Python\n\n  # stamp: a small stamp image\n  # paper: a larger destination image\n  for x in range(0, 100, 10):\n    paper.subimage(0, x, stamp.nrows, stamp.ncols).or_image(stamp, True)\n\nPutting part of a source image on the upper-left corner of a\ndestination image.\n\n.. code:: Python\n\n  # src: a source image\n  # dest: a destination image\n  dest.or_image(src.subimage(50, 50, 25, 25), True)\n\nRemoving a connected component from its original image.\n\n.. code:: Python\n\n  # src: the original image\n  # cc: a cc on that image\n  src.clip_image(cc).xor_image(cc, True)"        },
                        {  "xor_image",
          call_xor_image, METH_VARARGS,
           "**xor_image** (``Image`` [OneBit] *other*, ``bool`` *in_place* = False)\n\nPerform the XOR operation on two images.\n\nSince it would be difficult to determine what exactly to do if the images\nare a different size, the two images must be the same size.\n\n*in_place*\n  If true, the operation will be performed in-place, changing the\n  contents of the current image.\n\nSee or_image_ for some usage examples."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_logicalDef = {
        PyModuleDef_HEAD_INIT,
        "_logical",
        nullptr,
        -1,
        _logical_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__logical(void) {
    return PyModule_Create(&module_logicalDef);
  }
  

