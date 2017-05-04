//
// Created by pvobile on 17-5-4.
//
#pragma once

#include <opencv2/core/core.hpp>
#include "../HistoGram/HistoGram.h"
#include "../ImageTraversal/ImageTraversal.h"

class ImageComparator
{
private:
    cv::Mat reference;
    cv::Mat input;
    cv::MatND refH;
    cv::MatND inputH;
    ColorHistoGram hist;
    ImageTraversal traversal;
    int div;
public:
    ImageComparator():div(32) {}
    void setColorReduction(int factor);
    int getColorReduction();
    void setReferenceImage(const cv::Mat &image);
    /*
     * 基于直方图 比较图片的相似度
     */
    double compare(const cv::Mat &image);
};
