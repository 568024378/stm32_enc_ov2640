#ifndef FACEDETECT_H
#define FACEDETECT_H
#include <QDebug>
#include <QString>
#include <QImage>
#include <QThread>
#include <QLabel>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace cv;
using namespace std;

//----------------------------------人脸识别所需要的分类器-------------------------------------

#define FRONT_CASCADE "/var/face_system/haarcascades/haarcascade_frontalface_alt2.xml"        //检测正脸的分类器
#define PROFILE_CASCADE "/var/face_system/haarcascades/haarcascade_profileface.xml"           //检测侧脸的分类器
#define EYE_CASCADE "/var/face_system/haarcascades/haarcascade_eye_tree_eyeglasses.xml"       //人眼检测分类器




/*该类是用来检测图像中的人脸区域，截取下来存放到人脸库里面*/
class faceDetect : public QThread
{
public:
    faceDetect(CascadeClassifier *frontcascade, CascadeClassifier *profilecascade,QLabel *paraLabel, QLabel *paraDescript,
               QImage paraFrame, int *ifHaveFace, int paraSerial, QString &paraPath);
    int detect();
    void run();

private:
    CascadeClassifier *face_cascade;            //级联分类器，用来检测人脸
    CascadeClassifier *profileFace_cascade;     //级联分类器，用来检测人脸侧脸

    QLabel *showLabel;                          //显示用矩形画出的人脸区域图像
    QLabel *descriptTextLabel;                  //该标签用来显示图片中人脸的数目

    QImage frame;                               //采集到图片
    int *flag;                                  //标志是否检测到人脸

    int serialNum;                              //说明是第几张图片，拼接到存放路径用到
    QString dirPath;                            //人脸图像存放路径
};

#endif // FACEDETECT_H
