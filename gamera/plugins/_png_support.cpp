
        
        #include <png.h>
    #undef _POSIX_C_SOURCE
    #undef _XOPEN_SOURCE
  
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "png_support.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_png_support(void);
  }
#endif

                static PyObject* call_save_PNG(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      char* image_file_name_arg;
      
                                      if (PyArg_ParseTuple(args,  "Os:save_PNG"
                        ,
             &self_pyarg                        ,
             &image_file_name_arg                      ) <= 0)
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
save_PNG(*((OneBitImageView*)self_arg), image_file_name_arg);
break;
case CC:
save_PNG(*((Cc*)self_arg), image_file_name_arg);
break;
case ONEBITRLEIMAGEVIEW:
save_PNG(*((OneBitRleImageView*)self_arg), image_file_name_arg);
break;
case RLECC:
save_PNG(*((RleCc*)self_arg), image_file_name_arg);
break;
case MLCC:
save_PNG(*((MlCc*)self_arg), image_file_name_arg);
break;
case GREYSCALEIMAGEVIEW:
save_PNG(*((GreyScaleImageView*)self_arg), image_file_name_arg);
break;
case GREY16IMAGEVIEW:
save_PNG(*((Grey16ImageView*)self_arg), image_file_name_arg);
break;
case RGBIMAGEVIEW:
save_PNG(*((RGBImageView*)self_arg), image_file_name_arg);
break;
case FLOATIMAGEVIEW:
save_PNG(*((FloatImageView*)self_arg), image_file_name_arg);
break;
case COMPLEXIMAGEVIEW:
save_PNG(*((ComplexImageView*)self_arg), image_file_name_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'save_PNG' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                  Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_PNG_info(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        ImageInfo* return_arg;
PyObject* return_pyarg;
                                          char* image_file_name_arg;
      
                                      if (PyArg_ParseTuple(args,  "s:PNG_info"
                        ,
             &image_file_name_arg                      ) <= 0)
           return 0;
               
                    
              try {
                      return_arg = PNG_info(image_file_name_arg);
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
              return_pyarg = create_ImageInfoObject(return_arg);              return return_pyarg;
            }
                              }
                static PyObject* call_load_PNG(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          char* image_file_name_arg;
                      int storage_format_arg;
      
                                      if (PyArg_ParseTuple(args,  "si:load_PNG"
                        ,
             &image_file_name_arg                        ,
             &storage_format_arg                      ) <= 0)
           return 0;
               
                                  
              try {
                      return_arg = load_PNG(image_file_name_arg, storage_format_arg);
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
      
          static PyMethodDef _png_support_methods[] = {
                  {  "save_PNG",
          call_save_PNG, METH_VARARGS,
           "**save_PNG** (``FileSave`` *image_file_name*)\n\nSaves the image to a PNG format file."        },
                        {  "PNG_info",
          call_PNG_info, METH_VARARGS,
           "**PNG_info** (str *image_file_name*)\n\nReturns an ``ImageInfo`` object describing a PNG file.\n\n*image_file_name*\n  A PNG image filename"        },
                        {  "load_PNG",
          call_load_PNG, METH_VARARGS,
           "**load_PNG** (``FileOpen`` *image_file_name*, ``Choice`` [DENSE|RLE] *storage format*)\n\nLoads a PNG format image file.\n\n*image_file_name*\n  A PNG image filename\n\n*storage_format* (optional)\n  specifies the compression type for the result:\n\n  DENSE (0)\n    no compression\n  RLE (1)\n    run-length encoding compression"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_png_supportDef = {
        PyModuleDef_HEAD_INIT,
        "_png_support",
        nullptr,
        -1,
        _png_support_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__png_support(void) {
    return PyModule_Create(&module_png_supportDef);
  }
  

