//
// Created by pvobile on 17-4-27.
//
#include "demoMain.h"
#include "ImageTraversal/ImageTraversal.h"
#include "ImageComparator/ImageComparator.h"
#include "FileUtils/FileUtils.h"

void DemoMain::showAllModule()
{
    for(int i = 0; i < choices.size(); ++ i) {
        cout << choices.at(i) << endl;
    }
    cout << "Your choice: ";
    cin >> choice;
}
void DemoMain::filter()
{
    cv::Mat image = cv::imread("/home/pvobile/workspace/Cpp/OpenCVDemo/pic/000005OI.jpg");
    if (image.data == NULL)
        cout << "error\n";
    ImgMatchPreFilter filter("/home/pvobile/tmp/match/AdTracker_images/test", "");
    filter.run();
}
void DemoMain::traversalTest(int cs)
{
    cv::Mat image = cv::imread("/home/pvobile/workspace/Cpp/OpenCVDemo/pic/000005OI.jpg");
    if (image.data == NULL)
        cout << "error\n";
    cv::Mat result;
if(0 == cs )
    ImageTraversal::salt(image, 3000);
else if(1 == cs)
    ImageTraversal::colorReduce(image);
else if(2 == cs)
    ImageTraversal::sharpen(image, result);
    cv::namedWindow("test", CV_WINDOW_AUTOSIZE);
    cv::imshow("test", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    cv::destroyAllWindows();
}
void DemoMain::histoTest(int cs)
{
    cv::Mat image = cv::imread("/home/pvobile/workspace/Cpp/OpenCVDemo/pic/000005OI.jpg");
    if (image.data == NULL)
        cout << "error\n";
    cv::Mat result;
if(0 == cs)
    result = HistoGram1D().getHistoGramImg(image);
else if(1 == cs)
    result = HistoGram1D().getBinaryImg(image);
else if(2 == cs)
    result = ColorHistoGram().getHistoGramImg(image);
else if(3 == cs)
    result = HistoGram1D().stretch(image, 40000);
    cv::namedWindow("test", CV_WINDOW_AUTOSIZE);
    cv::imshow("test", result);
    cv::waitKey(0);
    cv::destroyAllWindows();
    cv::destroyAllWindows();
}
void DemoMain::contentFinder(int cs)
{
if(0 == cs)
    ContentFinder().bpFinderTest();
else if(1 == cs)
    ContentFinder().mfFinderTest();
}
void DemoMain::imageComparebyHist()
{
    ImageComparator comparator;
    cv::Mat image = cv::imread("/share/cvpic/hand1.jpg");
    comparator.setReferenceImage(image);
    FileUtils utils;
    vector<string> files = utils.get_need_files("/share/cvpic", "");
    for(auto it : files) {
        cv::Mat tmp = cv::imread("/share/cvpic/" + it);
        if(tmp.data) {
            cout << it << " simalar : " << comparator.compare(tmp) << endl;
        }
    }
}
void DemoMain::run()
{
    showAllModule();
    switch (choice)
    {
        case 0:
            filter();
            break;
        case 1:
            traversalTest();
            break;
        case 2:
            histoTest();
            break;
        case 3:
            contentFinder(1);
            break;
        case 4:
            imageComparebyHist();
    }
}

