# jimgload

jimgload is a fairly simple library for loading images (currently PNG or JPEG) into Java ByteBuffers.

# Dependencies

* libpng 1.2 or 1.6
* libjpeg-turbo 1.3
* JNI
* Python 2.7 (compile-time only)

# Building

IF YOU ARE USING ARCH LINUX: Arch does not have a critical symlink in the same directory as `jni.h`
(in `/usr/lib/jvm/java-7-openjdk/include` on my system).  Basically, `jni.h` references `jni_md.h`,
but it does so with quotes instead of angle brackets, and `jni_md.h` is in `include/linux`, which
probably isn't in your include path anyway.  So, you need a symlink to `jni_md.h` in the same
directory as `jni.h`.

Run `./configure.py --jdk=/path/to/java_home`.  This will set up `jni/GNUmakefile` correctly.
Run `./configure.py --help` for the full set of options.

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

If you want to install with `ant install`, use `-Djar.install.dir=$whatever`.  This option is
probably most useful for distribution packagers.

To deploy to a local Maven repository (useful for Clojure development), use `ant -Dremote.repo=$whatever deploy`.
If you do this, you will need to copy `libjimgload.so` yourself.

Any improvements to the build system are VERY welcome.  I'd like the whole thing to be very simple for the user.

# Portability

I want this to work on Linux, Windows, and OS X.  However, it currently only works on Linux.
To fix this, additional cleverness will be needed in [jni/GNUmakefile](jni/GNUmakefile).  A separate makefile
for Windows may also be necessary.  Or, perhaps using CMake would be a better idea.  I'm not sure.

# License

jimgload is under the LGPLv3+ license.

libpng and libjpeg-turbo are under permissive licenses.
