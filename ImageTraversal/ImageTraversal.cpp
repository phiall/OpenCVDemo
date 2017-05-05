//
// Created by peace on 17-4-27.
//
#include "ImageTraversal.h"
void ImageTraversal::salt(cv::Mat &img, int n) {
    for (int idx = 0; idx < n; ++ idx) {
        int i = rand() % img.cols;
        int j = rand() % img.rows;
        if (1 == img.channels()) {
            img.at<uchar>(j, i) = 255;
        } else {
            img.at<cv::Vec3b>(j, i)[0] = 255;
            img.at<cv::Vec3b>(j, i)[1] = 255;
            img.at<cv::Vec3b>(j, i)[2] = 255;
        }
    }
}
void ImageTraversal::colorReduce(cv::Mat &img, int div) {
    int row_len = img.rows;
    int pix_count = img.cols * img.channels();
    for(int i = 0; i < row_len; ++ i) {
        uchar *data = img.ptr<uchar>(i);
        for(int j = 0; j < pix_count; ++ j) {
            data[j] = data[j] / div * div + div / 2;
        }
    }
}
void ImageTraversal::sharpen(const cv::Mat &image, cv::Mat &result) {
#if 1
    result.create(image.size(), image.type());
    for(int i = 0; i < image.rows - 1; ++ i) {
        const cv::Vec3b *previous = image.ptr<const cv::Vec3b>(i-1);
        const cv::Vec3b *current = image.ptr<const cv::Vec3b>(i);
        const cv::Vec3b *next = image.ptr<const cv::Vec3b>(i+1);
        cv::Vec3b *output = result.ptr<cv::Vec3b>(i);
        for(int j = 1; j < image.cols - 1; ++ j) {
            (*output)[0] = cv::saturate_cast<uchar>(
                    5 * current[j][0] - current[j-1][0] - current[j+1][0]
                    - previous[j][0] - next[j][0]);
            (*output)[1] = cv::saturate_cast<uchar>(
                    5 * current[j][1] - current[j-1][1] - current[j+1][1]
                    - previous[j][1] - next[j][1]);
            (*output)[2] = cv::saturate_cast<uchar>(
                    5 * current[j][2] - current[j-1][2] - current[j+1][2]
                    - previous[j][2] - next[j][2]);
            output ++;
        }
    }
    result.row(0).setTo(cv::Scalar::all(0));
    result.row(result.rows-1).setTo(cv::Scalar::all(0));
    result.col(0).setTo(cv::Scalar::all(0));
    result.col(result.cols-1).setTo(cv::Scalar::all(0));
#elif 0
    result.create(image.size(), image.type());
    for(int i = 0; i < image.rows - 1; ++ i) {
        const uchar *previous = image.ptr<const uchar>(i-1);
        const uchar *current = image.ptr<const uchar>(i);
        const uchar *next = image.ptr<const uchar>(i+1);
        uchar *output = result.ptr<uchar>(i);
        int ch = image.channels();
        for(int j = ch; j < (image.cols - 1) * ch; ++ j) {
            *output ++= cv::saturate_cast<uchar>(
                    5 * current[j] - current[j-ch] - current[j+ch]
                    - previous[j] - next[j]);
        }
    }
    result.row(0).setTo(cv::Scalar::all(0));
    result.row(result.rows-1).setTo(cv::Scalar::all(0));
    result.col(0).setTo(cv::Scalar::all(0));
    result.col(result.cols-1).setTo(cv::Scalar::all(0));
#else
    cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
    kernel.at<float>(1, 1) = 5.0;
    kernel.at<float>(0, 1) = -1.0;
    kernel.at<float>(2, 1) = -1.0;
    kernel.at<float>(1, 0) = -1.0;
    kernel.at<float>(1, 2) = -1.0;
    cv::filter2D(image, result, image.depth(), kernel);
#endif
}
