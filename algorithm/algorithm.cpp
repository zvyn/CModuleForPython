// Copyright (2013) Milan Oberkirch <milan@oberkirch.org>.

#include <Python.h>
#include <algorithm>
#include "PythonSequenceIterator.cpp"

/* Performs a binary_search on a PySequence. Takes two arguments: the sequence
 * and the value to search for. Returns True if value is in the sequence and
 * False otherwise. Note that PyObjects (not C++-booleans) are returned. */
static PyObject * algorithm_binary_search(PyObject *self, PyObject *args) {
    PyObject *list = NULL;
    PyObject *value = NULL;
    if (PyArg_ParseTuple(args, "OO", &list, &value) && PySequence_Check(list)) {
        assert(PySequence_Size(list));
        PythonSequenceIterator first(list, 0);
        PythonSequenceIterator last(list, PySequence_Size(list));
        bool exists = std::binary_search(first, last, value);
        if (exists)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    } else {
        return NULL;
    }
}

// Method description for algorithm_binary_search.
static PyMethodDef AlgorithmMethods[] = {
    {"binary_search",  algorithm_binary_search, METH_VARARGS,
        "Perform a binary_search using the C++-implementation from stl."},
    {NULL, NULL, 0, NULL}
};

// Module description for the module containing algorithm_binary_search.
static struct PyModuleDef algorithmmodule = {
    PyModuleDef_HEAD_INIT,
    "algorithm",
    "Provides binary_search known from C++ stl/<algorithm>.",
    -1,
    AlgorithmMethods
};

// Provide the __init__-function for the module.
PyMODINIT_FUNC PyInit_algorithm(void) {
    return PyModule_Create(&algorithmmodule);
}

// Do the magic! Brew a bright and shining python-module from the definitions
// above (*_*).
int main(int argc, char *argv[]) {
    wchar_t * wargv = NULL;
    mbstowcs(wargv, argv[0], 100);
    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab("algorithm", PyInit_algorithm);

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(wargv);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyImport_ImportModule("algorithm");
}
