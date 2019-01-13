cmake_minimum_required(VERSION 3.1)

project(vigra_c)

#find . -type f -name \*.cxx | sed 's,^\./,,'
set(SOURCES 
	vigra_convert_c.cxx
	vigra_filters_c.cxx
	vigra_tensors_c.cxx
	vigra_imgproc_c.cxx
	vigra_impex_c.cxx
	vigra_morphology_c.cxx
	vigra_segmentation_c.cxx
	vigra_splineimageview_c.cxx)

#find . -type f -name \*.h | sed 's,^\./,,'
set(HEADERS 
	config.h
	vigra_c.h
	vigra_kernelutils_c.h
	vigra_convert_c.h
	vigra_filters_c.h
	vigra_tensors_c.h
	vigra_imgproc_c.h
	vigra_impex_c.h
	vigra_morphology_c.h
	vigra_segmentation_c.h
	vigra_splineimageview_c.h)

# Tell CMake to create the library
add_library(vigra_c SHARED ${SOURCES} ${HEADERS})
target_link_libraries(vigra_c vigraimpex ${FFTW_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})

# Add install target
install(TARGETS vigra_c DESTINATION lib)
