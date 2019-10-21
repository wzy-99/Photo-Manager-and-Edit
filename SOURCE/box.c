#include "box.h"

int WarnBox(char* error)
{
	double lenth = strlen(error) / 4.0;
	int x = SCR_WIDTH / 2 - lenth * 40;
	MOUSE mouse_old, mouse_new;
	BmpSave(248, 198, 552, 352, "DATA//BK3");
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
				BmpPut(248, 198, "DATA//BK3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 1;
			}
			else if (MouseDown(405, 320, 550, 350))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 0;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 0;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
			else
			{
				;
			}
		}
	}
}

void DrawZoomSettingBox(u8 patton)
{
	BmpPut(248, 198, "UI/ZOOM");

	if (patton)
	{
		Bar(455, 265, 465, 275, 0);
		Bar(455, 315, 465, 325, White);
	}
	else
	{
		Bar(455, 265, 465, 275, White);
		Bar(455, 315, 465, 325, 0);
	}
}

void DrawOpenBox()
{
	BmpPut(248, 198, "UI//OPEN");
}

void DrawNewBox()
{
	BmpPut(248, 198, "UI//NEW");
}

void DrawSaveBox()
{
	BmpPut(248, 198, "UI//SAVE");
}

void DrawListBox()
{
	BmpPut(150, 150, "UI//LIST");
}

void DrawSizeBox()
{
	BmpPut(248, 198, "UI//SIZE");
}

void DrawAdjustBox()
{
	BmpPut(248, 198, "UI//ADST");	//ADST:adjust
}

void Welcome()
{
	int i = 0, j = 0;
	u32 color = ColorStart;
	HSL tHSL;
	RGB tRGB;
	int tHue0;
	const double dLightness = -12 / 60000.0;
	const double dSaturation = 30 / 60000.0;
	const double dHue = -120 / 600.0;

	U32TRGB(&tRGB, color);
	RGB2HSL(tRGB, &tHSL);
	tHue0 = tHSL.h;

	//Bar(0, 0, 800, 600, White);
	//BmpPut(0, 0, "UI//WELC");
	
	delay(100);

	//渐变背景
	for (i = 0; i < 600; i++)
	{
		for (j = 0; j < 800; j++)
		{
			PutPixel(j, i, color);
		}
		tHSL.l = tHSL.l - dLightness;
		tHSL.s = tHSL.s - dSaturation;
		tHSL.h = (int)(tHue0 - dHue * i + 0.5);
		HSL2RGB(&tRGB, tHSL);
		color = RGB2U32(tRGB.r, tRGB.g, tRGB.b);
	}

	Bar(100, 100, 250, 100+2, White);
	Bar(100, 100, 100+2, 175, White);
	Bar(550, 250-2, 700, 250, White);
	Bar(700-2, 175, 700, 250, White);

	TextASC128(200+30, 100, 64, White, "Phot", 2);
	TextASC128(445+30, 100, 64, White, "o", 2);

	//TextGB64(80, 300, 72, White, "照片管理与编辑系统", 0);

	TextASC64(160-60, 250, 32, White, "M", 2);
	TextASC64(205-60, 250, 32, White, "anger And Edi", 2);
	TextASC64(600-60, 250, 32, White, "ting", 2);

	TextGB16(650, 550, 14, White, "按任意键进入");

	//TextGB64(330, 250, 64, 0, "作者：王子毅", 4);
	//TextGB64(520, 350, 64, 0, "牛保健", 4);

	//TextASC64(80-10, 150, 32, 0, "Phot", 2);
	//TextASC64(200-10, 150, 32, 0, "o M", 2);
	//TextASC64(315-10, 150, 32, 0, "anger and Edi", 2);
	//TextASC64(720-10, 150, 32, 0, "t", 2);

	//TextASC64(80 - 11, 150, 32, 0, "Phot", 2);
	//TextASC64(200 - 11, 150, 32, 0, "o M", 2);
	//TextASC64(315 - 11, 150, 32, 0, "anger and Edi", 2);
	//TextASC64(720 - 11, 150, 32, 0, "t", 2);

	/*TextASC128(80 - 10, 120, 64, 0, "Phot", 2);
	TextASC128(300 - 10, 120, 64, 0, "o S", 2);
	TextASC128(500 - 10, 120, 64, 0, "hop", 2);*/

	/*TextGB64(350, 250, 64, 0, "作者", 4);
	TextGB64(530, 250, 64, 0, "王子毅", 4);
	TextGB64(530, 350, 64, 0, "牛保健", 4);

	TextGB16(650, 450, 14, 0, "按任意键进入");*/

	/*TextGB64(150 + 2, 200 + 2, 64, 0xf0e981, "照片管理与编辑系统", 0);
	TextGB64(350 + 2, 300 + 2, 64, 0xf0e981, "作者：王子毅", 0);
	TextGB64(500 + 2, 400 + 2, 64, 0xf0e981, "牛保健", 0);*/

	getch();
}