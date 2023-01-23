# -*- mode: python; indent-tabs-mode: nil; tab-width: 4 -*-
# vim: set tabstop=4 shiftwidth=4 expandtab:
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
import multiprocessing
import glob
import os
import platform

from setuptools import setup, Extension, find_namespace_packages
from distutils.ccompiler import CCompiler
from distutils.command.build_ext import build_ext
from pathlib import Path
import sys
from gamera import gamera_setup

if sys.hexversion < 0x03050000:
    print("At least Python 3.5 is required to build Gamera.  You have")
    print(sys.version)
    sys.exit(1)

# We do this first, so that when gamera.__init__ loads gamera.__version__,
# it is in fact the new and updated version
gamera_version = open("version", 'r').readlines()[0].strip()
long_description = Path('README.md').read_text()

open("gamera/__version__.py", "w").write("ver = '%s'\n\n" % gamera_version)
print("Gamera version:", gamera_version)


##########################################
# generate the plugins
plugins = gamera_setup.get_plugin_filenames('gamera/plugins/')
plugin_extensions = gamera_setup.generate_plugins(plugins, "gamera.plugins")

########################################
# Non-plugin extensions

eodev_files = glob.glob("src/eodev/*.cpp") + glob.glob("src/eodev/*/*.cpp")
eodev_dir = glob.glob("src/eodev/*")
eodev_includes = ["src/eodev"]
for entry in eodev_dir:
    if os.path.isdir(entry):
        eodev_includes.append(entry)

graph_files = glob.glob("gamera/src/graph/*.cpp") + glob.glob("gamera/src/graph/graphmodule/*.cpp")
kdtree_files = ["gamera/src/geostructs/kdtreemodule.cpp", "gamera/src/geostructs/kdtree.cpp"]
# set it to false if you want to disable this feature
has_openmp = None

if has_openmp is None:
    has_openmp = False
    # try to check if openmp can be used
    if platform.system() in ["Linux", "Darwin"]:
        p = os.popen("gcc -dumpversion", "r")
        gccv = p.readline().strip().split(".")
        p.close()
        if int(gccv[0]) > 4 or (int(gccv[0]) == 4 and int(gccv[1]) >= 3):
            has_openmp = True

# write openmp config
f = open("gamera/__compiletime_config__.py", "w")
f.write("# automatically generated configuration at compile time\n")
if has_openmp:
    f.write("has_openmp = True\n")
    print("Compiling genetic algorithms with parallelization (OpenMP)")
else:
    f.write("has_openmp = False\n")
    print("Compiling genetic algorithms without parallelization (OpenMP)")
f.close()

args = []
if has_openmp:
    # Mac OS X need the Xpreprocessor flag for openmp
    if platform.system() == "Darwin":
        args += ["-Xpreprocessor"]
    args += ["-fopenmp"]


ExtGA = Extension("gamera.knnga",
                  ["src/knnga/knnga.cpp", "src/knnga/knngamodule.cpp"] + eodev_files,
                  include_dirs=["gamera/include/gamera", "src"] + eodev_includes,
                  extra_compile_args=gamera_setup.extras['extra_compile_args'] + args,
                  extra_link_args=args
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
                        include_dirs=["gamera/include/gamera"],
                        **gamera_setup.extras
                        ),
              Extension("gamera.knncore",
                        ["src/knncore/knncoremodule.cpp"],
                        include_dirs=["gamera/include/gamera", "src"],
                        **gamera_setup.extras
                        ),
              ExtGA,
              Extension("gamera.graph", graph_files,
                        include_dirs=["gamera/include/gamera", "src", "gamera/include/gamera/graph",
                                      "gamera/src/graph/graphmodule"],
                        **gamera_setup.extras),
              Extension("gamera.kdtree", kdtree_files,
                        include_dirs=["gamera/include/gamera", "src", "gamera/include/gamera/geostructs"],
                        **gamera_setup.extras)]
extensions.extend(plugin_extensions)

# https://stackoverflow.com/a/13176803
# multithreading building, can also be used with setuptools
try:
    from concurrent.futures import ThreadPoolExecutor as Pool
except ImportError:
    from multiprocessing.pool import ThreadPool as LegacyPool

    # To ensure the with statement works. Required for some older 2.7.x releases
    class Pool(LegacyPool):
        def __enter__(self):
            return self

        def __exit__(self, *args):
            self.close()
            self.join()


def _build_extensions(self):
    """Function to monkey-patch
    distutils.command.build_ext.build_ext.build_extensions
    """
    self.check_extensions_list(self.extensions)

    try:
        num_jobs = os.cpu_count()
    except AttributeError:
        num_jobs = multiprocessing.cpu_count()

    with Pool(num_jobs) as pool:
        pool.map(self.build_extension, self.extensions)


def _compile(self, sources, output_dir=None, macros=None, include_dirs=None, debug=0, extra_preargs=None,
             extra_postargs=None, depends=None):
    """Function to monkey-patch distutils.ccompiler.CCompiler"""
    macros, objects, extra_postargs, pp_opts, build = self._setup_compile(
        output_dir, macros, include_dirs, sources, depends, extra_postargs
    )
    cc_args = self._get_cc_args(pp_opts, debug, extra_preargs)

    for obj in objects:
        try:
            src, ext = build[obj]
        except KeyError:
            continue
        self._compile(obj, src, ext, cc_args, extra_postargs, pp_opts)

    # Return *all* object filenames, not just the ones we just built.
    return objects


build_ext.build_extensions = _build_extensions
CCompiler.compile = _compile

if __name__ == "__main__":
    setup(
        name="gamera",
        version=gamera_version,
        ext_modules=extensions,
        python_requires='>=3.5',
        license='GNU GENERAL PUBLIC LICENSE Version 2',
        description=(
            'Gamera is a framework for building document analysis applications. It is not a packaged '
            'document recognition system, but a toolkit for building document image recognition systems.'
        ),
        long_description=long_description,
        long_description_content_type='text/markdown',
        url="https://gamera.sourceforge.net/",
        author="Michael Droettboom and Christoph Dalitz",
        entry_points={
            'gui_scripts': ["gamera_gui=gamera.gamera_gui:gamera_gui"]
        },
        project_urls={
            'Documentation': 'https://gamera.informatik.hsnr.de/docs/gamera-docs/',
            'Source': 'https://github.com/hsnr-gamera/gamera-4'
        },
        include_package_data=True,
        packages=find_namespace_packages(),
        package_data={
            "gamera.src": ["*.hpp", "*.cpp"],
            "gamera.include": ["*.h", "*.hpp", "*.hxx"],
            "gamera.test": ["*.tff"],
            "gamera.pixmaps": ["*.png"]
        },
        classifiers=[
            'Development Status :: 5 - Production/Stable',
            'Intended Audience :: Developers',
            'License :: OSI Approved :: GNU General Public License v2 (GPLv2)',
            'Operating System :: OS Independent',
            'Programming Language :: Python',
            'Programming Language :: Python :: 3',
            'Programming Language :: Python :: 3 :: Only',
            'Topic :: Text Processing',
            'Topic :: Multimedia :: Graphics',
        ],
    )
