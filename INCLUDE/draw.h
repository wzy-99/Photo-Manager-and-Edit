#ifndef DRAW_H
#define DRAW_H

#include "head.h"
#include "svga.h"
#include "mouse.h"	

#include "bmp.h"	//Í¼Ïñ»ù´¡¿â
#include "pic.h"	//Í¼ÐÎ¿â
#include "box.h"	//´°¿Ú¿â
#include "color.h"	//É«²Ê¿â



int SelectSize(u8* size1, u8* size2);								//Ñ¡Ôñ»æÖÆ¹æ¸ñ

int DrawPen(BMPATTR bmpattr, MENUSTATE* state);						//»­±Ê
int DrawPixel(BMPATTR bmpattr, int x, int y, u32 color, u8 size);	//»­µã



#endif