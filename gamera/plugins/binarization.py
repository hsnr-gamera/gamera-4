#
#
# Copyright (C) 2005 John Ashley Burgoyne and Ichiro Fujinaga
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
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#


# TODO: Add GREY16 compatibility.
# TODO: Add Yanowitz and Bruckstein post-processing (a la Trier and Jain).

"""Adaptive binarization tools."""

from gamera.plugin import *
import _binarization

class image_mean(PluginFunction):
    """Returns the mean over all pixels of an image as a FLOAT."""
    return_type = Real("output")
    self_type = ImageType([GREYSCALE,GREY16,FLOAT])
    def __call__(self):
        return _binarization.image_mean(self)
    __call__ = staticmethod(__call__)


class image_variance(PluginFunction):
    """Returns the variance over all pixels of an image as a FLOAT."""
    return_type = Real("output")
    self_type = ImageType([GREYSCALE,GREY16,FLOAT])
    def __call__(self):
        return _binarization.image_variance(self)
    __call__ = staticmethod(__call__)


class mean_filter(PluginFunction):
    """Returns the regional mean of an image as a FLOAT.

*region_size*
  The size of the region in which to calculate a mean.
"""
    return_type = ImageType([FLOAT], "output")
    self_type = ImageType([GREYSCALE,GREY16,FLOAT])
    args = Args([Int("region size", default=5)])
    doc_examples = [(GREYSCALE,), (GREY16,), (FLOAT,)]
    def __call__(self, region_size=5):
        return _binarization.mean_filter(self, region_size)
    __call__ = staticmethod(__call__)


class variance_filter(PluginFunction):
    """Returns the regional variance of an image as a FLOAT.

*means*
  Pre-calculated means for each region.

*region_size*
  The size of the region in which to calculate the variance.
"""
    return_type = ImageType([FLOAT], "output")
    self_type = ImageType([GREYSCALE,GREY16,FLOAT])
    args = Args([ImageType([FLOAT], "means"),
                 Int("region size", default=5)])
    def __call__(self, means, region_size=5):
        return _binarization.variance_filter(self, means, region_size)
    __call__ = staticmethod(__call__)


class wiener_filter(PluginFunction):
    """Adaptive Wiener filter for de-noising. See:
    
J. Lim. 2001. Two-Dimensional Signal Processing. Englewood Cliffs: Prentice Hall.

*region_size*
  The size of the region within which to calculate the filter coefficients.

*noise_variance* 
  Variance of the noise in the image. If negative, estimated
  automatically as the median of local variances.
"""
    return_type = ImageType([GREYSCALE,GREY16,FLOAT], "output")
    self_type = ImageType([GREYSCALE,GREY16,FLOAT])
    args = Args([Int("region size", default=5),
                 Real("noise variance", default=-1.0)])
    doc_examples = [(GREYSCALE,), (GREY16,), (FLOAT,)]
    def __call__(self, region_size=5, noise_variance=-1):
        return _binarization.wiener_filter(self, region_size, noise_variance)
    __call__ = staticmethod(__call__)


class niblack_threshold(PluginFunction):
    """Creates a binary image using Niblack's adaptive algorithm.

Niblack, W. 1986. An Introduction to Digital Image Processing. Englewood
Cliffs, NJ: Prentice Hall.

Like the QGAR library, there are two extra global thresholds for the lightest
and darkest regions.

*region_size*
  The size of the region in which to calculate a threshold.

*sensitivity*
  The sensitivity weight on the variance.

*lower bound*
  A global threshold beneath which all pixels are considered black.

*upper bound*
  A global threshold above which all pixels are considered white.
"""
    return_type = ImageType([ONEBIT], "output")
    self_type = ImageType([GREYSCALE])
    args = Args([Int("region size", default=15),
                 Real("sensitivity", default=-0.2),
                 Int("lower bound", range=(0,255), default=20),
                 Int("upper bound", range=(0,255), default=150)])
    doc_examples = [(GREYSCALE,)]
    def __call__(self, 
                 region_size=15, 
                 sensitivity=-0.2,
                 lower_bound=20,
                 upper_bound=150):
        return _binarization.niblack_threshold(self, 
                                               region_size, 
                                               sensitivity,
                                               lower_bound,
                                               upper_bound)
    __call__ = staticmethod(__call__)

   
class sauvola_threshold(PluginFunction):
    """Creates a binary image using Sauvola's adaptive algorithm.

Sauvola, J. and M. Pietikainen. 2000. Adaptive document image binarization.
Pattern Recognition 33: 225-236.

Like the QGAR library, there are two extra global thresholds for the lightest
and darkest regions.

*region_size*
  The size of the region in which to calculate a threshold.

*sensitivity*
  The sensitivity weight on the adjusted variance.

*dynamic_range*
  The dynamic range of the variance.

*lower bound*
  A global threshold beneath which all pixels are considered black.

*upper bound*
  A global threshold above which all pixels are considered white.
"""
    return_type = ImageType([ONEBIT], "output")
    self_type = ImageType([GREYSCALE])
    args = Args([Int("region size", default=15),
                 Real("sensitivity", default=0.5),
                 Int("dynamic range", range=(1, 255), default=128),
                 Int("lower bound", range=(0,255), default=20),
                 Int("upper bound", range=(0,255), default=150)])
    doc_examples = [(GREYSCALE,)]
    def __call__(self, 
                 region_size=15, 
                 sensitivity=0.5, 
                 dynamic_range=128,
                 lower_bound=20,
                 upper_bound=150):
        return _binarization.sauvola_threshold(self, 
                                               region_size, 
                                               sensitivity, 
                                               dynamic_range,
                                               lower_bound,
                                               upper_bound)
    __call__ = staticmethod(__call__)

class gatos_background(PluginFunction):
    """Estimates the background of an image according to Gatos et al.'s method. See:

Gatos, Basilios, Ioannis Pratikakis, and Stavros J. Perantonis. 2004. An
adaptive binarization technique for low quality historical documents. Lecture
Notes in Computer Science 3163: 102-113.

*region_size* 
  Region size for interpolation.

*binarization*
  A preliminary binarization of the image.
"""
    return_type = ImageType([GREYSCALE], "output")
    self_type = ImageType([GREYSCALE])
    args = Args([ImageType([ONEBIT], "binarization"),
                 Int("region size", default=15)])
    def __call__(self, binarization, region_size=15):
        return _binarization.gatos_background(self, binarization, region_size)
    __call__ = staticmethod(__call__)
        

class gatos_threshold(PluginFunction):
    """Thresholds an image according to Gatos et al.'s method. See:

Gatos, Basilios, Ioannis Pratikakis, and Stavros J. Perantonis. 2004. An
adaptive binarization technique for low quality historical documents. Lecture
Notes in Computer Science 3163: 102-113.

*background*
  Estimated background of the image.

*binarization*
  A preliminary binarization of the image.

Use the default settings for the other parameters unless you know what you are 
doing.
"""
    return_type = ImageType([ONEBIT], "output")
    self_type = ImageType([GREYSCALE])
    args = Args([ImageType([GREYSCALE], "background"),
                 ImageType([ONEBIT], "binarization"),
                 Real("q", default=0.6),
                 Real("p1", default=0.5),
                 Real("p2", default=0.8)])
    def __call__(self, background, binarization, q=0.6, p1=0.5, p2=0.8):
        return _binarization.gatos_threshold(self, 
                                             background, 
                                             binarization, 
                                             q, 
                                             p1, 
                                             p2)
    __call__ = staticmethod(__call__)


class white_rohrer_threshold(PluginFunction):
    """Creates a binary image using White and Rohrer's dynamic thresholding
algorithm. It is the first of the two algorithms described in:

J. M. White and G. D. Rohrer. 1983. Image thresholding for optical character
recognition and other applications requiring character image extraction.
IBM J. Res. Dev. 27(4), pp. 400-411

The algorithm uses a 'running' average instead of true
average of the gray values in the neighborhood.
The lookahead parameter gives the number of lookahead
pixels used in the biased running average that is used
in deciding the threshold at each pixel location.

Parameters:

 *x_lookahead*
   the number of lookahead pixels in the horizontal direction
   for computing the running average. White and Rohrer suggest a value
   of 8 for a 240 dpi scanning resolution.

 *y_lookahead*
   no of lines used for further averaging from the horizontal averages

The other parameters are for calculating biased running average.
Without bias the thresholding decision would be determined by noise
fluctuations in uniform areas.

This implementation uses code from XITE__. See the corresponding header
source file for details.

.. __: http://www.ifi.uio.no/forskning/grupper/dsb/Software/Xite/
"""
    return_type = ImageType([ONEBIT], "onebit")
    self_type = ImageType([GREYSCALE])
    args = Args([Int("x lookahead", default=8),
                 Int("y lookahead", default=1),
                 Int("bias mode", default=0),
                 Int("bias factor", default=100),
                 Int("f factor",default=100),
                 Int("g factor",default=100)])
    author = "Uma Kompella (using code from the XITE library)"
    doc_examples = [(GREYSCALE,)]

    def __call__(self, x_lookahead=8, y_lookahead=1, bias_mode=0,
				 bias_factor=100, f_factor=100, g_factor=100):
        return _binarization.white_rohrer_threshold(self, 
											   x_lookahead, 
                                               y_lookahead,
                                               bias_mode,
                                               bias_factor,
                                               f_factor,
                                               g_factor)
    __call__ = staticmethod(__call__)


class BinarizationGenerator(PluginModule):
    category = "Binarization"
    cpp_headers = ["binarization.hpp"]
    functions = [image_mean,
                 image_variance,
                 mean_filter,
                 variance_filter,
                 wiener_filter,
                 niblack_threshold, 
                 sauvola_threshold,
                 gatos_background,
                 gatos_threshold,
				 white_rohrer_threshold]
    author = "John Ashley Burgoyne and Ichiro Fujinaga"
    url = "http://gamera.dkc.jhu.edu/"

module = BinarizationGenerator()
