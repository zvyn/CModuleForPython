PythonSequenceIterator.cpp
--------------------------

Iteraters are the favourite-food for most search-related functions in the
C++-Standart-Library. This file provides an iterator-class for Python-Sequences
(e.g. lists). I do not write the .h file from hand, so it's not included in
the repo. There are tools to do the 'copy the declarations and replace
code-blocks by semicolon' automatically :)

algorithm.cpp
-------------

This is a proof-of-concept for using functions from the C++-STL on PyObjects
(Currently only std::binary_search).

Installation and usage
----------------------
```bash
python setup.py build
cd build/lib.*
python
>>> import algorithm
>>> if algorithm.binary_search([1,2,3],2):
...     print("2 is in the list!")
2 is in the list!
>>>
```
Note that the function returns a 0 (False) or 1 (True), but not a python-boolean.
