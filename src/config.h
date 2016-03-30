#ifndef VIGRA_C_CONFIG_H
#define VIGRA_C_CONFIG_H


// Library settings
#ifdef _WIN32
    #define LIBEXPORT  extern "C" __declspec(dllexport)
#else
    #define LIBEXPORT  extern "C"
#endif


// Pixel and Image Types
// Please note, that all vigra_c accessing libs need float as pixel type!
#include <vigra/multi_array.hxx>

typedef float PixelType;
typedef vigra::MultiArray<2, PixelType> ImageView;

#endif
