MACOSX_CXXFLAGS_32 = -I/src `vigra-config --cppflags` -arch i386 -O3
MACOSX_LDFLAGS_32  = `vigra-config --libs` `vigra-config --fftw-lib` -arch i386 -bundle -undefined dynamic_lookup

MACOSX_CXXFLAGS_64 = -I/src `vigra-config --cppflags` -arch x86_64 -O3
MACOSX_LDFLAGS_64  = `vigra-config --libs` `vigra-config --fftw-lib` -arch x86_64 -bundle -undefined dynamic_lookup
CC = gcc

UNIX_CXXFLAGS_32 = -I/src `vigra-config --cppflags` -m32 -O3 -fPIC -shared
UNIX_LDFLAGS_32  = `vigra-config --libs` `vigra-config --fftw-lib` -m32 -shared

UNIX_CXXFLAGS_64 = -I/src `vigra-config --cppflags` -m64 -O3 -fPIC -shared
UNIX_LDFLAGS_64  = `vigra-config --libs` `vigra-config --fftw-lib` -m64 -shared

CC = gcc

macosx32:	src/vigra_filters_c.hxx src/vigra_convert_c.hxx src/vigra_imgproc_c.hxx src/vigra_impex_c.hxx src/vigra_morphology_c.hxx src/vigra_segmentation_c.hxx
	cd bin && $(CC) $(MACOSX_CXXFLAGS_32) -c ../src/vigra_c.cxx
	$(CC) $(MACOSX_LDFLAGS_32) bin/vigra_c.o -o bin/libvigra_c.dylib

macosx64:	src/vigra_filters_c.hxx src/vigra_convert_c.hxx src/vigra_imgproc_c.hxx src/vigra_impex_c.hxx src/vigra_morphology_c.hxx src/vigra_segmentation_c.hxx
	cd bin && $(CC) $(MACOSX_CXXFLAGS_64) -c ../src/vigra_c.cxx
	$(CC) $(MACOSX_LDFLAGS_64) bin/vigra_c.o -o bin/libvigra_c.dylib

unix32:	src/vigra_filters_c.hxx src/vigra_convert_c.hxx src/vigra_imgproc_c.hxx src/vigra_impex_c.hxx src/vigra_morphology_c.hxx src/vigra_segmentation_c.hxx
	cd bin && $(CC) $(UNIX_CXXFLAGS_32) -c ../src/vigra_c.cxx
	$(CC) bin/vigra_c.o $(UNIX_LDFLAGS_32) -o bin/libvigra_c.so

unix64:	src/vigra_filters_c.hxx src/vigra_convert_c.hxx src/vigra_imgproc_c.hxx src/vigra_impex_c.hxx src/vigra_morphology_c.hxx src/vigra_segmentation_c.hxx
	cd bin && $(CC) $(UNIX_CXXFLAGS_64) -c ../src/vigra_c.cxx
	$(CC) bin/vigra_c.o $(UNIX_LDFLAGS_64) -o bin/libvigra_c.so

clean:
	rm bin/*.*

