cmake_minimum_required(VERSION 2.8.11)

project(vigra_c)

#find . -type f -name \*.cxx | sed 's,^\./,,'
set(SOURCES 
	vigra_convert_c.cxx
	vigra_filters_c.cxx
	vigra_imgproc_c.cxx
	vigra_impex_c.cxx
	vigra_morphology_c.cxx
	vigra_segmentation_c.cxx
	vigra_splineimageview_c.cxx)

#find . -type f -name \*.h | sed 's,^\./,,'
set(HEADERS  
	os_settings.h
	vigra_c.h
	vigra_convert_c.h
	vigra_filters_c.h
	vigra_imgproc_c.h
	vigra_impex_c.h
	vigra_morphology_c.h
	vigra_segmentation_c.h
	vigra_splineimageview_c.h)

# Tell CMake to create the library
add_library(vigra_c SHARED ${SOURCES} ${HEADERS})
target_link_libraries(vigra_c vigraimpex ${FFTW_LIBRARIES})