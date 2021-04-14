
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "features.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_features(void);
  }
#endif

                static PyObject* call_black_area(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:black_area",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
black_area(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
black_area(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
black_area(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
black_area(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
black_area(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'black_area' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_moments(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:moments",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 9];
         } else {
           if (self_arg->features_len < offset + 9) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
moments(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
moments(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
moments(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
moments(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
moments(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'moments' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 9* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_nholes(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:nholes",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 2];
         } else {
           if (self_arg->features_len < offset + 2) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
nholes(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
nholes(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
nholes(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
nholes(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
nholes(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'nholes' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 2* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_nholes_extended(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:nholes_extended",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 8];
         } else {
           if (self_arg->features_len < offset + 8) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
nholes_extended(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
nholes_extended(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
nholes_extended(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
nholes_extended(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
nholes_extended(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'nholes_extended' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 8* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_volume(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:volume",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
volume(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
volume(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
volume(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
volume(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
volume(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'volume' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_area(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:area",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
area(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
area(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
area(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
area(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
area(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'area' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_aspect_ratio(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:aspect_ratio",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
aspect_ratio(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
aspect_ratio(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
aspect_ratio(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
aspect_ratio(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
aspect_ratio(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'aspect_ratio' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_nrows_feature(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:nrows_feature",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
nrows_feature(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
nrows_feature(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
nrows_feature(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
nrows_feature(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
nrows_feature(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'nrows_feature' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_ncols_feature(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:ncols_feature",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
ncols_feature(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
ncols_feature(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
ncols_feature(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
ncols_feature(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
ncols_feature(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'ncols_feature' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_compactness(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:compactness",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
compactness(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
compactness(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
compactness(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
compactness(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
compactness(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'compactness' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_volume16regions(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:volume16regions",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 16];
         } else {
           if (self_arg->features_len < offset + 16) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
volume16regions(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
volume16regions(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
volume16regions(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
volume16regions(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
volume16regions(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'volume16regions' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 16* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_volume64regions(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:volume64regions",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 64];
         } else {
           if (self_arg->features_len < offset + 64) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
volume64regions(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
volume64regions(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
volume64regions(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
volume64regions(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
volume64regions(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'volume64regions' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 64* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                      static PyObject* call_zernike_moments(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:zernike_moments",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 14];
         } else {
           if (self_arg->features_len < offset + 14) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
zernike_moments(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
zernike_moments(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
zernike_moments(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
zernike_moments(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
zernike_moments(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'zernike_moments' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 14* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_zernike_moments_plugin(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                FloatVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int order_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:zernike_moments_plugin"
                        ,
             &self_pyarg                        ,
             &order_arg                      ) <= 0)
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
return_arg = zernike_moments_plugin(*((GreyScaleImageView*)self_arg), order_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'zernike_moments_plugin' can not have pixel type '%s'. Acceptable value is GREYSCALE.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = FloatVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_skeleton_features(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:skeleton_features",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 6];
         } else {
           if (self_arg->features_len < offset + 6) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
skeleton_features(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
skeleton_features(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
skeleton_features(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
skeleton_features(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
skeleton_features(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'skeleton_features' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 6* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_top_bottom(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:top_bottom",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 2];
         } else {
           if (self_arg->features_len < offset + 2) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
top_bottom(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
top_bottom(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
top_bottom(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
top_bottom(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
top_bottom(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'top_bottom' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 2* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
                static PyObject* call_diagonal_projection(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:diagonal_projection",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 1];
         } else {
           if (self_arg->features_len < offset + 1) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
diagonal_projection(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
diagonal_projection(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
diagonal_projection(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
diagonal_projection(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
diagonal_projection(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'diagonal_projection' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 1* sizeof(feature_t));
           if (str != 0) {
                            PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)"sO", (char *)"d", str);
              Py_XDECREF(str);
              delete[] feature_buffer;
              return array;
           } else {
             delete[] feature_buffer;
             return 0;
           }
         } else {
           Py_XINCREF(Py_None);
           return Py_None;
         }
            }
      
          static PyMethodDef _features_methods[] = {
                  {  "black_area",
          call_black_area, METH_VARARGS,
           "**black_area** ()\n\nThe simplest of all feature-generating functions, ``black_area``\nsimply returns the number of black pixels.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|       |     X    |   X    |\n+-------+----------+--------+\n\n.. warning:: This feature is not scale invariant."        },
                        {  "moments",
          call_moments, METH_VARARGS,
           "**moments** ()\n\nReturns *moments* of the image.\n\nThe first two elements of the returned ``FloatVector`` are the \ncenter of gravity on *x* and *y* axis normalized by width and height,\nrespectively. The following seven entries are the \n*normalized central moments* (*u20,u02,u11,u30,u12,u21,u03*). For their\ndefinition, see Gonzalez, Woods: \"Digital Image Processing\",\nPrentice Hall, second edition (2002).\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |        |\n+-------+----------+--------+"        },
                        {  "nholes",
          call_nholes, METH_VARARGS,
           "**nholes** ()\n\nComputes for each row or column the average number of white runs not\n	touching the border. From these values, the average over all rows and\n	all columns is returned.\n\nThe elements of the returned ``FloatVector`` are:\n\n0. vertical\n1. horizontal\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |   X    |\n+-------+----------+--------+"        },
                        {  "nholes_extended",
          call_nholes_extended, METH_VARARGS,
           "**nholes_extended** ()\n\nDivides the image into four strips and then does a nholes_\nanalysis on each of those strips. This is first done vertically\nand then horizontally, resulting in a total of eight feature values.\n\nThe elements of the returned ``FloatVector`` are:\n\n0 - 3\n  vertical ``nholes`` for each of the strips in order left to right.\n4 - 7\n  horizonal ``nholes`` for each of the strips in order top to bottom.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |        |\n+-------+----------+--------+"        },
                        {  "volume",
          call_volume, METH_VARARGS,
           "**volume** ()\n\nThe percentage of black pixels within the rectangular bounding box\nof the image.  Result in range (0, 1].\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |   X    |\n+-------+----------+--------+"        },
                        {  "area",
          call_area, METH_VARARGS,
           "**area** ()\n\nThe area of the bounding box (i.e. *nrows* * *ncols*).\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|       |          |   X    |\n+-------+----------+--------+"        },
                        {  "aspect_ratio",
          call_aspect_ratio, METH_VARARGS,
           "**aspect_ratio** ()\n\nThe aspect ratio of the bounding box (i.e. *ncols* / *nrows*).\n\nThis feature is scale invariant.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |   X    |\n+-------+----------+--------+"        },
                        {  "nrows_feature",
          call_nrows_feature, METH_VARARGS,
           "**nrows_feature** ()\n\nSimply the number of rows. As this feature is *not* scale\ninvariant, it is helpful for distinguishing similar symbols of\ndifferent size.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|       |          |   X    |\n+-------+----------+--------+"        },
                        {  "ncols_feature",
          call_ncols_feature, METH_VARARGS,
           "**ncols_feature** ()\n\nSimply the number of cols. As this feature is *not* scale\ninvariant, it is helpful for distinguishing similar symbols of\ndifferent size.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|       |          |   X    |\n+-------+----------+--------+"        },
                        {  "compactness",
          call_compactness, METH_VARARGS,
           "**compactness** ()\n\nCompactness is the volume to surface ratio. Highly ornate connected\ncomponents have a low compactness, whereas a perfect circle has a \nhigh compactness. The present implementation of this feature in\nGamera does however not return the compactness, but its *inverse*,\ni.e. the surface to volume ratio.\n\nSince this function requires allocation and deallocation of\nmemory, it is relatively slow.  However, it has proven to be a\nvery useful feature in many cases.\n\nThis feature is not scale invariant, because, as\nthe image is scaled by *a*, the surface increases proportional to *a*\nwhile the volume grows with *a^2*.\nThis is currently not corrected for.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|       |    X     |   X    |\n+-------+----------+--------+"        },
                        {  "volume16regions",
          call_volume16regions, METH_VARARGS,
           "**volume16regions** ()\n\nDivides the image into a 4 x 4 grid of 16 regions and calculates\nthe volume within each. This feature is also known as \"zoning\" method.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |        |\n+-------+----------+--------+"        },
                        {  "volume64regions",
          call_volume64regions, METH_VARARGS,
           "**volume64regions** ()\n\nDivides the image into an 8 x 8 grid of 64 regions and calculates\nthe volume within each. This feature is also known as \"zoning\" method.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |        |\n+-------+----------+--------+"        },
                                  {  "zernike_moments",
          call_zernike_moments, METH_VARARGS,
           "**zernike_moments** ()\n\nComputes the absolute values of the Normalized Zernike Moments up to\norder six.\n\nZernike moments are the scalar product in the complex L2\nHilbert space between the image and the complex Zernike polynomials.\nThis results in complex values, the absolute values of which are\ninvariant under image rotation and reflection. To make them additionally\nscale invariant, different normalization schemes have been suggested.\nThe present implementation normalizes the Zernike moments by\ndivision with the zeroeth geometric moment *m00*, which results\nin an approximate scale invariance according to\nS. Belkasim, E. Hassan, T. Obeidi: \"Explicit invariance of Cartesian\nZernike moments.\" Pattern Recognition Letters 28, pp. 1969-1980 (2007)\n\nThe return values are the absolute values of\n*A20, A22, A31, A33, A40, A42, A44, A51, A53, A54, A60, A62, A64, A66*.\nThe moments *A00* and *A11* are not computed because these are constant\nunder the used normalization scheme.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |    X     |   X    |\n+-------+----------+--------+"        },
                        {  "zernike_moments_plugin",
          call_zernike_moments_plugin, METH_VARARGS,
           "**zernike_moments_plugin** (int *order* = 6)\n\nComputes the absolute values of the Normalized Zernike Moments up to\nthe given order. This is separate from the feature *zernike_moments*,\nbecause features only support onebit images, so we need a different\nfunction for greyscale images.\n\nZernike moments are the scalar product in the complex L2\nHilbert space between the image and the complex Zernike polynomials.\nThis results in complex values, the absolute values of which are\ninvariant under image rotation and reflection. To make them additionally\nscale invariant, different normalization schemes have been suggested.\nThe present implementation normalizes the Zernike moments by\ndivision with the zeroeth geometric moment *m00*, which results\nin an approximate scale invariance according to\nS. Belkasim, E. Hassan, T. Obeidi: \"Explicit invariance of Cartesian\nZernike moments.\" Pattern Recognition Letters 28, pp. 1969-1980 (2007)\n\nThe return values are the absolute values of\n*A20, A22, A31, A33, A40, A42, A44, A51, A53, A54, A60, A62, A64, A66*.\nThe moments *A00* and *A11* are not computed because these are constant\nunder the used normalization scheme."        },
                        {  "skeleton_features",
          call_skeleton_features, METH_VARARGS,
           "**skeleton_features** ()\n\nGenerates a number of features based on the skeleton of an image.\nFirst, the image in skeletonized using the Lee and Chen algorithm,\nwhich guarantees that the pixels of the resulting skeleton are\nnever more than 4-connected.  Then, this skeleton is analysed for\na number of properties:\n\n0. Number of X joints (4-connected pixels)\n1. Number of T joints (3-connected pixels)\n2. Average number of bend points (pixels which do not form a horizontal or\n   vertical line with its neighbors)\n3. Number of end points (1-connected pixels)\n4. Number of *x*-axis crossings with respect to the *x*-axis through the center of mass\n5. Number of *y*-axis crossings with respect to the *y*-axis through the center of mass\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |   X    |\n+-------+----------+--------+"        },
                        {  "top_bottom",
          call_top_bottom, METH_VARARGS,
           "**top_bottom** ()\n\nFeatures useful only for segmentation-free analysis.  Currently,\nthe first feature is the first row containing a black pixel, and\nthe second feature is the last row containing a black pixel.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |   X    |\n+-------+----------+--------+"        },
                        {  "diagonal_projection",
          call_diagonal_projection, METH_VARARGS,
           "**diagonal_projection** ()\n\nComputes the ratio of sum of the interquartile (center plusminus half width)\nrotated projections at +/- 45 degrees.\n\n+---------------------------+\n| **Invariant to:**         |  \n+-------+----------+--------+\n| scale | rotation | mirror | \n+-------+----------+--------+\n|   X   |          |        |\n+-------+----------+--------+"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_featuresDef = {
        PyModuleDef_HEAD_INIT,
        "_features",
        nullptr,
        -1,
        _features_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__features(void) {
    return PyModule_Create(&module_featuresDef);
  }
  

