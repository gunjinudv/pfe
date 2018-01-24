COMPILATEUR = g++
#COMPILATEUR = CC
 

OPTIONS= -g -O3
LIBS     =    -lm


SOURCES =  project_seg_catalys.cpp coordinates.cpp	memalloc.cpp	procedures.cpp	svbksb.cpp diagonalize.cpp	image.cpp inout.cpp	lissage.cpp	matrix.cpp	pythag.cpp	nrutil.cpp	pixel.cpp	voxel.cpp svdcmp.cpp
		
				

OBJECTS=$(SOURCES:.cpp=.o)

.SUFFIXES: .cpp

.cpp.o:
	$(COMPILATEUR) $(OPTIONS) -c $<


TARGETS = project_seg_catalys

default all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(COMPILATEUR) $(OPTIONS)   -o  $@  $(OBJECTS) $(LIBS)

clean:
	-rm -f $(OBJECTS)
