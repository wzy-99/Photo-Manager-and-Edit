#include "head.h"
#include "svga.h"
#include "menu.h"
#include "text.h"
#include "bmp.h"
#include "color.h"
#include "box.h"


void main()
{
	SetSVGA();
	MouseReset();
	//Welcome();
	DrawMenu();
	MenuManager();
}