/*
 *
 * Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, Karl MacMillan
 *               2012      Christoph Dalitz
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

static PyTypeObject PointType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

static PyNumberMethods point_number_methods;


PyTypeObject* get_PointType() {
  return &PointType;
}

static PyObject* _point_new(PyTypeObject* pytype, Point *p) {
  PointObject* so;
  so = (PointObject*)pytype->tp_alloc(pytype, 0);
  so->m_x = p;
  return (PyObject*)so;
}

static PyObject* point_new(PyTypeObject* pytype, PyObject* args,
			  PyObject* kwds) {
  int num_args = PyTuple_GET_SIZE(args);
  if (num_args == 2) {
    int x, y;
    if (PyArg_ParseTuple(args,  "ii", &x, &y))
      return _point_new(pytype, new Point((size_t)x, (size_t)y));
  }

  PyErr_Clear();

  if (num_args == 1) {
    PyObject* py_point;
    if (PyArg_ParseTuple(args,  "O", &py_point)) {
      try {
	return _point_new(pytype, new Point(coerce_Point(py_point)));
      } catch (std::invalid_argument e) {
	;
      }
    }
  }

  PyErr_Clear();
  PyErr_SetString(PyExc_TypeError, "Invalid arguments to Point constructor.  Must be Point(int x, int y)");
  return 0;
}

static void point_dealloc(PyObject* self) {
  PointObject* x = (PointObject*)self;
  delete x->m_x;
  self->ob_type->tp_free(self);
}

#define CREATE_GET_FUNC(name) static PyObject* point_get_##name(PyObject* self) {\
  Point* x = ((PointObject*)self)->m_x; \
  return PyLong_FromLong((int)x->name()); \
}

#define CREATE_SET_FUNC(name) static int point_set_##name(PyObject* self, PyObject* value) {\
  Point* x = ((PointObject*)self)->m_x; \
  x->name((size_t)PyLong_AS_LONG(value)); \
  return 0; \
}

CREATE_GET_FUNC(x)
CREATE_GET_FUNC(y)
CREATE_SET_FUNC(x)
CREATE_SET_FUNC(y)

static PyObject* point_move(PyObject* self, PyObject* args) {
  Point* x = ((PointObject*)self)->m_x;
  int xv, y;
  if (PyArg_ParseTuple(args,  "ii:move", &xv, &y) <= 0)
    return 0;
  x->move(xv, y);
  Py_XINCREF(Py_None);
  return Py_None;
}

static PyObject* point_richcompare(PyObject* a, PyObject* b, int op) {
  if (!is_PointObject(a)) {
    Py_XINCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }

  Point ap = *((PointObject*)a)->m_x;
  Point bp;

  try {
    bp = coerce_Point(b);
  } catch (std::invalid_argument e) {
    Py_XINCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }

  /*
    Only equality and inequality make sense.
  */
  bool cmp;
  switch (op) {
  case Py_LT:
    Py_XINCREF(Py_NotImplemented);
    return Py_NotImplemented;
  case Py_LE:
    Py_XINCREF(Py_NotImplemented);
    return Py_NotImplemented;
  case Py_EQ:
    cmp = ap == bp;
    break;
  case Py_NE:
    cmp = ap != bp;
    break;
  case Py_GT:
    Py_XINCREF(Py_NotImplemented);
    return Py_NotImplemented;
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

static PyObject* point_repr(PyObject* self) {
  Point* x = ((PointObject*)self)->m_x;
  return PyUnicode_FromFormat("Point(%i, %i)",
			     (int)x->x(), (int)x->y());
}

static long point_hash(PyObject* self) {
  Point* x = ((PointObject*)self)->m_x;
  return ((x->x() << 16) + x->y());
}

static PyObject* point_add(PyObject* self, PyObject* args) {
  Point* x = ((PointObject*)self)->m_x;
  try {
    Point p = coerce_Point(args);
    //Point result(x->x()+p.x(), x->y()+p.y());
    Point result = *x + p;
    return create_PointObject(result);
  } catch (std::exception e) {
    return 0;
  }
}
static PyGetSetDef point_getset[] = {
        { (char *)"x", (getter)point_get_x, (setter)point_set_x, (char *)"(int property)\n\nThe current x value", 0},
        { (char *)"y", (getter)point_get_y, (setter)point_set_y, (char *)"(int property)\n\nThe current y value", 0},
        { NULL }
};

static PyMethodDef point_methods[] = {
        { (char *)"move", point_move, METH_VARARGS,
                (char *)"**move** (*x*, *y*)\n\nMoves the point by the given *x*, *y* coordinate, i.e. the vector (*x*, *y*) is added to the point. The following two lines are equivalent:\n\n.. code:: Python\n\n    p.move(x,y)\n    p += Point(x,y)"},
        { NULL }
};


void init_PointType(PyObject* module_dict) {
  point_number_methods.nb_add = point_add;

  Py_TYPE(&PointType) = &PyType_Type;
  PointType.tp_name =  "gameracore.Point";
  PointType.tp_basicsize = sizeof(PointObject);
  PointType.tp_dealloc = point_dealloc;
  PointType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PointType.tp_new = point_new;
  PointType.tp_getattro = PyObject_GenericGetAttr;
  PointType.tp_alloc = NULL; // PyType_GenericAlloc;
  PointType.tp_richcompare = point_richcompare;
  PointType.tp_getset = point_getset;
  PointType.tp_free = NULL; // _PyObject_Del;
  PointType.tp_methods = point_methods;
  PointType.tp_repr = point_repr;
  PointType.tp_hash = point_hash;
  PointType.tp_doc =
"__init__(Int *x*, Int *y*)\n\n"
"Point stores an (*x*, *y*) coordinate point. On the C++ side, the\n"
"coordinates are unsigned integers, so that you cannot use negative\n"
"*x* or *y* values.\n\n"
"Most functions that take a Point as an argument can also take a\n"
"2-element sequence.  For example, the following are all equivalent:\n\n"
".. code:: Python\n\n"
"    px = image.get(Point(5, 2))\n"
"    px = image.get((5, 2))\n"
"    px = image.get([5, 2])\n\n"
"From the numeric operators, only *+* and *+=* are implemented, because\n"
"subtraction would cause problems when the result is negative.\n"
"On the C++ side, the comparison operator *<* is also implemented, which does\n"
"not make real sense, but allows Points to be used as keys in maps and sets.";
  PointType.tp_as_number = &point_number_methods;
  PyType_Ready(&PointType);
  PyDict_SetItemString(module_dict, "Point", (PyObject*)&PointType);
}
