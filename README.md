Environment setup instruction for ACCU2017 "The Art of Writing Reasonable Concurrent Code"


Please clone this repository.

Linux
=====
The following assumes a Debian based Linux (I hope the other distributions work similarly)
* Have cmake installed, e.g. sudo apt-get install cmake
* Have gcc 6 or later installed, e.g. sudo apt-get install gcc-6 (the latest clang compiler currently does not work together with the nana library)
* Have the libraries libx11-dev and libxft-dev installed, e.g. sudo apt-get install libx11-dev libxft-dev 
* Have boost version 1.60.0 or later installed (http://boost.org) It is not necessary to compile any libraries, because only headers are needed
* Further it is assumed that the repository was cloned into ~/accu2017setup
* Create a build folder "mkdir accu2017setup_build"
* Change into the folder "cd accu2017setup_build"
* Create the makefiles with "cmake -D CMAKE_C_COMPILER=gcc-6 -D CMAKE_CXX_COMPILER=g++-6 ../accu2017setup"
* Run make
* Run both ./SetupNanaTest/SetupNanaTest and ./SetupStlabTest/SetupStlabTest. The first should display a small window and the second should output 42.


MacOS
=====
Ismail Pazarbasi was so kind to get the environment running with clang. If you want to go his direction, please follow: https://github.com/ipazarbasi/accu2017setup.

Or follow the steps below:
* Have homebrew installed (https://brew.sh/)
* Have cmake installed (http://cmake)
* Have gcc6 installed, e.g. "brew install gcc-6" (clang and mac's own compiler currently do not work together with the nana library)
* Have the freetype library installed, e.g. "brew install freetype"
* Have xQuarz installed (https://www.xquartz.org/)
* Have boost version 1.60.0 or later installed (http://boost.org) It is not necessary to compile any libraries, because only headers are needed
* Further it is assumed that the repository was cloned into ~/accu2017setup
* Create a build folder "mkdir accu2017setup_build"
* Change into the folder "cd accu2017setup_build"
* Create the makefiles with "cmake -D CMAKE_C_COMPILER=gcc-6 -D CMAKE_CXX_COMPILER=g++-6 ../accu2017setup"
* Run make
* Run both ./SetupNanaTest/SetupNanaTest and ./SetupStlabTest/SetupStlabTest. The first should display a small window and the second should output 42.


Windows
=======
* Have Visual Studio 2015 Update 3 or Visual Studio 2017 installed (previous versions will not work, because of lack of C++14 features)
* Have a recent cmake installed (http://cmake.org) (VS 2017 requires the very latest version)
* Have the boost 1.60.0 or newer library installed (http://boost.org) It is not necessary to compile any libraries, because only headers are needed
* Further it is assumed that the repository was cloned into d:\accu2017setup and boost was installed into d:\boost
* Open a "VS 2015 x64 Native Tools Command Prompt"
* Change to D:\
* Create a build folder "md accu2017setup_build"
* Change into the folder "cd accu2017setup_build"
* Create the Visual Studio Solution with "cmake -G "Visual Studio 14 2015 Win64" -DBOOST_ROOT=d:\boost d:\accu2017setup" for VS 2015 or "cmake -G "Visual Studio 15 Win64" -DBOOST_ROOT=d:\boost d:\accu2017setup" for VS 2017
* Open the created solution "devenv accu2017setup.sln" and build all
* Run both SetupNanaTest and SetupStlabTest. The first should display a small window and the second should output 42.

