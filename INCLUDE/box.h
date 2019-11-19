#ifndef BOX_H
#define BOX_H

#include "head.h"
#include "svga.h"
#include "mouse.h"

#include "pic.h"
#include "text.h"
#include "bmp.h"
#include "color.h"
#include "file.h"

#include "mix.h"


int WarnBox(char* error);

void DrawSFXBox(void);
void DrawNewBox(void);
void DrawOpenBox(void);
void DrawSaveBox(void);
void DrawListBox(void);
void DrawSizeBox(void);
void DrawAdjustBox(void);
void DrawShadingBox(void);

void DrawZoomSettingBox(u8 patton);

void Welcome(void);

int Exit(BMPATTR* bmpattr);							//³ÌÐòÍË³ö

#endif
