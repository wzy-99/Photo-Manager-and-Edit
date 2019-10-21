#ifndef BOX_H
#define BOX_H

#define CharColor 
#define ColorStart 0x7ecef4
//#define ColorEnd 

#include "head.h"
#include "svga.h"
#include "mouse.h"

#include "pic.h"
#include "text.h"
#include "bmp.h"
#include "color.h"


int WarnBox(char* error);

void DrawNewBox(void);
void DrawOpenBox(void);
void DrawSaveBox(void);
void DrawListBox(void);
void DrawSizeBox(void);
void DrawAdjustBox(void);

void DrawZoomSettingBox(u8 patton);

void Welcome();


#endif
