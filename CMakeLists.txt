cmake_minimum_required(VERSION 2.8)
project(OpenCVDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES
    main.cpp
    HistoGram/HistoGram.h
    HistoGram/HistoGram.cpp
    ImgMatchPreFilter/ImgMatchPreFilter.h
    ImgMatchPreFilter/ImgMatchPreFilter.cpp
    FileUtils/FileUtils.h
    FileUtils/FileUtils.cpp
    ContentFinder/ContentFinder.h
    ContentFinder/ContentFinder.cpp
    ImageTraversal/ImageTraversal.h
    ImageTraversal/ImageTraversal.cpp
    demoMain.cpp
    demoMain.h
        ImageComparator/ImageComparator.h ImageComparator/ImageComparator.cpp)
link_libraries(/usr/local/lib/libopencv_core.so
        /usr/local/lib/libopencv_imgproc.so
        /usr/local/lib/libopencv_highgui.so
        /usr/local/lib/libopencv_video.so
        )
add_executable(OpenCVDemo ${SOURCE_FILES})

#SET(LIBRARIES
#        libopencv.so)
