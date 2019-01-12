cmake_minimum_required(VERSION 3.1)

project(vigra_c)

set(CMAKE_CXX_STANDARD 11)

set(VIGRA_C_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#build windows binaries directly in the correct folder
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		# 64 bits
		set(VIGRA_C_BIN_DIR ${VIGRA_C_BIN_DIR}/win64)
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
		# 32 bits
		set(VIGRA_C_BIN_DIR ${VIGRA_C_BIN_DIR}/win32)
	endif()
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${VIGRA_C_BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VIGRA_C_BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${VIGRA_C_BIN_DIR})

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
	string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${VIGRA_C_BIN_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${VIGRA_C_BIN_DIR})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${VIGRA_C_BIN_DIR})
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPE)

set(CMAKE_MACOSX_RPATH FALSE)

# Find VIGRA
find_package(Vigra)
if(Vigra_FOUND)
  include_directories(${Vigra_INCLUDE_DIRS})
endif()

# Find the FFTW lib
find_library(FFTW_LIBRARY
   NAMES fftw-3.3 fftw3 fftw)
set(FFTW_LIBRARIES "${FFTW_LIBRARY}")
if(UNIX AND NOT WIN32)
   find_library(FFTW_libm_LIBRARY
     NAMES m)
   list(APPEND FFTW_LIBRARIES "${FFTW_libm_LIBRARY}")
endif()

# Find the FFTWF lib
find_library(FFTWF_LIBRARY
   NAMES fftw-3.3f fftw3f fftwf-3.3 fftwf3 fftwf)
list(APPEND FFTW_LIBRARIES "${FFTWF_LIBRARY}")

find_package(HDF5)
if(HDF5_FOUND)
   add_definitions("-DHAS_HDF5")
endif()

add_subdirectory(src)
add_subdirectory(doc)
