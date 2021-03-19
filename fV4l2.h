#ifndef V4L2_H
#define V4L2_H

#include <stdio.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#include <string>
using namespace std;

#define BUFFERCOUNT 4
//#define PIXWIDTH    320
//#define PIXHEIGHT   240

#define PIXWIDTH    640
#define PIXHEIGHT   480

struct buffer{
    void *start;
    unsigned int length;
};


typedef struct Fream_Buffer
{
    //unsigned char buf[1843200];
    unsigned char buf[PIXHEIGHT*PIXWIDTH*3];
    int length;
}FreamBuffer;


class v4l2
{
public:
    v4l2();

    int linux_v4l2_device_init(string device_name);

    int linux_v4l2_set_format();

    int linux_v4l2_init_mmap();

    int linux_v4l2_stream_start();

    int linux_v4l2_get_one_frame(FreamBuffer *freambuf_t);

    int linux_v4l2_device_release();

private:
    int fd;
    struct buffer *buffers;
};

#endif // V4L2_H
