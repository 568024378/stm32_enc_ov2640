#ifndef RECONGNIZEWIN_H
#define RECONGNIZEWIN_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include "fV4l2.h"
#include "facedetect.h"
#include "facerecognize.h"
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#define LPFModelPath        "/var/face_system/lbfmodel.yaml"

//注册声明 -------------------------------------------------------------------------------
#include <QImage>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <sys/types.h>
#include <sys/stat.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/face.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "csvfile.h"

#include <QTcpSocket>

using namespace std;
using namespace cv;
using namespace cv::face;



#define PCAModelFile                "/var/face_system/model/PCAModelState.xml"
#define LBPHModelFile               "/var/face_system/model/LBPHModelState.xml"
//---------------------------------------------------------------------------------------



namespace Ui {
class recongnizeWin;
class registerWin;
}

class recongnizeWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit recongnizeWin(QWidget *parent = 0);
    ~recongnizeWin();

    QString createNewDir(void);                             //创建新的目录存放人脸图像
    int getFaceSequence(void);                              //获取当前人脸库编号最大的数字
    //void image_sampler(void);
    int faceImagePrevProc(void);                            //人脸图像预处理函数
    int registerFace(void);                                //人脸数据训练
    void read_csv(const string &filename, vector<Mat> &images, vector<int> &labels, char separator = ';');

    void newRegister_prepare(void);

    void mytcpclose();

private slots:
    void detect_showHide();
   //void video_show();

    void on_takephotoButton_clicked();
    void on_registerButton_clicked();

    //定义注册相关函数
    void returnButton_handler(void);
    void trainButton_handler(void);
    void samplerButton_handler(void);
    void cancelRegister_handler(void);



private:
    Ui::recongnizeWin *ui;
    Ui::registerWin *rui;

    QTcpSocket * tcpSocket;

    // -------------------------------
    // 定时从stm32读图像
    //
    QString fileName ;  //
    qint64 fileSize ;
    qint64 recvSize ;

    QByteArray data ;
    QByteArray framebuffer ; // 保存有效jpeg数据流

    QTimer timer ;
    volatile bool isStart;

    // --------------------------------
    QThread *detectThread;
    QThread *recognizeThread;


    CascadeClassifier frontface;        //正脸检测级联分类器
    CascadeClassifier profileface;      //侧脸检测级联分类器
    Ptr<Facemark> facemark;             //定义Ptr智能指针


    QTimer mtimer;
    QTimer *showtimer;


    //下面定义注册界面变量
    QWidget *reg;
    volatile bool switch_flag;

    QThread *detectThread1;              //faceDetect对象，检测获取人脸图像
    QThread *createCSVThread;           //每次注册重新生成CSV文件
    QImage image;                       //存放从camera获取的图像
    QString newDirName;                 //新的人脸存放目录
    int photoNum;                       //说明是第几张图片




};

#endif // RECONGNIZEWIN_H
