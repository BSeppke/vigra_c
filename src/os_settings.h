#ifdef VIGRA_C_BUILD
    #ifdef _WIN32
        #define LIBEXPORT  extern "C" __declspec(dllexport)
    #else
        #define LIBEXPORT  extern "C"
    #endif
#else
    #ifdef _WIN32
        #define LIBEXPORT __declspec(dllimport)
    #else
        #define LIBEXPORT
    #endif
#endif