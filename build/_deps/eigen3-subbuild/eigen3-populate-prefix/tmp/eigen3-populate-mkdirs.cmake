# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-src"
  "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-build"
  "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-subbuild/eigen3-populate-prefix"
  "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-subbuild/eigen3-populate-prefix/tmp"
  "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-subbuild/eigen3-populate-prefix/src/eigen3-populate-stamp"
  "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-subbuild/eigen3-populate-prefix/src"
  "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-subbuild/eigen3-populate-prefix/src/eigen3-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-subbuild/eigen3-populate-prefix/src/eigen3-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/LENOVO/Documents/GitHub/EC-DE/build/_deps/eigen3-subbuild/eigen3-populate-prefix/src/eigen3-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
