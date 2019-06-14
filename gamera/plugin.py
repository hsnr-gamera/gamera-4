# -*- mode: python; indent-tabs-mode: nil; tab-width: 3 -*-
# vim: set tabstop=3 shiftwidth=3 expandtab:
#
# Copyright (C) 2001-2009 Ichiro Fujinaga, Michael Droettboom,
#                         Karl MacMillan, and Christoph Dalitz
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

import copy
import importlib
from importlib import util
import inspect
import os
import os.path
import sys
from types import *

from gamera import util
from gamera.args import *
from gamera.enums import *

plugin_methods = {}


class PluginModule:
    category = None
    cpp_namespaces = []
    cpp_sources = []
    cpp_headers = []
    cpp_defines = []
    cpp_include_dirs = []
    extra_libraries = []
    library_dirs = []
    define_macros = []
    extra_compile_args = []
    extra_link_args = []
    extra_objects = []
    functions = []
    pure_python = False
    version = "1.0"
    author = None
    url = None
    stable = True

    def __init__(self):
        for function in self.functions:
            function.module = self.__class__
        core = __import__("gamera.core")
        if core is None:
            return
        for function in self.functions:
            if not inspect.isclass(function):
                function = function.__class__
            function.register()


class Builtin(PluginModule):
    author = "Michael Droettboom and Karl MacMillan"
    url = "http://dkc.jhu.edu/"


class PluginFunction:
    return_type = None
    self_type = ImageType(ALL)
    args = Args([])
    image_types_must_match = 0
    testable = 0
    feature_function = False
    doc_examples = []
    category = None
    pure_python = False
    progress_bar = ""
    author = None
    add_to_image = True

    def get_formatted_argument_list(cls):
        return "**%s** (%s)" % (cls.__name__, ', '.join(
            [x.rest_repr(True) for x in cls.args.list]))

    get_formatted_argument_list = classmethod(get_formatted_argument_list)

    def escape_docstring(cls):
        if cls.__doc__ is None:
            doc = ''
        doc = util.dedent(cls.__doc__)
        doc = doc.replace("\n", r"\n").replace('"', r'\"')
        return r'"%s\n\n%s"' % (cls.get_formatted_argument_list(), doc)

    escape_docstring = classmethod(escape_docstring)

    def register(cls):
        # add_to_image = add_to_image and cls.add_to_image
        if cls.return_type is not None:
            if cls.return_type.name is None:
                cls.return_type = copy.copy(cls.return_type)
                cls.return_type.name = cls.__name__
        if "__call__" not in cls.__dict__:
            # This loads the actual C++ function if it is not directly
            # linked in the Python PluginFunction class
            parts = cls.__module__.split('.')
            file = inspect.getfile(cls)
            cpp_module_name = '_' + parts[-1]
            directory = os.path.split(file)[0]
            sys.path.append(directory)
            #found = imp.find_module(cpp_module_name)
            spec = importlib.util.find_spec(cpp_module_name)
            module = None
            del sys.path[-1]
            if spec:
                #module = imp.load_module(cpp_module_name, *found)
                module = importlib.util.module_from_spec(spec)
            if module is None:
                return
            func = getattr(module, cls.__name__)
        elif cls.__call__ is None:
            func = None
        else:
            func = cls.__call__
            if isinstance(cls.__call__, MethodType):
                func = cls.__call__.__func__
            func.__doc__ = ("%s\n\n%s" %
                            (cls.get_formatted_argument_list(),
                             util.dedent(cls.__doc__)))
        cls.__call__ = staticmethod(func)

        if cls.category is None:
            category = cls.module.category
        else:
            category = cls.category
        if not category is None and not func is None:
            image_type = isinstance(cls.self_type, ImageType)
            if image_type:
                pixel_types = cls.self_type.pixel_types
            else:
                pixel_types = [NONIMAGE]
            for pixel_type in pixel_types:
                if pixel_type not in plugin_methods:
                    plugin_methods[pixel_type] = {}
                start = plugin_methods[pixel_type]
                for subcategory in category.split('/'):
                    if subcategory not in start:
                        start[subcategory] = {}
                    start = start[subcategory]
                start[cls.__name__] = cls

        if not func is None and not cls.self_type is None:
            cls.self_type.register(cls, func)

    register = classmethod(register)


def PluginFactory(name, category=None,
                  return_type=None,
                  self_type=ImageType(ALL),
                  args=None):
    from gamera import core
    func = getattr(core.ImageBase, name)
    cls = type(name, (PluginFunction,), {"__doc__": util.dedent(func.__doc__)})
    if not category is None:
        cls.category = category
    cls.return_type = return_type
    cls.self_type = self_type
    if args is None:
        cls.args = Args([])
    else:
        cls.args = args
    func = getattr(core.ImageBase, name)
    cls.__call__ = func
    cls.__doc__ = util.dedent(func.__doc__)
    cls.module = Builtin
    return cls


def get_config_options(command):
    return os.popen(command).read()


def methods_flat_category(category, pixel_type=None):
    if pixel_type is None:
        methods = set()
        for pixel_type in ALL + [NONIMAGE]:
            # We have to cast the lists to sets here to make Python 2.3.0 happy.
            methods.update(set(methods_flat_category(category, pixel_type)))
        return list(methods)
    elif pixel_type in plugin_methods:
        methods = plugin_methods[pixel_type]
        if category in methods:
            return _methods_flatten(methods[category])
    return []


def _methods_flatten(mat):
    list = []
    for key, val in mat.items():
        if type(val) is dict:
            list.extend(_methods_flatten(val))
        else:
            list.append((key, val))
    return list
