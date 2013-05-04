Extending Python with C or C++
==============================

spammodule.cpp
--------------

This is an implementation of the HowTo at http://docs.python.org/3.3/extending/extending.html,
a small example of a module for python which is written in C.
The method(s) and description of the module is written in 'spammodule.cpp'.
The 'setup.py' file is used to compile the module (currently it will build algoritm.cpp, but the changes are trivial).

algorithm.cpp
-------------

This is a proof-of-concept for using a function from the C++-STL on PyObjects. You can find a iterator-class for
a PySequence as well as a wrapper for std::binary_search in there (see below for a short usage).

I got the idea to write a own iterator-class from doomster at http://stackoverflow.com/a/16375061/2349767.

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
