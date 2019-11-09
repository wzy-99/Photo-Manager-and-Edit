#include "head.h"
#include "svga.h"
#include "mouse.h"
#include "menu.h"

void main()
{
	SetSVGA();		//初始化SVGA
	MouseReset();	//初始化MOUSE
	Welcome();		//Weclome界面
	DrawMenu();		//WorkSpace界面
	MenuManager();	//消息管理机制
}