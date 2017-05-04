//
// Created by pvobile on 17-4-17.
//
#include "HistoGram.h"

cv::MatND HistoGram1D::getHistoGram(const cv::Mat &image)
{
    cv::MatND hist;
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize,ranges);
    return hist;
}
cv::Mat HistoGram1D::getHistoGramImg(const cv::Mat &image)
{
    cv::MatND hist = getHistoGram(image);
    double maxVal = 0, minVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));
    int hpt = static_cast<int>(0.9 * histSize[0]);
    for(int i = 0; i < histSize[0]; ++ i) {
        float binVal = hist.at<float>(i);
        int intensity = static_cast<int>(binVal * hpt / maxVal);
        cv::line(histImg, cv::Point(i, histSize[0]),
            cv::Point(i, histSize[0] - intensity),
            cv::Scalar::all(0));
    }
    return histImg;
}
cv::Mat HistoGram1D::getBinaryImg(const cv::Mat &image)
{
    cv::Mat ret;
    cv::threshold(image, ret, 60, 255, cv::THRESH_BINARY);
    return ret;
}

cv::SparseMat ColorHistoGram::getHistoGram(const cv::Mat &image)
{
    cv::SparseMat hist(3, histSize, CV_32F);
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 3, histSize,ranges);
    return hist;
}
cv::MatND ColorHistoGram::getHueHistoGram(const cv::Mat &image, int minSaturation)
{
    cv::MatND hist;
    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);
    cv::Mat mask;
    if(minSaturation > 0) {
        std::vector<cv::Mat> v;
        //分割为三个通道
        cv::split(hsv, v);
        //标记低饱和像素
        cv::threshold(v[1], mask, minSaturation, 255, cv::THRESH_BINARY);
    }
    hranges[0] = 0.0;
    hranges[1] = 180;
    channels[0] = 0;
    cv::calcHist(&hsv, 1, channels, mask, hist, 1, histSize, ranges);
    return hist;
}
cv::MatND ColorHistoGram::getHistoGramNoZip(const cv::Mat &image)
{
    cv::MatND hist;
    //计算直方图
    calcHist(&image,
             1,                     //计算单张图像的直方图
             channels,        //通道的数量
             cv::Mat(),              //不使用图像作为掩码
             hist,                //返回的直方图
             3,                    //这是三维的直方图
             histSize,         //项的数量
             ranges            //像素值的范围
    );
    return hist;
}
cv::Mat ColorHistoGram::getHistoGramImg(const cv::Mat &image)
{
    cv::SparseMat hist = getHistoGram(image);
    double maxVal = 0, minVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));
    /*int hpt = static_cast<int>(0.9 * histSize[0]);
    for(int i = 0; i < histSize[0]; ++ i) {
        float binVal =  hist. hist.at<float>(i);
        int intensity = static_cast<int>(binVal * hpt / maxVal);
        cv::line(histImg, cv::Point(i, histSize[0]),
                 cv::Point(i, histSize[0] - intensity),
                 cv::Scalar::all(0));
    }
    hpt = static_cast<int>(0.9 * histSize[1]);
    for(int i = 0; i < histSize[1]; ++ i) {
        float binVal = hist.at<float>(i);
        int intensity = static_cast<int>(binVal * hpt / maxVal);
        cv::line(histImg, cv::Point(i, histSize[1]),
                 cv::Point(i, histSize[1] - intensity),
                 cv::Scalar(255, 255, 0));
    }
    hpt = static_cast<int>(0.9 * histSize[2]);
    for(int i = 0; i < histSize[2]; ++ i) {
        float binVal = hist.at<float>(i);
        int intensity = static_cast<int>(binVal * hpt / maxVal);
        cv::line(histImg, cv::Point(i, histSize[2]),
                 cv::Point(i, histSize[2] - intensity),
                 cv::Scalar(0, 255, 255));
    }*/
    return histImg;
}
cv::Mat HistoGram1D::stretch(const cv::Mat &image, int minVal)
{
    cv::MatND hist = getHistoGram(image);
    int imin = 0;
    for(; imin < histSize[0]; ++ imin) {
        if(hist.at<float>(imin) > minVal)
            break;
    }
    int imax = histSize[0] - 1;
    for(; imax >= 0; -- imax) {
        if(hist.at<float>(imax) > minVal)
            break;
    }
    int dim(256);
    cv::Mat lookup(1, &dim, CV_8U);
    for(int i = 0; i < 256; ++ i) {
        if(i < imin) {
            lookup.at<uchar>(i) = 0;
        } else if(i > imax) {
            lookup.at<uchar>(i) = 255;
        } else {
            lookup.at<uchar>(i) = static_cast<uchar>(255.0 * (i - imin) / (imax - imin) + 0.5);
        }
    }
    cv::Mat result = applyLookUp(image, lookup);
    return result;
}

cv::Mat HistoGram1D::applyLookUp(const cv::Mat &image, const cv::Mat &lookup)
{
    cv::Mat result;
    cv::LUT(image, lookup, result);
    return result;
}