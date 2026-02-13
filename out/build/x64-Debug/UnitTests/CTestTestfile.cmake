# CMake generated Testfile for 
# Source directory: C:/Users/jonas/source/repos/COME/UnitTests
# Build directory: C:/Users/jonas/source/repos/COME/out/build/x64-Debug/UnitTests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[UnitTests]=] "C:/Users/jonas/source/repos/COME/out/build/x64-Debug/UnitTests/UnitTests.exe")
set_tests_properties([=[UnitTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/jonas/source/repos/COME/UnitTests/CMakeLists.txt;9;add_test;C:/Users/jonas/source/repos/COME/UnitTests/CMakeLists.txt;0;")
subdirs("LinearAlgebra")
subdirs("LinearSolvers")
subdirs("FEM")
