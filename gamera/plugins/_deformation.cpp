
        
    
  #include "gameramodule.hpp"
  #include "knnmodule.hpp"

        #include "deformations.hpp"
  
    #include <string>
  #include <stdexcept>
  #include "Python.h"
  #include <list>

  using namespace Gamera;
  
        
    #ifndef _MSC_VER
  extern "C" {
    void init_deformation(void);
  }
#endif

                static PyObject* call_noise(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int amplitude_arg;
                      int direction_arg;
                      int random_seed_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiii:noise"
                        ,
             &self_pyarg                        ,
             &amplitude_arg                        ,
             &direction_arg                        ,
             &random_seed_arg                      ) <= 0)
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
return_arg = noise(*((OneBitImageView*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case CC:
return_arg = noise(*((Cc*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = noise(*((OneBitRleImageView*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case RLECC:
return_arg = noise(*((RleCc*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case MLCC:
return_arg = noise(*((MlCc*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = noise(*((GreyScaleImageView*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case GREY16IMAGEVIEW:
return_arg = noise(*((Grey16ImageView*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case RGBIMAGEVIEW:
return_arg = noise(*((RGBImageView*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
case FLOATIMAGEVIEW:
return_arg = noise(*((FloatImageView*)self_arg), amplitude_arg, direction_arg, random_seed_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'noise' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_inkrub(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int transcription_prob_arg;
                      int random_seed_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oii:inkrub"
                        ,
             &self_pyarg                        ,
             &transcription_prob_arg                        ,
             &random_seed_arg                      ) <= 0)
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
return_arg = inkrub(*((OneBitImageView*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case CC:
return_arg = inkrub(*((Cc*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = inkrub(*((OneBitRleImageView*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case RLECC:
return_arg = inkrub(*((RleCc*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case MLCC:
return_arg = inkrub(*((MlCc*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = inkrub(*((GreyScaleImageView*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case GREY16IMAGEVIEW:
return_arg = inkrub(*((Grey16ImageView*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case RGBIMAGEVIEW:
return_arg = inkrub(*((RGBImageView*)self_arg), transcription_prob_arg, random_seed_arg);
break;
case FLOATIMAGEVIEW:
return_arg = inkrub(*((FloatImageView*)self_arg), transcription_prob_arg, random_seed_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'inkrub' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_wave(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int amplitude_arg;
                      int period_arg;
                      int direction_arg;
                      int waveform_arg;
                      int offset_arg;
                      double turbulence_arg;
                      int random_seed_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oiiiiidi:wave"
                        ,
             &self_pyarg                        ,
             &amplitude_arg                        ,
             &period_arg                        ,
             &direction_arg                        ,
             &waveform_arg                        ,
             &offset_arg                        ,
             &turbulence_arg                        ,
             &random_seed_arg                      ) <= 0)
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
return_arg = wave(*((OneBitImageView*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case CC:
return_arg = wave(*((Cc*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = wave(*((OneBitRleImageView*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case RLECC:
return_arg = wave(*((RleCc*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case MLCC:
return_arg = wave(*((MlCc*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = wave(*((GreyScaleImageView*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case GREY16IMAGEVIEW:
return_arg = wave(*((Grey16ImageView*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case RGBIMAGEVIEW:
return_arg = wave(*((RGBImageView*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
case FLOATIMAGEVIEW:
return_arg = wave(*((FloatImageView*)self_arg), amplitude_arg, period_arg, direction_arg, waveform_arg, offset_arg, turbulence_arg, random_seed_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'wave' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_ink_diffuse(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      int diffusion_type_arg;
                      double exponential_decay_constant_arg;
                      int random_seed_arg;
      
                                      if (PyArg_ParseTuple(args,  "Oidi:ink_diffuse"
                        ,
             &self_pyarg                        ,
             &diffusion_type_arg                        ,
             &exponential_decay_constant_arg                        ,
             &random_seed_arg                      ) <= 0)
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
return_arg = ink_diffuse(*((OneBitImageView*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case CC:
return_arg = ink_diffuse(*((Cc*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = ink_diffuse(*((OneBitRleImageView*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case RLECC:
return_arg = ink_diffuse(*((RleCc*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case MLCC:
return_arg = ink_diffuse(*((MlCc*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case GREYSCALEIMAGEVIEW:
return_arg = ink_diffuse(*((GreyScaleImageView*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case GREY16IMAGEVIEW:
return_arg = ink_diffuse(*((Grey16ImageView*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case RGBIMAGEVIEW:
return_arg = ink_diffuse(*((RGBImageView*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
case FLOATIMAGEVIEW:
return_arg = ink_diffuse(*((FloatImageView*)self_arg), diffusion_type_arg, exponential_decay_constant_arg, random_seed_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'ink_diffuse' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, ONEBIT, GREYSCALE, GREY16, RGB, and FLOAT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_degrade_kanungo(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double eta_arg;
                      double a0_arg;
                      double a_arg;
                      double b0_arg;
                      double b_arg;
                      int k_arg;
                      int random_seed_arg;
      
                                      if (PyArg_ParseTuple(args,  "Odddddii:degrade_kanungo"
                        ,
             &self_pyarg                        ,
             &eta_arg                        ,
             &a0_arg                        ,
             &a_arg                        ,
             &b0_arg                        ,
             &b_arg                        ,
             &k_arg                        ,
             &random_seed_arg                      ) <= 0)
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
return_arg = degrade_kanungo(*((OneBitImageView*)self_arg), eta_arg, a0_arg, a_arg, b0_arg, b_arg, k_arg, random_seed_arg);
break;
case CC:
return_arg = degrade_kanungo(*((Cc*)self_arg), eta_arg, a0_arg, a_arg, b0_arg, b_arg, k_arg, random_seed_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = degrade_kanungo(*((OneBitRleImageView*)self_arg), eta_arg, a0_arg, a_arg, b0_arg, b_arg, k_arg, random_seed_arg);
break;
case RLECC:
return_arg = degrade_kanungo(*((RleCc*)self_arg), eta_arg, a0_arg, a_arg, b0_arg, b_arg, k_arg, random_seed_arg);
break;
case MLCC:
return_arg = degrade_kanungo(*((MlCc*)self_arg), eta_arg, a0_arg, a_arg, b0_arg, b_arg, k_arg, random_seed_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'degrade_kanungo' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
                static PyObject* call_white_speckles(PyObject* self, PyObject* args) {
            
      PyErr_Clear();
                                                                                Image* return_arg;
PyObject* return_pyarg;
                                          Image* self_arg;
PyObject* self_pyarg;
                      double p_arg;
                      int n_arg;
                      int k_arg;
                      int connectivity_arg;
                      int random_seed_arg;
      
                                      if (PyArg_ParseTuple(args,  "Odiiii:white_speckles"
                        ,
             &self_pyarg                        ,
             &p_arg                        ,
             &n_arg                        ,
             &k_arg                        ,
             &connectivity_arg                        ,
             &random_seed_arg                      ) <= 0)
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
return_arg = white_speckles(*((OneBitImageView*)self_arg), p_arg, n_arg, k_arg, connectivity_arg, random_seed_arg);
break;
case CC:
return_arg = white_speckles(*((Cc*)self_arg), p_arg, n_arg, k_arg, connectivity_arg, random_seed_arg);
break;
case ONEBITRLEIMAGEVIEW:
return_arg = white_speckles(*((OneBitRleImageView*)self_arg), p_arg, n_arg, k_arg, connectivity_arg, random_seed_arg);
break;
case RLECC:
return_arg = white_speckles(*((RleCc*)self_arg), p_arg, n_arg, k_arg, connectivity_arg, random_seed_arg);
break;
case MLCC:
return_arg = white_speckles(*((MlCc*)self_arg), p_arg, n_arg, k_arg, connectivity_arg, random_seed_arg);
break;
default:
PyErr_Format(PyExc_TypeError,"The 'self' argument of 'white_speckles' can not have pixel type '%s'. Acceptable values are ONEBIT, ONEBIT, ONEBIT, ONEBIT, and ONEBIT.", get_pixel_type_name(self_pyarg));
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
      
          static PyMethodDef _deformation_methods[] = {
                  {  "noise",
          call_noise, METH_VARARGS,
           "**noise** (int(0, 500) *amplitude*, ``Choice`` [Horizontal|Vertical] *direction*, int *random_seed* = -1)\n\nCauses random shifting of pixels within a user-specified range, in\na user-specified direction."        },
                        {  "inkrub",
          call_inkrub, METH_VARARGS,
           "**inkrub** (int(0, 500) *transcription_prob*, int *random_seed* = -1)\n\nSimulates rubbing off of ink from another page."        },
                        {  "wave",
          call_wave, METH_VARARGS,
           "**wave** (int(0, 9223372036854775807) *amplitude*, int(0, 9223372036854775807) *period*, ``Choice`` [Horizontal|Vertical] *direction*, ``Choice`` [Sinusoid|Square|Sawtooth|Triangle|Sinc] *waveform*, int *offset*, float *turbulence* = 0.00, int *random_seed* = -1)\n\nCauses periodic disturbance of user-defined frequency, amplitude,\nand direction.  Turbulence specifies the amount of random\nvariation from that line."        },
                        {  "ink_diffuse",
          call_ink_diffuse, METH_VARARGS,
           "**ink_diffuse** (``Choice`` [Linear Horizontal|Linear Vertical|Brownian] *diffusion_type*, float *exponential_decay_constant*, int *random_seed* = -1)\n\nSimulates water-driven diffusion of ink in paper."        },
                        {  "degrade_kanungo",
          call_degrade_kanungo, METH_VARARGS,
           "**degrade_kanungo** (float(0.00, 1.00) *eta*, float(0.00, 1.00) *a0*, float *a*, float(0.00, 1.00) *b0*, float *b*, int *k* = 2, int *random_seed* = 0)\n\nDegrades an image due to a scheme proposed by Kanungo et al.\n(see the reference below). This is supposed to emulate image defects\nintroduced through printing and scanning.\n\nThe degradation scheme depends on six parameters *(eta,a0,a,b0,b,k)* with\nthe following meaning:\n\n  - each foreground pixel (black) is flipped with probability\n    `a0*exp(-a*d^2) + eta`, where d is the distance to the closest\n    background pixel\n\n  - each background pixel (white) is flipped with probability\n    `b0*exp(-b*d^2) + eta`, where d is the distance to the closest\n    foreground pixel\n\n  - eventually a morphological closing operation is performed with a disk\n    of diameter *k*. If you want to skip this step set *k=0*; in that\n    case you should do your own smoothing afterwards.\n\nThe random generator is initialized with *random_seed* for allowing\nreproducible results.\n\nReferences:\n\n  T. Kanungo, R.M. Haralick, H.S. Baird, et al.:\n  *A statistical, nonparametric methodology for document\n  degradation model validation.*\n  IEEE Transactions on Pattern Analysis and Machine Intelligence\n  22, pp. 1209-1223 (2000)\n"        },
                        {  "white_speckles",
          call_white_speckles, METH_VARARGS,
           "**white_speckles** (float(0.00, 1.00) *p*, int *n*, int *k* = 2, ``Choice`` [rook|bishop|king] *connectivity* = king, int *random_seed* = 0)\n\nAdds white speckles to an image. This is supposed to emulate\nimage defects introduced through printing, scanning and thresholding.\n\nThe degradation scheme depends on three parameters *(p,n,k)* with\nthe following meaning:\n\n - Each black pixel in the input image is taken with probability *p*\n   as a starting point for a random walk of length *n*.\n   Consequently *p* can be interpreted as the speckle frequency and *n*\n   as a measure for the speckle size.\n\n - An image containing the random walk is smoothed by a closing operation\n   with a rectangle of size *k*.\n\n - Eventually the image with the random walks is subtracted from the input\n   image, which results in white speckles at the random walk positions\n\nInput arguments:\n\n *p, n, k*:\n   speckle frequency, random walk length and closing disc size\n\n *connectivity*:\n   effects the connectivity of adjacent random walk points as shown\n   in the following figure (in case of bishop moves the final closing\n   operation whitens the neighbouring 4-connected pixels too):\n\n   .. image:: images/randomwalk_connectivity.png\n\nReferences:\n\n  C. Dalitz, M. Droettboom, B. Pranzas, I. Fujinaga:\n  *A Comparative Study of Staff Removal Algorithms.*\n  IEEE Transactions on Pattern Analysis and Machine Intelligence 30,\n  pp. 753-766 (2008)\n"        },
              { nullptr }
  };
  
  static struct PyModuleDef module_deformationDef = {
        PyModuleDef_HEAD_INIT,
        "_deformation",
        nullptr,
        -1,
        _deformation_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit__deformation(void) {
    return PyModule_Create(&module_deformationDef);
  }
  

