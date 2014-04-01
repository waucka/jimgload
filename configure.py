#!/usr/bin/env python2

import os.path as path

LIBDIR='/usr/lib'

libpng = 'png'

if path.exists(path.join(LIBDIR, 'libpng16.so')):
	libpng = 'png16'
elif path.exists(path.join(LIBDIR, 'libpng12.so')):
	libpng = 'png12'

with open('jni/GNUmakefile.in', 'rb') as infile:
	intext = infile.read()

with open('jni/GNUmakefile', 'wb') as outfile:
	outfile.write(intext.format(libpng=libpng))
