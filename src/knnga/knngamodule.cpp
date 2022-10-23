/*
 * Copyright (C) 2012 Tobias Bolten
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
 
//@see https://docs.python.org/3/c-api/intro.html#include-files
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "knnga.hpp"

using namespace Gamera;
using namespace Gamera::GA;

//******************************************************************************
// interface for GABaseSetting class
//******************************************************************************

struct GABaseSettingObject {
    PyObject_HEAD
    GABaseSetting *baseSetting;
};

static PyTypeObject GABaseSettingType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

static PyObject *GABaseSetting_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GABaseSettingObject *self;
    self = (GABaseSettingObject*)(GABaseSettingType.tp_alloc(&GABaseSettingType, 0));

    // Default values for new GABaseSetting-Object
    int opMode = GA_SELECTION;
    unsigned int pSize = 75;
    double cRate = 0.95;
    double mRate = 0.05;

    if (!PyArg_ParseTuple(args,  "|iIdd", &opMode, &pSize, &cRate, &mRate)) {
        PyErr_SetString(PyExc_RuntimeError, "GABaseSetting: argument parse error");
        return nullptr;
    }

    if (opMode != GA_SELECTION && opMode != GA_WEIGHTING) {
        PyErr_SetString(PyExc_RuntimeError, "GABaseSetting: unknown mode of operation");
        return nullptr;
    }

    try {
        self->baseSetting = new GABaseSetting(opMode, pSize, cRate, mRate);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    return (PyObject*) self;
}

static void GABaseSetting_dealloc(PyObject *object) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    try {
        delete self->baseSetting;
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject*)self)->ob_type->tp_free(self);
}

static PyObject* getOpMode(PyObject* object) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    try {
        return Py_BuildValue( "i", self->baseSetting->getOpMode());
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static PyObject* getPopSize(PyObject* object) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    try {
        return Py_BuildValue( "I", self->baseSetting->getPopSize());
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static PyObject* getCrossRate(PyObject* object) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    try {
        return Py_BuildValue( "d", self->baseSetting->getCrossRate());
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static PyObject* getMutRate(PyObject* object) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    try {
        return Py_BuildValue( "d", self->baseSetting->getMutRate());
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static int setOpMode(PyObject* object, PyObject* arg) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    if(!PyLong_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "GABaseSetting.setOpMode: mode have to be an int");
        return -1;
    }

    int opMode = (int) PyLong_AsLong(arg);

    if (opMode != GA_SELECTION && opMode != GA_WEIGHTING) {
        PyErr_SetString(PyExc_RuntimeError, "GABaseSetting: unknown mode of operation");
        return -1;
    }

    try {
        self->baseSetting->setOpMode((int) PyLong_AsLong(arg));
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return -1;
    }

    return 0;
}

static int setPopSize(PyObject* object, PyObject* arg) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    if(!PyLong_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "GABaseSetting.setPopSize: popSize have to be an int");
        return -1;
    }

    try {
        self->baseSetting->setPopSize((unsigned int) PyLong_AsLong(arg));
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return -1;
    }

    return 0;
}

static int setCrossRate(PyObject* object, PyObject* arg) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    if(!PyFloat_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "GABaseSetting.setCrossRate: cRate have to be a float value");
        return -1;
    }

    try {
        self->baseSetting->setCrossRate(PyFloat_AsDouble(arg));
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return -1;
    }

    return 0;
}

static int setMutRate(PyObject* object, PyObject* arg) {
    GABaseSettingObject *self = (GABaseSettingObject*) object;

    if(!PyFloat_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "GABaseSetting.setMutRate: mRate have to be a float value");
        return -1;
    }

    try {
        self->baseSetting->setMutRate(PyFloat_AsDouble(arg));
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return -1;
    }

    return 0;
}


PyMethodDef GABaseSetting_methods[] = {
        { nullptr }
};

PyGetSetDef GABaseSetting_getset[] = {
        { (char *) "opMode", (getter)getOpMode, (setter)setOpMode,
                (char *) "flag which determines the mode of operation (can be set to the "
                         "defined constants ``GA_SELECTION`` (0) or ``GA_WEIGHTING`` (1))", nullptr },
        { (char *) "popSize", (getter)getPopSize, (setter)setPopSize,
                (char *) "the population size", nullptr },
        { (char *) "crossRate", (getter)getCrossRate, (setter)setCrossRate,
                (char *) "the crossover probability "
                         "(should be between 0.0 and 1.0)", nullptr },
        { (char *) "mutRate", (getter)getMutRate, (setter)setMutRate,
                (char *) "the mutation probability "
                         "(should be between 0.0 and 1.0)", nullptr },
        { nullptr }
};

void init_GABaseSettingType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GABaseSettingType, &PyType_Type);
    #else
      Py_TYPE(&GABaseSettingType) = &PyType_Type;
    #endif
    GABaseSettingType.tp_name =  "gamera.knnga.GABaseSetting";
    GABaseSettingType.tp_basicsize = sizeof(GABaseSettingObject);
    GABaseSettingType.tp_dealloc = GABaseSetting_dealloc;
    GABaseSettingType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GABaseSettingType.tp_new = GABaseSetting_new;
    GABaseSettingType.tp_getattro = PyObject_GenericGetAttr;
    GABaseSettingType.tp_alloc = nullptr;
    GABaseSettingType.tp_free = nullptr;
    GABaseSettingType.tp_methods = GABaseSetting_methods;
    GABaseSettingType.tp_getset = GABaseSetting_getset;
    GABaseSettingType.tp_doc =
        "**GABaseSetting** (*opMode* = ``GA_SELECTION``,"
        " int *popSize* = ``75``,"
        " double *crossRate* = ``0.95``,"
        " double *mutRate* = ``0.05``)\n\n"
        "The ``GABaseSetting`` constructor creates a new settings object with "
        "the basic parameters for GA-optimization for the later usage in a "
        "GAOptimization-object.\n\n"
        "*opMode* (optional)\n"
        "    set optimization mode to ``GA_SELECTION`` or ``GA_WEIGHTING``\n"
        "int *popSize* (optional)\n"
        "    population size which is used in the GA-progress\n"
        "double *crossRate* (optional)\n"
        "    crossover probability which is used in the GA-progress\n"
        "double *mutRate* (optional)\n"
        "    mutation probability which is used in the GA-progress\n";

    PyType_Ready(&GABaseSettingType);
    PyDict_SetItemString(d, "GABaseSetting", (PyObject*)&GABaseSettingType);
}

//******************************************************************************
// interface for GASelection class
//******************************************************************************


static PyTypeObject GASelectionType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
};

struct GASelectionObject {
    PyObject_HEAD
    GASelection<SelectionIndi> *bitSelection;
    GASelection<WeightingIndi> *realSelection;
};

static PyObject *GASelection_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GASelectionObject *self;
    self = (GASelectionObject*)(GASelectionType.tp_alloc(&GASelectionType, 0));

    try {
        self->bitSelection = new GASelection<SelectionIndi>();
        self->realSelection = new GASelection<WeightingIndi>();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    return (PyObject*) self;
}

static void GASelection_dealloc(PyObject *object) {
    GASelectionObject *self = (GASelectionObject*) object;

    try {
        delete self->bitSelection;
        delete self->realSelection;
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject *)self)->ob_type->tp_free(self);
}

static PyObject* setRoulettWheel(PyObject* object, PyObject* args) {
    GASelectionObject *self = (GASelectionObject*) object;

    try {
        self->bitSelection->setRoulettWheel();
        self->realSelection->setRoulettWheel();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setRoulettWheelScaled(PyObject* object, PyObject* args) {
    GASelectionObject *self = (GASelectionObject*) object;
    double preasure = 2.0;

    if (PyArg_ParseTuple(args,  "|d", &preasure) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GASelection.setRoulettWheelScaled: argument parse error");
        return nullptr;
    }

    try {
        self->bitSelection->setRoulettWheelScaled(preasure);
        self->realSelection->setRoulettWheelScaled(preasure);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setStochUniSampling(PyObject* object, PyObject* args) {
    GASelectionObject *self = (GASelectionObject*) object;

    try {
        self->bitSelection->setStochUniSampling();
        self->realSelection->setStochUniSampling();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setRankSelection(PyObject* object, PyObject* args) {
    GASelectionObject *self = (GASelectionObject*) object;
    double preasure = 2.0;
    double exponent = 1.0;

    if (PyArg_ParseTuple(args,  "|dd", &preasure, &exponent) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GASelection.setRankSelection: argument parse error");
        return nullptr;
    }

    try {
        self->bitSelection->setRankSelection(preasure, exponent);
        self->realSelection->setRankSelection(preasure, exponent);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setTournamentSelection(PyObject* object, PyObject* args) {
    GASelectionObject *self = (GASelectionObject*) object;
    unsigned int tSize = 3;

    if (PyArg_ParseTuple(args,  "|I", &tSize) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GASelection.setTournamentSelection: argument parse error");
        return nullptr;
    }

    try {
        self->bitSelection->setTournamentSelection(tSize);
        self->realSelection->setTournamentSelection(tSize);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setRandomSelection(PyObject* object, PyObject* args) {
    GASelectionObject *self = (GASelectionObject*) object;

    try {
        self->bitSelection->setRandomSelection();
        self->realSelection->setRandomSelection();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}


PyMethodDef GASelection_methods[] = {
        { (char *) "setRoulettWheel", setRoulettWheel, METH_NOARGS,
                (char *) "**setRoulettWheel** ()\n\n"
                         "Set the roulette wheel selection method for the GA-progress. "
                         "This method picks up an individual proportional to the "
                         "stored fitness value."
        },
        { (char *) "setRoulettWheelScaled", setRoulettWheelScaled, METH_VARARGS,
                (char *) "**setRoulettWheelScaled** (double *preasure* = ``2.0``)\n\n"
                         "Set the roulette wheel selection with linear scaled fitness "
                         "values as selection method for the GA-progress.\n\n"
                         "double *preasure* (optional)\n"
                         "    the selective pressure, should be in [1,2]"
        },
        { (char *) "setStochUniSampling", setStochUniSampling, METH_NOARGS,
                (char *) "**setStochUniSampling** ()\n\n"
                         "Set the stochastic universal sampling method as selection "
                         "method for the GA-progress.\n\nThis method selects an individual "
                         "proportional to the stores fitness value. Compared with the "
                         "roulette wheel selection method all individuals are selected "
                         "in only one step."
        },
        { (char *) "setRankSelection", setRankSelection, METH_VARARGS,
                (char *) "**setRankSelection** (double *preasure* = ``2.0``, double *exponent* = ``1.0``)\n\n"
                         "Set the rank selection method as selection method for the "
                         "GA-progress.\n\n"
                         "This method picks up an individual by roulette wheel based on his "
                         "rank in the current population.\n\n"
                         "double *preasure* (optional)\n"
                         "    the selective pressure, should be in [1,2]\n"
                         "double *exponent* (optional)\n"
                         "    exponent (1 == linear)\n"
        },
        { (char *) "setTournamentSelection", setTournamentSelection, METH_VARARGS,
                (char *) "**setTournamentSelection** (int *tSize* = ``3``)\n\n"
                         "Set a deterministic tournament selection method for selecting "
                         "the individuals in the genetic algorithm.\n\n"
                         "int *tSize* (optional)\n"
                         "    the number of individuals in the tournament"
        },
        { (char *) "setRandomSelection", setRandomSelection, METH_NOARGS,
                (char *) "**setRandomSelection** ()\n\n"
                         "Select all individuals in the genetic progress randomly."
        },
        { nullptr }
};

PyGetSetDef GASelection_getset[] = {
        { nullptr }
};

void init_GASelectionType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GASelectionType, &PyType_Type);
    #else
      Py_TYPE(&GASelectionType) = &PyType_Type;
    #endif
    GASelectionType.tp_name =  "gamera.knnga.GASelection";
    GASelectionType.tp_basicsize = sizeof(GASelectionObject);
    GASelectionType.tp_dealloc = GASelection_dealloc;
    GASelectionType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GASelectionType.tp_new = GASelection_new;
    GASelectionType.tp_getattro = PyObject_GenericGetAttr;
    GASelectionType.tp_alloc = nullptr;
    GASelectionType.tp_free = nullptr;
    GASelectionType.tp_methods = GASelection_methods;
    GASelectionType.tp_getset = GASelection_getset;
    GASelectionType.tp_doc =  "**GASelection** ()\n\n"
        "The ``GASelection`` constructor creates a new settings object "
        "for the GA-optimization which specifies the used individuals selection method. "
        "This object can later be used in an ``GAOptimization``-object. \n\n"
        "Only one selection method can be chosen. Multiple settings will "
        "override each other.";

    PyType_Ready(&GASelectionType);
    PyDict_SetItemString(d, "GASelection", (PyObject*)&GASelectionType);
}

//******************************************************************************
// interface for GACrossover class
//******************************************************************************


struct GACrossoverObject {
    PyObject_HEAD
    GACrossover<SelectionIndi> *bitCrossover;
    GACrossover<WeightingIndi> *realCrossover;
};

static PyTypeObject GACrossoverType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
};

static PyObject *GACrossover_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GACrossoverObject *self;
    self = (GACrossoverObject*)(GACrossoverType.tp_alloc(&GACrossoverType, 0));

    try {
        self->bitCrossover = new GACrossover<SelectionIndi>();
        self->realCrossover = new GACrossover<WeightingIndi>();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    return (PyObject*) self;
}

static void GACrossover_dealloc(PyObject *object) {
    GACrossoverObject *self = (GACrossoverObject*) object;

    try {
        delete self->bitCrossover;
        delete self->realCrossover;
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject *)self)->ob_type->tp_free(self);
}

static PyObject* setNPointCrossover(PyObject* object, PyObject* args) {
    GACrossoverObject *self = (GACrossoverObject*) object;
    unsigned int n = 1;

    if (PyArg_ParseTuple(args,  "|I", &n) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GACrossover.setNPointCrossover: argument parse error");
        return nullptr;
    }

    try {
        self->bitCrossover->setNPointCrossover(n);
        self->realCrossover->setNPointCrossover(n);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setUniformCrossover(PyObject* object, PyObject* args) {
    GACrossoverObject *self = (GACrossoverObject*) object;
    double preference = 0.5;

    if (PyArg_ParseTuple(args,  "|d", &preference) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GACrossover.setUniformCrossover: argument parse error");
        return nullptr;
    }

    try {
        self->bitCrossover->setUniformCrossover(preference);
        self->realCrossover->setUniformCrossover(preference);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setSBXcrossover(PyObject* object, PyObject* args) {
    GACrossoverObject *self = (GACrossoverObject*) object;
    unsigned int numFeatures;
    double min = 0.0, max = 1.0;
    double eta = 1.0;

    if (PyArg_ParseTuple(args,  "I|ddd", &numFeatures, &min, &max, &eta) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GACrossover.setSBXcrossover: argument parse error");
        return nullptr;
    }

    try {
        self->realCrossover->setSBXcrossover(numFeatures, min, max, eta);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setSegmentCrossover(PyObject* object, PyObject* args) {
    GACrossoverObject *self = (GACrossoverObject*) object;
    unsigned int numFeatures;
    double min = 0.0, max = 1.0;
    double alpha = 0.0;

    if (PyArg_ParseTuple(args,  "I|ddd", &numFeatures, &min, &max, &alpha) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GACrossover.setSegmentCrossover: argument parse error");
        return nullptr;
    }

    try {
        self->realCrossover->setSegmentCrossover(numFeatures, min, max, alpha);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setHypercubeCrossover(PyObject* object, PyObject* args) {
    GACrossoverObject *self = (GACrossoverObject*) object;
    unsigned int numFeatures;
    double min = 0.0, max = 1.0;
    double alpha = 0.0;

    if (PyArg_ParseTuple(args,  "I|ddd", &numFeatures, &min, &max, &alpha) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GACrossover.setHypercubeCrossover: argument parse error");
        return nullptr;
    }

    try {
        self->realCrossover->setHypercubeCrossover(numFeatures, min, max, alpha);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}



PyMethodDef GACrossover_methods[] = {
        { (char *) "setNPointCrossover", setNPointCrossover, METH_VARARGS,
                (char *) "**setNPointCrossover** (int *n* = ``1``)\n\n"
                         "Enables the classic n-Point crossover as recombination "
                         "operator in the GA-optimization.\n\n"
                         "int *n* (optional)\n"
                         "    the number of crossover points"
        },
        { (char *) "setUniformCrossover", setUniformCrossover, METH_VARARGS,
                (char *) "**setUniformCrossover** (double *preference* = ``0.5``)\n\n"
                         "Enables the classic uniform crossover operator in the "
                         "recombination of the GA.\n\n"
                         "double *preference* (optional)\n"
                         "    crossover-probability for each allele (should be in [0,1])"
        },
        { (char *) "setSBXcrossover", setSBXcrossover, METH_VARARGS,
                (char *) "**setSBXcrossover** (int *numFeatures*, double *min*, double *max*, double *eta* = ``1.0``)\n\n"
                         "Enables the simulated binary crossover operator for the real "
                         "value encoded individuals used in feature weighting.\n"
                         "For more details on this operator see:\n"
                         "Deb, K. & Agrawal, R. B. (1995) "
                         "Simulated Binary Crossover for Continuous Search Space. "
                         "Complex Systems, 9, pp. 115-148.\n\n"
                         "int *numFeatures*\n"
                         "    the number of used features. Usually this value is set to "
                         "``classifier.num_features``.\n"
                         "double *min* (optional)\n"
                         "    the minimum value which is allowed in an allele (usually 0.0)\n"
                         "double *max* (optional)\n"
                         "    the maximum value which is allowed in an allele (usually 1.0)\n"
                         "double *eta* (optional)\n"
                         "    the amount of exploration OUTSIDE the parents as in BLX-alpha notation"
        },
        { (char *) "setSegmentCrossover", setSegmentCrossover, METH_VARARGS,
                (char *) "**setSegmentCrossover** (int *numFeatures*, double *min*, double *max*, double *alpha* = ``0.0``)\n\n"
                         "Enables the segment crossover operator for the real value "
                         "encoded individuals used in feature weighting.\n"
                         "This operator is a variation from the classical arithmetic "
                         "recombination which performs a uniform choice in segment "
                         "(arithmetical with same value along all coordinates).\n\n"
                         "int *numFeatures*\n"
                         "    the number of used features. Usually this value is set to "
                         "``classifier.num_features``.\n"
                         "double *min* (optional)\n"
                         "    the minimum value which is allowed in an allele (usually 0.0)\n"
                         "double *max* (optional)\n"
                         "    the maximum value which is allowed in an allele (usually 1.0)\n"
                         "double *alpha* (optional)\n"
                         "    the amount of exploration OUTSIDE the parents as in BLX-alpha notation"
        },
        { (char *) "setHypercubeCrossover", setHypercubeCrossover, METH_VARARGS,
                (char *) "**setHypercubeCrossover** (int *numFeatures*, double *min*, double *max*, double *alpha* = ``0.0``)\n\n"
                         "Enables the hypercube crossover operator for the real value "
                         "encoded individuals used in feature weighting.\n"
                         "This operator is a variation from the classicial arithmetic "
                         "recombination which performs a uniform choice in hypercube "
                         "(arithmetical with different values for each coordinate).\n\n"
                         "int *numFeatures*\n"
                         "    the number of used features. Usually this value is set to "
                         "``classifier.num_features``.\n"
                         "double *min* (optional)\n"
                         "    the minimum value which is allowed in an allele (usually 0.0)\n"
                         "double *max* (optional)\n"
                         "    the maximum value which is allowed in an allele (usually 1.0)\n"
                         "double *alpha* (optional)\n"
                         "    the amount of exploration OUTSIDE the parents as in BLX-alpha notation"
        },
        { nullptr }
};

PyGetSetDef GACrossover_getset[] = {
        { nullptr }
};

void init_GACrossoverType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GACrossoverType, &PyType_Type);
    #else
      Py_TYPE(&GACrossoverType) = &PyType_Type;
    #endif
    GACrossoverType.tp_name =  "gamera.knnga.GACrossover";
    GACrossoverType.tp_basicsize = sizeof(GACrossoverObject);
    GACrossoverType.tp_dealloc = GACrossover_dealloc;
    GACrossoverType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GACrossoverType.tp_new = GACrossover_new;
    GACrossoverType.tp_getattro = PyObject_GenericGetAttr;
    GACrossoverType.tp_alloc = nullptr;
    GACrossoverType.tp_free = nullptr;
    GACrossoverType.tp_methods = GACrossover_methods;
    GACrossoverType.tp_getset = GACrossover_getset;
    GACrossoverType.tp_doc =  "**GACrossover** ()\n\n"
        "The ``GACrossover`` constructor creates a new settings object "
        "for the GA-optimization which specifies the selected "
        "crossover-operators. This object can later be used in an "
        "``GAOptimization``-object.\n\n"
        "Combination from different crossover-operators are possible. Each "
        "selected operator can later used with an equal probability within "
        "the optimization.";

    PyType_Ready(&GACrossoverType);
    PyDict_SetItemString(d, "GACrossover", (PyObject*)&GACrossoverType);
}

//******************************************************************************
// interface for GAMutation class
//******************************************************************************
struct GAMutationObject {
    PyObject_HEAD
    GAMutation<SelectionIndi> *bitMutation;
    GAMutation<WeightingIndi> *realMutation;
};

static PyTypeObject GAMutationType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};
static PyObject *GAMutation_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GAMutationObject *self;
    self = (GAMutationObject*)(GAMutationType.tp_alloc(&GAMutationType, 0));

    try {
        self->bitMutation = new GAMutation<SelectionIndi>();
        self->realMutation = new GAMutation<WeightingIndi>();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    return (PyObject*) self;
}

static void GAMutation_dealloc(PyObject *object) {
    GAMutationObject *self = (GAMutationObject*) object;

    try {
        delete self->bitMutation;
        delete self->realMutation;
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject *)self)->ob_type->tp_free(self);
}

static PyObject* setShiftMutation(PyObject* object, PyObject* args) {
    GAMutationObject *self = (GAMutationObject*) object;

    try {
        self->bitMutation->setShiftMutation();
        self->realMutation->setShiftMutation();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setSwapMutation(PyObject* object, PyObject* args) {
    GAMutationObject *self = (GAMutationObject*) object;

    try {
        self->bitMutation->setSwapMutation();
        self->realMutation->setSwapMutation();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setInversionMutation(PyObject* object, PyObject* args) {
    GAMutationObject *self = (GAMutationObject*) object;

    try {
        self->bitMutation->setInversionMutation();
        self->realMutation->setInversionMutation();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setBinaryMutation(PyObject* object, PyObject* args) {
    GAMutationObject *self = (GAMutationObject*) object;
    double rate = 0.05;
    bool norm = false;

    PyObject *normalize = nullptr;
    if (PyArg_ParseTuple(args,  "|dO", &rate, &normalize) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GAMutation.setBinaryMutation: argument parse error");
        return nullptr;
    }

    if (normalize != nullptr) {
        if(!PyBool_Check(normalize)) {
            PyErr_SetString(PyExc_TypeError, "GAMutation.setBinaryMutation: normalize have to be a bool");
            return nullptr;
        }

        norm = PyObject_IsTrue(normalize);
    }

    try {
        self->bitMutation->setBinaryMutation(rate, norm);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setGaussMutation(PyObject* object, PyObject* args) {
    GAMutationObject *self = (GAMutationObject*) object;
    unsigned int numFeatures;
    double min, max;
    double sigma, pChange;

    if (PyArg_ParseTuple(args,  "Idddd", &numFeatures, &min, &max, &sigma, &pChange) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GAMutation.setGaussMutation: argument parse error");
        return nullptr;
    }

    try {
        self->realMutation->setGaussMutation(numFeatures, min, max, sigma, pChange);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

PyMethodDef GAMutation_methods[] = {
        { (char *) "setShiftMutation", setShiftMutation, METH_NOARGS,
                (char *) "**setShiftMutation** () \n\n"
                         "Enables the shift mutation on the chromosome as mutation "
                         "operator in the genetic algorithm. This means the allele "
                         "between two points are right shifted."
        },
        { (char *) "setSwapMutation", setSwapMutation, METH_NOARGS,
                (char *) "**setSwapMutation** () \n\n"
                         "Enables the swap mutation on the chromosome as muation operator "
                         "in the genetic algorithm. This means two allele within the "
                         "chromosome are exchanged."
        },
        { (char *) "setInversionMutation", setInversionMutation, METH_NOARGS,
                (char *) "**setInversionMutation** ()\n\n"
                         "Enables the inversion mutation on the chromosome as mutation "
                         "operator in the genetic algorithm. This means the ordering "
                         "from the allels between two points will be reversed."
        },
        { (char *) "setBinaryMutation", setBinaryMutation, METH_VARARGS,
                (char *) "**setBinaryMutation** (double *rate* = ``0.05``, bool *normalize* = ``False``) \n\n"
                         "Enables the classic bit-flip mutation for bitstring "
                         "individuals. This means that this operator only effects "
                         "feature selection.\n\n"
                         "double *rate* (optional)\n"
                         "    the probability for mutation of an allele (should be in [0,1])\n"
                         "bool *normalize* (optional)\n"
                         "    if true ``rate/chromosomeSize`` is used"
        },
        { (char *) "setGaussMutation", setGaussMutation, METH_VARARGS,
                (char *) "**setGaussMutation** (int *numFeatures*, double *min*, double *max*, double *sigma*, double *rate*)\n\n"
                         "Enables the mutation based on a Gaussian distribution for real "
                         "value individuals. This means that his operator only effects "
                         "feature weighting. A random number is "
                         "added to the mutated allele.\n\n"
                         "int *numFeatures*\n"
                         "    the number of used features. Usually this value is set to "
                         "``classifier.num_features``.\n"
                         "double *min*\n"
                         "    the minimum value which is allowed in an allele (usually 0.0)\n"
                         "double *max*\n"
                         "    the maximum value which is allowed in an allele (usually 1.0)\n"
                         "double *sigma*\n"
                         "    the standard deviation of the gaussian distribution. This "
                         "parameter determines the strength of the mutation.\n"
                         "double *rate*\n"
                         "    the probability for mutating an allele (should be in [0,1])\n"
        },
        { nullptr }
};

PyGetSetDef GAMutation_getset[] = {
        { nullptr }
};

void init_GAMutationType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GAMutationType, &PyType_Type);
    #else
      Py_TYPE(&GAMutationType) = &PyType_Type;
    #endif
    GAMutationType.tp_name =  "gamera.knnga.GAMutation";
    GAMutationType.tp_basicsize = sizeof(GAMutationObject);
    GAMutationType.tp_dealloc = GAMutation_dealloc;
    GAMutationType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GAMutationType.tp_new = GAMutation_new;
    GAMutationType.tp_getattro = PyObject_GenericGetAttr;
    GAMutationType.tp_alloc = nullptr;
    GAMutationType.tp_free = nullptr;
    GAMutationType.tp_methods = GAMutation_methods;
    GAMutationType.tp_getset = GAMutation_getset;
    GAMutationType.tp_doc =  "**GAMutation** ()\n\n"
        "The ``GAMutation`` constructor creates a new settings object "
        "for the GA-optimization which specifies the selected "
        "mutation-operators. This object can later be used in an "
        "``GAOptimization``-object.\n\n"
        "Combinations of different mutations-operators are possible. Each "
        "selected operator is used with an equal probability within "
        "the optimization.\n\n"
        ".. note:: Only mutation-operators from the corresponding category "
        "(feature selection or weighting) are used later in the optimization "
        "based on the selection in the GABaseSetting-object.";

    PyType_Ready(&GAMutationType);
    PyDict_SetItemString(d, "GAMutation", (PyObject*)&GAMutationType);
}

//******************************************************************************
// interface for GAReplacement class
//******************************************************************************

struct GAReplacementObject {
    PyObject_HEAD
    GAReplacement<SelectionIndi> *bitReplacement;
    GAReplacement<WeightingIndi> *realReplacement;
};

static PyTypeObject GAReplacementType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

static PyObject *GAReplacement_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GAReplacementObject *self;
    self = (GAReplacementObject*)(GAReplacementType.tp_alloc(&GAReplacementType, 0));

    try {
        self->bitReplacement = new GAReplacement<SelectionIndi>();
        self->realReplacement = new GAReplacement<WeightingIndi>();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    return (PyObject*) self;
}

static void GAReplacement_dealloc(PyObject *object) {
    GAReplacementObject *self = (GAReplacementObject*) object;

    try {
        delete self->bitReplacement;
        delete self->realReplacement;
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject *)self)->ob_type->tp_free(self);
}

static PyObject* setGenerationalReplacement(PyObject* object, PyObject* args) {
    GAReplacementObject *self = (GAReplacementObject*) object;

    try {
        self->bitReplacement->setGenerationalReplacement();
        self->realReplacement->setGenerationalReplacement();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setSSGAworse(PyObject* object, PyObject* args) {
    GAReplacementObject *self = (GAReplacementObject*) object;

    try {
        self->bitReplacement->setSSGAworse();
        self->realReplacement->setSSGAworse();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setSSGAdetTournament(PyObject* object, PyObject* args) {
    GAReplacementObject *self = (GAReplacementObject*) object;
    unsigned int tSize = 3;

    if (PyArg_ParseTuple(args,  "|I", &tSize) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GAReplacement.setSSGAdetTournament: argument parse error");
        return nullptr;
    }

    try {
        self->bitReplacement->setSSGAdetTournament(tSize);
        self->realReplacement->setSSGAdetTournament(tSize);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}


PyMethodDef GAReplacement_methods[] = {
        { (char *) "setGenerationalReplacement", setGenerationalReplacement, METH_NOARGS,
                (char *) "**setGenerationalReplacement** ()\n\n"
                         "Sets the generational replacement as replacement method for "
                         "the GA-progress. This means that the new individuals in the "
                         "intermediate population will replace the whole population."
        },
        { (char *) "setSSGAworse", setSSGAworse, METH_NOARGS,
                (char *) "**setSSGAworse** ()\n\n"
                         "Sets the steady state worse replacement as replacement method in "
                         "the GA-progress. This means that the worst individuals are "
                         "continuous replaced by better ones."
        },
        { (char *) "setSSGAdetTournament", setSSGAdetTournament, METH_VARARGS,
                (char *) "**setSSGAdetTournament** (int *tSize* = ``3``)\n\n"
                         "Sets an steady state deterministic tournament as replacement "
                         "method in the GA-progress. This means that the loosers of this "
                         "tournament will be replaced in the following population.\n\n"
                         "int *tSize* (optional)\n"
                         "    the number of individuals in the tournament"
        },
        { nullptr }
};

PyGetSetDef GAReplacement_getset[] = {
        { nullptr }
};

void init_GAReplacementType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GAReplacementType, &PyType_Type);
    #else
      Py_TYPE(&GAReplacementType) = &PyType_Type;
    #endif
    GAReplacementType.tp_name =  "gamera.knnga.GAReplacement";
    GAReplacementType.tp_basicsize = sizeof(GAReplacementObject);
    GAReplacementType.tp_dealloc = GAReplacement_dealloc;
    GAReplacementType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GAReplacementType.tp_new = GAReplacement_new;
    GAReplacementType.tp_getattro = PyObject_GenericGetAttr;
    GAReplacementType.tp_alloc = nullptr;
    GAReplacementType.tp_free = nullptr;
    GAReplacementType.tp_methods = GAReplacement_methods;
    GAReplacementType.tp_getset = GAReplacement_getset;
    GAReplacementType.tp_doc =  "**GAReplacement** ()\n\n"
        "The ``GAReplacement`` constructor creates a new settings object "
        "for the GA-optimization which specifies the used replacement method. "
        "This object can later be used in an ``GAOptimization``-object. \n\n"
        "Only one replacement method can be chosen. Multiple settings will "
        "override each other.";

    PyType_Ready(&GAReplacementType);
    PyDict_SetItemString(d, "GAReplacement", (PyObject*)&GAReplacementType);
}

//******************************************************************************
// interface for GAStopCriteria class
//******************************************************************************

struct GAStopCriteriaObject {
    PyObject_HEAD
    GAStopCriteria<SelectionIndi> *bitStopCriteria;
    GAStopCriteria<WeightingIndi> *realStopCriteria;
};

static PyTypeObject GAStopCriteriaType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};
static PyObject *GAStopCriteria_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GAStopCriteriaObject *self;
    self = (GAStopCriteriaObject*)(GAStopCriteriaType.tp_alloc(&GAStopCriteriaType, 0));

    try {
        self->bitStopCriteria = new GAStopCriteria<SelectionIndi>();
        self->realStopCriteria = new GAStopCriteria<WeightingIndi>();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    return (PyObject*) self;
}

static void GAStopCriteria_dealloc(PyObject *object) {
    GAStopCriteriaObject *self = (GAStopCriteriaObject*) object;

    try {
        delete self->bitStopCriteria;
        delete self->realStopCriteria;
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject *)self)->ob_type->tp_free(self);
}

static PyObject* setBestFitnessStop(PyObject* object, PyObject* args) {
    GAStopCriteriaObject *self = (GAStopCriteriaObject*) object;
    double optimum = 1.0;

    if (PyArg_ParseTuple(args,  "|d", &optimum) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GAStopCriteria.setBestFitnessStop: argument parse error");
        return nullptr;
    }

    try {
        self->bitStopCriteria->setBestFitnessStop(optimum);
        self->realStopCriteria->setBestFitnessStop(optimum);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setMaxGenerations(PyObject* object, PyObject* args) {
    GAStopCriteriaObject *self = (GAStopCriteriaObject*) object;
    unsigned int n = 100;

    if (PyArg_ParseTuple(args,  "|I", &n) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GAStopCriteria.setMaxGenerations: argument parse error");
        return nullptr;
    }

    try {
        self->bitStopCriteria->setMaxGenerations(n);
        self->realStopCriteria->setMaxGenerations(n);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setMaxFitnessEvals(PyObject* object, PyObject* args) {
    GAStopCriteriaObject *self = (GAStopCriteriaObject*) object;
    unsigned int n = 5000;

    if (PyArg_ParseTuple(args,  "|I", &n) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GAStopCriteria.setMaxFitnessEvals: argument parse error");
        return nullptr;
    }

    try {
        self->bitStopCriteria->setMaxFitnessEvals(n);
        self->realStopCriteria->setMaxFitnessEvals(n);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* setSteadyStateStop(PyObject* object, PyObject* args) {
    GAStopCriteriaObject *self = (GAStopCriteriaObject*) object;
    unsigned int minGens = 40;
    unsigned int noChangeGens = 10;

    if (PyArg_ParseTuple(args,  "|II", &minGens, &noChangeGens) <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "GAStopCriteria.setSteadyStateStop: argument parse error");
        return nullptr;
    }

    try {
        self->bitStopCriteria->setSteadyStateStop(minGens, noChangeGens);
        self->realStopCriteria->setSteadyStateStop(minGens, noChangeGens);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}


PyMethodDef GAStopCriteria_methods[] = {
        { (char *) "setBestFitnessStop", setBestFitnessStop, METH_VARARGS,
                (char *) "**setBestFitnessStop** (double *optimum* = ``1.0``)\n\n"
                         "Enables the termination by attainment of the specified "
                         "fitness rating measured by one individual.\n\n"
                         "double *optimum* (optional)\n"
                         "    fitness rating"
        },
        { (char *) "setMaxGenerations", setMaxGenerations, METH_VARARGS,
                (char *) "**setMaxGenerations** (int *n* = 100)\n\n"
                         "Enables the termination by attainment of the specified "
                         "number of maximal generations within the optimization process.\n\n"
                         "int *n* (optional)\n"
                         "    the number of maximal generations"
        },
        { (char *) "setMaxFitnessEvals", setMaxFitnessEvals, METH_VARARGS,
                (char *) "**setMaxFitnessEvals** (int *n* = 5000)\n\n"
                         "Enables the termination by attainment of the specified "
                         "amount of fitness evaulations within the optimization "
                         "process\n\n"
                         "int *n* (optional)\n"
                         "    the number of fitness evaluations"
        },
        { (char *) "setSteadyStateStop", setSteadyStateStop, METH_VARARGS,
                (char *) "**setSteadyStateStop** (int *minGens* = 40, int *noChangeGens* = 10)\n\n"
                         "Enables the termination after *noChangeGens* generations without "
                         "improvements within the optimization after at least *minGens* "
                         "generations.\n\n"
                         "int *minGens* (optional)\n"
                         "    the minimum number of generations to be computed\n"
                         "int *noChangeGens* (optional)\n"
                         "    the number of generations without improvements"
        },
        { nullptr }
};

PyGetSetDef GAStopCriteria_getset[] = {
        { nullptr }
};

void init_GAStopCriteriaType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GAStopCriteriaType, &PyType_Type);
    #else
      Py_TYPE(&GAStopCriteriaType) = &PyType_Type;
    #endif
    GAStopCriteriaType.tp_name =  "gamera.knnga.GAStopCriteria";
    GAStopCriteriaType.tp_basicsize = sizeof(GAStopCriteriaObject);
    GAStopCriteriaType.tp_dealloc = GAStopCriteria_dealloc;
    GAStopCriteriaType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GAStopCriteriaType.tp_new = GAStopCriteria_new;
    GAStopCriteriaType.tp_getattro = PyObject_GenericGetAttr;
    GAStopCriteriaType.tp_alloc = nullptr;
    GAStopCriteriaType.tp_free = nullptr;
    GAStopCriteriaType.tp_methods = GAStopCriteria_methods;
    GAStopCriteriaType.tp_getset = GAStopCriteria_getset;
    GAStopCriteriaType.tp_doc =  "**GAStopCriteria** ()\n\n"
        "The ``GAStopCriteria`` constructor creates a new settings object "
        "for the GA-optimization which specified the termination condition "
        "of the optimization progress. This object can later be used in an "
        "``GAOptimization``-object.\n\n"
        "A combination of different stop-criteria methods is possible. "
        "The first condition which becomes ``True`` will end the optimization.";

    PyType_Ready(&GAStopCriteriaType);
    PyDict_SetItemString(d, "GAStopCriteria", (PyObject*)&GAStopCriteriaType);
}

//******************************************************************************
// interface for GAParallelization class
//******************************************************************************

struct GAParallelizationObject {
    PyObject_HEAD
    GAParallelization *parallel;
};

static PyTypeObject GAParallelizationType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

static PyObject *GAParallelization_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GAParallelizationObject *self;
    self = (GAParallelizationObject*)(GAParallelizationType.tp_alloc(&GAParallelizationType, 0));

    PyObject *enabled = nullptr;
    bool mode = true;
    unsigned int threadNum = 2;

    if (!PyArg_ParseTuple(args,  "|OI", &enabled, &threadNum)) {
        PyErr_SetString(PyExc_RuntimeError, "GAParallelization: argument parse error");
        return nullptr;
    }

    if ( enabled != nullptr ) {
        if (!PyBool_Check(enabled)) {
            PyErr_SetString(PyExc_TypeError, "GAParallelization: mode have to be a bool value");
            return nullptr;
        } else {
            mode = PyObject_IsTrue(enabled);
        }
    }

    try {
        self->parallel = new GAParallelization(mode, threadNum);
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    return (PyObject*) self;
}

static void GAParallelization_dealloc(PyObject *object) {
    GAParallelizationObject *self = (GAParallelizationObject*) object;

    try {
        delete self->parallel;
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject *)self)->ob_type->tp_free(self);
}

static PyObject* getMode(PyObject* object) {
    GAParallelizationObject *self = (GAParallelizationObject*) object;
    bool mode;

    try {
        mode = self->parallel->isParallel();
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }

    if ( mode ) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject* getThreadNum(PyObject* object) {
    GAParallelizationObject *self = (GAParallelizationObject*) object;

    try {
        return Py_BuildValue( "I", self->parallel->getThreadNum());
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static int setMode(PyObject* object, PyObject* arg) {
    GAParallelizationObject *self = (GAParallelizationObject*) object;

    if(!PyBool_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "GAParallelization.setMode: modeFlag have to be a bool");
        return -1;
    }

    try {
        self->parallel->changeMode(PyObject_IsTrue(arg));
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return -1;
    }

    return 0;
}

static int setThreadNum(PyObject* object, PyObject* arg) {
    GAParallelizationObject *self = (GAParallelizationObject*) object;

    if(!PyLong_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "GAParallelization.setThreadNum: thredNum have to be an int");
        return -1;
    }

    try {
        self->parallel->setThreadNum((unsigned int) PyLong_AsLong(arg));
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return -1;
    }

    return 0;
}

PyMethodDef GAParallelization_methods[] = {
        { nullptr }
};

PyGetSetDef GAParallelization_getset[] = {
        { (char *) "mode", (getter)getMode, (setter)setMode,
                (char *) "flag which indicates whether parallelization is "
                         "used (``True``) or not (``False``)", nullptr },
        { (char *) "thredNum", (getter)getThreadNum, (setter)setThreadNum,
                (char *) "the number of threads which are used by enabled "
                         "parallelization", nullptr },
        { nullptr }
};

void init_GAParallelizationType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GAParallelizationType, &PyType_Type);
    #else
      Py_TYPE(&GAParallelizationType) = &PyType_Type;
    #endif
    GAParallelizationType.tp_name =  "gamera.knnga.GAParallelization";
    GAParallelizationType.tp_basicsize = sizeof(GAParallelizationObject);
    GAParallelizationType.tp_dealloc = GAParallelization_dealloc;
    GAParallelizationType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GAParallelizationType.tp_new = GAParallelization_new;
    GAParallelizationType.tp_getattro = PyObject_GenericGetAttr;
    GAParallelizationType.tp_alloc = nullptr;
    GAParallelizationType.tp_free = nullptr;
    GAParallelizationType.tp_methods = GAParallelization_methods;
    GAParallelizationType.tp_getset = GAParallelization_getset;
    GAParallelizationType.tp_doc =  "**GAParallelization** (*mode* = ``True``, *threads* = 2)\n\n"
        "The ``GAParallelization`` constructor creates a new settings object "
        "which controls the parallelization within the GA-progress. It is used "
        "later within an ``GAOptimization``-object.\n\n"
        "*mode* (optional)\n"
        "   enable (``True``) or disable (``Flase``) the parallelization of "
        "individual fitness calculations\n"
        "*threads* (optional)\n"
        "   the number of threads which are used for parallelization";

    PyType_Ready(&GAParallelizationType);
    PyDict_SetItemString(d, "GAParallelization", (PyObject*)&GAParallelizationType);
}

//******************************************************************************
// interface for GAOptimization class
//******************************************************************************
struct GAOptimizationObject {
    PyObject_HEAD
    GAOptimization<SelectionIndi> *selection;
    GAOptimization<WeightingIndi> *weighting;
};

static PyTypeObject GAOptimizationType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

static PyObject *GAOptimization_new(PyTypeObject *pytype, PyObject *args, PyObject *kwds) {
    GAOptimizationObject *self;
    self = (GAOptimizationObject*)(GAOptimizationType.tp_alloc(&GAOptimizationType, 0));

    PyObject *baseSetting = nullptr;
    PyObject *classifier = nullptr;
    PyObject *selection = nullptr;
    PyObject *crossover = nullptr;
    PyObject *mutation = nullptr;
    PyObject *replacement = nullptr;
    PyObject *stop = nullptr;
    PyObject *parallelization = nullptr;

    if (!PyArg_ParseTuple(args,  "OOOOOOOO", &classifier, &baseSetting,
        &selection, &crossover, &mutation, &replacement, &stop, &parallelization)) {

        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: argument parse error");
        return nullptr;
    }

    // Check the objects for propper classes
    if (!PyObject_TypeCheck(baseSetting, &GABaseSettingType)) {
        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: baseSetting is not a GABaseSetting instance");
        return nullptr;
    }
    if (!PyObject_TypeCheck(selection, &GASelectionType)) {
        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: selection is not a GASelection instance");
        return nullptr;
    }
    if (!PyObject_TypeCheck(crossover, &GACrossoverType)) {
        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: crossover is not a GACrossover instance");
        return nullptr;
    }
    if (!PyObject_TypeCheck(mutation, &GAMutationType)) {
        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: mutation is not a GAMutation instance");
        return nullptr;
    }
    if (!PyObject_TypeCheck(replacement, &GAReplacementType)) {
        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: replacement is not a GAReplacement instance");
        return nullptr;
    }
    if (!PyObject_TypeCheck(stop, &GAStopCriteriaType)) {
        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: stopCriteria is not a GAStopCriteria instance");
        return nullptr;
    }
    if (!PyObject_TypeCheck(parallelization, &GAParallelizationType)) {
        PyErr_SetString(PyExc_RuntimeError, "GAOptimization: parallelization is not a GAParallelization instance");
        return nullptr;
    }

    // Attention: no type-checking is performed for the classifier object!
    KnnObject *knn = (KnnObject*) classifier;

    GABaseSettingObject *ga_baseSetting = (GABaseSettingObject*) baseSetting;
    GASelectionObject *ga_selection = (GASelectionObject*) selection;
    GACrossoverObject *ga_crossover = (GACrossoverObject*) crossover;
    GAMutationObject *ga_mutation = (GAMutationObject*) mutation;
    GAReplacementObject *ga_replacement = (GAReplacementObject*) replacement;
    GAStopCriteriaObject *ga_stop = (GAStopCriteriaObject*) stop;
    GAParallelizationObject *ga_parallel = (GAParallelizationObject*) parallelization;

    try {
        if (ga_baseSetting->baseSetting->getOpMode() == GA_SELECTION) {
            self->weighting = nullptr;

            self->selection = new GAOptimization<SelectionIndi>(
                knn,
                ga_baseSetting->baseSetting,
                ga_selection->bitSelection,
                ga_crossover->bitCrossover,
                ga_mutation->bitMutation,
                ga_replacement->bitReplacement,
                ga_stop->bitStopCriteria,
                ga_parallel->parallel
            );
        } else if (ga_baseSetting->baseSetting->getOpMode() == GA_WEIGHTING ) {
            self->selection = nullptr;

            self->weighting = new GAOptimization<WeightingIndi>(
                knn,
                ga_baseSetting->baseSetting,
                ga_selection->realSelection,
                ga_crossover->realCrossover,
                ga_mutation->realMutation,
                ga_replacement->realReplacement,
                ga_stop->realStopCriteria,
                ga_parallel->parallel
            );
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization: unknown mode of operation");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_XINCREF(classifier);
    Py_XINCREF(baseSetting);
    Py_XINCREF(selection);
    Py_XINCREF(crossover);
    Py_XINCREF(mutation);
    Py_XINCREF(replacement);
    Py_XINCREF(stop);
    Py_XINCREF(parallelization);

    return (PyObject*) self;
}

static void GAOptimization_dealloc(PyObject *object) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    try {
        if ( self->selection != nullptr ) {
            KnnObject *knn = self->selection->getKnnObject();
            Py_XDECREF((PyObject*)knn);

            GASelection<SelectionIndi> *selection = self->selection->getSelection();
            Py_XDECREF((PyObject*)selection);

            GACrossover<SelectionIndi> *crossover = self->selection->getCrossover();
            Py_XDECREF((PyObject*)crossover);

            GAMutation<SelectionIndi> *mutation = self->selection->getMutation();
            Py_XDECREF((PyObject*)mutation);

            GAReplacement<SelectionIndi> *replacement = self->selection->getReplacement();
            Py_XDECREF((PyObject*)replacement);

            GAStopCriteria<SelectionIndi> *stop = self->selection->getStopCriteria();
            Py_XDECREF((PyObject*)stop);

            GAParallelization *parallel = self->selection->getParallelization();
            Py_XDECREF((PyObject*)parallel);

            delete self->selection;
        }

        if ( self->weighting != nullptr ) {
            KnnObject *knn = self->weighting->getKnnObject();
            Py_XDECREF((PyObject*)knn);

            GASelection<WeightingIndi> *selection = self->weighting->getSelection();
            Py_XDECREF((PyObject*)selection);

            GACrossover<WeightingIndi> *crossover = self->weighting->getCrossover();
            Py_XDECREF((PyObject*)crossover);

            GAMutation<WeightingIndi> *mutation = self->weighting->getMutation();
            Py_XDECREF((PyObject*)mutation);

            GAReplacement<WeightingIndi> *replacement = self->weighting->getReplacement();
            Py_XDECREF((PyObject*)replacement);

            GAStopCriteria<WeightingIndi> *stop = self->weighting->getStopCriteria();
            Py_XDECREF((PyObject*)stop);

            GAParallelization *parallel = self->weighting->getParallelization();
            Py_XDECREF((PyObject*)parallel);

            delete self->weighting;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return;
    }

    ((PyObject *)self)->ob_type->tp_free(self);
}

static PyObject* startCalculation(PyObject* object, PyObject* args) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    Py_BEGIN_ALLOW_THREADS

    try {
        if ( self->selection != nullptr && self->weighting == nullptr) {
            self->selection->StartCalculation();
        } else if ( self->weighting != nullptr && self->selection == nullptr) {
            self->weighting->StartCalculation();
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization.startCalculation: invalid configuration settings");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyEval_RestoreThread(_save);
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_END_ALLOW_THREADS

    Py_RETURN_NONE;
}

static PyObject* stopCalculation(PyObject* object, PyObject* args) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    try {
        if ( self->selection != nullptr && self->weighting == nullptr) {
            self->selection->StopCalculation();
        } else if ( self->weighting != nullptr && self->selection == nullptr) {
            self->weighting->StopCalculation();
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization.stopCalculation: invalid configuration settings");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* getRunStatus(PyObject* object) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    try {
        if ( self->selection != nullptr && self->weighting == nullptr) {
            if (self->selection->getRunStatus()) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
        } else if ( self->weighting != nullptr && self->selection == nullptr) {
            if (self->weighting->getRunStatus()) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization.getRunStatus: invalid configuration settings");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static PyObject* getGenerationCount(PyObject* object) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    try {
        if ( self->selection != nullptr && self->weighting == nullptr) {
            return Py_BuildValue( "I", self->selection->getGenerationCount());
        } else if ( self->weighting != nullptr && self->selection == nullptr) {
            return Py_BuildValue( "I", self->weighting->getGenerationCount());
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization.getGenerationCount: invalid configuration settings");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static PyObject* getBestFitnessValue(PyObject* object) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    try {
        if ( self->selection != nullptr && self->weighting == nullptr) {
            return Py_BuildValue( "d", self->selection->getBestFitnessValue());
        } else if ( self->weighting != nullptr && self->selection == nullptr) {
            return Py_BuildValue( "d", self->weighting->getBestFitnessValue());
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization.getBestFitnessValue: invalid configuration settings");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static PyObject* getMonitorString(PyObject* object) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    try {
        if ( self->selection != nullptr && self->weighting == nullptr) {
            return Py_BuildValue( "s", self->selection->getMonitorString().c_str());
        } else if ( self->weighting != nullptr && self->selection == nullptr) {
            return Py_BuildValue( "s", self->weighting->getMonitorString().c_str());
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization.getMonitorString: invalid configuration settings");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

static PyObject* getBestIndiString(PyObject* object) {
    GAOptimizationObject *self = (GAOptimizationObject*) object;

    try {
        if ( self->selection != nullptr && self->weighting == nullptr) {
            return Py_BuildValue( "s", self->selection->getBestIndiString().c_str());
        } else if ( self->weighting != nullptr && self->selection == nullptr) {
            return Py_BuildValue( "s", self->weighting->getBestIndiString().c_str());
        } else {
            PyErr_SetString(PyExc_RuntimeError, "GAOptimization.getBestIndiString: invalid configuration settings");
            return nullptr;
        }
    } catch (std::exception &e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        Py_RETURN_NONE;
    }
}

PyMethodDef GAOptimization_methods[] = {
        { (char *) "startCalculation", startCalculation, METH_NOARGS,
                (char *) "**startCalculation** ()\n\n"
                         "Starts the evolutionary optimization progress\n\n"
                         ".. note:: After starting the optimization no changes in the "
                         "used classifier object are allowed until the optimization "
                         "is finished!"
        },
        { (char *) "stopCalculation", stopCalculation, METH_NOARGS,
                (char *) "**stopCalculation** ()\n\n"
                         "Manual stops the evolutionary optimization progress without "
                         "respect to the stoping-criterias.\n\n"
                         ".. note:: This function blocks until the current generation of "
                         "the optimization is finished. As a result it could take a "
                         "long time until this functions returns!"
        },
        { nullptr }
};

PyGetSetDef GAOptimization_getset[] = {
        { (char *) "status", (getter)getRunStatus, nullptr,
                (char *) "flag which indicates whether the optimization is in "
                         "progress (``True``) or not (``False``)", nullptr },
        { (char *) "generation", (getter)getGenerationCount, nullptr,
                (char *) "the number of the latest computed generation", nullptr },
        { (char *) "bestFitness", (getter)getBestFitnessValue, nullptr,
                (char *) "the best fitness value which has occurred in the "
                         "optimization progress so far", nullptr },
        { (char *) "monitorString", (getter)getMonitorString, nullptr,
                (char *) "string which contains some statistical information about "
                         "the optimization process, like number of fitness evaluations, "
                         "average and stdev of fitness values within each generation.", nullptr },
        { (char *) "bestIndiString", (getter)getBestIndiString, nullptr,
                (char *) "string coded version from the best individual of each "
                         "generation", nullptr },
        { nullptr }
};

void init_GAOptimizationType(PyObject *d) {
    #ifdef Py_SET_TYPE
      Py_SET_TYPE(&GAOptimizationType, &PyType_Type);
    #else
      Py_TYPE(&GAOptimizationType) = &PyType_Type;
    #endif
    GAOptimizationType.tp_name =  "gamera.knnga.GAOptimization";
    GAOptimizationType.tp_basicsize = sizeof(GAOptimizationObject);
    GAOptimizationType.tp_dealloc = GAOptimization_dealloc;
    GAOptimizationType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    GAOptimizationType.tp_new = GAOptimization_new;
    GAOptimizationType.tp_getattro = PyObject_GenericGetAttr;
    GAOptimizationType.tp_alloc = nullptr;
    GAOptimizationType.tp_free = nullptr;
    GAOptimizationType.tp_methods = GAOptimization_methods;
    GAOptimizationType.tp_getset = GAOptimization_getset;
    GAOptimizationType.tp_doc =  "**GAOptimization** (*KnnObject* classifier,"
        " *GABaseSetting* base,"
        " *GASelection* selection,"
        " *GACrossover* crossover,"
        " *GAMutation* mutation,"
        " *GAReplacement* replace,"
        " *GAStopCriteria* stop,"
        " *GAParallelization* parallel"
        ")\n\n"
        "The ``GAOptimization`` constructor combines all GA-setting "
        "objects and a kNN-Classifier into one executable genetic algorithm "
        "which allows the optimization.\n\n"
        "*KnnObject* classifier\n"
        "   a trained instance of a gamera kNN-classifier "
        "(no type checking is performed)\n"
        "*GABaseSetting* base\n"
        "   a configured instance of the ``GABaseSetting`` class\n"
        "*GASelection* selection\n"
        "   a configured instance of the ``GASelection`` class\n"
        "*GACrossover* crossover\n"
        "   a configured instance of the ``GACrossover`` class\n"
        "*GAMutation* mutation\n"
        "   a configured instance of the ``GAMutation`` class\n"
        "*GAReplacement* replace\n"
        "   a configured instance of the ``GAReplacement`` class\n"
        "*GAStopCriteria* stop\n"
        "   a configured instance of the ``GAStopCriteria`` class\n"
        "*GAParallelization* parallel\n"
        "   a configured instance of the ``GAParallelization`` class\n\n"
        ".. note:: No type checking is performed for the classifier object!";

    PyType_Ready(&GAOptimizationType);
    PyDict_SetItemString(d, "GAOptimization", (PyObject*)&GAOptimizationType);
}

//******************************************************************************
// interface for python module
//******************************************************************************


PyMethodDef knnga_module_methods[] = {
    { nullptr }
};

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "gamera.knnga",
        nullptr,
        -1,
        knnga_module_methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr
};


PyMODINIT_FUNC PyInit_knnga(void) {
    PyObject *m = PyModule_Create(&moduledef);
    PyObject *d = PyModule_GetDict(m);

    init_GASelectionType(d);
    init_GACrossoverType(d);
    init_GAMutationType(d);
    init_GAReplacementType(d);
    init_GAStopCriteriaType(d);
    init_GAParallelizationType(d);
    init_GAOptimizationType(d);
    init_GABaseSettingType(d);

    // enum constants
    PyDict_SetItemString(d, "GA_SELECTION",
        Py_BuildValue( "i", GA_SELECTION));
    PyDict_SetItemString(d, "GA_WEIGHTING",
        Py_BuildValue( "i", GA_WEIGHTING));

    return m;
}
