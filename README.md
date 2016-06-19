# papuc_exercises
Programming: Principles and Practice Using C++ - Exercises

User prefix will be written as <user-prefix>. User prefix
can be one of "lm", "ib", "mb".

## Build instructions

In the root directory of the project do the following:

1. create build directory and enter it
``` bash
mkdir build; cd build
```

2. run cmake and point it ot the root dir
``` bash
cmake ..
```

3. run make (point it to the desired target binary) e.g.
``` bash
make ch04-<user-prefix>
```

4. The resulting binary is at <project-root>/build/ch04/lm/ch04-lm

## Adding own code to the build system:

1. Move your files to your user directory (<project-root>/ch04/<user-prefix>)

2. Edit the CMakeLists.txt file in your user directory.
  * In "add_executable" command, replace empty.cpp with the name of
  your source file.
  * You can add more source files to the add_executable command - it takes in
   a space separated list of files of any length.
3. Follow the build instructions to let the cmake magic happen.
