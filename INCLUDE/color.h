#ifndef COLOR_H
#define COLOR_H

#include "head.h"
#include "svga.h"
#include "mouse.h"

#include "bmp.h"	//基础库
#include "text.h"	//文本库
//#include "box.h"	//窗口库

void DrawColorBox(void);

int SelectColor(u32* color);							//选色操作

int FreshColor(u32 color, HSL* nowhsl);					//初始信息
int RefreshColor(HSL hsl, u32* nowcolor);				//刷新信息

RGB* U32TRGB(RGB* rgb, u32 color);						//U32 to RGB
u32 RGB2U32(u8 r, u8 g, u8 b);							//RGB to U32
int HSL2RGB(RGB* rgb, HSL hsl);							//HSL to RGB
int RGB2HSL(RGB rgb, HSL*hsl);							//RGB to HSL
double ToRGB(double p, double q, double tC);			//HSL2RGB的子级函数

int PickColor(u32* color);						//拾色器

#endif


