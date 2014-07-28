


#
#	Building
#

1. Windows

1.1 Run cmake (At the moment only vc11 is supported by the vendor branch.)
1.2(optional) For debugging set the working directory to the directory of the output file.

2. Linux

Not supported yet

3. OS X

Not supported Yet

4. Android

For ADT integration do the following steps.

4.1  Start cmake. 
4.2  Configure.
4.3  Generator ninja or make. The former is recommended because it's cross-platform.
4.4  Specify custom toolchain file. Select android-null-toolchain.cmake.
4.5  Configure. Set the NDK location. Configure again. 
4.6  Generate.
4.7  Start ADT
4.8  Import existing Android code
4.9  Enable native code support
4.10.1	First change the Current Builder under Project Properties -> C/C++ Build -> Tool Chain Editor to Gnu Make Builder
4.10.2	Then change Project Properties -> C/C++ Build change the build command to ninja(or make).
4.11 Build the project.
