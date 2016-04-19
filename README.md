Binary Search Tree Implementation
=================================

## Building instructions

To build run the command `make`, this will build the tool in release mode.

The available targets are the following:
* `default`
    * Default target, runs the `release` target
* `prepare`
    * Creates the directory `obj/` and creates the .obj files from the source files in the new directory.
* `debug`
    * Compiles without obj files (for debugging reasons)
    * Creates the directory `out/` and compiles **BSTtest** with `binary_tree.cpp` and `my_test.obj` to the newly created dir and sets `DEBUG`.
* `release`
    * Runs the `clean` and `prepare` targets
      * Compiles **BSTtest** with `binary_tree.obj` and `test.cpp` to the newly created dir and sets `RELEASE`.
* `clean`
    * Deletes `out/` and `obj/` and with it all the previously compiled filed.
* `tests`
    * Runs the targets `prepare`, `release` and then runs the program without/BSTtest

The makefile is prepared for building with g++, if you don't have g++ installed, either change the appropriate values in the makefile to compile with your preferred compiler or install g++.


**This project was developed as a coursework for the Programming Fundamentals Module**

**Edinburgh Napier University @ 2016**

**Antero Duarte - Beng Computing**