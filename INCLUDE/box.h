#ifndef BOX_H
#define BOX_H

#include "head.h"
#include "svga.h"
#include "mouse.h"

//#include "pic.h"
#include "text.h"
#include "bmp.h"


int WarnBox(char* error);

void DrawNewBox(void);
void DrawOpenBox(void);
void DrawSaveBox(void);
void DrawListBox(void);
void DrawSizeBox(void);

void DrawZoomSettingBox(u8 patton);


#endif
