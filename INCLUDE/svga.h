#ifndef SVGA_H
#define SVGA_H

#include"head.h"

void SetSVGA(void);
u32 GetPixel(int x, int y);
void SelectPage(register u8 page);
void PutPixel(int x, int y, u32 color);
void Bar(int x1, int y1, int x2, int y2, u32 color);

//void Line(int x1, int y1, int x2, int y2, u32 color);
//void SetLogicalLine(u16 pixels);

#endif