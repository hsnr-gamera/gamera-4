/*
 *
 * Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, and Karl MacMillan
 *               2011      Christian Brandt
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

#include "nodeobject.hpp"
#include "graphobject.hpp"
#include "edgeobject.hpp"

// Factory wrapper for creating graph easier
template<flag_t F>
static PyObject* Factory(PyObject* self, PyObject* args) {
  PyObject *a = nullptr;
  if (PyArg_ParseTuple(args,  "|O", &a) <= 0)
    return 0;
  if (a == nullptr)
    return (PyObject*)graph_new(F);
  if (is_GraphObject(a))
    return (PyObject*)graph_copy((GraphObject*)a, F);
  PyErr_SetString(PyExc_TypeError, "Invalid argument type (must be Graph)");
  return 0;
}



// defines some convenience wrappers for creating graphs easier.
PyMethodDef graph_module_methods[] = {
  {  "Tree", Factory<FLAG_TREE>, METH_VARARGS,
     "Create a new Tree" },
  {  "FreeGraph", Factory<FLAG_FREE>, METH_VARARGS,
     "Create a new freeform Graph" },
  {  "Free", Factory<FLAG_FREE>, METH_VARARGS,
     "Create a new freeform Graph" },
  {  "DAG", Factory<FLAG_DAG>, METH_VARARGS,
     "Create a new directed acyclic graph" },
  {  "Undirected", Factory<FLAG_UNDIRECTED>, METH_VARARGS,
     "Create a new undirected (cyclic) graph" },
  {nullptr}
};

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "gamera.graph",
        nullptr,
        -1,
        graph_module_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
};


PyMODINIT_FUNC PyInit_graph(void) {
    PyObject *m = PyModule_Create(&moduledef);
    PyObject *d = PyModule_GetDict(m);

    init_NodeType();
    init_EdgeType();
    if(!init_GraphType(d)){
    	return nullptr;
    }

    PyDict_SetItemString(d, "DEFAULT", PyLong_FromLong(FLAG_DEFAULT));
    PyDict_SetItemString(d, "DIRECTED", PyLong_FromLong(FLAG_DIRECTED));
    PyDict_SetItemString(d, "CYCLIC", PyLong_FromLong(FLAG_CYCLIC));
    PyDict_SetItemString(d, "BLOB", PyLong_FromLong(FLAG_BLOB));
    PyDict_SetItemString(d, "MULTI_CONNECTED", PyLong_FromLong(FLAG_MULTI_CONNECTED));
    PyDict_SetItemString(d, "SELF_CONNECTED", PyLong_FromLong(FLAG_SELF_CONNECTED));
    PyDict_SetItemString(d, "UNDIRECTED", PyLong_FromLong(FLAG_UNDIRECTED));
    PyDict_SetItemString(d, "TREE", PyLong_FromLong(FLAG_TREE));
    PyDict_SetItemString(d, "FREE", PyLong_FromLong(FLAG_FREE));
    PyDict_SetItemString(d, "FLAG_DAG", PyLong_FromLong(FLAG_DAG));
    PyDict_SetItemString(d, "CHECK_ON_INSERT", PyLong_FromLong(FLAG_CHECK_ON_INSERT));

    return m;
}

