#ifndef MENU_H
#define MENU_H

#include "head.h"
#include "svga.h"
#include "mouse.h"
#include "bmp.h"
#include "file.h"
#include "image.h"

//菜单状态变量
typedef struct {
	u8 size;		//画笔大小
	u8 size2;		//图形大小
	u8 patton;		//放大模式	1双线性内插法 0临近点插值法
	u32 color;		//颜色
} MENUSTATE;



void DrawMenu();
void MenuManager();

#endif
