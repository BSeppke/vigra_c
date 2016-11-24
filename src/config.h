#ifndef VIGRA_C_CONFIG_H
#define VIGRA_C_CONFIG_H


//Library export settings for the mainly used OSes
#ifdef _WIN32
  #define LIBEXPORT extern "C" __declspec(dllexport)
#else
  #define LIBEXPORT extern "C"
#endif

#include <vigra/multi_array.hxx>

//Pixel and Image Types
//Please note, that all vigra_c accessing libs:
//  - work on single band images (unless otherwise mentioned)
//  - need float as pixel type!
typedef float PixelType;
typedef vigra::MultiArrayView<2, PixelType, vigra::UnstridedArrayTag> ImageView;

#endif
