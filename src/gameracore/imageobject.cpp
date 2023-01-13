/*
 * Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, Karl MacMillan
 *               2009      Jonathan Koch
 *               2009-2010 Christoph Dalitz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef GAMERACORE_INTERNAL
#define GAMERACORE_INTERNAL
#endif

#include "gameramodule.hpp"
#include "pixel.hpp"
#include <vector>

using namespace Gamera;


// ...but we must implement dummy __init__ functions
// to suppress deprecation warnings in python 2.6
static int image_init(PyObject *self, PyObject *args, PyObject *kwds) { return 0; };

static int sub_image_init(PyObject *self, PyObject *args, PyObject *kwds) { return 0; };

static int cc_init(PyObject *self, PyObject *args, PyObject *kwds) { return 0; };

static int mlcc_init(PyObject *self, PyObject *args, PyObject *kwds) { return 0; };

static PyTypeObject ImageType = {
		PyVarObject_HEAD_INIT(nullptr, 0)
};

PyTypeObject *get_ImageType() {
	return &ImageType;
}

static PyTypeObject SubImageType = {
		PyVarObject_HEAD_INIT(nullptr, 0)
};

PyTypeObject *get_SubImageType() {
	return &SubImageType;
}

static PyTypeObject CCType = {
		PyVarObject_HEAD_INIT(nullptr, 0)
};

PyTypeObject *get_CCType() {
	return &CCType;
}


static PyObject *_image_new(PyTypeObject *pytype, const Point &offset, const Dim &dim,
		int pixel, int format) {
	/*
	  This is looks really awful, but it is not. We are simply creating a
	  matrix view and some matrix data based on the pixel type and storage
	  format. The python interface only works with the base types, but here
	  we have to create the appropriate C++ type. The type pixel/storage info
	  is stored in the ImageDataObject structure, so we don't need another
	  copy here. Additionally, all of the type information can be determined
	  through RTTI, but it is simpler to use an enum and makes it easier to
	  export to Python.
	*/
	ImageDataObject *py_data = nullptr;
	Rect *image = nullptr;
	try {
		if (format == DENSE) {
			if (pixel == ONEBIT) {
				py_data = (ImageDataObject *) create_ImageDataObject(dim, offset, pixel, format);
				ImageData<OneBitPixel> *data = (ImageData<OneBitPixel> *) (py_data->m_x);
				image = (Rect *) new ImageView<ImageData<OneBitPixel> >(*data, offset, dim);
			} else if (pixel == GREYSCALE) {
				py_data = (ImageDataObject *) create_ImageDataObject(dim, offset, pixel, format);
				ImageData<GreyScalePixel> *data = (ImageData<GreyScalePixel> *) (py_data->m_x);
				image = (Rect *) new ImageView<ImageData<GreyScalePixel> >(*data, offset, dim);
			} else if (pixel == GREY16) {
				py_data = (ImageDataObject *) create_ImageDataObject(dim, offset, pixel, format);
				ImageData<Grey16Pixel> *data = (ImageData<Grey16Pixel> *) (py_data->m_x);
				image = (Rect *) new ImageView<ImageData<Grey16Pixel> >(*data, offset, dim);
			} else if (pixel == Gamera::FLOAT) {
				py_data = (ImageDataObject *) create_ImageDataObject(dim, offset, pixel, format);
				ImageData<FloatPixel> *data = (ImageData<FloatPixel> *) (py_data->m_x);
				image = (Rect *) new ImageView<ImageData<FloatPixel> >(*data, offset, dim);
			} else if (pixel == RGB) {
				py_data = (ImageDataObject *) create_ImageDataObject(dim, offset, pixel, format);
				ImageData<RGBPixel> *data = (ImageData<RGBPixel> *) (py_data->m_x);
				image = (Rect *) new ImageView<ImageData<RGBPixel> >(*data, offset, dim);
			} else if (pixel == Gamera::COMPLEX) {
				py_data = (ImageDataObject *) create_ImageDataObject(dim, offset, pixel, format);
				ImageData<ComplexPixel> *data = (ImageData<ComplexPixel> *) (py_data->m_x);
				image = (Rect *) new ImageView<ImageData<ComplexPixel> >(*data, offset, dim);
			} else {
				PyErr_Format(PyExc_TypeError, "Unknown pixel type '%d'.", pixel);
				return nullptr;
			}
		} else if (format == RLE) {
			if (pixel == ONEBIT) {
				py_data = (ImageDataObject *) create_ImageDataObject(dim, offset, pixel, format);
				RleImageData<OneBitPixel> *data = (RleImageData<OneBitPixel> *) (py_data->m_x);
				image = (Rect *) new ImageView<RleImageData<OneBitPixel> >(*data, offset, dim);
			} else {
				PyErr_SetString(PyExc_TypeError,
				                "Pixel type must be ONEBIT if storage format is RLE.");
				return nullptr;
			}
		} else {
			PyErr_SetString(PyExc_TypeError, "Unknown pixel type/storage format combination.");
			return nullptr;
		}
	} catch (std::exception &e) {
		Py_XDECREF(py_data);
		delete image;
		PyErr_SetString(PyExc_RuntimeError, e.what());
		return nullptr;
	}
	
	ImageObject *o;
	// we do not call rect_new here because we do all of the
	// required initializations
	o = (ImageObject *) pytype->tp_alloc(pytype, 0);
	// initialize the weakreflist
	o->m_weakreflist = nullptr;
	o->m_data = (PyObject *) py_data;
	((RectObject *) o)->m_x = image;
	PyObject *o2 = init_image_members(o);
	return o2;
}

static PyObject *image_new(PyTypeObject *pytype, PyObject *args,
		PyObject *kwds) {
	int num_args = PyTuple_GET_SIZE(args);
	
	if (num_args >= 2 && num_args <= 4) {
		PyObject *a = nullptr;
		PyObject *b = nullptr;
		int pixel = 0;
		int format = 0;
		static const char *kwlist[] = {"a", "b", "pixel_type", "storage_format", nullptr};
		if (PyArg_ParseTupleAndKeywords(args, kwds, (char *) "OO|ii", (char **) kwlist, &a, &b, &pixel, &format)) {
			Point point_a;
			try {
				point_a = coerce_Point(a);
			} catch (const std::invalid_argument& e) {
				goto phase2;
			}
			
			try {
				Point point_b = coerce_Point(b);
				int ncols = point_b.x() - point_a.x() + 1;
				int nrows = point_b.y() - point_a.y() + 1;
				return _image_new(pytype, point_a, Dim(ncols, nrows), pixel, format);
			} catch (const std::invalid_argument& e) {
				PyErr_Clear();
				if (is_SizeObject(b)) {
					Size *size_b = ((SizeObject *) b)->m_x;
					int nrows = size_b->height() + 1;
					int ncols = size_b->width() + 1;
					return _image_new(pytype, point_a, Dim(ncols, nrows), pixel, format);
				} else if (is_DimObject(b)) {
					Dim *dim_b = ((DimObject *) b)->m_x;
					return _image_new(pytype, point_a, *dim_b, pixel, format);
				}
#ifdef GAMERA_DEPRECATED
				else if (is_DimensionsObject(b)) {
				  if (send_deprecation_warning(
					"Image(Point point, Dimensions dimensions, pixel_type, storage_format) \n"
					"is deprecated.\n\n"
					"Reason: (x, y) coordinate consistency. (Dimensions is now deprecated \n"
					"in favor of Dim).\n\n"
					"Use Image((offset_x, offset_y), Dim(ncols, nrows), pixel_type, \n"
					"storage_format) instead.",
					"imageobject.cpp", __LINE__) == 0)
						  return 0;
						Dimensions* dim_b = ((DimensionsObject*)b)->m_x;
						return _image_new(pytype, point_a, Dim(dim_b->ncols(), dim_b->nrows()),
										  pixel, format);
				}
#endif
			}
		}
	}
	
	phase2:
	PyErr_Clear();
	
	if (num_args >= 1 && num_args <= 3) {
		PyObject *src = nullptr;
		int pixel = -1;
		int format = -1;
		static const char *kwlist[] = {"image", "pixel_type", "storage_format", nullptr};
		if (PyArg_ParseTupleAndKeywords(args, kwds, (char *) "O|ii", (char **) kwlist,
		                                &src, &pixel, &format)) {
			if (is_RectObject(src)) {
				Rect *rect = ((RectObject *) src)->m_x;
				if (is_ImageObject(src)) {
					ImageObject *py_src = (ImageObject *) src;
					if (pixel == -1) {
						pixel = ((ImageDataObject *) py_src->m_data)->m_pixel_type;
					}
					if (format == -1) {
						format = ((ImageDataObject *) py_src->m_data)->m_storage_format;
					}
				} else {
					if (pixel == -1)
						pixel = 0;
					if (format == -1)
						format = 0;
				}
				return _image_new(pytype, rect->origin(), rect->dim(), pixel, format);
			}
		}
	}

#ifdef GAMERA_DEPRECATED
	PyErr_Clear();
 
	if (num_args >= 4 && num_args <= 6) {
	  int offset_y, offset_x, nrows, ncols;
	  int pixel = 0;
	  int format = 0;
	  static char *kwlist[] = {"offset_y", "offset_x", "nrows", "ncols", "pixel_type", "storage_format", nullptr};
	  if (PyArg_ParseTupleAndKeywords(args, kwds, "iiii|ii", kwlist,
									  &offset_y, &offset_x, &nrows, &ncols, &pixel, &format)) {
		if (send_deprecation_warning(
  "Image(offset_y, offset_x, nrows, ncols, pixel_type, storage_format) is \n"
  "deprecated.\n\n"
  "Reason: (x, y) coordinate consistency.\n\n"
  "Use Image((offset_x, offset_y), Dim(ncols, nrows), pixel_type, \n"
  "storage_format) instead.",
  "imageobject.cpp", __LINE__) == 0)
		  return 0;
		return _image_new(pytype, Point(offset_x, offset_y), Dim(ncols, nrows),
						  pixel, format);
	  }
	}
#endif /* GAMERA_DEPRECATED */
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to Image constructor.  See the Image docstring for valid arguments.");
	return 0;
}

static PyObject *_sub_image_new(PyTypeObject *pytype, PyObject *py_src, const Point &offset,
		const Dim &dim) {
	if (!is_ImageObject(py_src)) {
		PyErr_SetString(PyExc_TypeError, "First argument to SubImage constructor must be an Image (or SubImage).");
		return nullptr;
	}
	
	int pixel, format;
	ImageObject *src = (ImageObject *) py_src;
	pixel = ((ImageDataObject *) src->m_data)->m_pixel_type;
	format = ((ImageDataObject *) src->m_data)->m_storage_format;
	Rect *subimage = nullptr;
	
	try {
		if (format == DENSE) {
			if (pixel == ONEBIT) {
				ImageData<OneBitPixel> *data =
						((ImageData<OneBitPixel> *) ((ImageDataObject *) src->m_data)->m_x);
				subimage = (Rect *) new ImageView<ImageData<OneBitPixel> >(*data, offset, dim);
			} else if (pixel == GREYSCALE) {
				ImageData<GreyScalePixel> *data =
						((ImageData<GreyScalePixel> *) ((ImageDataObject *) src->m_data)->m_x);
				subimage = (Rect *) new ImageView<ImageData<GreyScalePixel> >(*data, offset, dim);
			} else if (pixel == GREY16) {
				ImageData<Grey16Pixel> *data =
						((ImageData<Grey16Pixel> *) ((ImageDataObject *) src->m_data)->m_x);
				subimage = (Rect *) new ImageView<ImageData<Grey16Pixel> >(*data, offset, dim);
			} else if (pixel == Gamera::FLOAT) {
				ImageData<FloatPixel> *data =
						((ImageData<FloatPixel> *) ((ImageDataObject *) src->m_data)->m_x);
				subimage = (Rect *) new ImageView<ImageData<FloatPixel> >(*data, offset, dim);
			} else if (pixel == RGB) {
				ImageData<RGBPixel> *data =
						((ImageData<RGBPixel> *) ((ImageDataObject *) src->m_data)->m_x);
				subimage = (Rect *) new ImageView<ImageData<RGBPixel> >(*data, offset, dim);
			} else if (pixel == Gamera::COMPLEX) {
				ImageData<ComplexPixel> *data =
						((ImageData<ComplexPixel> *) ((ImageDataObject *) src->m_data)->m_x);
				subimage = (Rect *) new ImageView<ImageData<ComplexPixel> >(*data, offset, dim);
			} else {
				PyErr_Format(PyExc_TypeError, "Unknown pixel type '%d'.  Receiving this error indicates an internal inconsistency or memory corruption.  Please report it on the Gamera mailing list.", pixel);
				return nullptr;
			}
		} else if (format == RLE) {
			if (pixel == ONEBIT) {
				RleImageData<OneBitPixel> *data =
						((RleImageData<OneBitPixel> *) ((ImageDataObject *) src->m_data)->m_x);
				subimage = (Rect *) new ImageView<RleImageData<OneBitPixel> >(*data, offset, dim);
			} else {
				PyErr_SetString(PyExc_TypeError,
				                "Pixel type must be ONEBIT if storage format is RLE.  Receiving this error indicates an internal inconsistency or memory corruption.  Please report it on the Gamera mailing list.");
				return nullptr;
			}
		} else {
			PyErr_SetString(PyExc_TypeError, "Unknown pixel type/storage format combination.  Receiving this error indicates an internal inconsistency or memory corruption.  Please report it on the Gamera mailing list.");
			return nullptr;
		}
	} catch (std::exception &e) {
		delete subimage;
		PyErr_SetString(PyExc_RuntimeError, e.what());
		return nullptr;
	}
	
	ImageObject *o;
	o = (ImageObject *) pytype->tp_alloc(pytype, 0);
	((RectObject *) o)->m_x = subimage;
	o->m_data = ((ImageObject *) py_src)->m_data;
	Py_XINCREF(o->m_data);
	((Image *) ((RectObject *) o)->m_x)->resolution(((Image *) ((RectObject *) py_src)->m_x)->resolution());
	return init_image_members(o);
}

PyObject *sub_image_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
	int num_args = PyTuple_GET_SIZE(args);
	PyObject *image;
	if (num_args == 3) {
		PyObject *a, *b;
		if (PyArg_ParseTuple(args,  "OOO", &image, &a, &b)) {
			Point point_a;
			try {
				point_a = coerce_Point(a);
			} catch (const std::invalid_argument& e) {
				goto phase2;
			}
			try {
				Point point_b = coerce_Point(b);
				int nrows = point_b.y() - point_a.y() + 1;
				int ncols = point_b.x() - point_a.x() + 1;
				return _sub_image_new(pytype, image, point_a, Dim(ncols, nrows));
			} catch (const std::invalid_argument& e) {
				PyErr_Clear();
				if (is_SizeObject(b)) {
					Size *size_b = ((SizeObject *) b)->m_x;
					int nrows = size_b->height() + 1;
					int ncols = size_b->width() + 1;
					return _sub_image_new(pytype, image, point_a, Dim(ncols, nrows));
				} else if (is_DimObject(b)) {
					Dim *dim_b = ((DimObject *) b)->m_x;
					return _sub_image_new(pytype, image, point_a, *dim_b);
				}
#ifdef GAMERA_DEPRECATED
				else if (is_DimensionsObject(b)) {
				  if (send_deprecation_warning(
		"SubImage(image, Point offset, Dimensions dimensions) is deprecated.\n\n"
		"Reason: (x, y) coordinate consistency. (Dimensions is now deprecated \n"
		"in favor of Dim).\n\n"
		"Use Image(image, (offset_x, offset_y), Dim(ncols, nrows)) instead.",
		"imageobject.cpp", __LINE__) == 0)
				return 0;
				  Dimensions* dim_b = ((DimensionsObject*)b)->m_x;
				  int nrows = dim_b->nrows();
				  int ncols = dim_b->ncols();
				  return _sub_image_new(pytype, image, point_a, Dim(ncols, nrows));
				}
#endif
			}
		}
	}
	
	phase2:
	PyErr_Clear();
	
	if (num_args == 2) {
		PyObject *pyrect;
		if (PyArg_ParseTuple(args,  "OO", &image, &pyrect)) {
			if (is_RectObject(pyrect)) {
				Rect *rect = ((RectObject *) pyrect)->m_x;
				return _sub_image_new(pytype, image, rect->origin(), rect->dim());
			}
		}
	}

#ifdef GAMERA_DEPRECATED
	PyErr_Clear();
 
	if (num_args == 5) {
	  int offset_y, offset_x, nrows, ncols;
	  if (PyArg_ParseTuple(args, "Oiiii",
						   &image, &offset_y, &offset_x, &nrows, &ncols) > 0) {
		if (send_deprecation_warning(
  "SubImage(image, offset_y, offset_x, nrows, ncols) is deprecated.\n\n"
  "Reason: (x, y) coordinate consistency.\n\n"
  "Use SubImage(image, (offset_x, offset_y), Dim(ncols, nrows)) instead.",
  "imageobject.cpp", __LINE__) == 0)
		  return 0;
		return _sub_image_new(pytype, image, Point(offset_x, offset_y), Dim(ncols, nrows));
	  }
	}
#endif
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to SubImage constructor.  See the SubImage docstring for valid arguments.");
	return 0;
}

static PyObject *_cc_new(PyTypeObject *pytype, PyObject *py_src, int label,
		const Point &offset, const Dim &dim) {
	if (!is_ImageObject(py_src)) {
		PyErr_SetString(PyExc_TypeError, "First argument to the Cc constructor must be an Image (or SubImage).");
		return nullptr;
	}
	
	int pixel, format;
	ImageObject *src = (ImageObject *) py_src;
	pixel = ((ImageDataObject *) src->m_data)->m_pixel_type;
	format = ((ImageDataObject *) src->m_data)->m_storage_format;
	
	Rect *cc = nullptr;
	
	try {
		if (pixel != ONEBIT) {
			PyErr_SetString(PyExc_TypeError, "Cc objects may only be created from ONEBIT Images.");
			return nullptr;
		}
		
		if (format == DENSE) {
			ImageData<OneBitPixel> *data =
					((ImageData<OneBitPixel> *) ((ImageDataObject *) src->m_data)->m_x);
			cc = (Rect *) new ConnectedComponent<ImageData<OneBitPixel> >(*data, label, offset, dim);
		} else if (format == RLE) {
			RleImageData<OneBitPixel> *data =
					((RleImageData<OneBitPixel> *) ((ImageDataObject *) src->m_data)->m_x);
			cc = (Rect *) new ConnectedComponent<RleImageData<OneBitPixel> >(*data, label, offset, dim);
		} else {
			PyErr_SetString(PyExc_TypeError, "Unknown pixel type/storage format combination.   Receiving this error indicates an internal inconsistency or memory corruption.  Please report it on the Gamera mailing list.");
			return nullptr;
		}
	} catch (std::exception &e) {
		delete cc;
		PyErr_SetString(PyExc_RuntimeError, e.what());
		return nullptr;
	}
	
	ImageObject *o;
	o = (ImageObject *) pytype->tp_alloc(pytype, 0);
	((RectObject *) o)->m_x = cc;
	o->m_data = ((ImageObject *) py_src)->m_data;
	Py_XINCREF(o->m_data);
	// set the resolution
	((Image *) ((RectObject *) o)->m_x)->resolution(((Image *) ((RectObject *) py_src)->m_x)->resolution());
	return init_image_members(o);
}

PyObject *cc_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
	int num_args = PyTuple_GET_SIZE(args);
	PyObject *image = nullptr;
	
	if (num_args == 4) {
		PyObject *a, *b;
		int label;
		if (PyArg_ParseTuple(args,  "OiOO", &image, &label, &a, &b)) {
			Point point_a;
			try {
				point_a = coerce_Point(a);
			} catch (const std::invalid_argument& e) {
				goto phase2;
			}
			try {
				Point point_b = coerce_Point(b);
				int nrows = point_b.y() - point_a.y() + 1;
				int ncols = point_b.x() - point_a.x() + 1;
				return _cc_new(pytype, image, label, point_a, Dim(ncols, nrows));
			} catch (const std::invalid_argument& e) {
				PyErr_Clear();
				if (is_SizeObject(b)) {
					Size *size_b = ((SizeObject *) b)->m_x;
					int nrows = size_b->height() + 1;
					int ncols = size_b->width() + 1;
					return _cc_new(pytype, image, label, point_a, Dim(ncols, nrows));
				} else if (is_DimObject(b)) {
					Dim *dim_b = ((DimObject *) b)->m_x;
					return _cc_new(pytype, image, label, point_a, *dim_b);
				}
#ifdef GAMERA_DEPRECATED
				else if (is_DimensionsObject(b)) {
				  if (send_deprecation_warning(
		"Cc(image, label, Point offset, Dimensions dimensions) is deprecated.\n\n"
		"Reason: (x, y) coordinate consistency. (Dimensions is now deprecated \n"
		"in favor of Dim).\n\n"
		"Use Cc(image, label, (offset_x, offset_y), Dim(ncols, nrows)) instead.",
		"imageobject.cpp", __LINE__) == 0)
					return 0;
				  Dimensions* dim_b = ((DimensionsObject*)b)->m_x;
				  int nrows = dim_b->nrows();
				  int ncols = dim_b->ncols();
				  return _cc_new(pytype, image, label, point_a, Dim(ncols, nrows));
				}
#endif
			}
		}
	}
	
	phase2:
	PyErr_Clear();
	
	if (num_args == 3) {
		int label;
		PyObject *pyrect;
		if (PyArg_ParseTuple(args,  "OiO", &image, &label, &pyrect)) {
			if (is_RectObject(pyrect)) {
				Rect *rect = ((RectObject *) pyrect)->m_x;
				return _cc_new(pytype, image, label, rect->origin(), rect->dim());
			}
		}
	}

#ifdef GAMERA_DEPRECATED
	PyErr_Clear();
	if (num_args == 6) {
	  int offset_y, offset_x, nrows, ncols, label;
	  if (PyArg_ParseTuple(args, "Oiiiii",
						   &image, &label, &offset_y, &offset_x, &nrows, &ncols) > 0) {
		if (send_deprecation_warning(
  "Cc(image, label, offset_y, offset_x, nrows, ncols) is deprecated.\n\n"
  "Reason: (x, y) coordinate consistency.\n\n"
  "Use Cc(image, label, (offset_x, offset_y), Dim(ncols, nrows)) instead.",
  "imageobject.cpp", __LINE__) == 0)
		  return 0;
		return _cc_new(pytype, image, label, Point(offset_x, offset_y), Dim(ncols, nrows));
	  }
	}
#endif
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to Cc constructor.  See the Cc docstring for valid arguments.");
	return 0;
}


static int image_clear(PyObject *self) {
	ImageObject *o = (ImageObject *) self;
	PyObject *tmp = o->m_id_name;
	o->m_id_name = nullptr;
	Py_XDECREF(tmp);
	
	tmp = o->m_confidence;
	o->m_confidence = nullptr;
	Py_XDECREF(tmp);
	
	tmp = o->m_children_images;
	o->m_children_images = nullptr;
	Py_XDECREF(tmp);
	
	return 0;
}

static void image_dealloc(PyObject *self) {
	ImageObject *o = (ImageObject *) self;
	
	if (o->m_weakreflist != nullptr) {
		PyObject_ClearWeakRefs(self);
	}
	
	image_clear(self);
	
	Py_XDECREF(o->m_data);
	Py_XDECREF(o->m_features);
	Py_XDECREF(o->m_classification_state);
	
	delete ((RectObject *) self)->m_x;
	
	self->ob_type->tp_free(self);
}

static int image_traverse(PyObject *self, visitproc visit, void *arg) {
	ImageObject *o = (ImageObject *) self;
	if (o->m_id_name) {
		int err = visit(o->m_id_name, arg);
		if (err)
			return err;
	}
	if (o->m_children_images) {
		int err = visit(o->m_children_images, arg);
		if (err)
			return err;
	}
	return 0;
}

static PyObject *image_repr(PyObject *self) {
	Rect *x = ((RectObject *) self)->m_x;
	return PyUnicode_FromFormat("<gameracore.Image: offset_x = %i, offset_y = %i, ncols = %i, nrows = %i>",
	                            (int) x->offset_x(), (int) x->offset_y(),
	                            (int) x->ncols(), (int) x->nrows());
}

static PyObject *image_get(PyObject *self, const Point &point) {
	RectObject *o = (RectObject *) self;
	ImageDataObject *od = (ImageDataObject *) ((ImageObject *) self)->m_data;
	Rect *r = (Rect *) o->m_x;
	if (point.y() >= r->nrows() || point.x() >= r->ncols()) {
		PyErr_Format(PyExc_IndexError, "('%d', '%d') is out of bounds for image with size ('%d', '%d').  Remember get/set coordinates are relative to the upper left corner of the subimage, not to the corner of the page.", (int) point.x(), (int) point.y(), (int) r->ncols(), (int) r->nrows());
		return 0;
	}
	if (is_CCObject(self)) {
		if (od->m_storage_format == RLE)
			return PyLong_FromLong(((RleCc *) o->m_x)->get(point));
		else
			return PyLong_FromLong(((Cc *) o->m_x)->get(point));
	} else if (is_MLCCObject(self)) {
		return PyLong_FromLong(((MlCc *) o->m_x)->get(point));
	} else if (od->m_storage_format == RLE) {
		return PyLong_FromLong(((OneBitRleImageView *) o->m_x)->get(point));
	} else {
		switch (od->m_pixel_type) {
			case Gamera::FLOAT:
				return PyFloat_FromDouble(((FloatImageView *) o->m_x)->get(point));
				break;
			case Gamera::RGB:
				return create_RGBPixelObject(((RGBImageView *) o->m_x)->get(point));
				break;
			case Gamera::GREYSCALE:
				return PyLong_FromLong(((GreyScaleImageView *) o->m_x)->get(point));
				break;
			case Gamera::GREY16:
				return PyLong_FromLong(((Grey16ImageView *) o->m_x)->get(point));
				break;
			case Gamera::ONEBIT:
				return PyLong_FromLong(((OneBitImageView *) o->m_x)->get(point));
				break;
			case Gamera::COMPLEX: {
				ComplexPixel temp = ((ComplexImageView *) o->m_x)->get(point);
				return PyComplex_FromDoubles(temp.real(), temp.imag());
				break;
			}
			default:
				return 0;
		}
	}
}

static PyObject *image_set(PyObject *self, const Point &point, PyObject *value) {
	RectObject *o = (RectObject *) self;
	ImageDataObject *od = (ImageDataObject *) ((ImageObject *) self)->m_data;
	Rect *r = (Rect *) o->m_x;
	if (point.y() >= r->nrows() || point.x() >= r->ncols()) {
		PyErr_Format(PyExc_IndexError,
		             "('%d', '%d') is out of bounds for image with size ('%d', '%d').  "
		             "Remember get/set coordinates are relative to the upper left corner "
		             "of the subimage, not to the corner of the page.",
		             (int) point.x(), (int) point.y(), (int) r->ncols(), (int) r->nrows());
		return 0;
	}
	if (is_CCObject(self)) {
		if (!PyLong_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for CC objects must be an int.");
			return 0;
		}
		((Cc *) o->m_x)->set(point, (OneBitPixel) PyLong_AS_LONG(value));
	} else if (is_MLCCObject(self)) {
		if (!PyLong_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for MlCc objects must be an int.");
			return 0;
		}
		((MlCc *) o->m_x)->set(point, (OneBitPixel) PyLong_AS_LONG(value));
	} else if (od->m_pixel_type == Gamera::FLOAT) {
		if (!PyFloat_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for Float objects must be a float.");
			return 0;
		}
		((FloatImageView *) o->m_x)->set(point, PyFloat_AS_DOUBLE(value));
	} else if (od->m_storage_format == RLE) {
		if (!PyLong_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for OneBit objects must be an int.");
			return 0;
		}
		((OneBitRleImageView *) o->m_x)->set(point,
		                                     (OneBitPixel) PyLong_AS_LONG(value));
	} else if (od->m_pixel_type == RGB) {
		if (!is_RGBPixelObject((PyObject *) value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for RGB objects must be an RGBPixel");
			return 0;
		}
		RGBPixelObject *v = (RGBPixelObject *) value;
		((RGBImageView *) o->m_x)->set(point, *v->m_x);
	} else if (od->m_pixel_type == GREYSCALE) {
		if (!PyLong_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for GreyScale objects must be an int.");
			return 0;
		}
		((GreyScaleImageView *) o->m_x)->set(point,
		                                     (GreyScalePixel) PyLong_AS_LONG(value));
	} else if (od->m_pixel_type == GREY16) {
		if (!PyLong_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for Grey16 objects must be an int.");
			return 0;
		}
		((Grey16ImageView *) o->m_x)->set(point,
		                                  (Grey16Pixel) PyLong_AS_LONG(value));
	} else if (od->m_pixel_type == ONEBIT) {
		if (!PyLong_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for OneBit objects must be an int.");
			return 0;
		}
		((OneBitImageView *) o->m_x)->set(point,
		                                  (OneBitPixel) PyLong_AS_LONG(value));
	} else if (od->m_pixel_type == Gamera::COMPLEX) {
		if (!PyComplex_Check(value)) {
			PyErr_SetString(PyExc_TypeError, "Pixel value for Complex objects must be a complex number.");
			return 0;
		}
		ComplexPixel temp(PyComplex_RealAsDouble(value), PyComplex_ImagAsDouble(value));
		((ComplexImageView *) o->m_x)->set(point, temp);
	}
	Py_XINCREF(Py_None);
	return Py_None;
}

static PyObject *image_get(PyObject *self, PyObject *args) {
	int num_args = PyTuple_GET_SIZE(args);
	if (num_args == 1) {
		PyObject *py_point;
		if (PyArg_ParseTuple(args,  "O", &py_point)) {
			try {
				return image_get(self, coerce_Point(py_point));
			} catch (const std::invalid_argument& e) {
				PyErr_Clear();
				int i;
				if (PyArg_ParseTuple(args,  "i", &i)) {
					Rect *image = (Image *) ((RectObject *) self)->m_x;
					return image_get(self, Point(i % image->ncols(), i / image->ncols()));
				}
			}
		}
	}

#ifdef GAMERA_DEPRECATED
	PyErr_Clear();
	if (num_args == 2) {
	  int row, col;
	  if (PyArg_ParseTuple(args, "ii", &row, &col)) {
		if (send_deprecation_warning(
  "get(y, x) is deprecated.\n\n"
  "Reason: (x, y) coordinate consistency.\n\n"
  "Use get((x, y)) instead.",
  "imageobject.cpp", __LINE__) == 0)
		  return 0 ;
		return image_get(self, Point(col, row));
	  }
	}
#endif
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to get.  Acceptable forms are: get(Point p), get((x, y)) and get(int index).");
	return 0;
}

static PyObject *image_set(PyObject *self, PyObject *args) {
	int num_args = PyTuple_GET_SIZE(args);
	PyObject *value;
	if (num_args == 2) {
		PyObject *py_point;
		if (PyArg_ParseTuple(args,  "OO", &py_point, &value)) {
			try {
				return image_set(self, coerce_Point(py_point), value);
			} catch (const std::invalid_argument& e) {
				PyErr_Clear();
				int i;
				if (PyArg_ParseTuple(args,  "iO", &i, &value)) {
					Rect *image = ((RectObject *) self)->m_x;
					return image_set(self, Point(i % image->ncols(), i / image->ncols()), value);
				}
			}
		}
	}

#ifdef GAMERA_DEPRECATED
	PyErr_Clear();
	if (num_args == 3) {
	  int row, col;
	  if (PyArg_ParseTuple(args, "iiO", &row, &col, &value)) {
		if (send_deprecation_warning(
  "set(y, x, value) is deprecated.\n\n"
  "Reason: (x, y) coordinate consistency.\n\n"
  "Use set((x, y), value) instead.",
  "imageobject.cpp", __LINE__) == 0)
		  return 0;
		return image_set(self, Point(col, row), value);
	  }
	}
#endif
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError,
	                "Invalid arguments to set.  "
	                "Acceptable forms are: set(Point p, Pixel v), get((x, y), Pixel v) "
	                "and get(Int index, Pixel v).");
	return 0;
}

static PyObject *image_white(PyObject *self, PyObject *args) {
	ImageDataObject *od = (ImageDataObject *) ((ImageObject *) self)->m_data;
	switch (od->m_pixel_type) {
		case Gamera::FLOAT:
			return PyFloat_FromDouble(pixel_traits<FloatPixel>::white());
			break;
		case Gamera::RGB:
			return create_RGBPixelObject(pixel_traits<RGBPixel>::white());
			break;
		case Gamera::GREYSCALE:
			return PyLong_FromLong(pixel_traits<GreyScalePixel>::white());
			break;
		case Gamera::GREY16:
			return PyLong_FromLong(pixel_traits<Grey16Pixel>::white());
			break;
		case Gamera::ONEBIT:
			return PyLong_FromLong(pixel_traits<OneBitPixel>::white());
			break;
		case Gamera::COMPLEX: {
			ComplexPixel temp = pixel_traits<ComplexPixel>::white();
			return PyComplex_FromDoubles(temp.real(), temp.imag());
			break;
		}
		default:
			return 0;
	}
}

static PyObject *image_black(PyObject *self, PyObject *args) {
	ImageDataObject *od = (ImageDataObject *) ((ImageObject *) self)->m_data;
	switch (od->m_pixel_type) {
		case Gamera::FLOAT:
			return PyFloat_FromDouble(pixel_traits<FloatPixel>::black());
			break;
		case Gamera::RGB:
			return create_RGBPixelObject(pixel_traits<RGBPixel>::black());
			break;
		case Gamera::GREYSCALE:
			return PyLong_FromLong(pixel_traits<GreyScalePixel>::black());
			break;
		case Gamera::GREY16:
			return PyLong_FromLong(pixel_traits<Grey16Pixel>::black());
			break;
		case Gamera::ONEBIT:
			return PyLong_FromLong(pixel_traits<OneBitPixel>::black());
			break;
		case Gamera::COMPLEX: {
			ComplexPixel temp = pixel_traits<ComplexPixel>::black();
			return PyComplex_FromDoubles(temp.real(), temp.imag());
			break;
		}
		default:
			return 0;
	}
}

// convert Python indexing into row/col format for images
// Removed, since getitem/setitem now take a tuple of coordinates
/*
static inline int get_rowcol(Image* image, long index, size_t* row, size_t* col) {
  if (index < 0) {
    size_t len = image->ncols() * image->nrows();
    size_t real_index = len + index;
    *row = real_index / image->ncols();
    *col = real_index - (*row * image->ncols());
  } else {
    *row = (size_t)(index / image->ncols());
    *col = (size_t)(index - (*row * image->ncols()));
  }
  if (size_t(*row) >= image->nrows() || size_t(*col) >= image->ncols()) {
    PyErr_SetString(PyExc_IndexError, "Out of bounds for image");
    return -1;
  }
  return 0;
  } */

static PyObject *image_getitem(PyObject *self, PyObject *args) {
	PyObject *arg = PyTuple_GET_ITEM(args, 0);
	Point point;
	if (PyLong_Check(arg)) {
		size_t i;
		i = PyLong_AsLong(arg);
		Rect *image = ((RectObject *) self)->m_x;
		return image_get(self, Point(i % image->ncols(), i / image->ncols()));
	}
	try {
		return image_get(self, coerce_Point(arg));
	} catch (const std::invalid_argument& e) { ;
	}
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to __getitem__.  Acceptable forms are: image[Point p], image[x, y], image[index]");
	return 0;
}

static PyObject *image_setitem(PyObject *self, PyObject *args) {
	PyObject *value;
	PyObject *arg;
	Point point;
	if (PyArg_ParseTuple(args,  "OO", &arg, &value) <= 0)
		return 0;
	if (PyLong_Check(arg)) {
		size_t i;
		i = PyLong_AsLong(arg);
		Rect *image = ((RectObject *) self)->m_x;
		return image_set(self, Point(i % image->ncols(), i / image->ncols()), value);
	}
	try {
		return image_set(self, coerce_Point(arg), value);
	} catch (const std::invalid_argument& e) { ;
	}
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to __setitem__.  Acceptable forms are: image[Point p], image[x, y], image[int index]");
	return 0;
}

static PyObject *image_len(PyObject *self, PyObject *) {
	Image *image = (Image *) ((RectObject *) self)->m_x;
	return Py_BuildValue( "i", (long) (image->nrows() * image->ncols()));
}

static PyObject *image_eq(PyObject *self, PyObject *args) {
	Image* image = (Image *) ((RectObject *) self)->m_x;
	PyObject *other;
	
	if (PyArg_ParseTuple(args,  "O", &other)) {
		if (!is_ImageObject(other)) Py_RETURN_FALSE;
		
		Image* otherImage = (Image *) ((RectObject *) other)->m_x;
		if (*image == *otherImage) {
			Py_RETURN_TRUE;
		}
		Py_RETURN_FALSE;
	}
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to __eg__.  Need an image object as first argument");
	return 0;
}

static PyObject *image_gt(PyObject *self, PyObject *args) {
	Image* image = (Image *) ((RectObject *) self)->m_x;
	PyObject *other;
	if (PyArg_ParseTuple(args,  "O", &other)) {
		if (!is_ImageObject(other)) Py_RETURN_FALSE;
		
		Image* otherImage = (Image *) ((RectObject *) other)->m_x;
		if (image->origin() > otherImage->origin()) {
			Py_RETURN_TRUE;
		}
		if (image->origin() == otherImage->origin()) {
			if (image->lr() > otherImage->lr()) {
				Py_RETURN_TRUE;
			}
		}
		Py_RETURN_FALSE;
	}
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to __gt__.  Need an image object as first argument");
	return 0;
}
/*
 * In Python 3.10a7 (or b1), python started using the identity for the hash
 * when a value is NaN.  See https://bugs.python.org/issue43475
 */
#if PY_VERSION_HEX > 0x030a00a6
#define Npy_HashDouble _Py_HashDouble
#else
static inline Py_hash_t
#ifndef __COMP_NPY_UNUSED
    #if defined(__GNUC__)
        #define __COMP_NPY_UNUSED __attribute__ ((__unused__))
    #elif defined(__ICC)
        #define __COMP_NPY_UNUSED __attribute__ ((__unused__))
    #elif defined(__clang__)
        #define __COMP_NPY_UNUSED __attribute__ ((unused))
    #else
        #define __COMP_NPY_UNUSED
    #endif
    #define NPY_UNUSED(x) (__NPY_UNUSED_TAGGED ## x) __COMP_NPY_UNUSED
#endif

Npy_HashDouble(PyObject *NPY_UNUSED(identity), double val)
{
    return _Py_HashDouble(val);
}
#endif

static PyObject *image_hash(PyObject *self, PyObject *) {
	Image* image = (Image *) ((RectObject *) self)->m_x;
	Point origin = image->origin();
	Point lr = image->lr();
	return Py_BuildValue("i",  Npy_HashDouble(self,(double)origin.x()) +
	                           Npy_HashDouble(self,(double)origin.y())+
	                           Npy_HashDouble(self,(double)lr.x())+
	                           Npy_HashDouble(self,(double)lr.y())+
	                           Npy_HashDouble(self,(double)image->nrows())+
	                           Npy_HashDouble(self,(double)image->ncols()));
}

static PyObject *cc_hash(PyObject *self, PyObject *) {
	Image* cc = (Image *) ((RectObject *) self)->m_x;
	Point origin = cc->origin();
	Point lr = cc->lr();
	return Py_BuildValue("i",  Npy_HashDouble(self,(double)origin.x()) +
	                           Npy_HashDouble(self,(double)origin.y())+
	                           Npy_HashDouble(self,(double)lr.x())+
	                           Npy_HashDouble(self,(double)lr.y())+
	                           Npy_HashDouble(self,(double)cc->nrows())+
	                           Npy_HashDouble(self,(double)cc->ncols()));
}

#define CREATE_GET_FUNC(name) static PyObject* image_get_##name(PyObject* self) {\
  ImageObject* o = (ImageObject*)self; \
  Py_XINCREF(o->m_##name); \
  return o->m_##name; \
}

#define CREATE_SET_FUNC(name) static int image_set_##name(PyObject* self, PyObject* v) {\
  ImageObject* o = (ImageObject*)self; \
  Py_XDECREF(o->m_##name); \
  o->m_##name = v; \
  Py_XINCREF(o->m_##name); \
  return 0; \
}

CREATE_GET_FUNC(data)

CREATE_GET_FUNC(features)

CREATE_SET_FUNC(features)

CREATE_SET_FUNC(id_name)

CREATE_GET_FUNC(id_name)

CREATE_SET_FUNC(confidence)

CREATE_GET_FUNC(confidence)

CREATE_GET_FUNC(children_images)

CREATE_SET_FUNC(children_images)

CREATE_GET_FUNC(classification_state)

CREATE_SET_FUNC(classification_state)


static PyObject *image_get_scaling(PyObject *self) {
	RectObject *o = (RectObject *) self;
	return Py_BuildValue( "f", ((Image *) o->m_x)->scaling());
}

static int image_set_scaling(PyObject *self, PyObject *v) {
	RectObject *o = (RectObject *) self;
	if (!PyFloat_Check(v)) {
		PyErr_SetString(PyExc_TypeError, "scaling must be a float value.");
		return -1;
	}
	((Image *) o->m_x)->scaling(PyFloat_AS_DOUBLE(v));
	return 0;
}

static PyObject *image_get_resolution(PyObject *self) {
	RectObject *o = (RectObject *) self;
	return Py_BuildValue( "f", ((Image *) o->m_x)->resolution());
}

static int image_set_resolution(PyObject *self, PyObject *v) {
	RectObject *o = (RectObject *) self;
	if (!PyFloat_Check(v)) {
		PyErr_SetString(PyExc_TypeError, "resolution must be a float value.");
		return -1;
	}
	((Image *) o->m_x)->resolution(PyFloat_AS_DOUBLE(v));
	return 0;
}

static PyObject *cc_get_label(PyObject *self) {
	RectObject *o = (RectObject *) self;
	return Py_BuildValue( "i", ((Cc *) o->m_x)->label());
}

static int cc_set_label(PyObject *self, PyObject *v) {
	RectObject *o = (RectObject *) self;
	if (!PyLong_Check(v)) {
		PyErr_SetString(PyExc_TypeError, "label must be an int value.");
		return -1;
	}
	((Cc *) o->m_x)->label(PyLong_AS_LONG(v));
	return 0;
}

static PyObject *image_richcompare(PyObject *a, PyObject *b, int op) {
	if (!is_ImageObject(a) || !is_ImageObject(b)) {
		Py_XINCREF(Py_NotImplemented);
		return Py_NotImplemented;
	}
	
	Image &ap = *(Image *) ((RectObject *) a)->m_x;
	Image &bp = *(Image *) ((RectObject *) b)->m_x;
	
	/*
	  Only equality and inequality make sense.
	*/
	bool cmp;
	switch (op) {
		case Py_EQ:
			cmp = (ap == bp) && (ap.data() == bp.data());
			break;
		case Py_NE:
			cmp = (ap != bp) || (ap.data() != bp.data());
			break;
		case Py_GT:
			cmp = ap > bp && ap.data() != bp.data();
			break;
		case Py_LT:
		case Py_LE:
		case Py_GE:
			Py_XINCREF(Py_NotImplemented);
			return Py_NotImplemented;
		default:
			return 0; // cannot happen
	}
	if (cmp) {
		Py_XINCREF(Py_True);
		return Py_True;
	} else {
		Py_XINCREF(Py_False);
		return Py_False;
	}
}

static PyObject *cc_richcompare(PyObject *a, PyObject *b, int op) {
	if (!is_ImageObject(a) || !is_ImageObject(b)) {
		Py_XINCREF(Py_NotImplemented);
		return Py_NotImplemented;
	}
	//#define DEBUG_COMPARE
	
	Image &ap = *(Image *) ((RectObject *) a)->m_x;
	Image &bp = *(Image *) ((RectObject *) b)->m_x;
	
	/*
	  Only equality and inequality make sense.
	*/
	bool cmp;
	switch (op) {
		case Py_EQ:
			if (!is_CCObject(a) || !is_CCObject(b))
				cmp = false;
			else {
				Cc ac = *(Cc *) ((RectObject *) a)->m_x;
				Cc bc = *(Cc *) ((RectObject *) b)->m_x;
				cmp = (ap == bp) && (ap.data() == bp.data()) && ac.label() == bc.label();
			}
			break;
		case Py_NE:
			if (!is_CCObject(a) || !is_CCObject(b))
				cmp = true;
			else {
				Cc ac = *(Cc *) ((RectObject *) a)->m_x;
				Cc bc = *(Cc *) ((RectObject *) b)->m_x;
				cmp = (ap != bp) || (ap.data() != bp.data()) || ac.label() != bc.label();
			}
			break;
		case Py_GT:
			if (!is_CCObject(a) || !is_CCObject(b))
				cmp = false;
			else {
				Cc ac = *(Cc *) ((RectObject *) a)->m_x;
				Cc bc = *(Cc *) ((RectObject *) b)->m_x;
				
				if (ac.origin() == bc.origin()) {
					if (ac.lr() == bc.lr()) {
						if (ac.nrows() == bc.nrows()) {
							if (ac.nrows() == bc.nrows()) {
								cmp = ac.size() > bc.size();
							} else {
								cmp = ac.nrows() > bc.nrows();
							}
						} else {
							cmp = ac.nrows() > bc.nrows();
						}
					} else {
						cmp = ac.lr() > bc.lr();
					}
				} else {
					cmp = ac.origin() > bc.origin();
				}
			}
			break;
		case Py_LT:
		case Py_LE:
		case Py_GE:
			#ifdef DEBUG_COMPARE
			std::cerr << "Compare (" << op << ") = Py_NotImplemented" << std::endl;
			reprint(a);
			reprint(b);
		#endif
			Py_XINCREF(Py_NotImplemented);
			return Py_NotImplemented;
		default:
			return 0; // cannot happen
	}
	
	if (cmp) {
		
		#ifdef DEBUG_COMPARE
		std::cerr << "Compare (" << op << ") = true" << std::endl;
		reprint(a);
		reprint(b);
		#endif
		Py_XINCREF(Py_True);
		return Py_True;
	} else {
		#ifdef DEBUG_COMPARE
		std::cerr << "Compare (" << op << ") = false" << std::endl;
		reprint(a);
		reprint(b);
		#endif
		Py_XINCREF(Py_False);
		return Py_False;
	}
}

static PyTypeObject MLCCType = {
		PyVarObject_HEAD_INIT(nullptr, 0)
};

PyTypeObject *get_MLCCType() {
	return &MLCCType;
}

/*
(char *)"**get** (Point *p*)\n\n"
"Gets a pixel value at the given (*x*, *y*) coordinate.\n\n"
"A 2-element sequence may be used in place of the ``Point`` argument.  For "
"instance, the following are all equivalent:\n\n"
*/
static PyObject *mlcc_add_neighbors(PyObject *self, PyObject *args) {
	int i, j;
	
	if (!PyArg_ParseTuple(args, "ii", &i, &j)) {
		PyErr_SetString(PyExc_TypeError, "Both labels need to be int values.");
		return 0;
	}
	RectObject *o = (RectObject *) self;
	((MlCc *) o->m_x)->add_neighbors(i, j);
	
	Py_XINCREF(Py_None);
	return Py_None;
}

// static PyObject* mlcc_find_bounding_box(PyObject* self, PyObject* args){
//   RectObject* o = (RectObject*)self;
//   ((MlCc*)o->m_x)->find_bounding_box();

//   Py_XINCREF(Py_None);
//   return Py_None;
// }

static PyObject *mlcc_remove_label(PyObject *self, PyObject *args) {
	
	if (!PyLong_Check(args)) {
		PyErr_SetString(PyExc_TypeError, "Label must be an int value.");
		return 0;
	}
	
	RectObject *o = (RectObject *) self;
	((MlCc *) o->m_x)->remove_label(PyLong_AS_LONG(args));
	
	Py_XINCREF(Py_None);
	return Py_None;
}

static PyObject *mlcc_add_label(PyObject *self, PyObject *args) {
	int i;
	PyObject *pyrect;
	
	if (!PyArg_ParseTuple(args, "iO", &i, &pyrect)) {
		PyErr_SetString(PyExc_TypeError, "usage: add_label(int, Rect).");
		return 0;
	}
	Rect *rect;
	try {
		rect = (Rect *) (((RectObject *) pyrect)->m_x);
	} catch (...) {
		PyErr_SetString(PyExc_TypeError, "The second argument has to be of the type Rectangle.");
		return 0;
	}
	
	RectObject *o = (RectObject *) self;
	((MlCc *) o->m_x)->add_label(i, *rect);
	
	Py_XINCREF(Py_None);
	return Py_None;
}

static PyObject *mlcc_get_labels(PyObject *self) {
	PyObject *pylist;
	RectObject *o = (RectObject *) self;
	std::vector<int> labels;
	((MlCc *) o->m_x)->get_labels(labels);
	pylist = PyList_New(labels.size());
	for (size_t i = 0; i < labels.size(); i++) {
		PyList_SetItem(pylist, i, PyLong_FromLong(labels[i]));
	}
	return pylist;
}

static PyObject *_mlcc_copy(MlCc *mlcc, const Point &offset, const Dim &dim) {
	MlCc *mlcc_new = new MultiLabelCC<ImageData<OneBitPixel> >(*mlcc, offset, dim);
	return create_ImageObject(mlcc_new);
}

static PyObject *mlcc_copy(PyObject *self, PyObject *args) {
	int num_args = PyTuple_GET_SIZE(args);
	RectObject *o = (RectObject *) self;
	MlCc *mlcc = (MlCc *) o->m_x;
	
	if (num_args == 2) {
		PyObject *a, *b;
		if (PyArg_ParseTuple(args,  "OO", &a, &b)) {
			Point point_a;
			try {
				point_a = coerce_Point(a);
			} catch (const std::invalid_argument& e) {
				goto phase2;
			}
			try {
				Point point_b = coerce_Point(b);
				int nrows = point_b.y() - point_a.y() + 1;
				int ncols = point_b.x() - point_a.x() + 1;
				return _mlcc_copy(mlcc, point_a, Dim(ncols, nrows));
			} catch (const std::invalid_argument& e) {
				PyErr_Clear();
				if (is_SizeObject(b)) {
					Size *size_b = ((SizeObject *) b)->m_x;
					int nrows = size_b->height() + 1;
					int ncols = size_b->width() + 1;
					return _mlcc_copy(mlcc, point_a, Dim(ncols, nrows));
				} else if (is_DimObject(b)) {
					Dim *dim_b = ((DimObject *) b)->m_x;
					return _mlcc_copy(mlcc, point_a, *dim_b);
				}
			}
		}
	}
	
	phase2:
	PyErr_Clear();
	
	if (num_args == 3) {
		PyObject *pyrect;
		if (PyArg_ParseTuple(args,  "O", &pyrect)) {
			if (is_RectObject(pyrect)) {
				Rect *rect = ((RectObject *) pyrect)->m_x;
				return _mlcc_copy(mlcc, rect->origin(), rect->dim());
			}
		}
	}
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to MlCc constructor.  See the MlCc docstring for valid arguments.");
	return 0;
}

static PyObject *mlcc_get_neighbors(PyObject *self) {
	PyObject *pylist, *tuple;
	RectObject *o = (RectObject *) self;
	std::vector<int> neighbors;
	((MlCc *) o->m_x)->get_neighbors(neighbors);
	pylist = PyList_New(neighbors.size() / 2);
	
	for (size_t i = 0; i < neighbors.size(); i += 2) {
		tuple = PyTuple_New(2);
		PyTuple_SetItem(tuple, 0, PyLong_FromLong(neighbors[i]));
		PyTuple_SetItem(tuple, 1, PyLong_FromLong(neighbors[i + 1]));
		
		PyList_SetItem(pylist, i / 2, tuple);
	}
	
	return pylist;
}

static PyObject *mlcc_has_label(PyObject *self, PyObject *v) {
	RectObject *o = (RectObject *) self;
	if (!PyLong_Check(v)) {
		PyErr_SetString(PyExc_TypeError, "Label must be an int value.");
		return 0;
	}
	
	if (((MlCc *) o->m_x)->has_label(PyLong_AS_LONG(v))) {
		Py_XINCREF(Py_True);
		return Py_True;
	} else {
		Py_XINCREF(Py_False);
		return Py_False;
	}
}

static PyObject *mlcc_relabel(PyObject *self, PyObject *args) {
	RectObject *o = (RectObject *) self;
	PyObject *pyList;
	int outer_size;
	bool error = false;
	bool listOfList = false;  //used as a trick to "overload" the function. The return value also depends from this value.
	std::vector<std::vector<int> *> labelVector;
	std::vector<MlCc *> mlccs;
	
	if (!PyArg_ParseTuple(args, "O", &pyList)) {
		PyErr_SetString(PyExc_TypeError, "no argument given.");
		error = true;
		goto tidyUp;
	}
	if (!PyList_Check(pyList)) {
		PyErr_SetString(PyExc_TypeError, "argument has to be a list.");
		error = true;
		goto tidyUp;
	}
	
	outer_size = PyList_Size(pyList);
	
	if (outer_size == 0) {
		PyErr_SetString(PyExc_TypeError, "argument (list) has to contain further values (lists/integers).");
		error = true;
		goto tidyUp;
	}
	
	if (!PyList_Check(PyList_GetItem(pyList, 0))) { //if first inner element is not a list assume, that the given argument is a list of labels
		IntVector *labels = new IntVector();
		labelVector.push_back(labels);
		for (int i = 0; i < outer_size; i++) {
			PyObject *label = PyList_GetItem(pyList, i);
			if (PyLong_Check(label)) {
				labels->push_back(PyLong_AS_LONG(label));
			} else {
				PyErr_SetString(PyExc_TypeError, "label values have to be int values.");
				error = true;
				goto tidyUp;
			}
		}
	} else {
		listOfList = true;
		for (int i = 0; i < outer_size; i++) {
			PyObject *pyList_inner = PyList_GetItem(pyList, i);
			if (PyList_Check(pyList_inner)) {
				int inner_size = PyList_Size(pyList_inner);
				IntVector *labels = new IntVector();
				labelVector.push_back(labels);
				for (int j = 0; j < inner_size; j++) {
					PyObject *label = PyList_GetItem(pyList_inner, j);
					if (PyLong_Check(label)) {
						labels->push_back(PyLong_AS_LONG(label));
					} else {
						PyErr_SetString(PyExc_TypeError, "label values have to be int values.");
						error = true;
						goto tidyUp;
					}
				}
			} else {
				PyErr_SetString(PyExc_TypeError, "one of the inner elements is not a list.");
				error = true;
				goto tidyUp;
			}
		}
	}
	
	try {
		((MlCc *) o->m_x)->relabel(labelVector, mlccs);
	} catch (std::exception &e) {
		error = true;
		PyErr_SetString(PyExc_RuntimeError, e.what());
		goto tidyUp;
	}
	
	pyList = PyList_New(mlccs.size());
	for (size_t i = 0; i < mlccs.size(); i++) {
		PyObject *retVal = create_ImageObject(mlccs[i]);
		PyList_SetItem(pyList, i, retVal);
	}
	
	tidyUp:
	for (size_t i = 0; i < labelVector.size(); i++)
		delete labelVector[i];
	
	if (error) {
		for (size_t i = 0; i < mlccs.size(); i++)
			delete mlccs[i];
		return 0;
	} else {
		if (listOfList) {
			return pyList;
		} else {
			PyObject *retVal = PyList_GetItem(pyList, 0);
			Py_XINCREF(retVal);
			Py_XDECREF(pyList);
			return retVal;
		}
	}
}

static PyObject *cc_convert_to_mlcc(PyObject *self) {
	CCObject *ccObject = (CCObject *) self;
	ImageObject *imageObject = &(ccObject->m_parent);
	RectObject *rectObject = &(imageObject->m_parent);
	Image *mlcc = (((Cc *) rectObject->m_x)->convert_to_mlcc());
	PyObject *retVal = create_ImageObject(mlcc);
	return retVal;
}

static PyObject *mlcc_convert_to_cc_list(PyObject *self) {
	CCObject *ccObject = (CCObject *) self;
	ImageObject *imageObject = &(ccObject->m_parent);
	RectObject *rectObject = &(imageObject->m_parent);
	std::list<Cc *> *ccs = (((MlCc *) rectObject->m_x)->convert_to_cc_list());
	
	PyObject *pylist = PyList_New(ccs->size());
	std::list<Cc *>::iterator it = ccs->begin();
	for (size_t i = 0; i < ccs->size(); ++i, ++it) {
		PyObject *item = create_ImageObject(*it);
		PyList_SetItem(pylist, i, item);
	}
	delete ccs;
	return pylist;
}

static PyObject *mlcc_convert_to_cc(PyObject *self) {
	CCObject *ccObject = (CCObject *) self;
	ImageObject *imageObject = &(ccObject->m_parent);
	RectObject *rectObject = &(imageObject->m_parent);
	Image *cc = (((MlCc *) rectObject->m_x)->convert_to_cc());
	PyObject *retVal = create_ImageObject(cc);
	return retVal;
}

static PyObject *_mlcc_new(PyTypeObject *pytype, PyObject *py_src, int label, const Point &offset, const Dim &dim) {
	if (!is_ImageObject(py_src)) {
		PyErr_SetString(PyExc_TypeError, "First argument to the MlCc constructor must be an Image (or SubImage).");
		return nullptr;
	}
	
	int pixel, format;
	ImageObject *src = (ImageObject *) py_src;
	pixel = ((ImageDataObject *) src->m_data)->m_pixel_type;
	format = ((ImageDataObject *) src->m_data)->m_storage_format;
	
	Rect *mlcc = nullptr;
	
	try {
		if (pixel != ONEBIT) {
			PyErr_SetString(PyExc_TypeError, "MlCc objects may only be created from ONEBIT Images.");
			return nullptr;
		}
		
		if (format == DENSE) {
			ImageData<OneBitPixel> *data =
					((ImageData<OneBitPixel> *) ((ImageDataObject *) src->m_data)->m_x);
			mlcc = (Rect *) new MultiLabelCC<ImageData<OneBitPixel> >(*data, label, offset, dim);
		} else if (format == RLE) {
			PyErr_SetString(PyExc_TypeError, "MultiLabelCCs cannot be used with runline length encoding.");
			return nullptr;
		} else {
			PyErr_SetString(PyExc_TypeError, "Unknown pixel type/storage format combination. Receiving this error indicates an internal inconsistency or memory corruption.  Please report it on the Gamera mailing list.");
			return nullptr;
		}
	} catch (std::exception &e) {
		delete mlcc;
		PyErr_SetString(PyExc_RuntimeError, e.what());
		return nullptr;
	}
	
	ImageObject *o;
	o = (ImageObject *) pytype->tp_alloc(pytype, 0);
	((RectObject *) o)->m_x = mlcc;
	o->m_data = ((ImageObject *) py_src)->m_data;
	Py_XINCREF(o->m_data);
	// set the resolution
	((Image *) ((RectObject *) o)->m_x)->resolution(((Image *) ((RectObject *) py_src)->m_x)->resolution());
	return init_image_members(o);
}

PyObject *mlcc_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
	int num_args = PyTuple_GET_SIZE(args);
	PyObject *image = nullptr;
	
	if (num_args == 1) {
		// create MLCC from list of CCs
		PyObject *cclist;
		size_t n, N;
		if (PyArg_ParseTuple(args,  "O", &cclist)) {
			if (!PyList_Check(cclist)) {
				PyErr_SetString(PyExc_TypeError, "MlCc objects must be constructed from a Cc list.");
				return 0;
			}
			N = PyList_Size(cclist);
			for (n = 0; n < N; n++) { //check if every argument has the right type (Cc)
				PyObject *py_cc = PyList_GetItem(cclist, n);
				if (!is_CCObject(py_cc)) {
					PyErr_SetString(PyExc_TypeError, "MlCc objects must be constructed from a Cc list.");
					return 0;
				}
			}
			
			PyObject *py_mlcc = cc_convert_to_mlcc(PyList_GetItem(cclist, 0));
			RectObject *o = (RectObject *) py_mlcc;
			MlCc *mlcc = (MlCc *) (o->m_x);
			for (n = 1; n < N; n++) {
				RectObject *o_cc = (RectObject *) PyList_GetItem(cclist, n);
				Cc *cc = (Cc *) (o_cc->m_x);
				if (mlcc->data() != cc->data()) { //check if every Cc has the same image
					Py_XDECREF(py_mlcc); //free memory on error
					PyErr_SetString(PyExc_TypeError, "All Ccs have to be a part of the same image.");
					return 0;
				}
				mlcc->add_label(cc->label(), *cc);
			}
			return py_mlcc;
		}
	}
	
	if (num_args == 4) {
		PyObject *a, *b;
		int label;
		if (PyArg_ParseTuple(args,  "OiOO", &image, &label, &a, &b)) {
			Point point_a;
			try {
				point_a = coerce_Point(a);
			} catch (const std::invalid_argument& e) {
				goto phase2;
			}
			try {
				Point point_b = coerce_Point(b);
				int nrows = point_b.y() - point_a.y() + 1;
				int ncols = point_b.x() - point_a.x() + 1;
				return _mlcc_new(pytype, image, label, point_a, Dim(ncols, nrows));
			} catch (const std::invalid_argument& e) {
				PyErr_Clear();
				if (is_SizeObject(b)) {
					Size *size_b = ((SizeObject *) b)->m_x;
					int nrows = size_b->height() + 1;
					int ncols = size_b->width() + 1;
					return _mlcc_new(pytype, image, label, point_a, Dim(ncols, nrows));
				} else if (is_DimObject(b)) {
					Dim *dim_b = ((DimObject *) b)->m_x;
					return _mlcc_new(pytype, image, label, point_a, *dim_b);
				}
#ifdef GAMERA_DEPRECATED
				else if (is_DimensionsObject(b)) {
				  if (send_deprecation_warning(
					"MlCc(image, label, Point offset, Dimensions dimensions) is deprecated.\n\n"
					"Reason: (x, y) coordinate consistency. (Dimensions is now deprecated \n"
					"in favor of Dim).\n\n"
					"Use MlCc(image, label, (offset_x, offset_y), Dim(ncols, nrows)) instead.",
					"imageobject.cpp", __LINE__) == 0)
					return 0;
				  Dimensions* dim_b = ((DimensionsObject*)b)->m_x;
				  int nrows = dim_b->nrows();
				  int ncols = dim_b->ncols();
				  return _mlcc_new(pytype, image, label, point_a, Dim(ncols, nrows));
				}
#endif
			}
		}
	}
	
	phase2:
	PyErr_Clear();
	
	if (num_args == 3) {
		int label;
		PyObject *pyrect;
		if (PyArg_ParseTuple(args,  "OiO", &image, &label, &pyrect)) {
			if (is_RectObject(pyrect)) {
				Rect *rect = ((RectObject *) pyrect)->m_x;
				return _mlcc_new(pytype, image, label, rect->origin(), rect->dim());
			}
		}
	}

#ifdef GAMERA_DEPRECATED
	PyErr_Clear();
	if (num_args == 6) {
	  int offset_y, offset_x, nrows, ncols, label;
	  if (PyArg_ParseTuple(args, "Oiiiii",
		 &image, &label, &offset_y, &offset_x, &nrows, &ncols) > 0) {
		if (send_deprecation_warning(
		  "MlCc(image, label, offset_y, offset_x, nrows, ncols) is deprecated.\n\n"
		  "Reason: (x, y) coordinate consistency.\n\n"
		  "Use MlCc(image, label, (offset_x, offset_y), Dim(ncols, nrows)) instead.",
		  "imageobject.cpp", __LINE__) == 0)
		  return 0;
		return _mlcc_new(pytype, image, label, Point(offset_x, offset_y), Dim(ncols, nrows));
	  }
	}
#endif
	
	PyErr_Clear();
	PyErr_SetString(PyExc_TypeError, "Invalid arguments to MlCc constructor.  See the MlCc docstring for valid arguments.");
	return 0;
}

static PyObject *mlcc_richcompare(PyObject *a, PyObject *b, int op) {
	if (!is_ImageObject(a) || !is_ImageObject(b)) {
		Py_XINCREF(Py_NotImplemented);
		return Py_NotImplemented;
	}
	
	Image &ap = *(Image *) ((RectObject *) a)->m_x;
	Image &bp = *(Image *) ((RectObject *) b)->m_x;
	
	/*
	  Only equality and inequality make sense.
	*/
	bool cmp;
	switch (op) {
		case Py_EQ:
			if (!is_MLCCObject(a) || !is_MLCCObject(b))
				cmp = false;
			else {
				MlCc &ac = *(MlCc *) ((RectObject *) a)->m_x;
				MlCc &bc = *(MlCc *) ((RectObject *) b)->m_x;
				
				cmp = true;
				std::vector<int> labels;
				ac.get_labels(labels);
				for (size_t i = 0; i < labels.size(); i++) {
					if (!bc.has_label(labels[i])) {
						cmp = false;
						break;
					}
				}
				
				//Neighborhoods don't need to be compared because they do not depend from the mlcc but from the underlying data (i.e. image).
				//Therefore they have to be equal for both mlccs (if not there is an internal error).
				
				cmp = (ap == bp) && (ap.data() == bp.data()) && cmp;
			}
			break;
		case Py_NE:
			if (!is_MLCCObject(a) || !is_MLCCObject(b))
				cmp = true;
			else {
				MlCc &ac = *(MlCc *) ((RectObject *) a)->m_x;
				MlCc &bc = *(MlCc *) ((RectObject *) b)->m_x;
				
				cmp = true;
				std::vector<int> labels;
				ac.get_labels(labels);
				for (size_t i = 0; i < labels.size(); i++) {
					if (!bc.has_label(labels[i])) {
						cmp = false;
						break;
					}
				}
				
				//Neighborhoods don't need to be compared because they do not depend from the mlcc but from the underlying data (i.e. image).
				//Therefore they have to be equal for both mlccs (if not there is an internal error).
				
				cmp = (ap != bp) || (ap.data() != bp.data()) || !cmp;
			}
			break;
		case Py_LT:
		case Py_LE:
		case Py_GT:
		case Py_GE:
			Py_XINCREF(Py_NotImplemented);
			return Py_NotImplemented;
		default:
			return 0; // cannot happen
	}
	if (cmp) {
		Py_XINCREF(Py_True);
		return Py_True;
	} else {
		Py_XINCREF(Py_False);
		return Py_False;
	}
}

static PyGetSetDef image_getset[] = {
		{"data",                 (getter) image_get_data,       0,
				"(read-only property)\n\n"
				"Returns the underlying ImageData__ object.\n\n"
				".. __: gamera.core.ImageData.html", 0},
		{"features",             (getter) image_get_features,   (setter) image_set_features,
				"(read/write property)\n\n"
				"The feature vector of the image (of type array)",
				                                     0},
		{"id_name",              (getter) image_get_id_name,    (setter) image_set_id_name,
				"(read/write property)\n\n"
				"A list of strings representing the classifications of the image.",
				                                     0},
		{"confidence",           (getter) image_get_confidence, (setter) image_set_confidence,
				"(read/write property)\n\n"
				"A mapping of confidence values for the main id (id_name[0]).",
				                                     0},
		{"children_images",      (getter) image_get_children_images,
		                                                        (setter) image_set_children_images,
				"(read/write property)\n\n"
				"A list of images created from classifications that produce images, such as splitting algorithms.",
				                                     0},
		{"classification_state", (getter) image_get_classification_state,
		                                                        (setter) image_set_classification_state,
				"(read/write property)\n\n"
				"How (or whether) an image is classified",
				                                     0},
		{"scaling",              (getter) image_get_scaling,    (setter) image_set_scaling,
				"(read/write property)\n\n"
				"The scaling (if any) applied to the features as a floating-point value.",
				                                     0},
		{"resolution",           (getter) image_get_resolution, (setter) image_set_resolution,
				"(read/write property)\n\n"
				"The resolution of the image",
				                                     0},
		{nullptr}
};

static PyGetSetDef cc_getset[] = {
		{"label", (getter) cc_get_label, (setter) cc_set_label, "(read/write property)\n\nThe pixel label value for the Cc", 0},
		{nullptr}
};

static PyMethodDef cc_methods[] = {
		{"convert_to_mlcc", (PyCFunction) cc_convert_to_mlcc, METH_NOARGS,
				"**convert_to_mlcc** ()\n\n"
				"Converts the ConnectedComponent into a MultiLabelCC."
		},
		{"__hash__",        cc_hash,                          METH_NOARGS},
		{nullptr} //Sentinel//
};

static PyMethodDef image_methods[] = {
		{"get",         image_get,     METH_VARARGS,
				"**get** (Point *p*)\n\n"
				"Gets a pixel value at the given (*x*, *y*) coordinate.\n\n"
				"A 2-element sequence may be used in place of the ``Point`` argument.  For "
				"instance, the following are all equivalent:\n\n"
				".. code:: Python\n\n"
				"    px = image.get(Point(5, 2))\n"
				"    px = image.get((5, 2))\n"
				"    px = image.get([5, 2])\n\n"
				"This coordinate is relative to the image view, not the absolute coordinates."
		},
		{"set",         image_set,     METH_VARARGS,
				"**set** (Point *p*, Pixel *value*)\n\n"
				"Sets a pixel value at the given (*x*, *y*) coordinate.\n\n"
				"A 2-element sequence may be used in place of the ``Point`` argument.  For "
				"instance, the following are all equivalent:\n\n"
				".. code:: Python\n\n"
				"    image.set(Point(5, 2), value)\n"
				"    image.set((5, 2), value)\n"
				"    image.set([5, 2], value)\n\n"
				"This coordinate is relative to the image view, not the absolute coordinates."
		},
		{"white",       image_white,   METH_NOARGS,
				"Pixel **white** ()\n\n"
				"Returns the pixel value representing the color white for this image."
		},
		{"black",       image_black,   METH_NOARGS,
				"Pixel **black** ()\n\n"
				"Returns the pixel value representing the color black for this image."
		},
		{"__getitem__", image_getitem, METH_VARARGS},
		{"__setitem__", image_setitem, METH_VARARGS},
		{"__len__",     image_len,     METH_NOARGS},
		{"__eq__",      image_eq,      METH_O},
		{"__gt__",      image_gt,      METH_O},
		{"__hash__",    image_hash,    METH_NOARGS},
		// Removed 07/28/04 MGD.  Can't figure out why this is useful.
		// { "sort", image_sort, METH_NOARGS },
		{nullptr}
};


static PyMethodDef mlcc_methods[] = {
		{"add_label",          (PyCFunction) mlcc_add_label,          METH_VARARGS,
				"**add_label** (int *label*, Rect *rect*)\n\n"
				"Adds a label and a bounding box (for the label) to a MultiLabelCC. The bounding box of the MlCc is extended by the given *rect*."
		},
		{"remove_label",       (PyCFunction) mlcc_remove_label,       METH_O,
				"**remove_label** (int *label*)\n\n"
				"Removes a label from a MultiLabelCC. The bounding box of the MlCc is shrunk by the bounding box associated with the removed label as far as possible with respect to the other bounding boxes."
		},
//     {"find_bounding_box", (PyCFunction)mlcc_find_bounding_box, METH_NOARGS,
//      "**find_bounding_box** ()\n\n"
//      "Calculates the bounding box of a MultiLabelCC depending from the stored labels/rectangles."
//     },
		{"add_neighbors",      (PyCFunction) mlcc_add_neighbors,      METH_VARARGS,
				"**add_neighbors** (int *i*, int *j*)\n\n"
				"Adds a neighborhood relation to the MultiLabelCC.\n\n"
				"This is entirely optional: neighborship relations are only stored, and can be returned with get_neighbors(), but are not used internally by MlCc."
		},
		{"copy",               (PyCFunction) mlcc_copy,               METH_VARARGS,
				"**copy** ()\n\n"
				"Makes a deep copy of a MultiLabelCC. "
				"There are a number of ways to to call this Method:\n\n"
				"  - **copy** (MlCc *other*, Point *upper_left*, Point *lower_right*)\n\n"
				"  - **copy** (MlCc *other*, Point *upper_left*, Size *size*)\n\n"
				"  - **copy** (MlCc *other*, Point *upper_left*, Dim *dim*)\n\n"
				"  - **copy** (MlCc *other*, Rect *rectangle*)\n\n"
		},
		{"get_labels",         (PyCFunction) mlcc_get_labels,         METH_NOARGS,
				"**get_labels** ()\n\n"
				"Returns a list of all labels belonging to the MultiLabelCC."
		},
		{"has_label",          (PyCFunction) mlcc_has_label,          METH_O,
				"**has_label** (int *label*)\n\n"
				"Returns whether a label belongs to the MlCc or not."
		},
		{"get_neighbors",      (PyCFunction) mlcc_get_neighbors,      METH_NOARGS,
				"**get_neighbors** ()\n\n"
				"Returns all pairs of neighbors that have been previously added with add_neighbors()."
		},
		{"relabel",            (PyCFunction) mlcc_relabel,            METH_VARARGS,
				"Returns a new MlCc containing only the given labels. For computing the new bounding boxes, the bounding box information stored for each label are utilized. The neighborship information is lost in the returned MlCc.\n\nThis function is overloaded to return either a single or several new MlCc's:\n\n"
				"**relabel** (List<int> *l*)\n\n"
				"Creates a single MultiLabelCC based on the current one.\n\n"
				".. code:: Python\n\n"
				"    new_mlcc = mlcc.relabel([2,3,4])\n\n"
				"This returns a single MultiLabelCC which contains the labels 2,3,4.\n\n"
				"**relabel** (List<List<int>> *l*)\n\n"
				"Creates a list of MultiLabelCC based on the current one.\n\n"
				".. code:: Python\n\n"
				"    new_mlcc_list = mlcc.relabel([[2,3],[4]])\n\n"
				"This returns a list of two MultiLabelCCs. The first one contains the labels 2,3; the "
				"second one contains the label 4."
		},
		{"convert_to_cc",      (PyCFunction) mlcc_convert_to_cc,      METH_NOARGS,
				"**convert_to_cc** ()\n\n"
				"Converts the MultiLabelCC into a ConnectedComponent. All labels belonging to the MultiLabelCc are set to the value of the first label. After calling this method, the MultiLabelCc only has one label."
		},
		{"convert_to_cc_list", (PyCFunction) mlcc_convert_to_cc_list, METH_NOARGS,
				"**convert_to_cc_list** ()\n\n"
				"Converts the MultiLabelCC into a  list of ConnectedComponent."
				"Each ConnectedComponent in the List represents one label of the MultiLabelCC.\n"
				"For example: You have a MultiLabelCC with the labels 2, 3, 4. Therefore it would be "
				"transformed into a list of 3 ConnectedComponent, one for each label."
		},
		{nullptr} //Sentinel//
};

void init_ImageType(PyObject *module_dict) {
	#ifdef Py_SET_TYPE
		Py_SET_TYPE(&ImageType, &PyType_Type);
	#else
		Py_TYPE(&ImageType) = &PyType_Type;
	#endif
	ImageType.tp_name =  "gameracore.Image";
	ImageType.tp_basicsize = sizeof(ImageObject);
	ImageType.tp_dealloc = image_dealloc;
	ImageType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
	                     Py_TPFLAGS_HAVE_GC;
	ImageType.tp_base = get_RectType();
	ImageType.tp_getset = image_getset;
	ImageType.tp_methods = image_methods;
	ImageType.tp_new = image_new;
	ImageType.tp_init = (initproc) image_init;
	ImageType.tp_getattro = PyObject_GenericGetAttr;
	ImageType.tp_alloc = nullptr; // PyType_GenericAlloc;
	ImageType.tp_free = nullptr; //_PyObject_Del;
	ImageType.tp_richcompare = image_richcompare;
	ImageType.tp_weaklistoffset = offsetof(ImageObject, m_weakreflist);
	ImageType.tp_traverse = image_traverse;
	ImageType.tp_clear = image_clear;
	ImageType.tp_repr = image_repr;
	ImageType.tp_doc =
			"The Image constructor creates a new image with newly allocated underlying data.\n\n"
			"There are multiple ways to create an Image:\n\n"
			"  - **Image** (Point *upper_left*, Point *lower_right*, Choice *pixel_type* = ONEBIT, Choice *format* = DENSE)\n\n"
			"  - **Image** (Point *upper_left*, Size *size*, Choice *pixel_type* = ONEBIT, Choice *format* = DENSE)\n\n"
			"  - **Image** (Point *upper_left*, Dim *dim*, Choice *pixel_type* = ONEBIT, Choice *format* = DENSE)\n\n"
			"  - **Image** (Rect *rectangle*, Choice *pixel_type* = ONEBIT, Choice *format* = DENSE)\n\n"
			"  - **Image** (Image *image*, Choice *pixel_type* = ONEBIT, Choice *format* = DENSE)\n\n"
			"**Deprecated forms:**\n\n"
			"  - **Image** (Point *upper_left*, Dimensions *dimensions*, Choice *pixel_type* = ONEBIT, Choice *format* = DENSE)\n\n"
			"  - **Image** (Int *offset_y*, Int *offset_x*, Int *nrows*, Int *ncols*, Choice *pixel_type* = ONEBIT, Choice *format* = DENSE)\n\n"
			"Note that the constructor taking an Image creates a new image with the same position\n"
			"and dimensions as the passed in image, but does not copy the data.\n"
			"(For that, use image_copy).\n\n"
			"*pixel_type*\n"
			"  An integer value specifying the type of the pixels in the image.\n"
			"  See `pixel types`__ for more information.\n\n"
			".. __: image_types.html#pixel-types\n\n"
			"*storage_format*\n"
			"  An integer value specifying the method used to store the image data.\n"
			"  See `storage formats`__ for more information.\n\n"
			".. __: image_types.html#storage-formats\n";
	if(PyType_Ready(&ImageType) != 0){
		return Py_FatalError("PyType_Ready for 'Image' failed");
	}
	if(PyDict_SetItemString(module_dict, "Image", (PyObject *) &ImageType) != 0){
		return Py_FatalError("PyDict_SetItemString for 'Image' failed");
	}
	
	#ifdef Py_SET_TYPE
		Py_SET_TYPE(&SubImageType, &PyType_Type);
	#else
		Py_TYPE(&SubImageType) = &PyType_Type;
	#endif
	SubImageType.tp_name =  "gameracore.SubImage";
	SubImageType.tp_basicsize = sizeof(SubImageObject);
	SubImageType.tp_dealloc = image_dealloc;
	SubImageType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
	                        Py_TPFLAGS_HAVE_GC;
	SubImageType.tp_base = &ImageType;
	SubImageType.tp_new = sub_image_new;
	SubImageType.tp_traverse = image_traverse;
	SubImageType.tp_init = (initproc) sub_image_init;
	SubImageType.tp_getattro = PyObject_GenericGetAttr;
	SubImageType.tp_alloc = nullptr; // PyType_GenericAlloc;
	SubImageType.tp_free = nullptr; // _PyObject_Del;
	SubImageType.tp_doc =
			"Creates a new view on existing data.\n\nThere are a number of ways to create a subimage:\n\n"
			"  - **SubImage** (Image *image*, Point *upper_left*, Point *lower_right*)\n\n"
			"  - **SubImage** (Image *image*, Point *upper_left*, Size *size*)\n\n"
			"  - **SubImage** (Image *image*, Point *upper_left*, Dim *dim*)\n\n"
			"  - **SubImage** (Image *image*, Rect *rectangle*)\n\n"
			"**Deprecated forms:**\n\n"
			"  - **SubImage** (Image *image*, Point *upper_left*, Dimensions *dimensions*)\n\n"
			"  - **SubImage** (Image *image*, Int *offset_y*, Int *offset_x*, Int *nrows*, Int *ncols*)\n\n"
			"Changes to subimages will affect all other subimages viewing the same data.\n\n"
			".. warning:: The *upper_left* and *lower_right* coordinates are absolute and not\n"
			"   relative to the image origin. Hence, for all practical use cases, you must\n"
			"   add the image offset to the coordinates, e.g.::\n\n"
			"     subimg = SubImage(image, Point(p.x + image.offset_x, p.y + image.offset_y), dim)\n";
	if(PyType_Ready(&SubImageType) != 0){
		PyErr_Print();
		return Py_FatalError("PyType_Ready for 'SubImage' failed");
	}
	if(PyDict_SetItemString(module_dict, "SubImage", (PyObject *) &SubImageType) != 0){
		return Py_FatalError("PyDict_SetItemString for 'SubImage' failed");
	}
	
	#ifdef Py_SET_TYPE
		Py_SET_TYPE(&CCType, &PyType_Type);
	#else
		Py_TYPE(&CCType) = &PyType_Type;
	#endif
	CCType.tp_name =  "gameracore.Cc";
	CCType.tp_basicsize = sizeof(CCObject);
	CCType.tp_dealloc = image_dealloc;
	CCType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
	                  Py_TPFLAGS_HAVE_GC;
	CCType.tp_base = &ImageType;
	CCType.tp_new = cc_new;
	CCType.tp_init = (initproc) cc_init;
	CCType.tp_getset = cc_getset;
	CCType.tp_methods = cc_methods;
	CCType.tp_traverse = image_traverse;
	CCType.tp_getattro = PyObject_GenericGetAttr;
	CCType.tp_alloc = nullptr;
	CCType.tp_richcompare = cc_richcompare;
	CCType.tp_free = nullptr; //_PyObject_Del;
	CCType.tp_doc =
			"Creates a connected component representing part of a OneBit image.\n\n"
			"It is rare to create one of these objects directly: most often you "
			"will just use cc_analysis to create connected components.\n\n"
			"There are a number of ways to create a Cc:\n\n"
			"  - **Cc** (Image *image*, Int *label*, Point *upper_left*, Point *lower_right*)\n\n"
			"  - **Cc** (Image *image*, Int *label*, Point *upper_left*, Size *size*)\n\n"
			"  - **Cc** (Image *image*, Int *label*, Point *upper_left*, Dim *dim*)\n\n"
			"  - **Cc** (Image *image*, Int *label*, Rect *rectangle*)\n\n"
			"**Deprecated forms:**\n\n"
			"  - **Cc** (Image *image*, Int *label*, Point *upper_left*, Dimensions *dimensions*)\n\n"
			"  - **Cc** (Image *image*, Int *label*, Int *offset_y*, Int *offset_x*, Int *nrows*, Int *ncols*)\n\n"
			"*label*\n  The pixel value used to represent this Cc.";
	if(PyType_Ready(&CCType) != 0){
		return Py_FatalError("PyType_Ready for 'Cc' failed");
	}
	if(PyDict_SetItemString(module_dict, "Cc", (PyObject *) &CCType) != 0){
		return Py_FatalError("PyDict_SetItemString for 'Cc' failed");
	}
	
	#ifdef Py_SET_TYPE
		Py_SET_TYPE(&MLCCType, &PyType_Type);
	#else
		Py_TYPE(&MLCCType) = &PyType_Type;
	#endif
	MLCCType.tp_name =  "gameracore.MlCc";
	MLCCType.tp_basicsize = sizeof(MLCCObject);
	MLCCType.tp_dealloc = image_dealloc;
	MLCCType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
	                    Py_TPFLAGS_HAVE_GC;
	MLCCType.tp_base = &ImageType;
	MLCCType.tp_new = mlcc_new;
	MLCCType.tp_traverse = image_traverse;
	MLCCType.tp_init = (initproc) mlcc_init;
	MLCCType.tp_methods = mlcc_methods;
	MLCCType.tp_getattro = PyObject_GenericGetAttr;
	MLCCType.tp_alloc = nullptr;
	MLCCType.tp_richcompare = mlcc_richcompare;
	MLCCType.tp_free = nullptr; //_PyObject_Del;
	MLCCType.tp_doc =
			"Creates a multi label connected component (MultiLabelCC) representing part of a OneBit image.\n\n"
			"Most often you will create a MultiLabelCCs from a list of Cc's.\n\n"
			"There are a number of ways to create a MultiLabelCC:\n\n"
			"  - **MlCc** (Image *image*, int *label*, Point *upper_left*, Point *lower_right*)\n\n"
			"  - **MlCc** (Image *image*, int *label*, Point *upper_left*, Size *size*)\n\n"
			"  - **MlCc** (Image *image*, int *label*, Point *upper_left*, Dim *dim*)\n\n"
			"  - **MlCc** (Image *image*, int *label*, Rect *rectangle*)\n\n"
			"  - **MlCc** (CcList *ccs*)\n\n"
			"**Deprecated forms:**\n\n"
			"  - **MlCc** (Image *image*, int *label*, Point *upper_left*, Dimensions *dimensions*)\n\n"
			"  - **MlCc** (Image *image*, int *label*, Int *offset_y*, Int *offset_x*, Int *nrows*, Int *ncols*)\n\n";
	if(PyType_Ready(&MLCCType) != 0){
		return Py_FatalError("PyType_Ready for 'Cc' failed");
	}
	if(PyDict_SetItemString(module_dict, "MlCc", (PyObject *) &MLCCType) != 0){
		return Py_FatalError("PyDict_SetItemString for 'MlCc' failed");
	}
	// some constants
	//-------------------------------
	// classification states
	PyDict_SetItemString(module_dict, "UNCLASSIFIED",
	                     Py_BuildValue( "i", UNCLASSIFIED));
	PyDict_SetItemString(module_dict, "AUTOMATIC",
	                     Py_BuildValue( "i", AUTOMATIC));
	PyDict_SetItemString(module_dict, "HEURISTIC",
	                     Py_BuildValue( "i", HEURISTIC));
	PyDict_SetItemString(module_dict, "MANUAL",
	                     Py_BuildValue( "i", MANUAL));
	// confidence types
	PyDict_SetItemString(module_dict, "CONFIDENCE_DEFAULT",
	                     Py_BuildValue( "i", CONFIDENCE_DEFAULT));
	PyDict_SetItemString(module_dict, "CONFIDENCE_KNNFRACTION",
	                     Py_BuildValue( "i", CONFIDENCE_KNNFRACTION));
	PyDict_SetItemString(module_dict, "CONFIDENCE_INVERSEWEIGHT",
	                     Py_BuildValue( "i", CONFIDENCE_INVERSEWEIGHT));
	PyDict_SetItemString(module_dict, "CONFIDENCE_LINEARWEIGHT",
	                     Py_BuildValue( "i", CONFIDENCE_LINEARWEIGHT));
	PyDict_SetItemString(module_dict, "CONFIDENCE_NUN",
	                     Py_BuildValue( "i", CONFIDENCE_NUN));
	PyDict_SetItemString(module_dict, "CONFIDENCE_NNDISTANCE",
	                     Py_BuildValue( "i", CONFIDENCE_NNDISTANCE));
	PyDict_SetItemString(module_dict, "CONFIDENCE_AVGDISTANCE",
	                     Py_BuildValue( "i", CONFIDENCE_AVGDISTANCE));
}

