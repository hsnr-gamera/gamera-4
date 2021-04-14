
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "fourier_features.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_fourier_features(void);
  }
#endif

                static PyObject* call_fourier_broken(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                                        Image* self_arg;
PyObject* self_pyarg;
      
                           int offset = -1;
         if (PyArg_ParseTuple(args,  "O|i:fourier_broken",&self_pyarg, &offset) <= 0)
           return 0;
      
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
              
               feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ 48];
         } else {
           if (self_arg->features_len < offset + 48) {
             PyErr_Format(PyExc_ValueError, "Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
fourier_broken(*((OneBitImageView*)self_arg), feature_buffer);break;
case CC:
fourier_broken(*((Cc*)self_arg), feature_buffer);break;
case ONEBITRLEIMAGEVIEW:
fourier_broken(*((OneBitRleImageView*)self_arg), feature_buffer);break;
case RLECC:
fourier_broken(*((RleCc*)self_arg), feature_buffer);break;
case MLCC:
fourier_broken(*((MlCc*)self_arg), feature_buffer);break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'fourier_broken' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
      
               if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, 48* sizeof(feature_t));
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
      
          static PyMethodDef _fourier_features_methods[] = {
                  {  "fourier_broken",
          call_fourier_broken, METH_VARARGS,
           "**fourier_broken** ()\n\nFourier descriptor for arbitrary (not necessarily connected) shapes\naccording to equations (18) and (19) in \n\n  C. Dalitz, C. Brandt, S. Goebbels, D. Kolanus:\n  `Fourier Descriptors for Broken Shapes`__.\n  EURASIP Journal on Advances in Signal Processing 2013:161, 2013\n \nThe coefficient c_0 is used for scale normalisation. The \nabsolute values of the coefficients A(0), A(N-1) A(1), A(N-2), ... are \nreturned.\n\n    +---------------------------+\n    | **Invariant to:**         |  \n    +-------+----------+--------+\n    | scale | rotation | mirror | \n    +-------+----------+--------+\n    |   X   |     X    |        |\n    +-------+----------+--------+\n\n.. __: http://dx.doi.org/10.1186/1687-6180-2013-161\n"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_fourier_featuresDef = {
        PyModuleDef_HEAD_INIT,
        "_fourier_features",
        nullptr,
        -1,
        _fourier_features_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__fourier_features(void) {
    return PyModule_Create(&module_fourier_featuresDef);
  }
  

