
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "runlength.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_runlength(void);
  }
#endif

                static PyObject* call_most_frequent_run(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                int return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      char* color_arg;
                      char* direction_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oss:most_frequent_run"
                        ,
             &self_pyarg                        ,
             &color_arg                        ,
             &direction_arg                      ) <= 0)
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
return_arg = most_frequent_run(*((OneBitImageView*)self_arg), color_arg, direction_arg);
break;
case CC:
return_arg = most_frequent_run(*((Cc*)self_arg), color_arg, direction_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = most_frequent_run(*((OneBitRleImageView*)self_arg), color_arg, direction_arg);
break;
case RLECC:
return_arg = most_frequent_run(*((RleCc*)self_arg), color_arg, direction_arg);
break;
case MLCC:
return_arg = most_frequent_run(*((MlCc*)self_arg), color_arg, direction_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'most_frequent_run' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
                static PyObject* call_most_frequent_runs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int n_arg;
                      char* color_arg;
                      char* direction_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiss:most_frequent_runs"
                        ,
             &self_pyarg                        ,
             &n_arg                        ,
             &color_arg                        ,
             &direction_arg                      ) <= 0)
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
return_arg = most_frequent_runs(*((OneBitImageView*)self_arg), n_arg, color_arg, direction_arg);
break;
case CC:
return_arg = most_frequent_runs(*((Cc*)self_arg), n_arg, color_arg, direction_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = most_frequent_runs(*((OneBitRleImageView*)self_arg), n_arg, color_arg, direction_arg);
break;
case RLECC:
return_arg = most_frequent_runs(*((RleCc*)self_arg), n_arg, color_arg, direction_arg);
break;
case MLCC:
return_arg = most_frequent_runs(*((MlCc*)self_arg), n_arg, color_arg, direction_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'most_frequent_runs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_run_histogram(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                IntVector* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      char* color_arg;
                      char* direction_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oss:run_histogram"
                        ,
             &self_pyarg                        ,
             &color_arg                        ,
             &direction_arg                      ) <= 0)
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
return_arg = run_histogram(*((OneBitImageView*)self_arg), color_arg, direction_arg);
break;
case CC:
return_arg = run_histogram(*((Cc*)self_arg), color_arg, direction_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = run_histogram(*((OneBitRleImageView*)self_arg), color_arg, direction_arg);
break;
case RLECC:
return_arg = run_histogram(*((RleCc*)self_arg), color_arg, direction_arg);
break;
case MLCC:
return_arg = run_histogram(*((MlCc*)self_arg), color_arg, direction_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'run_histogram' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = IntVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_filter_narrow_runs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      int length_arg;
                      char* color_arg;
      
                                      if (PyArg_ParseTuple(args,  "Ois:filter_narrow_runs"
                        ,
             &self_pyarg                        ,
             &length_arg                        ,
             &color_arg                      ) <= 0)
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
filter_narrow_runs(*((OneBitImageView*)self_arg), length_arg, color_arg);
break;
case CC:
filter_narrow_runs(*((Cc*)self_arg), length_arg, color_arg);
break;
case ONEBITRLEIMAGEVIEW:
filter_narrow_runs(*((OneBitRleImageView*)self_arg), length_arg, color_arg);
break;
case RLECC:
filter_narrow_runs(*((RleCc*)self_arg), length_arg, color_arg);
break;
case MLCC:
filter_narrow_runs(*((MlCc*)self_arg), length_arg, color_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'filter_narrow_runs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_filter_wide_runs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      int length_arg;
                      char* color_arg;
      
                                      if (PyArg_ParseTuple(args,  "Ois:filter_wide_runs"
                        ,
             &self_pyarg                        ,
             &length_arg                        ,
             &color_arg                      ) <= 0)
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
filter_wide_runs(*((OneBitImageView*)self_arg), length_arg, color_arg);
break;
case CC:
filter_wide_runs(*((Cc*)self_arg), length_arg, color_arg);
break;
case ONEBITRLEIMAGEVIEW:
filter_wide_runs(*((OneBitRleImageView*)self_arg), length_arg, color_arg);
break;
case RLECC:
filter_wide_runs(*((RleCc*)self_arg), length_arg, color_arg);
break;
case MLCC:
filter_wide_runs(*((MlCc*)self_arg), length_arg, color_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'filter_wide_runs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_filter_short_runs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      int length_arg;
                      char* color_arg;
      
                                      if (PyArg_ParseTuple(args,  "Ois:filter_short_runs"
                        ,
             &self_pyarg                        ,
             &length_arg                        ,
             &color_arg                      ) <= 0)
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
filter_short_runs(*((OneBitImageView*)self_arg), length_arg, color_arg);
break;
case CC:
filter_short_runs(*((Cc*)self_arg), length_arg, color_arg);
break;
case ONEBITRLEIMAGEVIEW:
filter_short_runs(*((OneBitRleImageView*)self_arg), length_arg, color_arg);
break;
case RLECC:
filter_short_runs(*((RleCc*)self_arg), length_arg, color_arg);
break;
case MLCC:
filter_short_runs(*((MlCc*)self_arg), length_arg, color_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'filter_short_runs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_filter_tall_runs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      int length_arg;
                      char* color_arg;
      
                                      if (PyArg_ParseTuple(args,  "Ois:filter_tall_runs"
                        ,
             &self_pyarg                        ,
             &length_arg                        ,
             &color_arg                      ) <= 0)
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
filter_tall_runs(*((OneBitImageView*)self_arg), length_arg, color_arg);
break;
case CC:
filter_tall_runs(*((Cc*)self_arg), length_arg, color_arg);
break;
case ONEBITRLEIMAGEVIEW:
filter_tall_runs(*((OneBitRleImageView*)self_arg), length_arg, color_arg);
break;
case RLECC:
filter_tall_runs(*((RleCc*)self_arg), length_arg, color_arg);
break;
case MLCC:
filter_tall_runs(*((MlCc*)self_arg), length_arg, color_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'filter_tall_runs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                    Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_iterate_runs(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      char* color_arg;
                      char* direction_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oss:iterate_runs"
                        ,
             &self_pyarg                        ,
             &color_arg                        ,
             &direction_arg                      ) <= 0)
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
return_arg = iterate_runs(*((OneBitImageView*)self_arg), color_arg, direction_arg);
break;
case CC:
return_arg = iterate_runs(*((Cc*)self_arg), color_arg, direction_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = iterate_runs(*((OneBitRleImageView*)self_arg), color_arg, direction_arg);
break;
case RLECC:
return_arg = iterate_runs(*((RleCc*)self_arg), color_arg, direction_arg);
break;
case MLCC:
return_arg = iterate_runs(*((MlCc*)self_arg), color_arg, direction_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'iterate_runs' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_to_rle(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::string return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "O:to_rle"
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
return_arg = to_rle(*((OneBitImageView*)self_arg));
break;
case CC:
return_arg = to_rle(*((Cc*)self_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = to_rle(*((OneBitRleImageView*)self_arg));
break;
case RLECC:
return_arg = to_rle(*((RleCc*)self_arg));
break;
case MLCC:
return_arg = to_rle(*((MlCc*)self_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'to_rle' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                            return_pyarg = PyUnicode_FromStringAndSize(return_arg.data(), return_arg.size());            return return_pyarg;
                              }
                static PyObject* call_from_rle(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                          Image* self_arg;
PyObject* self_pyarg;
                      char* runs_arg;
      
                                      if (PyArg_ParseTuple(args,  "Os:from_rle"
                        ,
             &self_pyarg                        ,
             &runs_arg                      ) <= 0)
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
from_rle(*((OneBitImageView*)self_arg), runs_arg);
break;
case CC:
from_rle(*((Cc*)self_arg), runs_arg);
break;
case ONEBITRLEIMAGEVIEW:
from_rle(*((OneBitRleImageView*)self_arg), runs_arg);
break;
case RLECC:
from_rle(*((RleCc*)self_arg), runs_arg);
break;
case MLCC:
from_rle(*((MlCc*)self_arg), runs_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'from_rle' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                  Py_XINCREF(Py_None);
          return Py_None;
                    }
                static PyObject* call_runlength_from_point(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                int return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      FloatPoint point_arg;
PyObject* point_pyarg;
                      char* color_arg;
                      char* direction_arg;
      
                                      if (PyArg_ParseTuple(args,  "OOss:runlength_from_point"
                        ,
             &self_pyarg                        ,
             &point_pyarg                        ,
             &color_arg                        ,
             &direction_arg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
      try {
         point_arg = coerce_FloatPoint(point_pyarg);
      } catch (const std::invalid_argument& e) {
         PyErr_SetString(PyExc_TypeError, "Argument 'point' must be a FloatPoint object, or convertible to a FloatPoint object");
         return 0;
      }
                                        
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = runlength_from_point(*((OneBitImageView*)self_arg), point_arg, color_arg, direction_arg);
break;
case CC:
return_arg = runlength_from_point(*((Cc*)self_arg), point_arg, color_arg, direction_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = runlength_from_point(*((OneBitRleImageView*)self_arg), point_arg, color_arg, direction_arg);
break;
case RLECC:
return_arg = runlength_from_point(*((RleCc*)self_arg), point_arg, color_arg, direction_arg);
break;
case MLCC:
return_arg = runlength_from_point(*((MlCc*)self_arg), point_arg, color_arg, direction_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'runlength_from_point' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
return 0;
}
                  } catch (const std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      
                                                                                                  return_pyarg = PyLong_FromLong((long)return_arg);            return return_pyarg;
                              }
      
          static PyMethodDef _runlength_methods[] = {
                  {  "most_frequent_run",
          call_most_frequent_run, METH_VARARGS,
           "**most_frequent_run** (``ChoiceString(strict)`` [black|white] *color*, ``ChoiceString(strict)`` [horizontal|vertical] *direction*)\n\nReturns the length of the most frequently occurring run of pixels\nin the given color and given direction."        },
                        {  "most_frequent_runs",
          call_most_frequent_runs, METH_VARARGS,
           "**most_frequent_runs** (int *n*, ``ChoiceString(strict)`` [black|white] *color*, ``ChoiceString(strict)`` [horizontal|vertical] *direction*)\n\nReturns the lengths of the *n* most frequently occurring runs in\nthe given *color* and *direction*.\n\n*n*\n  The number of runlengths to return.  If *n* < 0, all runlengths\n  will be returned.\n\nThe return value is a list of 2-tuples.  The first element in the\ntuple is the run length, and the second element is its frequency.\nThe list is sorted by descending frequency."        },
                        {  "run_histogram",
          call_run_histogram, METH_VARARGS,
           "**run_histogram** (``ChoiceString(strict)`` [black|white] *color*, ``ChoiceString(strict)`` [horizontal|vertical] *direction*)\n\nReturns the histogram of runlengths in the given *color* and\n*direction*.\n\n*return_value*\n  The return value is an integer array.  Each index in the array\n  corresponds to a particular run length, and the value at that\n  index is the number of times that that run length occurs in the\n  image."        },
                        {  "filter_narrow_runs",
          call_filter_narrow_runs, METH_VARARGS,
           "**filter_narrow_runs** (int *length*, ``ChoiceString(strict)`` [black|white] *color*)\n\nRemoves horizontal runs in the given *color* narrower than a given\n*length*."        },
                        {  "filter_wide_runs",
          call_filter_wide_runs, METH_VARARGS,
           "**filter_wide_runs** (int *length*, ``ChoiceString(strict)`` [black|white] *color*)\n\nRemoves horizontal runs in the given *color* wider than a given\n*length*."        },
                        {  "filter_short_runs",
          call_filter_short_runs, METH_VARARGS,
           "**filter_short_runs** (int *length*, ``ChoiceString(strict)`` [black|white] *color*)\n\nRemoves vertical runs in the given *color* shorter than a given\n*length*."        },
                        {  "filter_tall_runs",
          call_filter_tall_runs, METH_VARARGS,
           "**filter_tall_runs** (int *length*, ``ChoiceString(strict)`` [black|white] *color*)\n\nRemoves vertical runs in the given *color* taller than a given\n*length*."        },
                        {  "iterate_runs",
          call_iterate_runs, METH_VARARGS,
           "**iterate_runs** (``ChoiceString(strict)`` [black|white] *color*, ``ChoiceString(strict)`` [horizontal|vertical] *direction*)\n\nReturns nested iterators over the runs in the given *color* and\n*direction*.\n\nEach run is returned as a Rect object.\n\nFor example, to iterate over all runs:\n\n.. code:: Python\n\n  for row in image.iterate_black_horizontal_runs():\n  # All the runs in each row\n  for run in row:\n      print run"        },
                        {  "to_rle",
          call_to_rle, METH_VARARGS,
           "**to_rle** ()\n\nEncodes a string-based run-length encoded version of the image.\n\nThe numbers alternate between \"length of black run\" and \"length of\nwhite run\".  Runs go left-to-right, top-to-bottom.  Runs rollover\nthe right hand edge and continue on the left edge of the next run.\n\nTo decode an RLE string, use from_rle_."        },
                        {  "from_rle",
          call_from_rle, METH_VARARGS,
           "**from_rle** (str *runs*)\n\nDecodes a string-based run-length encoded version of the image.\n\nThe numbers alternate between \"length of black run\" and \"length of\nwhite run\".  Runs go left-to-right, top-to-bottom.  Runs rollover\nthe right hand edge and continue on the left edge of the next run.\n\nTo encode an RLE string, use to_rle_."        },
                        {  "runlength_from_point",
          call_runlength_from_point, METH_VARARGS,
           "**runlength_from_point** (``FloatPoint`` *point*, ``ChoiceString(strict)`` [black|white] *color*, ``ChoiceString(strict)`` [top|bottom|left|right] *direction*)\n\nReturns the runlength of *color* in the direction *direction* starting\nfrom one pixel after *point*."        },
              { nullptr }
  };
  
  static struct PyModuleDef module_runlengthDef = {
        PyModuleDef_HEAD_INIT,
        "_runlength",
        nullptr,
        -1,
        _runlength_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__runlength(void) {
    return PyModule_Create(&module_runlengthDef);
  }
  

