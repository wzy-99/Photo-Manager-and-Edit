#include "box.h"

int WarnBox(char* error)
{
	double lenth = strlen(error) / 4.0;
	int x = SCR_WIDTH / 2 - lenth * 40;
	MOUSE mouse_old, mouse_new;
	BmpSave(248, 198, 552, 352, "UI//temp3");
	BmpPut(248, 198, "UI//ERROR");
	TextGB32(x, 260, 40, 0, error);
	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
	MouseDraw(mouse_old);
	while (1)
	{
		MouseStatus(&mouse_new);
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_old.button == mouse_new.button)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);
			MouseStoreBk(mouse_new.x, mouse_new.y);
			MouseDraw(mouse_new);
			mouse_old = mouse_new;
			if (MouseDown(250, 320, 405, 350))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "UI//temp3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 1;
			}
			else if (MouseDown(405, 320, 550, 350))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "UI//temp3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 0;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "UI//temp3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 0;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//ÍË³ö
				exit(0);
			}
			else
			{
				;
			}
		}
	}
}