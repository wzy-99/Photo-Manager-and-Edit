#ifndef TEXT_H
#define TEXT_H

#include "head.h"
#include "svga.h"

int TextASC24(int x, int y, int part, u32 color, unsigned char* str);
int TextASC16(int x, int y, int part, u32 color, unsigned char* str);
int TextASC12(int x, int y, int part, u32 color, unsigned char* str);
int TextGB16(int x, int y, int part, u32 color, unsigned char* str);
int TextGB32(int x, int y, int part, u32 color, unsigned char* str);

#endif
