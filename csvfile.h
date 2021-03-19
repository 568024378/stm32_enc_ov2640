#ifndef CSVFILE_H
#define CSVFILE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <QThread>
#include <QDebug>

#define MAX_PATH 128

#define CSVFilePath "/var/face_system/csvfile/pathLabel.csv"
//#define FaceDataPath "/var/face_system/facedata/"

#define FaceDataPath                "/var/face_system/facedata/"
#define ColorFacePath               "/var/face_system/colorface/"


class CSVfile : public QThread
{
public:
    CSVfile();
    void print_file_info(char *pathname);           //获取文件路径
    void dir_order(char *pathname);                 //递归遍历目录
    void run();

private:
    int fd;                                         //文件描述符
};

#endif // CSVFILE_H
