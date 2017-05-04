//
// Created by pvobile on 17-4-24.
//
#include <opencv2/imgproc/imgproc.hpp>
#include "ContentFinder.h"
#include "../HistoGram/HistoGram.h"
#include <opencv2/video/tracking.hpp>
#include <string>
using namespace std;
void ContentFinder::setThreshold(float t) {
    threshold = t;
}

float ContentFinder::getTrheshold() {
    return threshold;
}

void ContentFinder::setHistogram(const cv::MatND &h) {
    histogram = h;
    cv::normalize(histogram, histogram, 1.0);
}
cv::Mat ContentFinder::find(const cv::Mat &image, float min, float max, int *ch, int dim) {
    cv::Mat result;
    hranges[0] = min;
    hranges[1] = max;
    this->channels = ch;
    cv::calcBackProject(&image, 1, channels, histogram, result, ranges, 255.0);
    if(threshold > 0) {
        cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
    }
    return result;
}
void ContentFinder::bpFinderTest()
{
    string path = "/share/cvpic/goat.jpg";
    cv::Mat initimage= cv::imread(path);
    if (!initimage.data)
        return;
    cv::namedWindow("org image");
    cv::imshow("org image",initimage);

    cv::Mat image= cv::imread(path.c_str(), CV_8U);
    if (!image.data)
        return;

    //设置目标区域
    cv::Mat imageROI;
    imageROI= image(cv::Rect(370,300,50,50)); //

    //显示目标区域
    cv::namedWindow("target zone");
    cv::imshow("target zone",imageROI);

    //计算目标区域直方图
    HistoGram1D h;
    cv::MatND hist= h.getHistoGram(imageROI);
    cv::namedWindow("target hist");
    cv::imshow("target hist",h.getHistoGramImg(imageROI));

    //创建检查类
    setHistogram(hist);

    //初始化阈值
    setThreshold(-1.0f);

    //进行反投影
    cv::Mat result;
    int ch[3] = {0, 1, 2};
    result= find(image, 0, 255, ch, 64);

    //创建负图像并显示概率结果
    cv::Mat tmp;
    result.convertTo(tmp, CV_8U, -1.0, 255.0);// bin * (-1) + 255
    cv::namedWindow("Negative Img");//负图像概率结果图像越暗概率越大
    cv::imshow("Negative Img",tmp);

    //得到二值反投影图像
    setThreshold(0.01f);
    result= find(image, 0, 255, ch, 64);

    //在图像中绘制选中区域
    cv::rectangle(image,cv::Rect(262,151,113,150),cv::Scalar(0,0,0));

    cv::namedWindow("Org Gray Img");//原图片的灰度图
    cv::imshow("Org Gray Img",image);

    //显示反影后的结果
    cv::namedWindow("Binary Result Img");
    cv::imshow("Binary Result Img",result);

    cv::waitKey();
}
void ContentFinder::mfFinderTest()
{
    //读取參考图像
    cv::Mat image= cv::imread("/share/cvpic/hand1.jpg");
    if (!image.data)
        return;

    //定义查找物体
    cv::Mat imageROI= image(cv::Rect(0,466,478,478));
    cv::rectangle(image, cv::Rect(0,466,478,478),cv::Scalar(0,0,255));

    //显示參考图像
    cv::namedWindow("org img-mark ball");
    cv::imshow("org img-mark ball",image);

    int minSat=65;

    //读入目标图像
    image= cv::imread("/share/cvpic/hand2.jpg");

    //显示目标图像
    cv::namedWindow("target org img");
    cv::imshow("target org img",image);

    //将RGB图像图像转换为HSV图像
    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);

    //分离图像通道
    vector<cv::Mat> v;
    cv::split(hsv,v);

    //消除饱和度较低的像素点
    cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);
    cv::namedWindow("消除饱和度较低的像素点");
    cv::imshow("消除饱和度较低的像素点",v[1]);

    //获得色度直方图
    ColorHistoGram hc;
    cv::MatND colorhist= hc.getHueHistoGram(imageROI, minSat);
    //进行直方图反投影
    setHistogram(colorhist);
    setThreshold(0.3f);
    int ch[1]={0};
    cv::Mat result= find(hsv,0.0f,180.0f,ch,1);

    cv::namedWindow("进行直方图反投影");
    cv::imshow("进行直方图反投影",result);

    //利用位运算消除低饱和度像素
    cv::bitwise_and(result,v[1],result);
    cv::namedWindow("利用位运算进一步消除低饱和度像素点");
    cv::imshow("利用位运算进一步消除低饱和度像素点",result);

    // 得到反投影直方图概率图像
    setThreshold(-1.0f);
    result= find(hsv,0.0f,180.0f,ch,1);
    cv::bitwise_and(result,v[1],result);
    cv::namedWindow("处理后的二值图像");
    cv::imshow("处理后的二值图像",result);

    cv::Rect rect(0,466,478,478);
    cv::rectangle(image, rect, cv::Scalar(0,0,255));


    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,10,0.01);
    cout << "迭代次数 = " << cv::meanShift(result,rect,criteria) << endl;

    cv::rectangle(image, rect, cv::Scalar(0,255,0));

    //展示结果图
    cv::namedWindow("result");
    cv::imshow("result",image);

    cv::waitKey();
}