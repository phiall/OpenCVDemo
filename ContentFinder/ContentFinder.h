//
// Created by peace on 17-4-24.
//
#pragma once

#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class ContentFinder
{
private:
    float hranges[2];
    const float *ranges[3];
    int *channels;
    float threshold;
    cv::MatND histogram;
public:
    ContentFinder():threshold(-1.0f) {
        ranges[0] = hranges;
        ranges[1] = hranges;
        ranges[2] = hranges;
    }
    void setThreshold(float t);
    float getTrheshold();
    void setHistogram(const cv::MatND &h);
    cv::Mat find(const cv::Mat &image, float min, float max, int *channels, int dim);
    /*
     * 反投影目标查找
     */
    void bpFinderTest();
    /*
     * Mean Shift目标查找
     */
    void mfFinderTest();
};
