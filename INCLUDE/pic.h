#ifndef PIC_H
#define PIC_H

#include "svga.h"
#include "head.h"
#include "bmp.h"

int ImgRectangle(int x1, int y1, int x2, int y2, u32 color, u8 size);	//画矩形
int ImgLine(BMPATTR bmpattr, int x1, int y1, int x2, int y2, u32 color, u8 size); //画直线
int Line(int x1, int y1, int x2, int y2, u32 color, u8 size);//画直线（界面）
int ImgTriangle(BMPATTR bmpattr, int x1, int y1, int x2, int y2, int x3, int y3, u32 color, u8 size); //画三角形
int Triangle(int x1, int y1, int x2, int y2, int x3, int y3, u32 color, u8 size);//画三角形（界面）
int ImgCircle(BMPATTR bmpattr, int x, int y, int r, u32 color, u8 size); //画圆
int Circle(int x, int y, int r, u32 color, u8 size);//画圆（界面）
void DrawImgCircle_8(BMPATTR bmpattr, int x, int y, int a, int b, u32 color, u8 size); //圆的八对称性
void DrawCircle_8(int x, int y, int a, int b, u32 color, u8 size);//圆的八对称性（界面）
int ImgDrawPixel(BMPATTR bmpattr, int x, int y, u32 color, u8 size);	//画点
int DrawPixel(int x, int y, u32 color, u8 size);					//画点（界面）

#endif