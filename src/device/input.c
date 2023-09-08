/*******************************************************************
 * @Descripttion   : Ctrl+C -> Ctrl+V
 * @version        : 3.14
 * @Author         : Rjie
 * @Date           : 2023-09-07 18:49
 * @LastEditTime   : 2023-09-08 17:26
 *******************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include "input.h"

/*
1
2
3
4
*/
int get_xy_s(int *x, int *y)
{
    int ty, tx;
    int fd = open("/dev/input/event0", O_RDWR);
    if (fd < 0)
    {
        perror("open touch fail:");
        return -1;
    }
    while (1)
    {
        struct input_event xy;
        while (1)
        {
            read(fd, &xy, sizeof(xy));
            if (xy.type == EV_ABS)
            {
                xy.code == REL_X ? (*x = xy.value * 800 / 1024) : (*y = xy.value * 480 / 600);
                printf("(%d,%d)\n", *x, *y);
            }
            if (xy.type == EV_KEY && xy.code == BTN_TOUCH)
            {
                // printf("touch %d\n",xy.value);
                if (xy.value == 1)
                {
                    // printf("press\n");
                    tx = *x;
                    ty = *y;
                }
                if (xy.value == 0)
                {
                    // printf("up\n");
                    // 左
                    if ((*x - tx < -50))
                        return 1;
                    // 右
                    if ((*x - tx > 50))
                        return 2;
                    // 上
                    if (*y - ty < -50)
                        return 3;
                    // 下
                    if (*y - ty > 50)
                        return 4;
                    // printf("%s%s\n", (x - tx == 0) ? "" : (x - tx < 0) ? "左": "右",(y - ty == 0) ? "" : (y - ty < 0) ? "上" : "下");
                    return 0;
                }
            }
        }
    }
    close(fd);
}

// int main(){
//     int x=0,y=0,s=0;
// s=get_xy_s(&x,&y);
// printf("%d\n",s);
// }