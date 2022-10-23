/*
 *
 * Copyright (C) 2011 Christian Brandt
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
#ifndef _GRAPHDATAPYOBJECT_HPP_367750A70EE140
#define _GRAPHDATAPYOBJECT_HPP_367750A70EE140

//@see https://docs.python.org/3/c-api/intro.html#include-files
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "graphdata.hpp"
#include "gameramodule.hpp"

namespace Gamera { namespace GraphApi {

   
   
// -----------------------------------------------------------------------------
/** GraphDataPyObject holds data for a node and pointer to a possibly delivered 
 * NodeObject used in the Python wrapper
 * */
struct GraphDataPyObject: public GraphData {
   PyObject* data;
   PyObject* _node;

    explicit GraphDataPyObject(PyObject* d = nullptr)  {
      data = d;
      _node = nullptr;
      incref();
   }

   ~GraphDataPyObject() override {
      decref();
   }

   GraphDataPyObject& operator=(const GraphDataPyObject& other) {
    	decref();
      data = other.data;
      _node = other._node;
      incref();
      return *this;
   }

   void incref() override{
     Py_XINCREF(data);
     Py_XINCREF(_node);
   }

   void decref() override{
     Py_XDECREF(data);
     Py_XDECREF(_node);
   }

   int compare(const GraphData& b) const override {
     if (PyObject_RichCompareBool(data, dynamic_cast<const GraphDataPyObject &>(b).data, Py_LT))
       return -1;
     else if (PyObject_RichCompareBool(data, dynamic_cast<const GraphDataPyObject &>(b).data, Py_GT))
       return 1;
     else
       return 0;
   }


    GraphData* copy() override {
      return new GraphDataPyObject(data);
   }
};



}} //end Gamera::GraphApi
#endif /* _GRAPHDATAPYOBJECT_HPP_367750A70EE140 */

