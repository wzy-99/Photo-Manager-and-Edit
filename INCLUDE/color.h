#ifndef COLOR_H
#define COLOR_H

#include "bmp.h"
#include "head.h"
#include "svga.h"
#include "mouse.h"
#include "text.h"

void DrawColorBox();

int SelectColor(u32* color);							//选色操作

int FreshColor(u32 color, u32* nowcolor, HSL* nowhsl);	//初始化信息
int RefreshColor(HSL hsl, u32* nowcolor);				//刷新信息

u32 RGB2U32(u8 r, u8 g, u8 b);							//RGB to U32
int HSL2RGB(u8* r, u8* g, u8* b, HSL hsl);				//HSL to RGB
int RGB2HSL(RGB rgb, int* h, double* s, double* l);		//RGB to HSL
double ToRGB(double p, double q, double tC);			//HSL2RGB的子级函数

#endif


