# jimgload

jimgload is a fairly simple library for loading images (currently PNG or JPEG) into Java ByteBuffers.

# Dependencies

* libpng 1.2
* libjpeg-turbo 1.3
* JNI

# Building

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

# License

jimgload is under the LGPLv3+ license.

libpng and libjpeg-turbo are under permissive licenses.
