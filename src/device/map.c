/*******************************************************************
 * @Descripttion   : Ctrl+C -> Ctrl+V
 * @version        : 3.14
 * @Author         : Rjie
 * @Date           : 2023-09-07 18:49
 * @LastEditTime   : 2023-09-07 18:49
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //头文件: 对函数接口进行声明
#include <stdio.h>
#include <unistd.h>
#include "map.h"
char *lcd_p = NULL;
// rgb to  argb
char argb[800 * 4 * 480] = {0};
char rgb[800 * 480 * 3] = {0};
void init_lcd()
{

    int lcd = open("/dev/fb0", O_RDWR);
    if (lcd < 0)
    {
        perror("打开设备失败\n");
        exit(0);
    }
    // 2.对LCD 设备进行映射
    lcd_p = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);
    if (lcd_p == MAP_FAILED)
    {
        perror("映射失败\n");
        exit(0);
    }
}
void show_24_bmp(const char *path)
{
    int i = 0;
    int j = 0;
    if (lcd_p == NULL)
    {
        printf("lcd no inti!\n");
        exit(0);
    }

    // 1.open BMP  file
    int fd = open(path, O_RDWR);
    if (fd < 0)
    {
        printf("open bmp fail:\n");
        exit(0);
    }
    else
    {
        printf("open bmp ok\n");
    }

    char head[54];
    read(fd, head, 54);           // 把头数据读走
    read(fd, rgb, 800 * 480 * 3); // 读取像素数据

    // rgb to  argb
    for (i = 0; i < 800 * 480; i++)
    {
        argb[0 + i * 4] = rgb[0 + i * 3];
        argb[1 + i * 4] = rgb[1 + i * 3];
        argb[2 + i * 4] = rgb[2 + i * 3];
        argb[3 + i * 4] = 0;
    }

    // 翻转  Y 轴
    char f_argb[800 * 4 * 480] = {0};

    for (j = 0; j < 480; j++)
    {
        for (i = 0; i < 800 * 4; i++)
        {
            f_argb[j * 800 * 4 + i] = argb[(479 - j) * 800 * 4 + i];
        }
    }

    // 把翻转后的数据放入   lcd 设备中
    for (i = 0; i < 800 * 480 * 4; i++)
    {
        lcd_p[i] = f_argb[i];
    }

    // 回收资源

    close(fd);
}

void show_led_bmp(int num, int status)
{
    int i = 0;
    int j = 0;
    if (lcd_p == NULL)
    {
        printf("lcd no inti!\n");
        exit(0);
    }
    // rgb to  argb
    for (i = 0; i < 800 * 480; i++)
    {
        if (status && (190 < i / 800) && (i / 800 < 390) && (i % 800 < 210 + (num * 190)) && (i % 800 > 55 + (num * 180)))
            argb[i * 4] = 255;
        else if (!status && (190 < i / 800) && (i / 800 < 390) && (i % 800 < 210 + (num * 190)) && (i % 800 > 55 + (num * 180)))
            argb[i * 4] = rgb[i * 3];
    }

    // 翻转  Y 轴
    char f_argb[800 * 4 * 480] = {0};

    for (j = 0; j < 480; j++)
    {
        for (i = 0; i < 800 * 4; i++)
        {
            f_argb[j * 800 * 4 + i] = argb[(479 - j) * 800 * 4 + i];
        }
    }

    // 把翻转后的数据放入   lcd 设备中
    for (i = 0; i < 800 * 480 * 4; i++)
    {
        lcd_p[i] = f_argb[i];
    }
}
