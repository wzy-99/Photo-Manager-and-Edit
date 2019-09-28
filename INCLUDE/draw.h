#ifndef DRAW_H
#define DRAW_H

#include "head.h"
#include "svga.h"

#include "bmp.h"
#include "mouse.h"
#include "pic.h"
#include "box.h"
#include "color.h"

void DrawSizeBox(void);

int SelectSize(u8* size1, u8* size2);								//选择绘制规格

int DrawPen(BMPATTR bmpattr, MENUSTATE* state);						//画笔
int DrawPixel(BMPATTR bmpattr, int x, int y, u32 color, u8 size);	//画点



#endif