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
>>> import spam
>>> spam.system("echo test")
test
0
>>>
```
