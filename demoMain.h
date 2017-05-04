//
// Created by pvobile on 17-4-27.
//
#pragma once
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "HistoGram/HistoGram.h"
#include "ImgMatchPreFilter/ImgMatchPreFilter.h"
#include "ContentFinder/ContentFinder.h"
static vector<string> choices = {
        "0 : Image filter:",
        "1 : Image traversal:",
        "2 : Image Histogram:",
        "3 : Content Finder:",
        "4 : Image compare hist:"
};
using namespace std;
class DemoMain
{
private:
    int choice;
private:
    void showAllModule();
    void filter();
    void traversalTest(int cs = 0);
    void histoTest(int cs = 0);
    void contentFinder(int cs = 0);
    void imageComparebyHist();
public:
    void run();
};
