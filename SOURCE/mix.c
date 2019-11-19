#include "mix.h"

/**
*  函数名      DrawShading
*  传入参数    x1        矩形一个顶点的横坐标
			   y1        矩形一个顶点的纵坐标
			   x2        矩形另一个对角顶点的横坐标
			   y2        矩形另一个对角顶点的纵坐标
			   color1    用于渐变的颜色值
			   color2    渐变结束的颜色值
*  功能        画渐变矩形
*  返回值      无
**/
void DrawShading(int x1, int y1, int x2, int y2, u32 color1, u32 color2)
{
	int i = 0, j = 0;           //循环变量

	HSL tHSL1, tHSL2;           //存储HSL的临时变量
	RGB tRGB1, tRGB2;           //存储RGB的临时变量
	int tHue0;                  //用于计算色相的临时变量

	double dLightness;          //每行渐变的亮度的值
	double dSaturation;         //每行渐变的饱和度的值
	double dHue;                //每行渐变的色相的值

	U32TRGB(&tRGB1, color1);    //获取color的RGB值
	U32TRGB(&tRGB2, color2);
	RGB2HSL(tRGB1, &tHSL1);     //将RGB转化为HSL
	RGB2HSL(tRGB2, &tHSL2);

	tHue0 = tHSL1.h;                                      //赋初值

	dLightness = (tHSL2.l - tHSL1.l) / fabs(y1 - y2);     //计算每行渐变的亮度的值
	dSaturation = (tHSL2.s - tHSL1.s) / fabs(y1 - y2);    //计算每行渐变的饱和度的值
	dHue = (tHSL2.h - tHSL1.h) / fabs(y1 - y2);           //计算每行渐变的色相的值

	delay(100);

	//渐变背景
	for (i = y1; i <= y2; i++)
	{
		for (j = x1; j <= x2; j++)
		{
			PutPixel(j, i, color1);
		}

		/*计算渐变一行后的HSL值*/
		tHSL1.l = tHSL1.l + dLightness;
		tHSL1.s = tHSL1.s + dSaturation;
		tHSL1.h = (int)(tHue0 + dHue * i + 0.5);

		HSL2RGB(&tRGB1, tHSL1);                         //将HSL转化为RGB
		color1 = RGB2U32(tRGB1.r, tRGB1.g, tRGB1.b);    //将RGB转化为颜色值赋给color
	}
}

/**
*  函数名      Shading
*  输入参数    bmpattr    图片

*  功能        滤镜
*  返回值      0          图片未打开
			   -1         取消
			   -2         关闭
			   1          成功画滤镜
**/
int Shading(BMPATTR* bmpattr)
{
	u32 color1, color2;                 //用于存储用于渐变的颜色值的临时变量
	const u32 ColorStart = 0x7ecef4;    //滤镜默认值
	const u32 ColorEnd = 0xf09fc3;      //滤镜默认值
	const char* data_path = "DATA//temp2";

	MOUSE mouse_old, mouse_new;

	/*若图片未打开，显示警告框，退出函数*/
	if (bmpattr->flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}

	color1 = ColorStart;
	color2 = ColorEnd;

	BmpSave(248, 198, 552, 352, "DATA//BK8");    //保存显示框下方的图片

	DrawShadingBox();                            //显示框

	Bar(348 + 1, 260 + 1, 400 - 1, 282 - 1, color1);	//显示颜色一
	Bar(348 + 1, 300 + 1, 400 - 1, 325 - 1, color2);    //显示颜色二

	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
	MouseDraw(mouse_old);

	while (1)
	{
		MouseStatus(&mouse_new);

		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_new.button == mouse_old.button)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);
			MouseStoreBk(mouse_new.x, mouse_new.y);
			MouseDraw(mouse_new);

			if (mouse_new.button == mouse_old.button)
			{
				mouse_old = mouse_new;
				continue;
			}

			if (MouseDown(348, 260, 400, 282))
			{
				/*选择用于渐变的颜色*/
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&color1);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);

				Bar(348 + 1, 260 + 1, 400 - 1, 282 - 1, color1);    //显示颜色一
			}
			else if (MouseDown(348, 300, 400, 325))
			{
				/*选择渐变结束的颜色*/
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&color2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);

				Bar(348 + 1, 300 + 1, 400 - 1, 325 - 1, color2);    //显示颜色二
			}
			else if (MouseDown(455, 260, 512, 282))
			{
				//点击确认（颜色一默认为ColorStart，颜色二默认为ColorEnd）
				MousePutBk(mouse_new.x, mouse_new.y);
				BmpPut(248, 198, "DATA//BK8");												 //显示之前保存的图片

				DataSave(bmpattr, data_path);
				DrawShading(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2, color1, color2);
				ImgMix(bmpattr, data_path, 0.7, 1);

				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 1;
			}
			else if (MouseDown(455, 300, 512, 325))
			{
				//取消
				MousePutBk(mouse_new.x, mouse_new.y);
				BmpPut(248, 198, "DATA//BK8");    //显示之前保存的图片
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return -1;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				//关闭
				MousePutBk(mouse_new.x, mouse_new.y);
				BmpPut(248, 198, "DATA//BK8");    //显示之前保存的图片
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return -2;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				////退出
				//MousePutBk(mouse_new.x, mouse_new.y);
				//Exit(bmpattr);
				//MouseStatus(&mouse_new);
				//MouseStoreBk(mouse_new.x, mouse_new.y);
			}

			mouse_old = mouse_new;
		}
	}
}


//Special effects 特效 SFX

int OldSFX(BMPATTR* bmpattr)
{
	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;

	int i, j;	//循环变量

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	int r, g, b;

	for (i = y1; i < y2; i++)
	{
		for (j = x1; j < x2;j++)
		{
			color = GetPixel(j, i);
			U32TRGB(&rgb_scr, color);

			r = (int)(0.393 * rgb_scr.r + 0.769 * rgb_scr.g + rgb_scr.b * 0.189);
			g = (int)(0.349 * rgb_scr.r + 0.686 * rgb_scr.g + rgb_scr.b * 0.168);
			b = (int)(0.272 * rgb_scr.r + 0.534 * rgb_scr.g + rgb_scr.b * 0.131);

			RGBRange(&r);
			RGBRange(&g);
			RGBRange(&b);

			rgb_dst.r = r;
			rgb_dst.g = g;
			rgb_dst.b = b;

			color = RGB2U32(rgb_dst.r, rgb_dst.g, rgb_dst.b);
			PutPixel(j, i, color);
		}
	}
	return 0;
}

int ComicSFX(BMPATTR* bmpattr)
{
	const char* path = "DATA//data1";

	int x1 = bmpattr->x1;
	int x2 = bmpattr->x1 + bmpattr->width;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y1 + bmpattr->heigth;

	int i, j;	//循环变量

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	int r, g, b;

	DataSave(bmpattr, path);

	for (i = y1; i <= y2; i++)
	{
		for (j = x1; j <= x2; j++)
		{
			color = GetPixel(j, i);
			U32TRGB(&rgb_scr, color);

			r = abs((int)rgb_scr.g - rgb_scr.b + rgb_scr.g + rgb_scr.r) * rgb_scr.r / 256;
			g = abs((int)rgb_scr.b - rgb_scr.g + rgb_scr.b + rgb_scr.r) * rgb_scr.r / 256;
			b = abs((int)rgb_scr.b - rgb_scr.g + rgb_scr.b + rgb_scr.r) * rgb_scr.g / 256;

			RGBRange(&r);
			RGBRange(&g);
			RGBRange(&b);

			rgb_dst.r = r;
			rgb_dst.g = g;
			rgb_dst.b = b;

			color = RGB2U32(rgb_dst.r, rgb_dst.g, rgb_dst.b);
			PutPixel(j, i, color);
		}
	}

	GraySFX(bmpattr);

	ImgMix(bmpattr, path, 0.7, 1);

	return 0;
}

int GraySFX(BMPATTR* bmpattr)
{
	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;

	int i, j;	//循环变量

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	for (i = y1; i < y2; i++)
	{
		for (j = x1; j < x2; j++)
		{
			color = GetPixel(j, i);
			U32TRGB(&rgb_scr, color);

			rgb_dst.r = rgb_scr.r * 0.3 + rgb_scr.g * 0.59 + rgb_scr.b * 0.11;
			rgb_dst.g = rgb_dst.r;
			rgb_dst.b = rgb_dst.r;

			color = RGB2U32(rgb_dst.r, rgb_dst.g, rgb_dst.b);
			PutPixel(j, i, color);
		}
	}
	return 0;
}


int CastingSFX(BMPATTR* bmpattr)
{
	const char* path = "DATA//data1";

	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;

	int i, j;	//循环变量

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	int r, g, b;

	for (i = y1; i < y2; i++)
	{
		for (j = x1; j < x2; j++)
		{
			color = GetPixel(j, i);
			U32TRGB(&rgb_scr, color);

			r = rgb_scr.r * 128 / (rgb_scr.g + rgb_scr.b + 1);
			g = rgb_scr.g * 128 / (rgb_scr.r + rgb_scr.b + 1);
			b = rgb_scr.b * 128 / (rgb_scr.g + rgb_scr.r + 1);

			RGBRange(&r);
			RGBRange(&g);
			RGBRange(&b);

			rgb_dst.r = r;
			rgb_dst.g = g;
			rgb_dst.b = b;

			color = RGB2U32(rgb_dst.r, rgb_dst.g, rgb_dst.b);
			PutPixel(j, i, color);
		}
	}

	return 0;
}

int FrozenSFX(BMPATTR* bmpattr)
{
	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;

	int i, j;	//循环变量

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	int r, g, b;

	for (i = y1; i < y2; i++)
	{
		for (j = x1; j < x2; j++)
		{
			color = GetPixel(j, i);
			U32TRGB(&rgb_scr, color);

			r = ((int)rgb_scr.r - rgb_scr.g - rgb_scr.b) * 3 / 2;
			g = ((int)rgb_scr.g - rgb_scr.r - rgb_scr.b) * 3 / 2;
			b = ((int)rgb_scr.b - rgb_scr.g - rgb_scr.r) * 3 / 2;

			RGBRange(&r);
			RGBRange(&g);
			RGBRange(&b);

			rgb_dst.r = r;
			rgb_dst.g = g;
			rgb_dst.b = b;

			color = RGB2U32(rgb_dst.r, rgb_dst.g, rgb_dst.b);
			PutPixel(j, i, color);
		}
	}
	return 0;
}

int NegativeSFX(BMPATTR* bmpattr)
{
	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;

	int i, j;	//循环变量

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	for (i = y1; i < y2; i++)
	{
		for (j = x1; j < x2; j++)
		{
			color = GetPixel(j, i);
			U32TRGB(&rgb_scr, color);

			rgb_dst.r = 255 - rgb_scr.r;
			rgb_dst.g = 255 - rgb_scr.g;
			rgb_dst.b = 255 - rgb_scr.b;

			color = RGB2U32(rgb_dst.r, rgb_dst.g, rgb_dst.b);
			PutPixel(j, i, color);
		}
	}
	return 0;
}

int FreshSFX(BMPATTR* bmpattr)
{
	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;
	
	const char* path = "DATA//data2";
	const u32 mix_color = 0x00b7ee;

	int i, j;	//循环变量

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	DataSave(bmpattr, path);

	ImgMix(bmpattr, path, 0.5, 3);

	DataSave(bmpattr, path);

	Bar(x1, y1, x2, y2, mix_color);

	ImgMix(bmpattr, path, 0.5, 3);

	//ImageSaturation(*bmpattr, 1.5);
	//ImageLightness(*bmpattr, 1.25);

	return 0;
}

int InstagramSFX(BMPATTR* bmpattr)
{
	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;

	int i, j;	//循环变量

	int B[256]={ 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 65, 66, 68, 69, 70, 71, 72, 73, 75, 76, 77, 78, 79, 80, 82, 83, 84, 85, 86, 87, 89, 90, 91, 92, 93, 95, 96, 97, 98,
		99, 100, 102, 103, 104, 105, 106, 107, 109, 110, 111, 112, 113, 115, 116, 117, 118, 119, 120, 122, 123, 124, 125, 126, 127, 129,
		130, 131, 132, 133, 134, 136, 137, 138, 139, 139, 140, 142, 143, 144, 145, 146, 147, 149, 150, 151, 152, 153, 154, 156, 157, 158,
		159, 160, 161, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 176, 177, 178, 179, 180, 181, 183, 184, 185,186, 187, 189, 190,
		191, 192, 193, 194, 196, 197, 198, 199, 200, 201, 203, 204, 205, 206, 207, 208, 210, 211, 212, 212, 212, 212, 212, 212, 212, 212,
		212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212,
		212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212,
		212, 212, 212 };//
	int G[256]={ 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
		57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 59, 60, 61, 
		62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 73, 73, 74, 75, 76, 77, 78, 79, 80, 81, 83, 84, 85, 85, 86, 87, 88, 89, 90, 91, 93, 94, 95, 96,
		96, 97, 98, 99, 100, 102, 103, 104, 105, 106, 107, 108, 108, 109, 110, 112, 113, 114, 115, 116, 117, 118, 119, 120, 120, 122, 123, 124, 
		125, 126, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 142, 143, 143, 144, 145, 146, 147, 148, 149, 150, 
		152, 153, 154, 155, 155, 156, 157, 158, 159, 160, 162, 163, 164, 165, 166, 167, 167, 168, 169, 170, 172, 173, 174, 175, 176, 177, 178, 179, 
		179, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 202, 202, 203, 204, 205, 206, 207,
		208, 209, 210, 212, 213, 214, 214, 215, 216, 217, 218, 219, 221, 222, 223, 224, 225, 226, 226, 227, 228, 229, 231, 232, 233, 234, 235, 236, 
		237, 237, 238, 239, 241, 242, 243, 244, 245, 246, 247, 248, 249, 249, 251, 252, 253, 254 };//
	int R[256]={ 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
		81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 82, 84, 84, 85, 86, 88, 88, 89, 91, 92, 93, 93, 95, 96, 97, 98, 99,
		100, 101, 103, 103, 104, 106, 107, 107, 108, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 121, 121, 122, 123, 125, 126, 126, 128, 129,
		130, 131, 132, 133, 134, 135, 136, 137, 138, 140, 140, 141, 143, 144, 145, 145, 147, 148, 149, 150, 151, 152, 154, 154, 155, 156, 158, 159,
		159, 161, 162, 163, 164, 164, 165, 166, 167, 168, 169, 170, 171, 173, 173, 174, 176, 177, 178, 178, 180, 181, 182, 183, 184, 185, 186, 187,
		188, 189, 191, 192, 192, 193, 195, 196, 196, 198, 199, 200, 201, 202, 203, 204, 206, 206, 207, 208, 210, 210, 211, 213, 214, 215, 215, 217, 
		218, 219, 220, 221, 222, 223, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225,
		225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 
		225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225 };//

	RGB rgb_scr;
	RGB rgb_dst;
	u32 color;

	for (i = y1; i < y2; i++)
	{
		for (j = x1; j < x2; j++)
		{
			color = GetPixel(j, i);
			U32TRGB(&rgb_scr, color);

			rgb_dst.r = R[rgb_scr.r];
			rgb_dst.g = G[rgb_scr.g];
			rgb_dst.b = B[rgb_scr.b];

			color = RGB2U32(rgb_dst.r, rgb_dst.g, rgb_dst.b);
			PutPixel(j, i, color);
		}
	}
	return 0;
}

int GlassSFX(BMPATTR* bmpattr)
{
	int x1 = bmpattr->x1;
	int x2 = bmpattr->x2;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y2;

	int i, j;	//循环变量

	u32 color;
	
	int random;

	srand(time(0));

	for (i = y1; i < y2 - 1; i = i + 2)
	{
		for (j = x1; j < x2 - 1; j=j+2)
		{
			random = rand() % 4;

			switch (random)
			{
			case 0:
				color = GetPixel(j, i);
				break;
			case 1:
				color = GetPixel(j + 1, i);
				break;
			case 2:
				color = GetPixel(j, i + 1);
				break;
			case 3:
				color = GetPixel(j + 1, i + 1);
				break;
			default:
				break;
			}

			PutPixel(j, i, color);
			PutPixel(j + 1, i, color);
			PutPixel(j, i + 1, color);
			PutPixel(j + 1, i + 1, color);
		}
	}
	return 0;
}


int ImgSFX(BMPATTR* bmpattr)
{
	MOUSE mouse_old, mouse_new;

	BmpSave(248, 198, 552, 352, "DATA//BK9");
	DrawSFXBox();


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
			if (MouseDown(285, 260, 335, 280))
			{
				//
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK9");
				//ComicSFX(bmpattr);
				//InstagramSFX(bmpattr);
				FreshSFX(bmpattr);
				return 0;
			}
			else if (MouseDown(375, 260, 425, 280))
			{
				//怀旧
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK9");
				OldSFX(bmpattr);
				return 0;
			}
			else if (MouseDown(460, 260, 510, 280))
			{
				//熔融
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK9");
				CastingSFX(bmpattr);
				return 0;
			}
			else if (MouseDown(285, 300, 335, 320))
			{
				//毛玻璃
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK9");
				GlassSFX(bmpattr);
				return 0;
			}
			else if (MouseDown(375, 300, 425, 320))
			{
				//灰度
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK9");
				GraySFX(bmpattr);
				return 0;
			}
			else if (MouseDown(460, 300, 510, 320))
			{
				//底片
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK9");
				//FrozenSFX(bmpattr);
				NegativeSFX(bmpattr);
				return 0;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK9");
				return 0;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				//exit(0);
			}
			else
			{
				;
			}
		}
	}
}


void ImgMix(BMPATTR* bmpattr, const char* path, double percent, int patton)
{
	int i, j;                      //循环变量

	u32 color_scr1;                //用于获取背景图案的颜色值
	u32	color_scr2;                //用于获取渐变矩形的颜色值
	u32 color_dst;                 //用于计算所得结果的颜色值
	RGB tRGB;                      //将计算结果的颜色值转化为RGB
	RGB tRGB1;                     //将背景图案的颜色值转化为RGB
	RGB tRGB2;                     //将渐变矩形的颜色值转化为RGB

	FILE* fp;

	int x1 = bmpattr->x1;
	int x2 = bmpattr->x1 + bmpattr->width;
	int y1 = bmpattr->y1;
	int y2 = bmpattr->y1 + bmpattr->heigth;

	/*以二进制只读模式打开临时文件，如果文件打开失败，退出*/
	if ((fp = fopen(path, "rb")) == NULL)
	{
		exit(0);
	}

	/*将背景图案的颜色值读出后，与渐变矩形的RGB按一定比例混合*/
	for (j = y1; j <= y2; j++)
	{
		for (i = x1; i <= x2; i++)
		{
			/*分别获取颜色值，并将其转化为RGB*/
			fread(&color_scr1, 4, 1, fp);
			color_scr2 = GetPixel(i, j);

			U32TRGB(&tRGB1, color_scr1);
			U32TRGB(&tRGB2, color_scr2);

			/*计算混合后的RGB*/
			switch (patton)
			{
			case 0:
				//正常模式
				tRGB.r = tRGB2.r;
				tRGB.g = tRGB2.g;
				tRGB.b = tRGB2.b;
				break;
			case 1:
				//叠加混合
				tRGB.r = Superpose(tRGB1.r, tRGB2.r);
				tRGB.g = Superpose(tRGB1.g, tRGB2.g);
				tRGB.b = Superpose(tRGB1.b, tRGB2.b);
				break;
			case 2:
				//正片叠底
				tRGB.r = (unsigned char)((int)tRGB1.r * tRGB2.r / 255);
				tRGB.g = (unsigned char)((int)tRGB1.g * tRGB2.g / 255);
				tRGB.b = (unsigned char)((int)tRGB1.b * tRGB2.b / 255);
				break;
			case 3:
				//柔光
				tRGB.r = SoftLight(tRGB1.r, tRGB2.r);
				tRGB.g = SoftLight(tRGB1.g, tRGB2.g);
				tRGB.b = SoftLight(tRGB1.b, tRGB2.b);
				break;
			default:
				break;
			}


			tRGB.r = (unsigned char)(percent * tRGB1.r + (1 - percent) * tRGB.r);
			tRGB.g = (unsigned char)(percent * tRGB1.g + (1 - percent) * tRGB.g);
			tRGB.b = (unsigned char)(percent * tRGB1.b + (1 - percent) * tRGB.b);

			/*将混合后的RGB转化为颜色值，并画点*/
			color_dst = RGB2U32(tRGB.r, tRGB.g, tRGB.b);
			PutPixel(i, j, color_dst);
		}
	}

	fclose(fp);    //关闭文件
}

u8 SoftLight(u8 color_base, u8 color_mix)
{
	u8 color_res = 0;
	if (color_mix <= 128)
	{
		color_res = color_base + (2 * color_mix - 255) * (color_base - (int)color_base * color_base / 255) / 255;
	}
	else
	{
		color_res = color_base + (2 * color_mix - 255) * (sqrt(color_base / 255.0) * 255 - color_base) / 255;
	}
	return color_res;
}

u8 Superpose(u8 color_base, u8 color_mix)
{
	u8 color_res;
	if (color_base <= 128)
	{
		color_res = (unsigned char)((int)color_base * color_mix / 128);
	}
	else
	{
		color_res = (unsigned char)(255 - (255 - color_base) * (255 - color_mix) / 128);
	}
	return color_res;
}

