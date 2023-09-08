/*******************************************************************
 * @Descripttion   : Ctrl+C -> Ctrl+V
 * @version        : 3.14
 * @Author         : Rjie
 * @Date           : 2023-09-07 18:51
 * @LastEditTime   : 2023-09-07 18:52
 *******************************************************************/
#ifndef __MAP_H__
#define __MAP_H__
void init_lcd();
void show_24_bmp(const char *path);
void show_led_bmp(int num, int status);
void show_buzzer_bmp(int status);
void show_alarm_bmp(int status);
#endif