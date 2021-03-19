#include "facerecognize.h"


double sysThreshold = 100.0;
int LBPHradius = 1;
int LBPHneighbors = 8;
int LBPHgridx = 8;
int LBPHgridy = 8;

facerecognize::facerecognize(QLabel *pshowLabel, QLabel *pSerialNumLabel, QLabel *pdetectLB, Ptr<Facemark> parafacemark,int *num,double *predictRate)
{
    ptrShowLabel = pshowLabel;
    ptrSerialNumLabel = pSerialNumLabel;
    ptrdetectLb = pdetectLB;
    facemark = parafacemark;

    pnum = num;
    pRate = predictRate;
}


int facerecognize::recognizeFace()
{
    //判断是否有用户注册
    QFile modFile(LBPHModelFile);
    if(!modFile.exists())
    {
        ptrShowLabel->setText("还没有用户注册，请注册再使用！");
        return 0;
    }

    //建立LBPHFace模型
    Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create(LBPHradius, LBPHneighbors, LBPHgridx, LBPHgridy);

    //读取训练文件,需要花费较长时间
    model->read(LBPHModelFile);


    cout<<"234"<<endl;


    QString dir = "/var/face_system/picTake/1.jpg";

    Mat srcImage, predictImage;
    Mat equalImage, warpAFFImg;

    //定义人脸关键点容器
    vector< vector<Point2f> > landmarks;

    //加载特征图像
    srcImage = imread(dir.toStdString(), 0);

    //定义矩形对象并添加到vector（数组）
    Rect convtImgRt(0, 0, srcImage.cols, srcImage.rows);
    faces.push_back(convtImgRt);

    //运行人脸关键点检测器
    facemark->fit(srcImage, faces, landmarks);

    cout<<"1"<<endl;
    //仿射变换处理
    for(unsigned int i = 0; i < landmarks.size(); i++)
    {
        warpAFFImg = getwarpAffineImg(srcImage, landmarks[i]);
    }
    cout<<"2"<<endl;

    //对图像进行均衡化处理
    equalizeHist(warpAFFImg, equalImage);
    //更改图像的大小
    resize(equalImage, predictImage, Size(92, 112));

    //定义预测标签号
    int predictNumber = -1;
    //定义预测准确率
    double confidence = 0.0;

    //预测解析处理
    model->predict(predictImage, predictNumber, confidence);
    cout << "way 2 predict label: " << predictNumber << endl;
    cout << "way 2 predict confidence: " << confidence << endl;

    *pnum = predictNumber;
    *pRate = confidence;

    return predictNumber;
}


//实现仿射变换
Mat facerecognize::getwarpAffineImg(Mat &src, vector<Point2f> &landmarks)
{
    Mat oral;
    src.copyTo(oral);
    for(unsigned int j = 0; j < landmarks.size(); j++)
    {
        circle(oral, landmarks[j], 2, Scalar(255, 0, 0));
    }

    //计算两眼中心，按照此点旋转，第36个为左眼坐标，42为右眼坐标
    Point2f eyesCenter = Point2f((landmarks[leftEye].x+landmarks[rightEye].x)*0.5f, (landmarks[leftEye].y+landmarks[rightEye].y)*0.5f);
    double dy = (landmarks[rightEye].y - landmarks[leftEye].y);
    double dx = (landmarks[rightEye].x - landmarks[leftEye].x);
    double angle = atan2(dy, dx)*180.0/CV_PI;

    //获得旋转矩阵
    Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, 1.0);
    Mat rot;

    //实现一些简单的重映射
    warpAffine(src, rot, rot_mat, src.size());

    return rot;
}

void facerecognize::run()
{
    recognizeFace();
}

