//
// Created by pvobile on 17-5-4.
//

#include "ImageComparator.h"
void ImageComparator::setColorReduction(int factor)
{
    this->div = factor;
}
int ImageComparator::getColorReduction()
{
    return this->div;
}
void ImageComparator::setReferenceImage(const cv::Mat &image)
{
    this->reference = image;
    traversal.colorReduce(this->reference, div);
    this->refH = hist.getHistoGramNoZip(this->reference);
}
double ImageComparator::compare(const cv::Mat &image)
{
    this->input = image;
    traversal.colorReduce(this->input, div);
    this->inputH = hist.getHistoGramNoZip(this->input);
    return cv::compareHist(refH, inputH, CV_COMP_INTERSECT);
}