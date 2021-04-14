
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "listutilities.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_listutilities(void);
  }
#endif

                static PyObject* call_permute_list(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        int return_arg;
PyObject* return_pyarg;
                                          PyObject* list_arg;
PyObject* list_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:permute_list"
                        ,
             &list_pyarg                      ) <= 0)
           return 0;
               
              list_arg = list_pyarg;      
              try {
                      return_arg = permute_list(list_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                              return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
                static PyObject* call_all_subsets(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PyObject* return_arg;
PyObject* return_pyarg;
                                          PyObject* list_arg;
PyObject* list_pyarg;
                      int size_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:all_subsets"
                        ,
             &list_pyarg                        ,
             &size_arg                      ) <= 0)
           return 0;
               
              list_arg = list_pyarg;                    
              try {
                      return_arg = all_subsets(list_arg, size_arg);
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
                      static PyObject* call_median_py(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        PyObject* return_arg;
PyObject* return_pyarg;
                                          PyObject* list_arg;
PyObject* list_pyarg;
                      int inlist_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oi:median_py"
                        ,
             &list_pyarg                        ,
             &inlist_arg                      ) <= 0)
           return 0;
               
              list_arg = list_pyarg;                    
              try {
                      return_arg = median_py(list_arg, inlist_arg);
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
                static PyObject* call_kernel_density(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        FloatVector* return_arg;
PyObject* return_pyarg;
                                          FloatVector* values_arg;
PyObject* values_pyarg;
                      FloatVector* x_arg;
PyObject* x_pyarg;
                      double bw_arg;
                      int kernel_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOdi:kernel_density"
                        ,
             &values_pyarg                        ,
             &x_pyarg                        ,
             &bw_arg                        ,
             &kernel_arg                      ) <= 0)
           return 0;
               
              
      values_arg = FloatVector_from_python(values_pyarg);
      if (values_arg == NULL) return 0;
                    
      x_arg = FloatVector_from_python(x_pyarg);
      if (x_arg == NULL) return 0;
                                        
              try {
                      return_arg = kernel_density(values_arg, x_arg, bw_arg, kernel_arg);
                  } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                        delete values_arg;                  delete x_arg;                                                                          if (return_arg== nullptr) {
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
                  
          static PyMethodDef _listutilities_methods[] = {
                  {  "permute_list",
          call_permute_list, METH_VARARGS,
           "**permute_list** (object *list*)\n\nPermutes the given list (in place) one step.\n\nReturns ``True`` if there are more permutations to go.  Returns\n``False`` if permutations are done.\n\nExample usage::\n\n  >>>from gamera.plugins import listutilities\n  >>>a = [1,2,3]\n  >>>while listutilities.permute_list(a):\n  ...    print a\n  ...\n  [2, 1, 3]\n  [1, 3, 2]\n  [3, 1, 2]\n  [2, 3, 1]\n  [3, 2, 1]"        },
                        {  "all_subsets",
          call_all_subsets, METH_VARARGS,
           "**all_subsets** (object *list*, int *size*)\n\nReturns all subsets of size *size* of the given list."        },
                                  {  "median_py",
          call_median_py, METH_VARARGS,
           "**median_py** (object *list*, ``bool`` *inlist*)\n\nThis is only for Gamera's Python-C++ interface."        },
                        {  "kernel_density",
          call_kernel_density, METH_VARARGS,
           "**kernel_density** (``FloatVector`` *values*, ``FloatVector`` *x*, float *bw* = 0.00, ``Choice`` [rectangular|triangular|gaussian] *kernel* = rectangular)\n\nComputes the kernel density for *values* at the specified\n*x*-positions. Reference: S.J. Sheather: \"Density Estimation.\"\nStatistical Science 19 pp. 588-597 (2004).\n\nArguments:\n\n  *values*\n     Sample values from which the density is to be estimated.\n\n  *x*\n     For each value in *x*, the density at this position is returned\n     in the returned float vector.\n\n  *bw*\n     Band width, i.e. the parameter *h* in the kernel density estimator.\n     when set to zero, Silverman's rule of thumb is used, which sets the\n     bandwidth to 0.9 min{sigma, iqr/1.34} n^(-1/5).\n\n  *kernel*\n     The kernel function that weights the values (0 = rectangular, \n     1 = triangular, 2 = Gaussian). A Gaussian kernel produces the smoothest\n     result, but is slightly slower than the other two.\n\n     Note that the kernels are normalized to variance one, which means that\n     the rectangular kernel has support [-sqrt(3), +sqrt(3)], and the\n     triangular kernel has support [-sqrt(6), sqrt(6)].\n"        },
                                  { nullptr }
  };
  
  static struct PyModuleDef module_listutilitiesDef = {
        PyModuleDef_HEAD_INIT,
        "_listutilities",
        nullptr,
        -1,
        _listutilities_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__listutilities(void) {
    return PyModule_Create(&module_listutilitiesDef);
  }
  

