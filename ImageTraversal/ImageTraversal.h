//
// Created by peace on 17-4-27.
//

#pragma once

#include <opencv2/core/core.hpp>

class ImageTraversal
{
public:
    static void salt(cv::Mat &img, int n);
    static void colorReduce(cv::Mat &img, int div = 64);
    static void sharpen(const cv::Mat &image, cv::Mat &result);
};
