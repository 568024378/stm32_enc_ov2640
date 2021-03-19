#include "csvfile.h"

CSVfile::CSVfile()
{
    fd = open(CSVFilePath,O_CREAT|O_WRONLY|O_TRUNC,0666);
    if(fd == -1)    //每次打开文件都清空，重写，csv文件每次都重新生成
    {
        printf("open file failed\n");
        printf("Message : %s\n", strerror(errno));
        return;
    }
}

void CSVfile::print_file_info(char *pathname)
{
    //获取结点信息
    struct stat filestat;
    if(stat(pathname, &filestat) == -1)
    {
        printf("cannot access the file %s\n", pathname);
        return;
    }

    //打印结点信息
//  printf("%s  %ld\n", pathname, filestat.st_size);

    //如果是目录，递归调用
    if((filestat.st_mode & S_IFDIR) == S_IFDIR)
    {
        dir_order(pathname);
    }
    else
    {   //将文件和具体路径拼接一起，然后将文件路径写入csv文件
        char *ptr = NULL;
        char temp[MAX_PATH] = {0};
        char num[4] = {0};
        strcpy(temp, pathname);
        ptr = strrchr(temp, '/');   //取出每个人脸目录名，格式为s+编号
        *ptr = 0;
        while(*ptr != 's')          //取出编号
            ptr--;
        ptr++;
        strcpy(num, ptr);           //存放编号
        //printf("num: %s\n", num);
        sprintf(temp, "%s;%s\n", pathname, num);    //拼接成csv文件格式
        write(fd, temp, strlen(temp));              //写入文件里面
    }
}

void CSVfile::dir_order(char *pathname)
{
    DIR *dp;
    char name[MAX_PATH] = {0};
    struct dirent *entry;
    //打开目录
    if((dp = opendir(pathname)) == NULL)
    {
        printf("dir_order:cannot open %s\n  %s", pathname, strerror(errno));
        return;
    }
    //读取目录
    while((entry = readdir(dp)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0  ||  strcmp(entry->d_name, "..") == 0)
            continue;

        if(strlen(pathname) + strlen(entry->d_name) + 2  >  sizeof(name))       //判断路径是否太长，考虑上一个空格和一个结束符
            printf("dir_order:name %s %s too long\n", pathname, entry->d_name);
        else
        {
            memset(name, 0, sizeof(name));
            sprintf(name, "%s/%s", pathname, entry->d_name);
            print_file_info(name);
        }
    }

    closedir(dp);
}

void CSVfile::run()
{
    qDebug()<<"csvfile running-------->";
    printf("FaceDataPath:%s\n", FaceDataPath);
    print_file_info(FaceDataPath);
    close(fd);
}



