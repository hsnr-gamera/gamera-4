# Utilities to cross-compile for Windows on a Debian box
# with the mingw32 cross-compiler installed.

# This is probably extremely brittle wrt new versions of setuptools,
# since all of this is just monkey-patched in.  Here's hoping that
# someday setuptools will be replaced.

# To use, specify the mingw32_cross compiler to setuptools:
#
#    python setup.py --compiler=mingw32_cross

import os
import sys

if sys.hexversion < 0x2050000:
    print("Cross-compiling has only been tested with Python 2.5.  Your ")
    print("results may vary.")

# Fool our own scripts that decide what to build
sys.platform = 'cygwin'


if sys.version_info[2] == 0:
    LATEST_PYTHON_RELEASE = "%d.%d" % tuple(sys.version_info[:2])
else:
    LATEST_PYTHON_RELEASE = "%d.%d.%d" % tuple(sys.version_info[:3])
PYTHON_LIB = "python%d%d" % tuple(sys.version_info[:2])
PYTHON_WIN32 = "python-win32-%s" % LATEST_PYTHON_RELEASE

prefix = 'i686-pc-mingw32-'
os.environ['CC'] = '%sgcc' % prefix
os.environ['CXX'] = '%sg++' % prefix
os.environ['LD'] = '%sld' % prefix
os.environ['LDFLAGS'] = '-L./%s/dll/ -l%s' % (
    PYTHON_WIN32, PYTHON_LIB)
os.environ['CFLAGS'] = '-I./%s/' % PYTHON_WIN32
os.environ['CXXFLAGS'] = '-I./%s/' % PYTHON_WIN32

if os.system(os.environ['CC'] + " --version") != 0:
    print("It does not appear that you have the mingw32 cross compiler")
    print("installed.  On Debian use:")
    print("   sudo apt-get install mingw32")
    sys.exit(1)

if not os.path.exists(PYTHON_WIN32) or not os.path.isdir(PYTHON_WIN32):
    os.mkdir(PYTHON_WIN32)
    os.chdir(PYTHON_WIN32)
    if (os.system("wget http://python.org/ftp/python/%s/python-%s.msi" %
                  (LATEST_PYTHON_RELEASE, LATEST_PYTHON_RELEASE)) != 0):
        print("Error getting Python Windows distribution")
        sys.exit(1)
    if (os.system("cabextract python-%s.msi" % LATEST_PYTHON_RELEASE) != 0):
        print("Error extracting Python Windows dist.  Do you have cabextract installed?")
        sys.exit(1)
    os.mkdir("dll")
    os.rename("%s.dll" % PYTHON_LIB, "dll/%s.dll" % PYTHON_LIB)
    os.chdir("..")