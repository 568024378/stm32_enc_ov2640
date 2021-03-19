#ifndef FACERECOGNIZE_H
#define FACERECOGNIZE_H

#include <QThread>
#include <QPushButton>
#include <QFile>
#include <QLabel>
#include <QImage>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "fMenu.h"

#include <QDebug>

using namespace cv;
using namespace std;
using namespace cv::face;

#define leftEye 36
#define rightEye 42


class facerecognize : public QThread
{
public:
    //facerecognize(QLabel *pshowLabel, QLabel *pSerialNumLabel, QLabel *pThresholVal, QLabel *pdetectLB, Ptr<Facemark> parafacemark);
    facerecognize(QLabel *pshowLabel, QLabel *pSerialNumLabel, QLabel *pdetectLB, Ptr<Facemark> parafacemark,int *num,double *predictRate);
    int recognizeFace();
    Mat getwarpAffineImg(Mat &src, vector<Point2f> &landmarks);
    void run();

private:
    //faceregister *registExitFace;
    QLabel *ptrShowLabel;
    QLabel *ptrSerialNumLabel;
//    QLabel *ptrThreshold;
    QLabel *ptrdetectLb;
    Ptr<Facemark> facemark;
    vector<Rect> faces;

    int *pnum;
    double *pRate;
};

#endif // FACERECOGNIZE_H



