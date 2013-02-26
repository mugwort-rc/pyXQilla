import os, sys

from distutils.core import setup
from distutils.command import build_ext

from distutils.core import Extension

include_dirs = ['/usr/local/include']
libraries = ['xqilla', 'boost_python', 'stdc++']
library_dirs = ['/usr/local/lib']
sources = []
for (root, dirs, files) in os.walk('src'):
    for name in files:
        if name[-4:] == '.cpp':
            sources.append('%s/%s'%(root,name))

xqilla = Extension(name = 'XQilla.__XQilla',
                   include_dirs = include_dirs,
                   libraries = libraries,
                   library_dirs = library_dirs,
                   sources = sources,
                   extra_compile_args = ['-std=c++0x'])

# distutils c++ bug fix.
from distutils.sysconfig import get_config_vars
(opt,) = get_config_vars('OPT')
os.environ['OPT'] = " ".join([flag for flag in opt.split() if flag != '-Wstrict-prototypes'])

setup(name = 'PyXQilla',
      version = '0.0.1',
      description = 'pyXQilla: A Python XQilla wrapper',
      author = 'mugwort_rc',
      author_email = 'mugwort rc at gmail com',
      url = 'https://github.com/mugwort_rc/pyxqilla',
      license = 'Apache Software License, Version 2.0',
      requires = ['Xerces'],
      packages = ['XQilla'],

      ext_modules = [xqilla])

