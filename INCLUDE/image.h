#ifndef IMAGE_H
#define IMAGE_H

#include "head.h"
#include "svga.h"
#include "mouse.h"

#include "bmp.h"	//基础库
#include "pic.h"	//图形库
#include "box.h"	//窗口库
#include "color.h"	//色彩库


//图像放缩
int ImageZoom(BMPATTR* bmpattr, double times, u8 patton);
int ImageXY(int* position, int boundary, int origin);
u32 ImageRGB(int x1, int x2, int y1, int y2, double x, double y, u8 patton);

//图像文件放缩
int ImageFileZoom(FILEATTR fileattr);
u32 ImageFileRGB(FILE* fp, int x1, int x2, int y1, int y2, double x, double y, u32 linebytes, u16 h);

int ImageTailor(BMPATTR *bmpattr);	//图像裁剪
int ImageRot(BMPATTR* bmpattr);		//图像旋转
int ImageMirror(BMPATTR bmpattr);	//图像镜像

int ImageContrast(BMPATTR bmpattr, int value);	//图像对比度
u8 ContrastCalc(u8 color, int value);			//图像对比度计算
int ImageSaturation(BMPATTR bmpattr, int value);//图像饱和度
int ImageLightness(BMPATTR bmpattr,int value);	//图像亮度
//int ImageAdjustment(BMPATTR* bmpattr);//图像调整


int ImageZoomSet(u8* patton);		//模式选择


#endif
