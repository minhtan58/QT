/****************************************************************************

    Copyright (C) 2018 by LGE
    File: FireDetection.h
    Create: 11
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef FIREDETECTION_H
#define FIREDETECTION_H

#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

#define COLOR_DETECTION_THRESHOLD 40

using namespace cv;
using namespace std;

class FireDetection
{

public:
    enum DetectionEngine {
        DETECT_ENGINE_HSV,
        DETECT_ENGINE_YCBCR,
    };

    FireDetection();
    FireDetection(std::string path);
    void setSourceImage(std::string path);
    void showImage(std::string path);
    Mat process(int engine = DETECT_ENGINE_HSV);

    Mat processEngine1();
    Mat processEngine2();
    Mat processEngine3();
    Mat processEngine4();
    Mat processEngine5();

private:
    Mat m_imageOrg;
    Mat m_imageResult;

    //extend variables
    bool isDebug;//调试模式显示中间过程图
    int oldDetectNum;//上次检测到的轮廓数
    int newDetectNum;//本次检测到的轮廓数
    //int detecModel;//颜色检测模型选择
    int detectSumMax;//检测帧累计最大值
    int detectSum;//检测帧累计数，减少偶然干扰，初始值为不为0，为了指数增长

    bool isFirePixel(const Mat &image, const int row, const int column);

    bool fireDetect(Mat &detecimg, Mat &sourceimg, int model);

    Mat ImgPreProcess(Mat rgbimg, int model);
};

#endif // FIREDETECTION_H
