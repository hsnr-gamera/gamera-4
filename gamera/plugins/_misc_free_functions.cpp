
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "misc_free_functions.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_misc_free_functions(void);
  }
#endif

                static PyObject* call_range_of_float(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PyObject* return_arg;
PyObject* return_pyarg;
                          
                                 
      
              try {
                                    return_arg=
                        range_of_float();
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
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
      
          static PyMethodDef _misc_free_functions_methods[] = {
                  {  "range_of_float",
          call_range_of_float, METH_VARARGS,
           "**range_of_float** ()\n\nReturns a tuple ``(float_min, float_max)`` containing the range\nof a float variable on the used operating system, as given by\n``std::numeric_limits<float>``.\n\nThis should be the same as ``sys.float_info.min`` and ``sys.float_info.max``,\nbut these have been introduced into python as late as 2.6, so we need an own\nimplementation for backward compatibility.\n"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_misc_free_functionsDef = {
        PyModuleDef_HEAD_INIT,
        "_misc_free_functions",
        nullptr,
        -1,
        _misc_free_functions_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__misc_free_functions(void) {
    return PyModule_Create(&module_misc_free_functionsDef);
  }
  

