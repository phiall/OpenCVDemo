//
// Created by pvobile on 17-4-17.
//
#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class HistoGram1D
{
private:
    int histSize[1];
    float hranges[2];
    const float *ranges[1];
    int channels[1];
public:
    HistoGram1D()
    {
        histSize[0] = 256;
        hranges[0] = 0;
        hranges[1] = 255;
        ranges[0] = hranges;
        channels[0] = 0;
    }

public:
    /*
     * 生成直方图图像
     */
    cv::Mat getHistoGramImg(const cv::Mat &image);
    /*
     * 图像二值化
     */
    cv::Mat getBinaryImg(const cv::Mat &image);
    /*
     * 旨在检测直方图中最高非零最低项和最高强度值重新映射到0和255,从而提高图片对比度
     */
    cv::Mat stretch(const cv::Mat &image, int minVal = 0);
    /*
     * 返回输入单通道图片的直方图
     */
    cv::MatND getHistoGram(const cv::Mat &image);
private:
    cv::Mat applyLookUp(const cv::Mat &image, const cv::Mat &lookup);
};

class ColorHistoGram
{
private:
    int histSize[3];
    float hranges[2];
    const float *ranges[3];
    int channels[3];
public:
    ColorHistoGram()
    {
        histSize[0] = histSize[1] = histSize[2] = 256;
        hranges[0] = 0;
        hranges[1] = 255;
        ranges[0] = hranges;
        ranges[1] = hranges;
        ranges[2] = hranges;
        channels[0] = 0;
        channels[1] = 1;
        channels[2] = 2;
    }

public:
    /*
     * 生成直方图图像
     */
    cv::Mat getHistoGramImg(const cv::Mat &image);
    /*
     * 图像二值化
     */
    cv::Mat getBinaryImg(const cv::Mat &image);

public:
    /*
     * 由于是彩色图像通道多,普通直方图需要更多的存储空间,
     * 返回稀疏矩阵存储的直方图
     */
    cv::SparseMat getHistoGram(const cv::Mat &image);
    /*
     * 返回直方图
     */
    cv::MatND getHistoGramNoZip(const cv::Mat &image);
    /*
     * 使用HSV颜色空间返回直方图
     */
    cv::MatND getHueHistoGram(const cv::Mat &image, int minSaturation = 0);
};
