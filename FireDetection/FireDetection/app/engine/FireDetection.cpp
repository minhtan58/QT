/****************************************************************************

    Copyright (C) 2018 by LGE
    File: FireDetection.cpp
    Create: 11
    Author: Vuong Nguyen

 ****************************************************************************/

#include "FireDetection.h"
#include "opencv2/video/background_segm.hpp"

FireDetection::FireDetection()
{
    oldDetectNum = 0;
    newDetectNum = 0;
    isDebug = true;
    detectSumMax = 20;//Phát hiện tối đa tích lũy khung
    detectSum = 1;//Phát hiện số lượng khung tích lũy, giảm khả năng gây nhiễu, giá trị ban đầu không bằng 0, để tăng trưởng theo cấp số nhân
}

FireDetection::FireDetection(std::string path)
{
    setSourceImage(path);
}

void FireDetection::setSourceImage(std::string path)
{
    m_imageOrg = imread(path);
}

void FireDetection::showImage(std::string path)
{
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", imread(path));
}

Mat FireDetection::process(int engine)
{
    Mat result;
    switch (engine) {
    case DETECT_ENGINE_HSV: {
        result = processEngine1();
        break;
    }
    case DETECT_ENGINE_YCBCR: {
        result = processEngine2();
        break;
    }
    case 3:
        result = processEngine3();
        break;
    default:
        break;
    }
    return result;
}

Mat FireDetection::processEngine1()
{
    Mat mask, blur, result;
    GaussianBlur(m_imageOrg, blur, Size(21, 21), 0);

    Mat hsv;
    cvtColor(blur, hsv, COLOR_BGR2HSV);

    std::vector<uint8_t> lowerMask = {18, 50, 50};
    std::vector<uint8_t> upperMask = {35, 255, 255};

    InputArray lower(lowerMask);
    InputArray upper(upperMask);

    inRange(hsv, lower, upper, mask);

    bitwise_and(m_imageOrg, hsv, result, mask);
    return result;
}

Mat FireDetection::processEngine2()
{
    Mat fgMaskMOG2, result;
    Ptr<BackgroundSubtractorMOG2> pMOG2 = createBackgroundSubtractorMOG2();
    pMOG2->apply(m_imageOrg, fgMaskMOG2);

    Mat temp;
    m_imageOrg.convertTo(temp, CV_32FC3, 1/255.0);

    Mat imageYCrCb;
    cvtColor(temp, imageYCrCb, CV_BGR2YCrCb);

//    Mat colorMask = Mat(m_imageOrg.rows, m_imageOrg.cols, CV_8UC1);
//    for (int i = 0; i < imageYCrCb.rows; i++){
//        const uchar* fgMaskValuePt = fgMaskMOG2.ptr<uchar>(i);
//        uchar* colorMaskValuePt = colorMask.ptr<uchar>(i);
//        for (int j = 0; j < imageYCrCb.cols; j++){
//            if (fgMaskMOG2[j] > 0 && isFirePixel(imageYCrCb, i, j))
//                colorMaskValuePt[j] = 255;
//            else
//                colorMaskValuePt[j] = 0;
//        }
//    }
    return imageYCrCb;
}

Mat FireDetection::processEngine3()
{
    Mat result;
    fireDetect(m_imageOrg, result, 3);
    return result;
}

bool FireDetection::isFirePixel(const Mat &image, const int row, const int column){
    uchar valueY, valueCb, valueCr;
    valueCb = image.at<Vec3b>(row, column)[0];
    valueCr = image.at<Vec3b>(row, column)[1];
    valueY = image.at<Vec3b>(row, column)[2];

    uchar meanCb, meanCr, meanY;
    Scalar meanVal = mean(image);
    meanCb = meanVal[0];
    meanCr = meanVal[1];
    meanY = meanVal[2];

    int intValueCr, intValueCb;
    intValueCb = (int)valueCb;
    intValueCr = (int)valueCr;

    if (valueY > valueCb
            && intValueCr > intValueCb
            && (valueY > meanY && valueCb < meanCb && valueCr > meanCr)
            && ((abs(valueCb - valueCr) * 255) > COLOR_DETECTION_THRESHOLD))
        return true;
    return false;
}

bool FireDetection::fireDetect(Mat &detecimg, Mat &sourceimg, int model)
{
    bool is_Fire = false;
    if(isDebug) {
        imshow("input image",detecimg);
    }
    Mat result_img = ImgPreProcess(detecimg,model);
    if(isDebug) {
        imshow("After color model processes",result_img);
    } else {
        destroyAllWindows();
    }
    blur(result_img,result_img,Size(5,5),Point(0,0));
    threshold(result_img,result_img,40,255,CV_THRESH_BINARY);
    GaussianBlur(result_img,result_img,Size(5,5),0,0);
    erode(result_img,result_img,Mat());
    dilate(result_img,result_img,Mat());
    if(isDebug) {
        imshow("Morphological processed",result_img);
    }
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //Tìm đường nét
    findContours(result_img,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
    newDetectNum = hierarchy.size();
    if(newDetectNum > oldDetectNum)
    {
        if(detectSum < detectSumMax*2)
            detectSum += 2;//Bước tăng trưởng nhanh hơn mức giảm - phát hiện nhanh hơn và biến mất chậm
        if(detectSum > detectSumMax)
        {
            is_Fire = true;
            for(int idx = 0;idx>=0;idx=hierarchy[idx][0])//Vẽ hình chữ nhật để khoanh tròn ngọn lửa
            {
                Scalar color(0,0,255);
                Rect rect = boundingRect(contours.at(idx));
                rectangle(sourceimg,rect,color,2);//Vẽ hình chữ nhật trên hình ảnh nguồn
            }
            if(isDebug)
            {
                imshow("end processed", sourceimg);
            }
        }
    }
    else
    {
        if(newDetectNum > 0)
        {
            if(detectSum < detectSumMax*2)
                detectSum ++;
            if(detectSum > detectSumMax)
            {
                is_Fire = true;
                for(int idx = 0;idx>=0;idx=hierarchy[idx][0])//Vẽ hình chữ nhật để khoanh tròn ngọn lửa
                {
                    Scalar color(0,0,255);
                    Rect rect = boundingRect(contours.at(idx));
                    rectangle(sourceimg,rect,color,2);//Vẽ hình chữ nhật trên hình ảnh nguồn
                }
                if(isDebug)
                {
                    imshow("end processed", sourceimg);
                }
            }
        }
        else
        {
            if(detectSum > 0)
                detectSum--;
        }
    }
    oldDetectNum = newDetectNum;

    return is_Fire;
}

Mat FireDetection::ImgPreProcess(Mat rgbimg, int model)
{
    Vec3b pixe,pixel;
    Vec3b pixe2;
    Scalar scalar,scalarRGB;
    int i,j;
    bool isMeetRGB=false,isMeetYCC=false,isMeetHSI=false;//Ba mô hình màu đáp ứng các điều kiện
    bool isDetected = false;//Đã phát hiện điểm phát hiện cháy
    int myThreshold = 35;//Ngưỡng mô hình YCbCr
    double RT = 115;//Ngưỡng kênh R của mô hình RGB
    double ST = 55;//Ngưỡng bão hòa mô hình RGB
    Mat tempimg(rgbimg.rows,rgbimg.cols,CV_8UC3);
    Mat hsiImg(rgbimg.rows,rgbimg.cols,CV_8UC3);
    Mat dst(rgbimg.rows,rgbimg.cols,CV_8UC1);


    cvtColor(rgbimg,hsiImg,CV_BGR2HLS);//Đồ họa RGB đến HSI
    cvtColor(rgbimg,tempimg,CV_BGR2YCrCb);//Đồ thị RGB được chuyển đổi thành YCRCB (đồ thị RGB được lưu trữ trong opencv dưới dạng BGR)
    scalar = mean(tempimg);//Tính toán giá trị pixel trung bình của mỗi kênh trong hình ảnh
    scalarRGB = mean(rgbimg);
    for(i=0;i<rgbimg.rows;i++)
    {
        for(j=0;j<rgbimg.cols;j++)
        {

            pixe = rgbimg.at<Vec3b>(i,j);
            uchar color_B = pixe[0];
            uchar color_G = pixe[1];
            uchar color_R = pixe[2];
            uchar color_min = color_R > color_G?color_G:color_R;
            color_min = color_min>color_B?color_B:color_min;

            pixel = tempimg.at<Vec3b>(i,j);
            uchar color_Y = pixel[0];
            uchar color_Cr = pixel[1];
            uchar color_Cb = pixel[2];

            pixe2 =  hsiImg.at<Vec3b>(i,j);

            uchar color_H = pixe2[0];
            uchar color_L = pixe2[1];
            uchar color_S = pixe2[2];

            double ds = (255.0 - color_R)*RT/ST;
            double S = color_S/255.0;//Chuyển đổi độ bão hòa về [0-1]

            //Mô hình ràng buộc RGB 1.R>RT 2.R>=G>=B 3.S>=(255-R)*ST/RT
            if(color_R > RT && color_R > color_G && color_G > color_B
                    && S >= ds)
            {
                isMeetRGB = true;
            }
            //Giới hạn mô hình YCbCr 6
            if(color_Y > color_Cb && color_Cr > color_Cb && color_Y > scalar.val[0] &&color_Cb
                    <scalar.val[2] && color_Cr > scalar.val[1] && color_Cr-color_Cb> myThreshold)
            {
                isMeetYCC = true;
            }
            // Mô hình HSL - H> 60 0,2 <S <1 0,5 <L <1
            if(color_H <= 60 && color_S >= 0.2*255 && color_S < 255 && color_L >= 0.5*255 &&color_L < 255 )
            {
                isMeetHSI = true;
            }
            switch(model)
            {
            case 0:
                if(isMeetRGB)
                {
                    isMeetRGB = false;
                    isDetected = true;
                }
                break;
            case 1:
                if(isMeetYCC)
                {
                    isMeetYCC = false;
                    isDetected = true;
                }
                break;
            case 2:
                if(isMeetHSI)
                {
                    isMeetHSI = false;
                    isDetected = true;
                }
                break;
            case 3:
                if(isMeetYCC && isMeetHSI)
                {
                    isMeetYCC = false;
                    isMeetHSI = false;
                    isDetected = true;
                }
                break;
            case 4:
                if(isMeetRGB && isMeetYCC && isMeetHSI)
                {
                    isMeetRGB = false;
                    isMeetYCC = false;
                    isMeetHSI = false;
                    isDetected = true;
                }
                break;
            }
            if(isDetected)
            {
                isDetected = false;
                pixel[0] = 255;//màu trắng
                pixel[1] = 255;
                pixel[2] = 255;
                tempimg.at<Vec3b>(i,j) = pixel;
                continue;
            }
            pixel[0] = 0;
            pixel[1] = 0;
            pixel[2] = 0;
            tempimg.at<Vec3b>(i,j) = pixel;
        }
    }
    cvtColor(tempimg,dst,CV_BGR2GRAY);
    return dst;
}
