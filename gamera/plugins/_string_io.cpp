
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "string_io.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_string_io(void);
  }
#endif

                static PyObject* call__to_raw_string(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:_to_raw_string"
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
return_arg = _to_raw_string(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = _to_raw_string(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = _to_raw_string(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = _to_raw_string(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = _to_raw_string(*((MlCc*)self_arg));
break;
case GREYSCALEIMAGEVIEW:
return_arg = _to_raw_string(*((GreyScaleImageView*)self_arg));
break;
case GREY16IMAGEVIEW:
return_arg = _to_raw_string(*((Grey16ImageView*)self_arg));
break;
case RGBIMAGEVIEW:
return_arg = _to_raw_string(*((RGBImageView*)self_arg));
break;
case FLOATIMAGEVIEW:
return_arg = _to_raw_string(*((FloatImageView*)self_arg));
break;
case COMPLEXIMAGEVIEW:
return_arg = _to_raw_string(*((ComplexImageView*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of '_to_raw_string' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, FLOAT, and COMPLEX.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
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
                static PyObject* call__from_raw_string(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        Image* return_arg;
PyObject* return_pyarg;
                                          Point offset_arg;
PyObject* offset_pyarg;
                      Dim dim_arg;
PyObject* dim_pyarg;
                      int pixel_type_arg;
                      int storage_type_arg;
                      PyObject* data_string_arg;
PyObject* data_string_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OOiiO:_from_raw_string"
                        ,
             &offset_pyarg                        ,
             &dim_pyarg                        ,
             &pixel_type_arg                        ,
             &storage_type_arg                        ,
             &data_string_pyarg                      ) <= 0)
           return 0;
               
              
      try {
         offset_arg = coerce_Point(offset_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'offset' must be a Point, or convertible to a Point");
         return 0;
      }
                    
      if (!is_DimObject(dim_pyarg)) {
        PyErr_SetString(PyExc_TypeError, "Argument 'dim' must be a Dim object");
        return 0;
      }
      dim_arg = *((Dim*)((DimObject*)dim_pyarg)->m_x);                                          data_string_arg = data_string_pyarg;      
              try {
                      return_arg = _from_raw_string(offset_arg, dim_arg, pixel_type_arg, storage_type_arg, data_string_arg);
                  } catch (const std::exception& e) {
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
      
          static PyMethodDef _string_io_methods[] = {
                  {  "_to_raw_string",
          call__to_raw_string, METH_VARARGS,
           "**_to_raw_string** ()\n\nReturns the image's binary data as a Python string.\n\nRequires a copying operation;  may fail for very large images.\n\nThis function is not intended to be used directly.  To move data\nto/from Numeric/numarray/PIL, use the functions in numeric_io.py,\nnumarray_io.py and pil_io.py respectively."        },
                        {  "_from_raw_string",
          call__from_raw_string, METH_VARARGS,
           "**_from_raw_string** (``Point`` *offset*, ``Dim`` *dim*, int *pixel_type*, int *storage_type*, object *data_string*)\n\nInstantiates an image from binary data in a Python string.\n\nRequires a copying operation;  may fail for very large images.\n\nThis function is not intended to be used directly.  To move data\nto/from Numeric/numarray/PIL, use the functions in numeric_io.py,\nnumarray_io.py and pil_io.py respectively."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_string_ioDef = {
        PyModuleDef_HEAD_INIT,
        "_string_io",
        nullptr,
        -1,
        _string_io_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__string_io(void) {
    return PyModule_Create(&module_string_ioDef);
  }
  

