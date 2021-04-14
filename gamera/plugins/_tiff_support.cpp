
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "tiff_support.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_tiff_support(void);
  }
#endif

                static PyObject* call_save_tiff(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      char* image_file_name_arg;
      
                                      if (PyArg_ParseTuple(args,  "Os:save_tiff"
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
save_tiff(*((OneBitImageView*)self_arg), image_file_name_arg);
break;
case CC:
save_tiff(*((Cc*)self_arg), image_file_name_arg);
break;
case ONEBITRLEIMAGEVIEW:
save_tiff(*((OneBitRleImageView*)self_arg), image_file_name_arg);
break;
case RLECC:
save_tiff(*((RleCc*)self_arg), image_file_name_arg);
break;
case MLCC:
save_tiff(*((MlCc*)self_arg), image_file_name_arg);
break;
case GREYSCALEIMAGEVIEW:
save_tiff(*((GreyScaleImageView*)self_arg), image_file_name_arg);
break;
case GREY16IMAGEVIEW:
save_tiff(*((Grey16ImageView*)self_arg), image_file_name_arg);
break;
case RGBIMAGEVIEW:
save_tiff(*((RGBImageView*)self_arg), image_file_name_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'save_tiff' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, and RGB.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                  Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_tiff_info(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        ImageInfo* return_arg;
PyObject* return_pyarg;
                                          char* image_file_name_arg;
      
                                      if (PyArg_ParseTuple(args,  "s:tiff_info"
                        ,
             &image_file_name_arg                      ) <= 0)
           return 0;
               
                    
              try {
                      return_arg = tiff_info(image_file_name_arg);
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
                static PyObject* call_load_tiff(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          char* image_file_name_arg;
                      int storage_format_arg;
      
                                      if (PyArg_ParseTuple(args,  "si:load_tiff"
                        ,
             &image_file_name_arg                        ,
             &storage_format_arg                      ) <= 0)
           return 0;
               
                                  
              try {
                      return_arg = load_tiff(image_file_name_arg, storage_format_arg);
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
      
          static PyMethodDef _tiff_support_methods[] = {
                  {  "save_tiff",
          call_save_tiff, METH_VARARGS,
           "**save_tiff** (``FileSave`` *image_file_name*)\n\nSaves an image to disk in TIFF format.\n\n*image_file_name*\n  A TIFF image filename"        },
                        {  "tiff_info",
          call_tiff_info, METH_VARARGS,
           "**tiff_info** (str *image_file_name*)\n\nReturns an ``ImageInfo`` object describing a TIFF file.\n\n*image_file_name*\n  A TIFF image filename"        },
                        {  "load_tiff",
          call_load_tiff, METH_VARARGS,
           "**load_tiff** (``FileOpen`` *image_file_name*, ``Choice`` [DENSE|RLE] *storage format*)\n\nLoads a TIFF file from disk.\n\n*image_file_name*\n  A TIFF image filename\n\n*storage_format* (optional)\n  specifies the compression type for the result:\n\n  DENSE (0)\n    no compression\n  RLE (1)\n    run-length encoding compression"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_tiff_supportDef = {
        PyModuleDef_HEAD_INIT,
        "_tiff_support",
        nullptr,
        -1,
        _tiff_support_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__tiff_support(void) {
    return PyModule_Create(&module_tiff_supportDef);
  }
  

