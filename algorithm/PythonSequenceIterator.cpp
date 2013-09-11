// Copyright (2013) Milan Oberkirch <milan@oberkirch.org>

#ifndef PYTHON_SEQUENCE_ITERATOR_CPP
#define PYTHON_SEQUENCE_IPERATOR_CPP

#include <Python.h>
#include <algorithm>
#include <iterator>

// Provides an iterator for python-objects, compatible to the std::iterator.
class PythonSequenceIterator
  : public std::iterator<std::input_iterator_tag, int>  {

  PyObject* m_sequence;
  Py_ssize_t m_position;

  public:
  typedef PyObject* value_type;

  PythonSequenceIterator(PyObject* sequence, Py_ssize_t position):
    m_sequence(sequence), m_position(position) {
    assert(PySequence_Check(m_sequence));
    assert(m_position >= 0);
    assert(m_position <= PySequence_Size(m_sequence));
  }

  value_type operator*() const {
    assert(m_position < PySequence_Size(m_sequence));
    return PySequence_GetItem(m_sequence, m_position);
  }

  PythonSequenceIterator& operator++() {
    assert(m_position <= PySequence_Size(m_sequence));
    ++m_position;
    return *this;
  }

  PythonSequenceIterator& operator+=(size_t x) {
    m_position += x;
    return *this;
  }

  Py_ssize_t getPosition() const { return m_position; }
  bool operator!=(const PythonSequenceIterator& other) {
    return m_position != other.getPosition();
  }

  bool operator==(const PythonSequenceIterator& other) {
    return m_position == other.getPosition();
  }
};
#endif  // PYTHON_SEQUENCE_ITERATOR_CPP
