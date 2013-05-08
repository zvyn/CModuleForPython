from distutils.core import setup, Extension

module1 = Extension('algorithm',
                    sources = ['algorithm.cpp'])

setup (name = 'algorithm',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
