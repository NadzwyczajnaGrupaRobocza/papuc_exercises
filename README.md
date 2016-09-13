# papuc_exercises
Programming: Principles and Practice Using C++ - Exercises

User prefix will be written as \<user-prefix\>. User prefix
can be one of "lm", "ib", "mb".

## Update your fork with changes from the common repository

In the root directory of the project:

1. add common repository as a git remote:
    ``` bash
    git remote add upstream https://github.com/NadzwyczajnaGrupaRobocza/papuc_exercises.git
    ```

2. pull common repository changes to local cache
    ``` bash
    git fetch upstream
    ```

3. make sure you're at your main brach
    ``` bash
    git checkout master
    ```

4. merge upstream changes to your checkout
    ``` bash
    git pull --rebase upstream master
    ```

*Only step 4 is needed to later repeat the procedure*


## Initialize gtest submodule

In the root directory of the project:

1. Make git aware of the fact we have submodule
    ``` bash
    git submodule init
    ```

2. Actually pull the submodules
    ``` bash
    git submodule update
    ```

You're now ready to compile stuff.

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

4. The resulting binary is at \<project-root\>/build/ch04/lm/ch04-\<user-prefix\>

## Adding own code to the build system:

1. Move your files to your user directory (\<project-root\>/ch04/\<user-prefix\>)

2. Edit the CMakeLists.txt file in your user directory.
    * In "add_executable" command, replace empty.cpp with the name of
      your source file.
    * You can add more source files to the add_executable command - it takes in
      a space separated list of files of any length.
3. Follow the build instructions to let the cmake magic happen.
