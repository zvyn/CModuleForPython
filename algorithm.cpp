#include <Python.h>
#include <algorithm>
#include <iterator>

class PySequenceIterator : public std::iterator<std::input_iterator_tag, int>  {
  PyObject* m_sequence;
  Py_ssize_t m_position;

  public:
  typedef PyObject* value_type;
  PySequenceIterator(PyObject* sequence, Py_ssize_t position):
    m_sequence(sequence), m_position(position)
  {
    assert(PySequence_Check(m_sequence));
    assert(m_position >= 0);
    assert(m_position <= PySequence_Size(m_sequence));
  }

  value_type operator*() const {
    assert(m_position < PySequence_Size(m_sequence));
    return PySequence_GetItem(m_sequence, m_position);
  }

  PySequenceIterator& operator++() {
    assert(m_position <= PySequence_Size(m_sequence));
    ++m_position;
    return *this;
  }

  PySequenceIterator& operator+=(size_t x) {
    m_position += x;
    return *this;
  }

  Py_ssize_t getPosition() const { return m_position; }
  bool operator!=(const PySequenceIterator& other) {return m_position != other.getPosition();}
  bool operator==(const PySequenceIterator& other) {return m_position == other.getPosition();}
};

static PyObject * algorithm_binary_search(PyObject *self, PyObject *args) {
  PyObject *list = NULL;
  PyObject *value = NULL;
  if (PyArg_ParseTuple(args, "OO", &list, &value) and PySequence_Check(list)) {
    assert(PySequence_Size(list));
    PySequenceIterator first(list, 0);
    PySequenceIterator last(list, PySequence_Size(list));
    unsigned const char exists = std::binary_search(first, last, value);
    return Py_BuildValue("b", exists);
  } else {
    return NULL;
  }
}

static PyMethodDef AlgorithmMethods[] = {
    {"binary_search",  algorithm_binary_search, METH_VARARGS,
     "Perform a binary_search using the C++-implementation from stl."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef algorithmmodule = {
   PyModuleDef_HEAD_INIT,
   "algorithm",   /* name of module */
   "Provides functions (currently only binary_search) known from C++ stl/<algorithm>.", /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   AlgorithmMethods
};

PyMODINIT_FUNC PyInit_algorithm(void)
{
    return PyModule_Create(&algorithmmodule);
}

int
main(int argc, char *argv[])
{
  wchar_t * wargv;
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
