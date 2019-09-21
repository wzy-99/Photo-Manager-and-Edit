#ifndef MOUSE_h
#define MOUSE_h

#include "head.h"
#include "svga.h"

typedef struct
{
	int x;
	int y;
	int button;
} MOUSE;

extern unsigned int MouseInit(void);

extern void MouseRange(int x1, int y1, int x2, int y2);

extern int MouseStatus(MOUSE* mouse);

extern int MouseDown(int x1, int y1, int x2, int y2);

extern void MouseStoreBk(int x, int y);

extern void MousePutBk(int x, int y);

extern void MouseReset(void);

extern void MouseDraw(MOUSE mouse);

extern int MouseUp(int x1, int y1, int x2, int y2);

#endif