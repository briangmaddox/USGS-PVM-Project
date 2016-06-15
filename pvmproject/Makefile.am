####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = pvmproject
pvmproject_SOURCES = mastermain.cpp inparms.cpp StitcherNode.cpp Stitcher.cpp PvmProjectorSlave.cpp PvmProjector.cpp ProjectorException.cpp Projector.cpp ProjectionParams.cpp ProjUtil.cpp CLineProgress.cpp BaseProgress.cpp 
pvmproject_LDADD   = -lProjectionMesh -lMathLib -lProjectionIO -lImageLib  -lgeotiff -ltiff -lProjection  -lgctpc -lMiscUtils -lpvm3 -lACE

SUBDIRS = docs 

EXTRA_DIST = BaseProgress.cpp BaseProgress.h CLineProgress.cpp CLineProgress.h DRect.h MessageTags.h ProjUtil.cpp ProjUtil.h ProjectionParams.cpp ProjectionParams.h Projector.cpp Projector.h ProjectorException.cpp ProjectorException.h PvmProjector.cpp PvmProjector.h PvmProjectorSlave.cpp PvmProjectorSlave.h Stitcher.cpp Stitcher.h StitcherNode.cpp StitcherNode.h inparms.cpp inparms.h mastermain.cpp 

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = pvmproject

# set the include path found by configure
INCLUDES= $(all_includes) -I$(prefix)/include -I/usr/share/pvm3/include -I$(prefix)/include/geotiff -I$(prefix)/include/tiff
 
# the library search path.
pvmproject_LDFLAGS = $(all_libraries) -L$(prefix)/lib -L/usr/share/pvm3/lib/LINUX
                                                                                
