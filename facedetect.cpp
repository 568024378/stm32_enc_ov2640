#include "facedetect.h"

faceDetect::faceDetect(CascadeClassifier *frontcascade, CascadeClassifier *profilecascade,\
                       QLabel *paraLabel, QLabel *paraDescript, QImage paraFrame, int *ifHaveFace, int paraSerial, QString &paraPath)
{
    face_cascade = frontcascade;                //接收传来的正脸检测级联分类器
    profileFace_cascade = profilecascade;       //接收传来的侧脸检测级联分类器

    showLabel = paraLabel;                      //显示用矩形画出的人脸区域图像
    descriptTextLabel = paraDescript;           //传过来的显示图片人脸数目的标签

    frame = paraFrame;                          //传过来的完整图像
    flag = ifHaveFace;                          //标志，判断是否检测到人脸，地址传递，原函数可以获得该参数的实时情况

    serialNum = paraSerial;                     //说明是第几张图片
    dirPath = paraPath;                         //接收调用该类对象的传来的存放路径
}

int faceDetect::detect()
{
    //Mat矩阵对象，用来存放图像和操作图像
    Mat srcImage;                                                               //存放QT传递过来的图像
    Mat faceCutImage;                                                           //存放剪切下来的人脸图像

    frame = frame.convertToFormat(QImage::Format_RGB888);                       //qt操作图像是QImage，opencv操作图像是Mat，该语句将QImage转换成Mat格式
    srcImage = Mat(frame.height(), frame.width(), CV_8UC3, frame.bits(), frame.bytesPerLine());
    cvtColor(srcImage, srcImage, CV_RGB2BGR);                                   //将图像转换为BGR格式

    //文件存放路径
    string dir;
    dirPath = dirPath + QString::number(serialNum) + QString(".jpg");           //拼接最终人脸图像存放路径
    dir = dirPath.toStdString();


    //矩形对象，存放人脸区域图像
    vector<Rect> faces(0);                                                      //矩形向量,存放正脸
    vector<Rect> profile_faces(0);                                              //矩形向量,存放侧脸

    //正脸人脸数检测
    face_cascade->detectMultiScale(srcImage, faces, 1.1, 2, 0, Size(30, 30));   //将人脸区域存入矩形向量里面
    cout << "detect front face num: " << faces.size() << endl;                  //图片中只有一个人脸，faces.size()就是1


    //正脸处理
    if(faces.size() > 0)
    {
        *flag = 1;
        descriptTextLabel->setText(QString(QString::number(faces.size())));     //在标签上显示人脸数

        //截取人脸区域
        for(size_t i = 0; i < faces.size(); i++)
        {
            cout << "face size: " << faces[i] << endl;                          //显示人脸矩形区域大小

            faceCutImage = srcImage(Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height)); //将人脸区域部分图像截取出来
            imwrite(dir, faceCutImage);                                         //将截取出来的人脸区域图像存入本地face库
            rectangle(srcImage, faces[i], Scalar(150, 0, 0), 2, 8, 0);          //在原图像中将人脸区域用矩形框出来
        }

        frame = QImage(srcImage.data, srcImage.cols, srcImage.rows, srcImage.step, QImage::Format_RGB888);
        cout << "QImage has been create" << endl;
        if(!frame.isNull())
        {
            return 0;
        }
    }

    else
    {
            profileFace_cascade->detectMultiScale(srcImage, profile_faces, 1.1, 2, 0, Size(30, 30));    //检测侧脸，将人脸区域存入矩形对象中
            cout << "detect profile face num: " << profile_faces.size() << endl;                        //图片中只有一个人脸，faces.size()就是1
            if(profile_faces.size() > 0)                                                                //侧脸检测
            {
                *flag = 1;
                descriptTextLabel->setText(QString::number(profile_faces.size()));                      //在标签上显示人脸数
                for(size_t i = 0; i < profile_faces.size(); i++)                                        //截取人脸区域
                {
                    cout << "face size: " << profile_faces[i] << endl;                                  //显示人脸矩形区域大小
                    faceCutImage = srcImage(Rect(profile_faces[i].x, profile_faces[i].y, profile_faces[i].width, profile_faces[i].height)); //将人脸区域部分图像截取出来
                    imwrite(dir, faceCutImage);                                                         //将截取出来的人脸区域图像存入本地face库
                    rectangle(srcImage, profile_faces[i], Scalar(150, 0, 0), 2, 8, 0);                  //在原图像中将人脸区域用矩形框出来
                }
                frame = QImage(srcImage.data, srcImage.cols, srcImage.rows, srcImage.step, QImage::Format_RGB888);
            }
            else
            {
                *flag = 0;                                                                              //检测不到人脸，标志置为0
                descriptTextLabel->setText(QString("0"));                                               //显示人脸数为0
            }
    }


    return 0;
}

void faceDetect::run()
{
    //检测处理图像
    detect();

    //显示检测后的图像
    showLabel->setAlignment(Qt::AlignCenter);
    showLabel->setScaledContents(true);
    showLabel->setPixmap(QPixmap::fromImage(frame.rgbSwapped()));
}




