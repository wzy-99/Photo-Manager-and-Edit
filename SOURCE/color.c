#include "color.h"

int RGB2HSL(RGB rgb, int* h, double* s, double* l)
{
	double rr, gg, bb;
	double Max, Min;

	rr = (double)rgb.r / 255.0;
	gg = (double)rgb.g / 255.0;
	bb = (double)rgb.b / 255.0;

	Max = rr;
	if (Max < gg)
	{
		Max = gg;
	}
	if (Max < bb)
	{
		Max = bb;
	}

	Min = rr;
	if (Min > gg)
	{
		Min = gg;
	}
	if (Min > bb)
	{
		Min = bb;
	}

	//计算亮度
	*l = (Max + Min) / 2.0;

	//计算色相
	if (Max == Min)
	{
		*h = 0;

	}
	else if (Max == rr && gg >= bb)
	{
		*h = 60 * (gg - bb) / (Max - Min) + 0;
	}
	else if (Max == rr && gg < bb)
	{
		*h = 60 * (gg - bb) / (Max - Min) + 360;
	}
	else if (Max == gg)
	{
		*h = 60 * (bb - rr) / (Max - Min) + 120;
	}
	else if (Max == bb)
	{
		*h = 60 * (rr - gg) / (Max - Min) + 240;
	}
	else
	{
		return 0;
	}


	//计算饱和度
	if (*l == 0 || Max == Min)
	{
		*s = 0;
	}
	else if (*l > 0 && *l <= 0.5)
	{
		*s = (Max - Min) / (Max + Min);
	}
	else if (*l > 0.5)
	{
		*s = (Max - Min) / (2 - (Max + Min));
	}
	else
	{
		return 0;
	}

	return 1;
}

int HSL2RGB(u8* r, u8* g, u8* b, HSL hsl)
{
	double tR, tG, tB;
	double p, q;
	double hk;

	if (hsl.s == 0)
	{
		tR = hsl.l;
		tG = hsl.l;
		tB = hsl.l;
	}
	else
	{
		if (hsl.l < 0.5)
		{
			q = hsl.l * (1.0 + hsl.s);
		}
		else
		{
			q = hsl.l + hsl.s - (hsl.l * hsl.s);
		}
		p = 2.0 * hsl.l - q;
		hk = (double)hsl.h / 360.0;
		tR = hk + 1.0 / 3.0;
		tG = hk + 0;
		tB = hk - 1.0 / 3.0;
		tR = ToRGB(p, q, tR);
		tG = ToRGB(p, q, tG);
		tB = ToRGB(p, q, tB);
	}
	*r = (int)(tR * 255.0 + 0.5);
	*g = (int)(tG * 255.0 + 0.5);
	*b = (int)(tB * 255.0 + 0.5);
	return 1;
}

double ToRGB(double p, double q, double tC)
{
	double ColorC;
	if (tC < 0)
	{
		tC = tC + 1.0;
	}
	else if (tC > 1)
	{
		tC = tC - 1.0;
	}
	else
	{
		;
	}
	if (tC < (1.0 / 6.0))
	{
		ColorC = p + ((q - p) * 6 * tC);
	}
	else if (tC >= (1.0 / 6.0) && tC < 0.5)
	{
		ColorC = q;
	}
	else if (tC >= 0.5 && tC < (2.0 / 3.0))
	{
		ColorC = p + ((q - p) * 6 * (2.0 / 3.0 - tC));
	}
	else
	{
		ColorC = p;
	}

	return ColorC;
}

u32 RGB2U32(u8 r,u8 g,u8 b)
{
	return ((u32)r << 16) | ((u32)g << 8) | (u32)b;
}

int RefreshColor(HSL hsl, u32* nowcolor)
{
	int i,j;
	u8 r, g, b;
	char colorinfo[3][8];
	HSL2RGB(&r, &g, &b, hsl);
	sprintf(colorinfo[0], "R%d", r);
	sprintf(colorinfo[1], "G%d", g);
	sprintf(colorinfo[2], "B%d", b);
	*nowcolor = RGB2U32(r, g, b);
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 36; j++)
		{
			hsl.l = (double)i / 100.0;
			HSL2RGB(&r, &g, &b, hsl);
			PutPixel(455 + j, 245 + i, RGB2U32(r, g, b));
		}
	}
	Bar(505, 295, 540, 315, *nowcolor);
	Bar(505, 245, 540, 285, 0xdeebf3);
	TextASC12(507, 245, 8, 0, colorinfo[0]);
	TextASC12(507, 257, 8, 0, colorinfo[1]);
	TextASC12(507, 269, 8, 0, colorinfo[2]);
	return 1;
}

int FreshColor(u32 color, u32* nowcolor, HSL* nowhsl)
{
	int i, j;
	RGB rgb;
	HSL hsl;
	char colorinfo[3][8];
	rgb.r = color >> 16 & 0xff;
	rgb.g = color >> 8 & 0xff;
	rgb.b = color & 0xff;
	RGB2HSL(rgb, &nowhsl->h, &nowhsl->s, &nowhsl->l);
	sprintf(colorinfo[0], "R%d", rgb.r);
	sprintf(colorinfo[1], "G%d", rgb.g);
	sprintf(colorinfo[2], "B%d", rgb.b);
	RGB2HSL(rgb, &hsl.h, &hsl.s, &hsl.l);
	*nowcolor = color;
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 36; j++)
		{
			hsl.l = (double)i / 100.0;
			HSL2RGB(&rgb.r, &rgb.g, &rgb.b, hsl);
			PutPixel(455 + j, 245 + i, RGB2U32(rgb.r, rgb.g, rgb.b));
		}
	}
	Bar(505, 295, 540, 315, *nowcolor);
	Bar(505, 245, 540, 285, 0xdeebf3);
	TextASC12(507, 245, 8, 0, colorinfo[0]);
	TextASC12(507, 257, 8, 0, colorinfo[1]);
	TextASC12(507, 269, 8, 0, colorinfo[2]);
	return 1;
}



void DrawColorBox()
{
	int i, j;
	u8 r, g, b;
	HSL hsl = { 0,0.0,0.5 };
	BmpPut(248, 198, "UI//COLOR");
	for (i = 0; i < 180; i++)
	{
		hsl.h = i * 2;
		for (j = 0; j < 100; j++)
		{	
			hsl.s = (double)j / 100.0;
			HSL2RGB(&r, &g, &b, hsl);
			PutPixel(260 + i, 245 + j, RGB2U32(r, g, b));
		}
	}
}

int SelectColor(u32* color)
{
	HSL nowhsl = { 0,0,0 };
	u32 nowcolor = 0;
	MOUSE mouse_old, mouse_new;
	BmpSave(248, 198, 552, 352, "UI//temp3");
	DrawColorBox();
	FreshColor(*color, &nowcolor, &nowhsl);
	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
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
			if (MouseDown(260, 245, 440, 345))
			{
				//色度(色相与饱和度)
				nowhsl.h = (mouse_old.x - 260) * 2;
				nowhsl.s = (double)(mouse_old.y - 245)/100.0;
				nowhsl.l = 0.5;
				RefreshColor(nowhsl, &nowcolor);
			}
			else if (MouseDown(455, 245, 490, 345))
			{
				//亮度
				nowhsl.l = (double)(mouse_old.y - 245) / 100.0;
				RefreshColor(nowhsl, &nowcolor);
				MouseDraw(mouse_new);
			}
			else if (MouseDown(505, 325, 540, 345))
			{
				//确认
				*color = nowcolor;
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "UI//temp3");
				return 0;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "UI//temp3");
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