/*
 *
 * Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, and Karl MacMillan
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

using namespace Gamera;

static PyTypeObject RegionType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

PyTypeObject* get_RegionType() {
  return &RegionType;
}

static PyObject* _region_new(PyTypeObject* pytype, Region* region) {
  RectObject* so;
  so = (RectObject*)pytype->tp_alloc(pytype, 0);
  so->m_x = region;
  return (PyObject*)so;
}

static PyObject* region_new(PyTypeObject* pytype, PyObject* args,
			    PyObject* kwds) {
  int num_args = PyTuple_GET_SIZE(args);
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
	return _region_new(pytype, new Region(point_a, point_b));
      } catch (const std::invalid_argument& e) {
	if (is_SizeObject(b)) {
	  return _region_new(pytype, new Region(point_a, *((SizeObject*)b)->m_x));
	} else if (is_DimObject(b)) {
	  return _region_new(pytype, new Region(point_a, *((DimObject*)b)->m_x));
	}
      }
    }
  }

 phase2:

  PyErr_Clear();
  PyErr_SetString(PyExc_TypeError, "Invalid arguments for Region constructor.");
  return 0;
}

static void region_dealloc(PyObject* self) {
  RectObject* r = (RectObject*)self;
  delete r->m_x;
  self->ob_type->tp_free(self);
}

static PyObject* region_get(PyObject* self, PyObject* args) {
  char* key;
  if (PyArg_ParseTuple(args,  "s", &key) <= 0)
    return 0;
  RectObject* r = (RectObject*)self;
  Region* region = (Region*)r->m_x;
  return Py_BuildValue( "d", region->get(key));
}

static PyObject* region_add(PyObject* self, PyObject* args) {
  char* key;
  double value;
  if (PyArg_ParseTuple(args,  "sd", &key, &value) <= 0)
    return 0;
  RectObject* r = (RectObject*)self;
  Region* region = (Region*)r->m_x;
  region->add(key, value);
  Py_XINCREF(Py_None);
  return Py_None;
}

static PyMethodDef region_methods[] = {
        {  "get", region_get, METH_VARARGS },
        {  "add", region_add, METH_VARARGS },
        { NULL }
};

void init_RegionType(PyObject* module_dict) {
  Py_TYPE(&RegionType) = &PyType_Type;
  RegionType.tp_name =  "gameracore.Region";
  RegionType.tp_basicsize = sizeof(RegionObject);
  RegionType.tp_dealloc = region_dealloc;
  RegionType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  RegionType.tp_base = get_RectType();
  RegionType.tp_methods = region_methods;
  RegionType.tp_new = region_new;
  RegionType.tp_getattro = PyObject_GenericGetAttr;
  RegionType.tp_alloc = NULL; // PyType_GenericAlloc;
  RegionType.tp_free = NULL; // _PyObject_Del;
  PyType_Ready(&RegionType);
  PyDict_SetItemString(module_dict, "Region", (PyObject*)&RegionType);
}
