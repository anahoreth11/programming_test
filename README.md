# Backend Programming Test Solution

My solution of Backend Programming Test. The solution is written on Windows, and although for the most part the code is cross-platform, there is a probability of the errors on other platforms.

## Structure

There are three parts of the solution:

1. cpp code, which gets input data, analyzes it and saves results (folder "cpp/src").
2. tests for the cpp code (folder "cpp/tests").
3. Jupyter notebook python/Example.ipynb, which is an entry point to the solution. 


## Cpp Source Code

In the main.cpp file cpp-code input data, analyzes it and saves results. For building sources to exe-file CMake is used (see python/Example.ipynb for the details).

## Cpp Tests

In folder "cpp/tests" there is a test project for cpp source code. This project uses Visual Studio test framework. It could be possible to check tests by opening the "UnitTests.vcxproj" file and push the "Run Tests" button.

## Jupyter notebook

It could be possible to check and use the solution by using the python/Example.ipynb notebook. There are details of its usage in the file
