#include "fMenu.h"
#include "ui_fMenu.h"
#include "ui_register.h"

#include <QHostAddress>

extern double sysThreshold;
extern int LBPHradius;          //1
extern int LBPHneighbors;       //8
extern int LBPHgridx;           //8
extern int LBPHgridy;           //8

recongnizeWin::recongnizeWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::recongnizeWin),
    rui(new Ui::registerWin)
{
    ui->setupUi(this);

    //1. 加载正脸检测分类器
    if(!frontface.load(FRONT_CASCADE))
    {
        cout << "front cascade file load failed." << endl;
    }


    //1. 加载侧脸检测分类器
    if(!profileface.load(PROFILE_CASCADE))
    {
        cout << "profile cascade file load failed." << endl;
    }

    //2. 创建Facemark类的对象
    facemark = FacemarkLBF::create();

    //3. 加载人脸关键点检测器模型
    facemark->loadModel(LPFModelPath);
    //cout << "facemark model load success." << endl;

    ui->detectLabel->hide();

    showtimer = new QTimer();
    connect(showtimer, SIGNAL(timeout()), this, SLOT(detect_showHide()));


    //camera.linux_v4l2_device_init("/dev/video0");
    //camera.linux_v4l2_stream_start();

    switch_flag = true;

    //定义注册界面
    photoNum = 1;                                                   //初始值为1，第一张图片
    createCSVThread = new CSVfile();                                //创建生成csv文件的线程






    tcpSocket = new QTcpSocket(this);

    isStart = true;

    connect(tcpSocket , &QTcpSocket::readyRead,
            [=](){

            QByteArray buf = tcpSocket->readAll();

            if(true == isStart){

                // first open file
                isStart = false;
                // 打开文件

                fileSize = QString(buf).section("\n" , 0 , 0).toInt();
                recvSize = 0;
                data.clear();
                // qDebug() << "fileSize:" << fileSize;
                tcpSocket->write("GET Body");
                //file.setFileName("hello.jpg");

               // bool isOk = file.open(QIODevice::WriteOnly);
                //if( false == isOk ){
               //     qDebug() << "WriteOnly error " << __LINE__ ;
               // }


            }else{
                qint64 len = buf.size();
                data.push_back(buf);
                recvSize += len;
                if( recvSize == fileSize ){
                    // file.close();
                    //qDebug() << "file wancheng data :" << data.size();
                    tcpSocket->disconnectFromHost();
                    tcpSocket->close();
                    isStart = true;
                    QPixmap pix ;
                    pix.loadFromData(data , "JPG");
                    if(switch_flag)
                    {
                        //播放识别界面
                        ui->camShow_lb->setAlignment(Qt::AlignCenter);
                        pix.scaled( ui->camShow_lb->width(), ui->camShow_lb->height(),Qt::KeepAspectRatio);
                        ui->camShow_lb->setScaledContents(true);
                        ui->camShow_lb->setPixmap(pix);
                    }
                    else
                    {
                        //添加图片自适应窗口功能
                        rui->displayLabel->setAlignment(Qt::AlignCenter);
                        pix.scaled(rui->displayLabel->width(),rui->displayLabel->height(),Qt::KeepAspectRatio);
                        rui->displayLabel->setScaledContents(true);
                        //播放注册界面
                        rui->displayLabel->setPixmap(pix);
                    }
                    timer.start(20);
                }
                else if( recvSize > fileSize ){ //  rong cuo chuli

                    tcpSocket->disconnectFromHost();
                    tcpSocket->close();
                    isStart = true;
                    timer.start(20);
                }
            }

    });

    connect(&timer , &QTimer::timeout ,
            [=](){
        //if(connectflag){
            timer.stop();
            tcpSocket->connectToHost(QHostAddress("192.168.1.119"),8088);
            tcpSocket->write("GET Header");

        //}
    });

    timer.start(50);

    //mtimer = new QTimer();
    //connect(mtimer, SIGNAL(timeout()), this, SLOT(video_show()));
    //mtimer->start(50);
}


void recongnizeWin::mytcpclose(){

    timer.stop();

    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    isStart = true;

}

recongnizeWin::~recongnizeWin()
{
    delete ui;
    //camera.linux_v4l2_device_release();
}

void recongnizeWin::detect_showHide()
{
    showtimer->stop();
    ui->detectLabel->hide();
}


void recongnizeWin::on_takephotoButton_clicked()
{
    mytcpclose();       //关闭tcp线程
    int number;
    double rate;

    // FreamBuffer Frame;
    int isHaveFace = 0;
    QImage image;
    QString dir = "/var/face_system/picTake/";

    //拍取一张照片
    //camera.linux_v4l2_get_one_frame(&Frame);
    image = ui->camShow_lb->pixmap()->toImage();
    while(image.isNull());

    //人脸检测处理
    detectThread = new faceDetect(&frontface, &profileface, ui->detectLabel, ui->faceNumLabel, image, &isHaveFace, 1, dir);
    detectThread->start();
    detectThread->wait();

    if(isHaveFace)
    {
        //人脸识别处理
        recognizeThread = new facerecognize(ui->recResultLabel, ui->serialNumLabel, ui->detectLabel, facemark,&number,&rate);
        recognizeThread->start();
        recognizeThread->wait();

        cout<<"number: "<<number<<endl;
        cout<<"rate: "<<rate<<endl;

        QString colorfile = QString("/var/face_system/colorface/") + QString("s")
                + QString::number(number) + QString(".jpg");

        //如果预测率小于预测阈值
        if(rate < sysThreshold)
        {
            ui->recResultLabel->setAlignment(Qt::AlignCenter);
            ui->recResultLabel->setScaledContents(true);
            ui->recResultLabel->setPixmap(QPixmap(colorfile));

            ui->serialNumLabel->setText(QString::number(number));
        }
        else
        {
            ui->recResultLabel->clear();
            ui->recResultLabel->setText("?");
        }
    }
    else
    {
        ui->recResultLabel->setText("无效数据，请正对摄像头！");
        ui->serialNumLabel->clear();
    }

    showtimer->start(20);
    timer.start(20);            // 重新打开tcp线程
}

//打开用户人脸注册界面
void recongnizeWin::on_registerButton_clicked()
{
    mytcpclose();
    //显示注册界面
    reg = new QWidget();
    rui->setupUi(reg);
    reg->show();

    //识别主界面隐藏
    this->hide();

    //播放注册界面
    switch_flag = false;

    connect(rui->returnButton, SIGNAL(clicked()), this, SLOT(returnButton_handler()));
    connect(rui->trainButton, SIGNAL(clicked()), this, SLOT(trainButton_handler()));
    connect(rui->samplerButton, SIGNAL(clicked()), this, SLOT(samplerButton_handler()));

    connect(rui->cancelReg_bt, SIGNAL(clicked()), this, SLOT(cancelRegister_handler()));

    //设置按键的开启状态
    rui->samplerButton->setDisabled(true);
    rui->trainButton->setDisabled(true);
    rui->returnButton->setDisabled(true);


    //设置初始提示信息
    rui->noticeLabel->setText("请点击“注册用户”，开始新用户注册过程....");


    //注册新用户准备--创建新用户目录
    newRegister_prepare();



    QString group_style(
                "QGroupBox{border:2px solid rgb(80,80,80);border-radius:5px;margin-top:12px;}"
                //"QGroupBox:title {color:rgb(28,151,234);subcontrol-origin: margin; left: 10px;}"
                "QGroupBox:title {color:rgb(255,255,255);subcontrol-origin: margin; left: 10px;}"
                );

    rui->userInfo_gb->setStyleSheet(group_style);
    rui->opsTips_gb->setStyleSheet(group_style);
    rui->realChan_gb->setStyleSheet(group_style);

    timer.start(20);
}

//返回识别主界面
void recongnizeWin::returnButton_handler()
{
    mytcpclose();
    this->show();

    reg->close();
    delete reg;
    switch_flag = true;
    timer.start(20);
}

//=============================注册新用户（训练新数据）===================================
//开始注册新用户
void recongnizeWin::newRegister_prepare(void)
{
    //创建新人脸的目录
    newDirName = createNewDir();
    qDebug()<<"new dir name: "<<newDirName;

    rui->samplerButton->setDisabled(false);

    rui->noticeLabel->setText("请点击“人脸采样”，开始图像数据采集过程....");
}


QString recongnizeWin::createNewDir()
{
    int serialNum = getFaceSequence() + 1;                          //获取当前人脸库里面有多少个人的信息，从下一个编号创建新的人脸目录
    QString fileName = QString(FaceDataPath) + QString("s") + QString::number(serialNum);   //拼接新的目录名
    string dir = fileName.toStdString();                            //将QString类型的路径转为String类型的路径

    if(mkdir(dir.c_str(), 0666) < 0)                                //创建新的目录
    {
        cout << "make directory failed" << endl;
        return "";
    }

    rui->serialNumLabel->setText(QString::number(serialNum));        //将编号在标签上显示
    return fileName + QString("/");                                 //返回新的目录路径
}


int recongnizeWin::getFaceSequence()                 //获取当前人脸库编号最大的数字
{
    int max = 1;                                    //如果还没有人脸，那么就返回1，新注册的编号就为1
    QString result;                                 //中间变量，临时存放目录名
    QDir distDir(FaceDataPath);                     //Qt操作目录对象
    QStringList list = distDir.entryList();         //获取目录下每个文件名，存入到QStringList

    if(list.size() == 2)                            //空目录下有. ..两个目录
        return 0;

    for(int i = 0; i < list.size(); i++)
    {
        result = list.at(i);
        if(result == "." || result == "..")
            continue;

        result.remove(0, 1);                        //将目录名第一个字母s去掉，获取编号
        if(result.toInt() > max)                    //将编号转为int型，更新到int里面
            max = result.toInt();
    }

    return max;
}

//取消注册处理
void recongnizeWin::cancelRegister_handler(void)
{
    mytcpclose();
    //删除注册目录
    QString file_path = newDirName;
    QDir dir;
    dir.setPath(file_path);
    dir.removeRecursively();

    //打开主界面
    this->show();
    //关闭注册界面
    reg->close();
    delete reg;
    switch_flag = true;
    timer.start(20);
}

//------------------------------------------------------------------



//图像采样
void recongnizeWin::samplerButton_handler(void)
{
    // FreamBuffer Frame;                                  //定义帧缓存结构体对象
    int ifHaveFace;                                     //人脸检测标志

    // camera.linux_v4l2_get_one_frame(&Frame);            //获取一帧图像
    mytcpclose();                                           // 关闭tcp线程
    QImage image = rui->displayLabel->pixmap()->toImage() ; //将从摄像头获取的一帧图像存入QImage对象
    while(image.isNull());


    detectThread = new faceDetect(&frontface, &profileface, rui->detectResultLabel, rui->faceNumLabel,
                                  image, &ifHaveFace, photoNum, newDirName);
    detectThread->start();
    detectThread->wait();

    if(ifHaveFace)
    {
        qDebug()<< "take a photo" << QString::number(photoNum);
        rui->noticeLabel->setText("[一共需要采样10张人脸像],当前采集图片为： 第 " + QString::number(photoNum) + " 张");
        photoNum++;
    }
    else
    {
        rui->noticeLabel->setText("没有检测到有效人脸图像，请调整姿态！");
    }

    if(photoNum > 10)
    {
        rui->noticeLabel->setText(QString("采集的人脸图像已达到10张，可以开始数据训练！"));
        rui->trainButton->setDisabled(false);
        rui->samplerButton->setDisabled(true);
        photoNum = 1;
    }
    timer.start(20);                                        // 重新打开tcp线程
}

//数据训练
void recongnizeWin::trainButton_handler()
{
    // int newFaceNum = getFaceSequence();
    mytcpclose();
    //对图像进行灰度等简单处理
    faceImagePrevProc();

    //csv文件(记录人脸图像及人脸图像对应标签)的生成
    createCSVThread->start();
    createCSVThread->wait();

    //开式训练数据
    if(registerFace() < 0)
    {
        qDebug() << "register face failed.";
        return;
    }

    rui->noticeLabel->setText(QString("用户注册成功，祝您使用愉快！"));
    QMessageBox::information(this, "提示", "用户注册成功，祝您使用愉快！");
    photoNum = 1;
    // mtimer->stop();
    // connectflag = false;

    rui->trainButton->setDisabled(true);
    rui->returnButton->setDisabled(false);

    timer.start(20);
}

//人脸图像预处理函数
int recongnizeWin::faceImagePrevProc()
{
    int newDirNum = getFaceSequence();              //获取新注册的编号
    QString dirName = QString(FaceDataPath) + QString("s") + QString::number(newDirNum);    //获取新注册人脸的目录

    qDebug()<<"newdirnum: "<<newDirNum;
    qDebug()<<"dirName: "<<dirName;

    QDir distDir(dirName);                          //打开目录
    QStringList list = distDir.entryList();         //存放文件路径

    QFile colorfile;
    QString result;
    QString openFile;
    Mat srcImage, dstImage;
    Mat cvtImage, equalImage;

    //在注册目录下(facedata/sx)将每张图片进行灰度化均衡化处理
    for(int i = 0; i < list.size(); i++)
    {
        result = list.at(i);
        if(result == "." || result == "..")
            continue;

        openFile = dirName + QString("/") + result;
        srcImage = imread(openFile.toStdString());
        cvtColor(srcImage, cvtImage, COLOR_BGR2GRAY);               //将拍摄到的图像灰度化
        equalizeHist(cvtImage, equalImage);                         //直方图均衡化，提高图像的质量
        cv::resize(equalImage, dstImage, Size(92, 112));
        imwrite(openFile.toStdString(), dstImage);
    }

    //将彩色人脸图像存到colorface目录里面，文件名为人脸目录名
    dirName = QString(ColorFacePath) + QString("s") + QString::number(newDirNum) + QString(".jpg");
    colorfile.setFileName(dirName);
    if(!colorfile.exists())
    {
        imwrite(dirName.toStdString(), srcImage);
        qDebug() << "color file save success.";
    }

    return 0;
}



/*
 * 人脸数据训练
 * 使用opencv的Facerecognizer类来训练模型,此类包含了所有的人脸识别模型
 */

int recongnizeWin::registerFace()
{
    string fn_csv;
    vector<Mat> images;
    vector<int> labels;

    fn_csv = string(CSVFilePath);

    try{
        read_csv(fn_csv, images, labels);
    }
    catch(Exception &e)
    {
        cerr << "Error opening file " << fn_csv << ".Reason " << e.msg << endl;
        return -1;
    }

    if(images.size() <= 1)
    {
        string error_message = "This demo needs at least 2 images, please check";
        CV_Error(CV_StsError, error_message);
        return -1;
    }

    //“特征脸”识别模型训练
    Ptr<FaceRecognizer> pcamodel = EigenFaceRecognizer::create();
    pcamodel->train(images, labels);
    pcamodel->write(PCAModelFile);

    //局部二值模式直方图模型训练
    Ptr<FaceRecognizer> lbphmodel = LBPHFaceRecognizer::create(LBPHradius, LBPHneighbors, LBPHgridx, LBPHgridy);
    lbphmodel->train(images, labels);
    lbphmodel->write(LBPHModelFile);
    qDebug() << "save model finished";
    return 0;
}


//读取csv文件,将图像和标签写入相应对象
void recongnizeWin::read_csv(const string &filename, vector<Mat> &images, vector<int> &labels, char separator)
{
    ifstream file(filename.c_str(), ifstream::in);
    if(!file)
    {
        string error_message = "No valid input file was given, please check.";
        CV_Error(CV_StsBadArg, error_message);
        return;
    }

    string line, path, classlabel;
    while(getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty())
        {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

