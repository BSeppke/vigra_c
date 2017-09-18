# vigra_c

An easy understandable C-Wrapper to re-use functionality of the VIGRA computer vision library in other programming environments.


## Introduction

VIGRA stands for "Vision with Generic Algorithms". It's a novel computer vision library that puts its main emphasize on customizable algorithms and data structures. By using template techniques similar to those in the C++ Standard Template Library, you can easily adapt any VIGRA component to the needs of your application, without thereby giving up execution speed. VIGRA was originally designed and implemented by Ullrich Köthe. To get more information, visit the [VIGRA Homepage](http://ukoethe.github.io/vigra/)!
As already mentioned, the VIGRA is a pure, template driven C++ library. This may be the language of choice in many cases, e.g. if you need very fast algorithms that can be written using the concrete object-oriented paradigma and the wonderful templates c++ offers.

On the other hand, there are enough reasons not to use C++, e.g. that it is not an interactive language because of the necessary code-compile-cycles and it is very hard to use C++ when you want to use another programming paradigma as the functional paradigma (of e.g. Lisp & Scheme) Additionally, C++ is still quite a low-level language and therefore may not be the language you want to use for high-level task where Common Lisp would be preferable. For Python, the VIGRA already provides a high-level interface by means of [vigranumpy](https://ukoethe.github.io/vigra/doc-release/vigranumpy/index.html).

As a summary, we can say that just the first point alone (the missing interactivity) is strong enough to motivate the use of the image processing algorithms that VIGRA offers. For the same reason, Python became that popular, and there is also some work going on a specialized python interface beside the interfaces described here.

## General Structure

The easiest way to integrate C/C++ code written in other programming languages is a generic C-interface to a C-dynamic library at runtime. That is why we also use this interface for all libraries presented herein. This interface allows us to load C-conform "shared libraries" (for Windows: DLLs, for Mac OS X: dylibs and under Linux: so) at any time interactively and to call the included functions directly.

Unfortunately, the VIGRA only offers a C++ dynamic library for the import- and export-facilities of pictures. Because of this. the first step is to abstract from the C++ image processing functions of the VIGRA to a C-dynamic-library-wrapper, vigra\_c, containing everything we want to call from the other languages. This dynamic library is the "glue component" between the VIGRA on the on side and the other languages on the other side, that will hide the low level C-calls and translate the functions into readable names.

The abstraction from VIGRA's templated C++ MultiArray image representation w.r.t. this module is as follows:

* Unless otherwise mentioned, all exported functions work band-wise, and may be called more than once, e.g. three times for and R,G,B-image.
* The image's pixel format is set/fixed to float (32bit).
* 2D image arrays need to be pre-allocated by the caller by means of an aligned and flattened 1D-memory block of size width*height and type float for each image band.
* Instead of a compound type, simply pass pointers of allocated memory blocks for input and output of correct size plus the corresponding width and height and additional parameters to the function.


## Installation

Currently, other modules, which use vigra\_c to bind [Racket](https://racket-lang.org), [MatLAB](https://www.mathworks.com/) etc. ship the vigra\_c by means of a submodule. They use the corresponding build-scripts (build-32.sh for 32bit, build-64.sh for 64bit builds) to build a vigra\_c binary.

However, since CMake is used to build the vigra\_c library, it is also possible to install the vigra\_c lib system-wide for Linux-like systems using:

    git clone https://github.com/bseppke/vigra_c
    cd vigra_c
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=/wherever/you/want/ ..
    make
    make install


This however, does neither help nor is it necessary for the language wrappers, since they rely on a dynamically loadable libary in their installation path.

Please note that the vigra\_c library relies on the installation of cmake, vigra and fftw on your system (and their dependencies). For Linux, use a package manager of choice, for Mac OS I prefer MacPorts. For Windows, binaries (created with Visual Studio 2015 and [vspkg](https://github.com/bseppke/vspkg) are shipped with the sources for 32 and 64bit.
To build the documentation documentation install doxygen and use:

    make doc


## Quick Start
To write another wrapper for a new programming languages, get inspiration from the already existing wrappers to:

* Racket ([vigracket](https://github.com/bseppke/vigracket))
* Common Lisp ([vigracl](https://github.com/bseppke/vigracl))
* exelvis IDL ([vigraidl](https://github.com/bseppke/vigraidl))
* MatLAB ([vigramatlab](https://github.com/bseppke/vigramatlab))
* Java ([vigraj](https://github.com/bseppke/vigraj))
* Guile ([guile-cv](https://www.gnu.org/software/guile-cv/)), by David Pirotte

All you need to make sure, is that the other programming language is able to load foreign (C-) functions and to allocate memory for the images.

## License

vigra\_c is published under the MIT License. See the [License file](https://github.com/bseppke/vigra_c/blob/master/LICENSE) for further information.
