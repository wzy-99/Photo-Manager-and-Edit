#include "head.h"
#include "svga.h"
#include "menu.h"
#include "text.h"
#include "bmp.h"
#include "color.h"


void main()
{
	SetSVGA();
	MouseReset();
	DrawMenu();
	MenuManager();
	getch();
}