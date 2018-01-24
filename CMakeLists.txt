cmake_minimum_required(VERSION 3.8)
project(project_seg_catalys)

#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )

set(SOURCE_FILES
        3dmorpho.cpp
        coordinates.cpp
        coordinates.h
        diagonalize.cpp
        diagonalize.h
        distcart.cpp
        distcart.h
        distmap.cpp
        distmap.h
        image.cpp
        image.h
        inout.cpp
        inout.h
        lissage.cpp
        lissage.h
        Makefile
        matrix.cpp
        matrix.h
        memalloc.cpp
        memalloc.h
        morpho.cpp
        morpho.h
        nrutil.cpp
        nrutil.h
        pixel.cpp
        pixel.h
        procedures.cpp
        procedures.h
        project_seg_catalys.cpp
        pythag.cpp
        pythag.h
        svbksb.cpp
        svbksb.h
        svdcmp.cpp
        svdcmp.h
        util.h
        voxel.cpp
        voxel.h 3dmorpho.h)

add_executable(project_seg_catalys ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( project_seg_catalys ${OpenCV_LIBS} )