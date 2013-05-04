Extending Python with C or C++
==============================

This is an implementation of the HowTo at http://docs.python.org/3.3/extending/extending.html.

What it does
------------

This is a small example of a module for python which is written in C. The method(s) and description of the module is written in 'spammodule.c'.
The 'setup.py' file is used to compile the module.

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
