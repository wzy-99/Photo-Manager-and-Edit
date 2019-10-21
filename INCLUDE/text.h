#ifndef TEXT_H
#define TEXT_H

#include "head.h"
#include "svga.h"


int TextASC24(int x, int y, int part, u32 color, unsigned char* str);	//宋体24位
int TextASC16(int x, int y, int part, u32 color, unsigned char* str);	//宋体16位
int TextASC12(int x, int y, int part, u32 color, unsigned char* str);	//宋体24位
int TextGB16(int x, int y, int part, u32 color, unsigned char* str);	//宋体16位 支持英文和汉字
int TextGB32(int x, int y, int part, u32 color, unsigned char* str);	//黑体32位 只支持汉字
int TextGB64(int x, int y, int part, u32 color, unsigned char* str, int delayus);	//潭体64位 只支持汉字
int TextASC64(int x, int y, int part, u32 color, unsigned char* str, int delayus);	//粉笔64位
int TextASC128(int x, int y, int part, u32 color, unsigned char* str, int delayus); //粉笔128位

#endif
