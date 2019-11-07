#include "color.h"

/**
 *  @ brief		RGB2HSL
 *
 *  @ param		rgb		RGB色彩空间
 *				hsl		HSL色彩空间
 *
 *	@ note		将RGB色彩空间转换为HSL色彩空间
 *
 *	@ return	正常返回	1
 *				错误返回	0
 **/

int RGB2HSL(RGB rgb, HSL* hsl)
{
	double rr, gg, bb;
	double Max, Min;
	int* h = &hsl->h;
	double* s = &hsl->s;
	double* l = &hsl->l;

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

/**
 *  @ brief		HSL2RGB
 *
 *  @ param		rgb		RGB色彩空间
 *				hsl		HSL色彩空间
 *
 *	@ note		将HSL色彩空间转换为RGB色彩空间
 *
 *	@ return	正常返回	1
 *				错误返回	0
 **/

int HSL2RGB(RGB* rgb, HSL hsl)
{
	double tR, tG, tB;
	double p, q;
	double hk;
	u8* r = &rgb->r;
	u8* g = &rgb->g;
	u8* b = &rgb->b;

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

/**
 *  @ brief		ToRGB
 *
 *  @ param		p、q	HSL2RGB中的临时变量
 *				tC		颜色分量
 *
 *	@ note		辅助HSL色彩空间的转换
 *
 *	@ return	色彩分量
 **/

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

/**
 *  @ brief		RGB2U32
 *
 *  @ param		r、g、b		RGB颜色分量
 *
 *	@ note		将RGB色彩空间转换为unsigned long形式
 *
 *	@ return	unsigned long形式的RGB变量
 **/

u32 RGB2U32(u8 r,u8 g,u8 b)
{
	return ((u32)r << 16) | ((u32)g << 8) | (u32)b;
}

/**
 *  @ brief		U32TRGB
 *
 *  @ param		rgb		RGB色彩空间
 *				color	unsigned long形式的RGB变量
 *
 *	@ note		将unsigned long形式的RGB变量转换为RGB色彩空间变量
 *
 *	@ return	RGB色彩空间变量
 **/

RGB* U32TRGB(RGB* rgb, u32 color)
{
	rgb->r = (color & 0xff0000) >> 16;
	rgb->g = (color & 0x00ff00) >> 8;
	rgb->b = (color & 0x0000ff);
	return rgb;
}

/**
 *  @ brief		RefreshColor
 *
 *  @ param		hsl			HSL色彩空间
 *				nowcolor	当前颜色
 *
 *	@ note		刷新当前颜色信息
 *
 *	@ return	1
 **/

int RefreshColor(HSL hsl, u32* nowcolor)
{
	int i,j;
	RGB tRGB;
	char colorinfo[3][8];
	HSL2RGB(&tRGB, hsl);
	sprintf(colorinfo[0], "R%d", tRGB.r);
	sprintf(colorinfo[1], "G%d", tRGB.g);
	sprintf(colorinfo[2], "B%d", tRGB.b);
	*nowcolor = RGB2U32(tRGB.r, tRGB.g, tRGB.b);
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 36; j++)
		{
			hsl.l = (double)i / 100.0;
			HSL2RGB(&tRGB, hsl);
			PutPixel(455 + j, 245 + i, RGB2U32(tRGB.r, tRGB.g, tRGB.b));
		}
	}
	Bar(505, 295, 540, 315, *nowcolor);
	Bar(505, 245, 540, 285, 0xdeebf3);
	TextASC12(507, 245, 8, 0, colorinfo[0]);
	TextASC12(507, 257, 8, 0, colorinfo[1]);
	TextASC12(507, 269, 8, 0, colorinfo[2]);
	return 1;
}

/**
 *  @ brief		FreshColor
 *
 *  @ param		nowhsl	当前HSL色彩空间
 *				color	当前颜色
 *
 *	@ note		初始化颜色信息
 *
 *	@ return	1
 **/

int FreshColor(u32 color, HSL* nowhsl)
{
	int i, j;
	RGB tRGB;
	HSL tHSL;
	char colorinfo[3][8];
	U32TRGB(&tRGB, color);
	RGB2HSL(tRGB, nowhsl);
	sprintf(colorinfo[0], "R%d", tRGB.r);
	sprintf(colorinfo[1], "G%d", tRGB.g);
	sprintf(colorinfo[2], "B%d", tRGB.b);
	RGB2HSL(tRGB, &tHSL);
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 36; j++)
		{
			tHSL.l = (double)i / 100.0;
			HSL2RGB(&tRGB, tHSL);
			PutPixel(455 + j, 245 + i, RGB2U32(tRGB.r, tRGB.g, tRGB.b));
		}
	}
	Bar(505, 295, 540, 315, color);
	Bar(505, 245, 540, 285, 0xdeebf3);
	TextASC12(507, 245, 8, 0, colorinfo[0]);
	TextASC12(507, 257, 8, 0, colorinfo[1]);
	TextASC12(507, 269, 8, 0, colorinfo[2]);
	return 1;
}

/**
 *  @ brief		DrawColorBox
 *
 *  @ param		
 *
 *	@ note		绘制选色器窗口
 *
 *	@ return	
 **/

void DrawColorBox()
{
	int i, j;
	RGB tRGB;
	HSL hsl = { 0,0.0,0.5 };
	BmpPut(248, 198, "UI//COLOR");
	for (i = 0; i < 180; i++)
	{
		hsl.h = i * 2;
		for (j = 0; j < 100; j++)
		{	
			hsl.s = (double)j / 100.0;
			HSL2RGB(&tRGB, hsl);
			PutPixel(260 + i, 245 + j, RGB2U32(tRGB.r, tRGB.g, tRGB.b));
		}
	}
}

/**
 *  @ brief		SelectColor
 *
 *  @ param		color	当前颜色值
 *
 *	@ note		选色操作函数
 *
 *	@ return	0
 **/

int SelectColor(u32* color)
{
	HSL nowhsl = { 0,0,0 };
	u32 nowcolor = *color;
	MOUSE mouse_old, mouse_new;

	BmpSave(248, 198, 552, 352, "DATA//BK4");
	DrawColorBox();
	FreshColor(*color, &nowhsl);

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
				BmpPut(248, 198, "DATA//BK4");
				return 0;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK4");
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

/**
*  函数名      PickColor
*  传入参数    color      当前颜色值
*  功能        拾色器
*  返回值      0          退出拾色器
			   20         切换为打开功能
			   30         切换为保存功能
			   40         切换为新建功能
			   45         切换为图库功能
			   50         切换为画笔功能
			   60         切换为裁剪功能
			   65         切换为图形功能
			   70         切换为调整功能
			   75         切换为粗细功能
			   80         切换为选色功能
			   85         切换为设置功能
			   90         切换为缩小功能
			   95         切换为放大功能
			   100        切换为旋转功能
			   105        切换为翻转功能
			   120        切换为滤镜功能
**/

int PickColor(u32* color, int flag)
{
	int x, y;						//所拾取颜色处的x,y坐标
	RGB tRGB;						//RGB临时变量，用于显示当前颜色的RGB值
	char colorstring[20];			//用于存放显示信息的字符数组
	MOUSE mouse_old, mouse_new;		//定义老鼠标和新鼠标

	U32TRGB(&tRGB, *color);                                            //获取当前颜色的RGB值
	sprintf(colorstring, "R:%d G:%d B:%d", tRGB.r, tRGB.g, tRGB.b);    //用字符数组存放显示信息
	TextGB16(200, 580, 14, 0, "当前颜色为：");
	Bar(300, 580, 320, 590, *color);                                   //显示当前颜色
	TextASC16(400, 580, 14, 0, colorstring);                           //输出当前颜色的RGB值

	MouseStatus(&mouse_old);                   //获取老鼠标状态
	MouseStoreBk(mouse_old.x, mouse_old.y);    //记录老鼠标的背景图案
	MouseDraw(mouse_old);                      //画新鼠标

	/*移动鼠标，执行拾色器功能*/
	while (1)
	{
		MouseStatus(&mouse_new);              //获取新鼠标状态

		/*如果鼠标状态未改变，不执行任何操作*/
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_new.button == mouse_old.button)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);      //擦去老鼠标
			MouseStoreBk(mouse_new.x, mouse_new.y);    //记录新鼠标的背景图案
			MouseDraw(mouse_new);                      //画新鼠标

			if (mouse_new.button == mouse_old.button)  //如果鼠标点击状态未改变，不执行拾色器操作
			{
				mouse_old = mouse_new;
				continue;
			}

			/*功能切换*/
			if (MouseDown(10, 0, 70, 50))
			{
				//打开
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 20;
			}
			else if (MouseDown(70, 0, 130, 50))
			{
				//保存
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 30;
			}
			else if (MouseDown(130, 0, 190, 50))
			{
				//新建
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 40;
			}
			else if (MouseDown(190, 0, 250, 50))
			{
				//图库
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 45;
			}
			else if (MouseDown(10, 50, 70, 100))
			{
				//画笔
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 50;
			}
			else if (MouseDown(70, 50, 130, 100))
			{
				//裁剪
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 60;
			}
			else if (MouseDown(130, 50, 190, 100))
			{
				//图形
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 65;
			}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 70;
			}
			else if (MouseDown(700, 50, 750, 100))
			{
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 75;
			}
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 80;
			}
			else if (MouseDown(703, 570, 735, 600))
			{
				//设置
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 85;
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 90;
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 95;
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 100;
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 105;
			}
			else if (MouseDown(84, 570, 126, 600))
			{
				//再次点击，退出拾色器
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 0;
			}
			else if (MouseDown(700, 0, 750, 50))
			{
				//滤镜
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 120;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
			else if (MouseDown(190, 50, 250, 100) && flag == 1)
			{
				//直线
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 125;
			}
			else if (MouseDown(250, 50, 300, 100) && flag == 1)
			{
				//三角形
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 130;
			}
			else if (MouseDown(300, 50, 380, 100) && flag == 1)
			{
				//矩形
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 135;
			}
			else if (MouseDown(380, 50, 450, 100) && flag == 1)
			{
				//圆
				MousePutBk(mouse_new.x, mouse_new.y);
				Bar(200, 570 + 1, 700, 600, Gray);
				return 140;
			}
			else if (MouseDown(1, 1, 800, 600))    //在屏幕内点击，触发拾色器功能
			{
				x = mouse_new.x - 1;        //拾取鼠标左上角处的颜色
				y = mouse_new.y - 1;
				*color = GetPixel(x, y);    //获取该处颜色，并将其修改为当前颜色

				/*显示当前颜色信息*/
				U32TRGB(&tRGB, *color);
				Bar(200, 570 + 1, 700, 600, Gray);
				sprintf(colorstring, "R:%d G:%d B:%d", tRGB.r, tRGB.g, tRGB.b);
				TextGB16(200, 580, 14, 0, "当前颜色为：");
				Bar(300, 580, 320, 590, *color);
				TextASC16(400, 580, 14, 0, colorstring);
			}
			else
			{
				;
			}

			mouse_old = mouse_new;    //重置鼠标
		}
	}
}