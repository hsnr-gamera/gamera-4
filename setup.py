#!/usr/bin/env python
# -*- mode: python; indent-tabs-mode: nil; tab-width: 3 -*-
# vim: set tabstop=3 shiftwidth=3 expandtab:
#
# Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, Karl MacMillan
#               2010-2012 Christoph Dalitz
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
import datetime
import glob
import os
import platform
from setuptools import setup, Extension
import sys
from gamera import gamera_setup

# # unfortunately this does not help installing data_files
# # to the same dir as gamera :(
# for scheme in INSTALL_SCHEMES.values():
#     scheme['data'] = scheme['purelib']

# sys.exit(0)

if sys.hexversion < 0x03050000:
    print("At least Python 3.5 is required to build Gamera.  You have")
    print(sys.version)
    sys.exit(1)

# We do this first, so that when gamera.__init__ loads gamera.__version__,
# it is in fact the new and updated version
gamera_version = open("version", 'r').readlines()[0].strip()
has_openmp = None
no_wx = False
i = 0
for argument in sys.argv:
    i = i + 1
    if argument == "--dated_version":
        d = datetime.date.today()
        monthstring = str(d.month)
        daystring = str(d.day)
        if d.month < 10:
            monthstring = '0' + monthstring
        if d.day < 10:
            daystring = '0' + daystring
        gamera_version = "2_nightly_%s%s%s" % (d.year, monthstring, daystring)
        sys.argv.remove(argument)
        break
    elif argument == '--openmp=yes':
        has_openmp = True
        sys.argv.remove(argument)
    elif argument == '--openmp=no':
        has_openmp = False
        sys.argv.remove(argument)
    elif argument == '--nowx':
        no_wx = True
        sys.argv.remove(argument)

open("gamera/__version__.py", "w").write("ver = '%s'\n\n" % gamera_version)
print("Gamera version:", gamera_version)

# query OpenMP (parallelization) support and save it to compile time config file
if has_openmp is None:
    has_openmp = False
    if platform.system() == "Linux":
        p = os.popen("gcc -dumpversion", "r")
        gccv = p.readline().strip().split(".")
        p.close()
        if int(gccv[0]) > 4 or (int(gccv[0]) == 4 and int(gccv[1]) >= 3):
            has_openmp = True
f = open("gamera/__compiletime_config__.py", "w")
f.write("# automatically generated configuration at compile time\n")
if has_openmp:
    f.write("has_openmp = True\n")
    print("Compiling genetic algorithms with parallelization (OpenMP)")
else:
    f.write("has_openmp = False\n")
    print("Compiling genetic algorithms without parallelization (OpenMP)")
f.close()

##########################################
# generate the plugins
plugins = gamera_setup.get_plugin_filenames('gamera/plugins/')
plugin_extensions = gamera_setup.generate_plugins(plugins, "gamera.plugins", True)

########################################
# Non-plugin extensions

eodev_files = glob.glob("src/eodev/*.cpp") + glob.glob("src/eodev/*/*.cpp")
eodev_dir = glob.glob("src/eodev/*")
eodev_includes = ["src/eodev"]
for entry in eodev_dir:
    if os.path.isdir(entry):
        eodev_includes.append(entry)

graph_files = glob.glob("src/graph/*.cpp") + glob.glob("src/graph/graphmodule/*.cpp")
kdtree_files = ["src/geostructs/kdtreemodule.cpp", "src/geostructs/kdtree.cpp"]

# libstdc++ does not exist with MS VC, but is linke dby default
galibraries = ["stdc++"]
if has_openmp:
   ExtGA = Extension("gamera.knnga",
                     ["src/knnga/knnga.cpp", "src/knnga/knngamodule.cpp"] + eodev_files,
                     include_dirs=["include", "src"] + eodev_includes,
                     libraries=galibraries,
                     extra_compile_args=gamera_setup.extras['extra_compile_args'] + ["-fopenmp"],
                     extra_link_args=["-fopenmp"]
                     )
else:
   ExtGA = Extension("gamera.knnga",
                     ["src/knnga/knnga.cpp", "src/knnga/knngamodule.cpp"] + eodev_files,
                     include_dirs=["include", "src"] + eodev_includes,
                     libraries=galibraries,
                     extra_compile_args=gamera_setup.extras['extra_compile_args']
                     )

extensions = [Extension("gamera.gameracore",
                        ["src/gameracore/gameramodule.cpp",
                         "src/gameracore/sizeobject.cpp",
                         "src/gameracore/pointobject.cpp",
                         "src/gameracore/floatpointobject.cpp",
                         "src/gameracore/dimobject.cpp",
                         "src/gameracore/rectobject.cpp",
                         "src/gameracore/regionobject.cpp",
                         "src/gameracore/regionmapobject.cpp",
                         "src/gameracore/rgbpixelobject.cpp",
                         "src/gameracore/imagedataobject.cpp",
                         "src/gameracore/imageobject.cpp",
                         "src/gameracore/imageinfoobject.cpp",
                         "src/gameracore/iteratorobject.cpp"
                         ],
                        include_dirs=["include"],
                        **gamera_setup.extras
                        ),
              Extension("gamera.knncore",
                        ["src/knncore/knncoremodule.cpp"],
                        include_dirs=["include", "src"],
                        **gamera_setup.extras
                        ),
              ExtGA,
              Extension("gamera.graph", graph_files,
                        include_dirs=["include", "src", "include/graph", "src/graph/graphmodule"],
                        **gamera_setup.extras),
              Extension("gamera.kdtree", kdtree_files,
                        include_dirs=["include", "src", "include/geostructs"],
                        **gamera_setup.extras)]
extensions.extend(plugin_extensions)

##########################################
# Here's the basic setuptools stuff
packages = ['gamera', 'gamera.gui', 'gamera.gui.gaoptimizer', 'gamera.plugins',
            'gamera.toolkits', 'gamera.backport']

includes = [(os.path.join(path), glob.glob(os.path.join("include", os.path.join(path, ext))))
            for path, ext in
            [("", "*.hpp"),
             ("plugins", "*.hpp"),
             ("vigra", "*.hxx"),
             ("geostructs", "*.hpp"),
             ("graph", "*.hpp")]]

srcfiles = [(os.path.join(path), glob.glob(os.path.join(path, ext)))
            for path, ext in
            [("src/geostructs", "*.cpp"), ("src/graph", "*.cpp")]]

data_files = includes
data_files += srcfiles

setup(version=gamera_version,
      ext_modules=extensions,
      data_files=data_files,
      entry_points={
         'gui_scripts': ["gamera_gui=gamera.gamera_gui:gamera_gui"]
      },
      packages=packages)
