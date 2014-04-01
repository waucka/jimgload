# jimgload

jimgload is a fairly simple library for loading images (currently PNG or JPEG) into Java ByteBuffers.

# Dependencies

* libpng 1.2 or 1.6
* libjpeg-turbo 1.3
* JNI
* Python 2 (compile-time only)

# Building

IF YOU ARE USING ARCH LINUX: Arch does not have a critical symlink in the same directory as `jni.h`
(in `/usr/lib/jvm/java-7-openjdk/include` on my system).  Basically, `jni.h` references `jni_md.h`,
but it does so with quotes instead of angle brackets, and the directory `jni_md.h` is in (`include/linux`)
probably isn't in your include path anyway.  So, you need a symlink to `jni_md.h` in the same
directory as `jni.h`.

Before you do anything else, you need to set `$JAVA_HOME`.  On a Debian/Ubuntu-type system, this
is typically `/usr/lib/jvm/default-java`.  `$JAVA_HOME/include` is where the build system expects
to find `jni.h`.

Run `./configure.py`.  This will set up `jni/GNUmakefile` correctly.

Run `ant -p` to see the list of targets.  Currently, these are:

* `clean`: removes compiled files
* `compile`: compiles all Java and C code
* `compile-java`: compiles all Java code
* `native-compile`: compiles all C code
* `compile-test`: compiles test code
* `deploy`: deploys to a repository (specify repo with `-Dremote.repo=$url`)
* `jar`: creates a jar file
* `test`: runs the test code

Dependencies between these targets should be set up so that all necessary steps
are performed first (e.g. `jar` gets run before `deploy`).

All compiled files end up in `build/`.  Java class files are in `build/classes`,
the jar file is in `build/jar`, the native library is in `build/native`, and the
compiled test code is in `build/test`.

When running, `libjimgload.so` needs to be on `java.library.path`.  The most straightforward
way to do this is to run with `-Djava.library.path=$whatever`.

# Portability

I want this to work on Linux, Windows, and OS X.  However, it currently only works on Linux.
To fix this, additional cleverness will be needed in [jni/GNUmakefile](jni/GNUmakefile).  A separate makefile
for Windows may also be necessary.  Or, perhaps using CMake would be a better idea.  I'm not sure.

# License

jimgload is under the LGPLv3+ license.

libpng and libjpeg-turbo are under permissive licenses.
