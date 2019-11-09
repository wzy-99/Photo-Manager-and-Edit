#include "head.h"
#include "svga.h"
#include "mouse.h"
#include "menu.h"

void main()
{
	SetSVGA();
	MouseReset();
	Welcome();
	DrawMenu();
	MenuManager();
}