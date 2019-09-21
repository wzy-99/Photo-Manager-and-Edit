#ifndef IMAGE_H
#define IMAGE_H

#include "head.h"
#include "svga.h"
#include "menu.h"
#include "bmp.h"

int ImageZoom(BMPATTR* bmpattr, double times, u8 patton);
int ImageXY(int* position, int boundary, int origin);
u32 ImageRGB(int x1, int x2, int y1, int y2, double x, double y, u8 patton);
int ImageTailor(BMPATTR *bmpattr);
int ImageRot(BMPATTR* bmpattr);
int ImageMirror(BMPATTR bmpattr);
int ImageFileZoom(FILEATTR fileattr);
u32 ImageFileRGB(FILE* fp, int x1, int x2, int y1, int y2, double x, double y, u32 linebytes, u16 h);
void DrawSettingBox(u8 patton);
int ImageZoomSet(u8* patton);


#endif
