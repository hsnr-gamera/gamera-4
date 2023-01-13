# -*- mode: python; indent-tabs-mode: nil; tab-width: 4 -*-
# vim: set tabstop=4 shiftwidth=4 expandtab:
#
# Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, Karl MacMillan
#               2010      Christoph Dalitz
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
from pathlib import Path

from .pyplate import *
from os import path, stat
import sys
from setuptools.extension import Extension

global std_import
global plugins_to_ignore
# we need this import for compiling
from gamera import args_wrappers


def newer(source, target):
    """Return true if 'source' exists and is more recently modified than
    'target', or if 'source' exists and 'target' doesn't.  Return false if
    both exist and 'target' is the same age or younger than 'source'.
    Raise RuntimeError if 'source' does not exist.
    """
    if not path.exists(source):
        raise RuntimeError("file '%s' does not exist" % path.abspath(source))
    if not path.exists(target):
        return 1

    from stat import ST_MTIME

    mtime1 = stat(source)[ST_MTIME]
    mtime2 = stat(target)[ST_MTIME]

    return mtime1 > mtime2


# newer ()

# magic_import and magic_import_setup
#
# This allows us to ignore a list of modules passed into
# magic_import_setup. generate_plugin uses this to prevent
# the loading of C++ modules that may not exist yet during
# the build process.
def magic_import(name, globals_=None, locals_=None, fromlist=None, level=0):
    if fromlist is None:
        fromlist = []
    if locals_ is None:
        locals_ = {}
    if globals_ is None:
        globals_ = {}
    if fromlist is not None and "core" in fromlist:
        fromlist = list(fromlist)
        fromlist.remove("core")

    for x in plugins_to_ignore:
        if name == x:
            return None

    if float(sys.version[0:3]) < 2.45:
        return std_import(name, globals_, locals_, fromlist)
    else:
        return std_import(name, globals_, locals_, fromlist, level)


def magic_import_setup(ignore):
    global plugins_to_ignore
    global std_import
    plugins_to_ignore = ignore
    # Save the standard __import__ function so we can chain to it
    std_import = __builtins__['__import__']
    # Override the __import__ function with our new one
    __builtins__['__import__'] = magic_import


def restore_import():
    global std_import
    __builtins__['__import__'] = std_import


template = Template("""
  [[exec from os import path]]
  [[exec from gamera.enums import *]]
  [[exec from gamera.plugin import *]]
  [[exec from gamera.util import get_pixel_type_name]]

  [[# This should be included first in order to avoid libpng.h/setjmp.h problems. #]]
  [[if module.__class__.__name__ == "PngSupportModule"]]
    #include <png.h>
    #undef _POSIX_C_SOURCE
    #undef _XOPEN_SOURCE
  [[end]]

  #include \"gameramodule.hpp\"
  #include \"knnmodule.hpp\"

  [[# include the headers that the module needs #]]
  [[for header in module.cpp_headers]]
    #include \"[[header]]\"
  [[end]]

  [[# Standard headers used in the plugins #]]
  #include <string>
  #include <stdexcept>
  #include \"Python.h\"
  #include <list>

  using namespace Gamera;
  [[for x in module.cpp_namespaces]]
    using namespace [[x]];
  [[end]]

  [[# Generate the plugin path and module name from the filename. #]]
  [[# The module name for our purposes will be prefixed with an underscore #]]
  [[exec plug_path, filename = path.split(__file__)]]
  [[exec module_name = '_' + filename.split('.')[0] ]]

  [[# Declare all of the functions - because this is a C++ file we have to #]]
  [[# declare the functions as C functions so that Python can access them #]]
#ifndef _MSC_VER
  extern \"C\" {
    void init[[module_name]](void);
  }
#endif

  [[# Each module can declare several functions so we loop through and generate wrapping #]]
  [[# code for each function #]]
  [[for function in module.functions]]
    [[if not function.pure_python]]
      static PyObject* call_[[function.__name__]](PyObject* self, PyObject* args) {
      [[# this holds the self argument - note that the self passed into the function will #]]
      [[# be Null because this functions is not actually bound to an object #]]

      PyErr_Clear();
      [[if function.self_type is None]]
        [[exec args = function.args.list]]
      [[else]]
        [[exec args = [function.self_type] + function.args.list]]
        [[exec function.self_type.name = 'self']]
      [[end]]
      [[# for each argument insert the appropriate conversion code into the string that will #]]
      [[# be passed to PyArg_ParseTuple and create a variable to hold the result. #]]
      [[if function.return_type is not None]]
        [[exec function.return_type.name = 'return']]
        [[exec function.return_type.convert_from_PyObject = True]]
        [[if not function.feature_function]]
          [[function.return_type.declare()]]
        [[end]]
      [[end]]
      [[exec pyarg_format = '']]
      [[for arg in args]]
        [[exec pyarg_format += arg.arg_format]]
        [[arg.declare()]]
      [[end]]

      [[# Now that we have all of the arguments and variables for them we can parse #]]
      [[# the argument tuple. #]]
      [[if function.feature_function]]
         int offset = -1;
         if (PyArg_ParseTuple(args,  \"O|i:[[function.__name__]]\",&[[function.self_type.pysymbol]], &offset) <= 0)
           return 0;
      [[else]]
         [[if pyarg_format != '']]
           if (PyArg_ParseTuple(args,  \"[[pyarg_format]]:[[function.__name__]]\"
           [[for arg in args]]
             ,
             &[[arg.pysymbol]]
           [[end]]
           ) <= 0)
           return 0;
         [[end]]
      [[end]]

      [[for arg in args]]
        [[arg.from_python()]]
      [[end]]

      [[if function.feature_function]]
         feature_t* feature_buffer = 0;
         if (offset < 0) {
           feature_buffer = new feature_t[ [[function.return_type.length]] ];
         } else {
           if (self_arg->features_len < offset + [[function.return_type.length]]) {
             PyErr_Format(PyExc_ValueError, \"Offset as given (%d) will cause data to be written outside of array of length (%d).  Perhaps the feature array is not initialised?\", offset, (int)self_arg->features_len);
             return 0;
           }
           feature_buffer = self_arg->features + offset;
         }
         [[args[0].call(function, args[1:], [])]]
      [[else]]
        try {
          [[if len(args)]]
            [[args[0].call(function, args[1:], [])]]
          [[else]]
            [[if function.return_type is not None]]
              [[function.return_type.symbol]] =
            [[end]]
            [[function.__name__]]([[if function.progress_bar]]ProgressBar("[[function.progress_bar]]")[[else]][[end]]);
          [[end]]
        } catch (std::exception& e) {
          PyErr_SetString(PyExc_RuntimeError, e.what());
          return 0;
        }
      [[end]]

      [[if function.feature_function]]
         if (offset < 0) {
           PyObject* str = PyBytes_FromStringAndSize((char*)feature_buffer, [[function.return_type.length]] * sizeof(feature_t));
           if (str != 0) {
              [[# This is pretty expensive, but simple #]]
              PyObject* array_init = get_ArrayInit();
              if (array_init == 0)
                return 0;
              PyObject* array = PyObject_CallFunction(
                    array_init, (char *)\"sO\", (char *)\"d\", str);
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
      [[else]]
        [[for arg in function.args]]
          [[arg.delete()]]
        [[end]]
        [[if function.return_type is None]]
          Py_XINCREF(Py_None);
          return Py_None;
        [[else]]
          [[if isinstance(function.return_type, (ImageType, Class))]]
            if ([[function.return_type.symbol]] == nullptr) {
              if (PyErr_Occurred() == nullptr) {
                Py_XINCREF(Py_None);
                return Py_None;
               } else
                return nullptr;
            } else {
              [[function.return_type.to_python()]]
              return return_pyarg;
            }
          [[else]]
            [[function.return_type.to_python()]]
            return return_pyarg;
          [[end]]
        [[end]]
      [[end]]
      }
    [[end]]
  [[end]]

  [[# Create the list of methods for the module - the name of the function #]]
  [[# is derived from the name of the class implementing the function - #]]
  [[# also, the function name is prepended with call_ so that there are no clashes #]]
  [[# with the real plugin functions #]]
  static PyMethodDef [[module_name]]_methods[] = {
    [[for function in module.functions]]
      [[if not function.pure_python]]
        {  \"[[function.__name__]]\",
          call_[[function.__name__]], METH_VARARGS,
           [[function.escape_docstring()]]
        },
      [[end]]
    [[end]]
    { nullptr }
  };
  
  static struct PyModuleDef module[[module_name]]Def = {
        PyModuleDef_HEAD_INIT,
        \"[[module_name]]\",
        nullptr,
        -1,
        [[module_name]]_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
  };


  PyMODINIT_FUNC PyInit_[[module_name]](void) {
    return PyModule_Create(&module[[module_name]]Def);
  }
  """)


def generate_plugin(plugin_filename, location,
                    extra_compile_args=None, extra_link_args=None,
                    define_macros=None):
    if define_macros is None:
        define_macros = []
    if extra_link_args is None:
        extra_link_args = []
    if extra_compile_args is None:
        extra_compile_args = []

    plug_path, filename = path.split(plugin_filename)
    module_name = filename.split('.')[0]
    cpp_filename = path.join(plug_path, "_" + module_name + ".cpp")

    regenerate = False
    if newer(plugin_filename, cpp_filename) or '-f' in sys.argv:
        regenerate = True

    sys.path.append(plug_path)

    # import plugin
    plugin_module = __import__(module_name)
    if not hasattr(plugin_module, 'module'):
        return None
    if plugin_module.module.pure_python:
        return None

    # see if any of the header files have changed since last time
    # we compiled

    # find gamera include directory
    gamera_include = Path(__file__).parent.joinpath("include/gamera")

    include_dirs = ([gamera_include.absolute().__str__(), plug_path,
                     gamera_include.joinpath("plugins").absolute().__str__()] +
                    plugin_module.module.cpp_include_dirs)
    if not regenerate:
        for header in plugin_module.module.cpp_headers:
            for include_dir in include_dirs:
                header_filename = path.join(include_dir, header)
                if path.exists(header_filename):
                    if newer(header_filename, cpp_filename):
                        regenerate = True
                        break
                    break
            if regenerate:
                break

    if regenerate:
        print("generating wrappers for", module_name, "plugin")
        template.execute_file(cpp_filename, plugin_module.__dict__)
    else:
        print("skipping wrapper generation for", module_name, "plugin (output up-to-date)")

    # make the setuptools extension class for this plugin
    cpp_files = [cpp_filename]
    for file in plugin_module.module.cpp_sources:
        cpp_files.append(file)

    extra_libraries = plugin_module.module.extra_libraries

    return Extension(location + "._" + module_name, cpp_files,
                     include_dirs=include_dirs,
                     library_dirs=plugin_module.module.library_dirs,
                     libraries=extra_libraries,
                     extra_compile_args=plugin_module.module.extra_compile_args + extra_compile_args,
                     extra_link_args=plugin_module.module.extra_link_args + extra_link_args,
                     define_macros=plugin_module.module.define_macros + define_macros,
                     extra_objects=plugin_module.module.extra_objects)
