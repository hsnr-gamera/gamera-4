
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "pagesegmentation.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_pagesegmentation(void);
  }
#endif

                static PyObject* call_projection_cutting(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::list<Image*>* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int Tx_arg;
                      int Ty_arg;
                      int noise_arg;
                      int gap_treatment_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiiii:projection_cutting"
                        ,
             &self_pyarg                        ,
             &Tx_arg                        ,
             &Ty_arg                        ,
             &noise_arg                        ,
             &gap_treatment_arg                      ) <= 0)
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
return_arg = projection_cutting(*((OneBitImageView*)self_arg), Tx_arg, Ty_arg, noise_arg, gap_treatment_arg);
break;
case CC:
return_arg = projection_cutting(*((Cc*)self_arg), Tx_arg, Ty_arg, noise_arg, gap_treatment_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = projection_cutting(*((OneBitRleImageView*)self_arg), Tx_arg, Ty_arg, noise_arg, gap_treatment_arg);
break;
case RLECC:
return_arg = projection_cutting(*((RleCc*)self_arg), Tx_arg, Ty_arg, noise_arg, gap_treatment_arg);
break;
case MLCC:
return_arg = projection_cutting(*((MlCc*)self_arg), Tx_arg, Ty_arg, noise_arg, gap_treatment_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'projection_cutting' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = ImageList_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                static PyObject* call_runlength_smearing(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                std::list<Image*>* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int Cx_arg;
                      int Cy_arg;
                      int Csm_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiii:runlength_smearing"
                        ,
             &self_pyarg                        ,
             &Cx_arg                        ,
             &Cy_arg                        ,
             &Csm_arg                      ) <= 0)
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
return_arg = runlength_smearing(*((OneBitImageView*)self_arg), Cx_arg, Cy_arg, Csm_arg);
break;
case CC:
return_arg = runlength_smearing(*((Cc*)self_arg), Cx_arg, Cy_arg, Csm_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = runlength_smearing(*((OneBitRleImageView*)self_arg), Cx_arg, Cy_arg, Csm_arg);
break;
case RLECC:
return_arg = runlength_smearing(*((RleCc*)self_arg), Cx_arg, Cy_arg, Csm_arg);
break;
case MLCC:
return_arg = runlength_smearing(*((MlCc*)self_arg), Cx_arg, Cy_arg, Csm_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'runlength_smearing' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              
      return_pyarg = ImageList_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
                            static PyObject* call_sub_cc_analysis(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                PyObject* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      ImageVector cclist_arg;
PyObject* cclist_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:sub_cc_analysis"
                        ,
             &self_pyarg                        ,
             &cclist_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(self_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'self' must be an image");
          return 0;
        }
        self_arg = ((Image*)((RectObject*)self_pyarg)->m_x);
        image_get_fv(self_pyarg, &self_arg->features, &self_arg->features_len);
                      
          const char* type_error_cclist = "Argument 'cclist' must be an iterable of images.";
          PyObject* cclist_pyarg_seq = PySequence_Fast(cclist_pyarg, type_error_cclist);
          if (cclist_pyarg_seq == NULL)
            return 0;
          int cclist_arg_size = PySequence_Fast_GET_SIZE(cclist_pyarg_seq);
          cclist_arg.resize(cclist_arg_size);
          for (int i=0; i < cclist_arg_size; ++i) {
            PyObject *element = PySequence_Fast_GET_ITEM(cclist_pyarg_seq, i);
            if (!is_ImageObject(element)) {
              PyErr_SetString(PyExc_TypeError, type_error_cclist);
              return 0;
            }
            cclist_arg[i] = std::pair<Image*, int>((Image*)(((RectObject*)element)->m_x), get_image_combination(element));
            image_get_fv(element, &cclist_arg[i].first->features,
                         &cclist_arg[i].first->features_len);
          }
          Py_DECREF(cclist_pyarg_seq);      
              try {
                      switch(get_image_combination(self_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = sub_cc_analysis(*((OneBitImageView*)self_arg), cclist_arg);
break;
case CC:
return_arg = sub_cc_analysis(*((Cc*)self_arg), cclist_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = sub_cc_analysis(*((OneBitRleImageView*)self_arg), cclist_arg);
break;
case RLECC:
return_arg = sub_cc_analysis(*((RleCc*)self_arg), cclist_arg);
break;
case MLCC:
return_arg = sub_cc_analysis(*((MlCc*)self_arg), cclist_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'sub_cc_analysis' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
              return_pyarg = return_arg;              return return_pyarg;
            }
                              }
                      static PyObject* call_segmentation_error(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                        IntVector* return_arg;
PyObject* return_pyarg;
                                          Image* Gseg_arg;
PyObject* Gseg_pyarg;
                      Image* Sseg_arg;
PyObject* Sseg_pyarg;
      
                                      if (PyArg_ParseTuple(args,  "OO:segmentation_error"
                        ,
             &Gseg_pyarg                        ,
             &Sseg_pyarg                      ) <= 0)
           return 0;
               
              if (!is_ImageObject(Gseg_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'Gseg' must be an image");
          return 0;
        }
        Gseg_arg = ((Image*)((RectObject*)Gseg_pyarg)->m_x);
        image_get_fv(Gseg_pyarg, &Gseg_arg->features, &Gseg_arg->features_len);
                      if (!is_ImageObject(Sseg_pyarg)) {
          PyErr_SetString(PyExc_TypeError, "Argument 'Sseg' must be an image");
          return 0;
        }
        Sseg_arg = ((Image*)((RectObject*)Sseg_pyarg)->m_x);
        image_get_fv(Sseg_pyarg, &Sseg_arg->features, &Sseg_arg->features_len);
              
              try {
                      switch(get_image_combination(Gseg_pyarg)) {
case ONEBITIMAGEVIEW:
switch(get_image_combination(Sseg_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = segmentation_error(*((OneBitImageView*)Gseg_arg), *((OneBitImageView*)Sseg_arg));
break;
case CC:
return_arg = segmentation_error(*((OneBitImageView*)Gseg_arg), *((Cc*)Sseg_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = segmentation_error(*((OneBitImageView*)Gseg_arg), *((OneBitRleImageView*)Sseg_arg));
break;
case RLECC:
return_arg = segmentation_error(*((OneBitImageView*)Gseg_arg), *((RleCc*)Sseg_arg));
break;
case MLCC:
return_arg = segmentation_error(*((OneBitImageView*)Gseg_arg), *((MlCc*)Sseg_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'Sseg' argument of 'segmentation_error' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(Sseg_pyarg));
return 0;
}
break;
case CC:
switch(get_image_combination(Sseg_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = segmentation_error(*((Cc*)Gseg_arg), *((OneBitImageView*)Sseg_arg));
break;
case CC:
return_arg = segmentation_error(*((Cc*)Gseg_arg), *((Cc*)Sseg_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = segmentation_error(*((Cc*)Gseg_arg), *((OneBitRleImageView*)Sseg_arg));
break;
case RLECC:
return_arg = segmentation_error(*((Cc*)Gseg_arg), *((RleCc*)Sseg_arg));
break;
case MLCC:
return_arg = segmentation_error(*((Cc*)Gseg_arg), *((MlCc*)Sseg_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'Sseg' argument of 'segmentation_error' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(Sseg_pyarg));
return 0;
}
break;
case ONEBITRLEIMAGEVIEW:
switch(get_image_combination(Sseg_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = segmentation_error(*((OneBitRleImageView*)Gseg_arg), *((OneBitImageView*)Sseg_arg));
break;
case CC:
return_arg = segmentation_error(*((OneBitRleImageView*)Gseg_arg), *((Cc*)Sseg_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = segmentation_error(*((OneBitRleImageView*)Gseg_arg), *((OneBitRleImageView*)Sseg_arg));
break;
case RLECC:
return_arg = segmentation_error(*((OneBitRleImageView*)Gseg_arg), *((RleCc*)Sseg_arg));
break;
case MLCC:
return_arg = segmentation_error(*((OneBitRleImageView*)Gseg_arg), *((MlCc*)Sseg_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'Sseg' argument of 'segmentation_error' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(Sseg_pyarg));
return 0;
}
break;
case RLECC:
switch(get_image_combination(Sseg_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = segmentation_error(*((RleCc*)Gseg_arg), *((OneBitImageView*)Sseg_arg));
break;
case CC:
return_arg = segmentation_error(*((RleCc*)Gseg_arg), *((Cc*)Sseg_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = segmentation_error(*((RleCc*)Gseg_arg), *((OneBitRleImageView*)Sseg_arg));
break;
case RLECC:
return_arg = segmentation_error(*((RleCc*)Gseg_arg), *((RleCc*)Sseg_arg));
break;
case MLCC:
return_arg = segmentation_error(*((RleCc*)Gseg_arg), *((MlCc*)Sseg_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'Sseg' argument of 'segmentation_error' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(Sseg_pyarg));
return 0;
}
break;
case MLCC:
switch(get_image_combination(Sseg_pyarg)) {
case ONEBITIMAGEVIEW:
return_arg = segmentation_error(*((MlCc*)Gseg_arg), *((OneBitImageView*)Sseg_arg));
break;
case CC:
return_arg = segmentation_error(*((MlCc*)Gseg_arg), *((Cc*)Sseg_arg));
break;
case ONEBITRLEIMAGEVIEW:
return_arg = segmentation_error(*((MlCc*)Gseg_arg), *((OneBitRleImageView*)Sseg_arg));
break;
case RLECC:
return_arg = segmentation_error(*((MlCc*)Gseg_arg), *((RleCc*)Sseg_arg));
break;
case MLCC:
return_arg = segmentation_error(*((MlCc*)Gseg_arg), *((MlCc*)Sseg_arg));
break;
default:
PyErr_Format(PyExc_TypeError,"The 'Sseg' argument of 'segmentation_error' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(Sseg_pyarg));
return 0;
}
break;
default:
PyErr_Format(PyExc_TypeError,"The 'Gseg' argument of 'segmentation_error' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(Gseg_pyarg));
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
              
      return_pyarg = IntVector_to_python(return_arg);
      delete return_arg;
                    return return_pyarg;
            }
                              }
      
          static PyMethodDef _pagesegmentation_methods[] = {
                  {  "projection_cutting",
          call_projection_cutting, METH_VARARGS,
           "**projection_cutting** (int *Tx* = 0, int *Ty* = 0, int *noise* = 0, ``Choice`` [cut|ignore] *gap_treatment* = cut)\n\nSegments a page with the *Iterative Projection Profile Cuttings*\nmethod.\n\nThe image is split recursively in the horizontal and vertical\ndirection by looking for 'gaps' in the projection profile.  A\n'gap' is a contiguous sequence of projection values smaller than\n*noise* pixels. The splitting is done for each gap wider or higher\nthan given thresholds *Tx* or *Ty*. When no further split points\nare found, the recursion stops.\n\nWhether the resulting segments represent lines, columns or\nparagraphs depends on the values for *Tx* and *Ty*. The return\nvalue is a list of 'CCs' where each 'CC' represents a found\nsegment. Note that the input image is changed such that each pixel\nis set to its CC label.\n\n*Tx*:\n  minimum 'gap' width in the horizontal direction.  When set to\n  zero, *Tx* is set to the median height of all connected\n  component * 7, which might be a reasonable assumption for the\n  gap width between adjacent text columns.\n\n*Ty*:\n  minimum 'gap' width in the vertical direction.  When set to\n  zero, *Ty* is set to half the median height of all connected\n  component, which might be a reasonable assumption for the gap\n  width between adjacent text lines.\n\n*noise*:\n  maximum projection value still considered as belonging to a\n  'gap'.\n\n*gap_treatment*:\n  decides how to treat gaps when *noise* is non zero.\n  When 0 ('cut'), gaps are cut in the middle and the noise pixels\n  in the gap are assigned to the segments.\n  When 1 ('ignore'), noise pixels within the gap are not assigned\n  to a segment, in other words, they are ignored."        },
                        {  "runlength_smearing",
          call_runlength_smearing, METH_VARARGS,
           "**runlength_smearing** (int *Cx* = -1, int *Cy* = -1, int *Csm* = -1)\n\nSegments a page with the *Run Length Smearing* algorithm.\n\nThe algorithm converts white horizontal and vertical runs shorter\nthan given thresholds *Cx* and *Cy* to black pixels (this is the\nso-called 'run length smearing').\n\nThe intersection of both smeared images yields the page segments\nas black regions. As this typically still consists small white\nhorizontal gaps, these gaps narrower than *Csm* are in a final\nstep also filled out.\n\nThe return value is a list of 'CCs' where each 'CC' represents a\nfound segment. Note that the input image is changed such that each\npixel is set to its CC label.\n\nArguments:\n\n*Cx*:\n  Minimal length of white runs in the rows. When set to *-1*, it\n  is set to 20 times the median height of all connected\n  components.\n\n*Cy*:\n  Minimal length of white runs in the columns. When set to *-1*,\n  it is set to 20 times the median height of all connected\n  components.\n\n*Csm*:\n  Minimal length of white runs row-wise in the almost final\n  image. When set to *-1*, it is set to 3 times the median height\n  of all connected components."        },
                                            {  "sub_cc_analysis",
          call_sub_cc_analysis, METH_VARARGS,
           "**sub_cc_analysis** ([object *cclist*])\n\nFurther subsegments the result of a page segmentation algorithm into\ngroups of actual connected components.\n\nThe result of a page segmentation plugin is a list of 'CCs' where\neach 'CC' does not represent a 'connected component', but a page\nsegment (typically a line of text). In a practical OCR application\nyou will however need the actual connected components (which\nshould roughly correspond to the glyphs) in groups of lines. That\nis what this plugin is meant for.\n\nThe input image must be an image that has been processed with a\npage segmentation plugin, i.e. all pixels in the image must be\nlabeled with a segment label. The input parameter *cclist* is the\nlist of segments returned by the page segmentation algorithm.\n\nThe return value is a tuple with two entries:\n\n- a new image with all pixels labeled according to the new CCs\n- a list of ImageLists, each list containing all connected components\n  belonging to the same page segments\n\n\n.. note:: The groups will be returned in the same order as given\n      in *cclist*.  This means that you can sort the page segments\n      by reading order before passing them to *sub_cc_analysis*.\n\n      Note that the order of the returned CCs within each group is\n      not well defined. Hence you will generally need to sort each\n      subgroup by reading order."        },
                                  {  "segmentation_error",
          call_segmentation_error, METH_VARARGS,
           "**segmentation_error** (``Image`` [OneBit] *Gseg*, ``Image`` [OneBit] *Sseg*)\n\nCompares a ground truth segmentation *Gseg* with a segmentation *Sseg*\nand returns error count numbers.\n\nThe input images must be given in such a way that each segment is\nuniquely labeled, similar to the output of a page segmentation\nalgorithm like `runlength_smearing`_. For ground truth data, such a labeled\nimage can be obtained from an external color image with `colors_to_labels`_.\n\n.. _`runlength_smearing`: #runlength-smearing\n.. _`colors_to_labels`: color.html#colors-to-labels\n\nThe two segmentations are compared by building equivalence classes of\noverlapping segments as described in\n\n  M. Thulke, V. Margner, A. Dengel:\n  *A general approach to quality evaluation of document\n  segmentation results.*\n  Lecture Notes in Computer Science 1655, pp. 43-57 (1999)\n\nEach class is assigned an error type depending on how many ground truth\nand test segments it contains. The return value is a tuple\n(*n1,n2,n3,n4,n5,n6)* where each value is the total number of classes\nwith the corresponding error type:\n\n+------+-----------------------+---------------+----------------------+\n| Nr   | Ground truth segments | Test segments | Error type           |\n+======+=======================+===============+======================+\n| *n1* | 1                     | 1             | correct              |\n+------+-----------------------+---------------+----------------------+\n| *n2* | 1                     | 0             | missed segment       |\n+------+-----------------------+---------------+----------------------+\n| *n3* | 0                     | 1             | false positive       |\n+------+-----------------------+---------------+----------------------+\n| *n4* | 1                     | > 1           | split                |\n+------+-----------------------+---------------+----------------------+\n| *n5* | > 1                   | 1             | merge                |\n+------+-----------------------+---------------+----------------------+\n| *n6* | > 1                   | > 1           | splits and merges    |\n+------+-----------------------+---------------+----------------------+\n\nThe total segmentation error can be computed from these numbers as\n*1 - n1 / (n1 + n2 + n3 + n4 + n5 + n6)*. The individual numbers can\nbe of use to determine what exactly is wrong with the segmentation.\n\nAs this function is not an image method, but a free function, it\nis not automatically imported with all plugins and you must import\nit explicitly with\n\n.. code:: Python\n\n      from gamera.plugins.pagesegmentation import segmentation_error\n"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_pagesegmentationDef = {
        PyModuleDef_HEAD_INIT,
        "_pagesegmentation",
        nullptr,
        -1,
        _pagesegmentation_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__pagesegmentation(void) {
    return PyModule_Create(&module_pagesegmentationDef);
  }
  

