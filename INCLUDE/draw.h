#ifndef DRAW_H
#define DRAW_H

#include "head.h"
#include "svga.h"
#include "mouse.h"	

#include "image.h"
#include "bmp.h"	//图像基础库
#include "pic.h"	//图形库
#include "box.h"	//窗口库
#include "color.h"	//色彩库



int SelectSize(u8* size1, u8* size2);								//选择绘制规格

int DrawPen(BMPATTR* bmpattr, MENUSTATE* state);						//画笔
int DrawPicture(BMPATTR* bmpattr, MENUSTATE* state);					//画图
int DrawLine(BMPATTR* bmpattr, MENUSTATE* state);					//调用画线函数
int DrawTriangle(BMPATTR* bmpattr, MENUSTATE* state);				//调用画三角形函数
int DrawRectangle(BMPATTR* bmpatttr, MENUSTATE* state);				//调用画矩形函数
int DrawCircle(BMPATTR* bmpattr, MENUSTATE* state);					//调用画圆函数




#endif