#!/usr/bin/env python2

import os.path as path
import argparse

parser = argparse.ArgumentParser(description='Configure jimgload for building')
parser.add_argument('--prefix', help='set prefix for installation', default='/usr')
parser.add_argument('--libdir', help='set directory for installation of libraries')
parser.add_argument('--includedir', help='set directory for installation of headers')
parser.add_argument('--jdk', help='set directory for JDK (i.e. $JAVA_HOME)', required=True)
#parser.add_argument('--with-libpng', help='specify a specific version of libpng')
parser.add_argument('--dep-libdir', help='set directory to search for dependency libraries')
parser.add_argument('--dep-includedir', help='set directory to search for dependency headers')

args = parser.parse_args()

LIBDIR = args.libdir
if not LIBDIR:
  LIBDIR = path.join(args.prefix, 'lib')

INCLUDEDIR = args.includedir
if not INCLUDEDIR:
  INCLUDEDIR = path.join(args.prefix, 'include')

DEP_LIBDIR = args.dep_libdir
if not DEP_LIBDIR:
  DEP_LIBDIR = path.join(args.prefix, 'lib')

DEP_INCLUDEDIR = args.dep_includedir
if not DEP_INCLUDEDIR:
  DEP_INCLUDEDIR = path.join(args.prefix, 'include')

libpng = 'png12'

libpng_includedir = DEP_INCLUDEDIR

if path.exists(path.join(DEP_LIBDIR, 'libpng16.so')):
  libpng = 'png16'
elif path.exists(path.join(DEP_LIBDIR, 'libpng12.so')):
  libpng = 'png12'
  libpng12_subdir = path.join(DEP_INCLUDEDIR, 'libpng12')
  if path.exists(libpng12_subdir):
    libpng_includedir = libpng12_subdir

with open('jni/GNUmakefile.in', 'rb') as infile:
  intext = infile.read()

with open('jni/GNUmakefile', 'wb') as outfile:
  outfile.write(intext.format(libpng=libpng,
                              includedir=INCLUDEDIR,
                              libdir=LIBDIR,
                              dep_includedir=DEP_INCLUDEDIR,
                              dep_libdir=DEP_LIBDIR,
                              libpng_includedir=libpng_includedir,
                              jdk=args.jdk))
