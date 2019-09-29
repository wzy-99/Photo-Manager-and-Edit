#include "image.h"

int ImageZoom(BMPATTR* bmpattr, double times, u8 patton)
{
	FILE* fp;
	int i, j;
	double tscale;
	double x, y;
	u32 color24;
	u16 nWidth, nHeigth;
	int nx1, nx2, ny1, ny2;
	int tx1, tx2, ty1, ty2;

	if (!bmpattr->flag)
	{
		//判断图片是否打开
		return 0;
	}

	tscale = bmpattr->scale;
	tscale = tscale * times;
	
	if ((fp = fopen("DATA//temp1", "wb")) == NULL)
	{
		//文件无法创建
		return 0;
	}

	nWidth = (unsigned int)(bmpattr->width * times);
	nHeigth = (unsigned int)(bmpattr->heigth * times);

	if (nWidth > 798 || nHeigth > 468)
	{
		//超界
		return 0;
	}

	if (nWidth < bmpattr->oWidth - 5 || nHeigth < bmpattr->oHeigth - 5)
	{
		//过小
		return 0;
	}

	for (i = 0; i < nHeigth; i++)
	{
		y = (double)i / times;
		ty1 = (int)(y - 1);
		ty2 = (int)(y + 1);
		ImageXY(&ty1, bmpattr->heigth, bmpattr->y1);
		ImageXY(&ty2, bmpattr->heigth, bmpattr->y1);
		for (j = 0; j < nWidth; j++)
		{
			x = (double)j / times;
			tx1 = (int)(x - 1);
			tx2 = (int)(x + 1);
			ImageXY(&tx1, bmpattr->width, bmpattr->x1);
			ImageXY(&tx2, bmpattr->width, bmpattr->x1);

			color24 = ImageRGB(tx1, tx2, ty1, ty2, x + bmpattr->x1, y + bmpattr->y1, patton);
			fwrite(&color24, 4, 1, fp);
		}
	}
	
	fclose(fp);

	if ((fp = fopen("DATA//temp1", "rb")) == NULL)
	{
		//文件无法打开
		return 0;
	}

	fseek(fp, 0, 0);
	
	nx1 = SCR_WIDTH / 2 - nWidth / 2;
	nx2 = SCR_WIDTH / 2 + nWidth / 2;
	ny1 = SCR_HEIGHT / 2 - nHeigth / 2 + 35;
	ny2 = SCR_HEIGHT / 2 + nHeigth / 2 + 35;

	Bar(0, 100, 800, 570, 0xffffff);

	for (i = 0; i < nHeigth; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			fread(&color24, 4, 1, fp);
			PutPixel(nx1 + j, ny1 + i, color24);
		}
	}

	bmpattr->heigth = nHeigth;
	bmpattr->width = nWidth;
	bmpattr->x1 = nx1;
	bmpattr->x2 = nx2;
	bmpattr->y1 = ny1;
	bmpattr->y2 = ny2;
	bmpattr->scale = tscale;

	fclose(fp);

	return 0;
}

int ImageZoomSet(u8* patton)
{

	u8 nPatton = *patton;
	MOUSE mouse_old, mouse_new;

	BmpSave(248, 198, 552, 352, "DATA//BK6");

	DrawZoomSettingBox(nPatton);

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
			if (MouseDown(450, 260, 470, 280))
			{
				//选择 双线性内插法
				if (nPatton)
				{
					;
				}
				else
				{
					nPatton = 1;
					MousePutBk(mouse_old.x, mouse_old.y);
					Bar(455, 265, 465, 275, 0);
					Bar(455, 315, 465, 325, White);
					MouseStatus(&mouse_old);
					MouseStoreBk(mouse_old.x, mouse_old.y);
					MouseDraw(mouse_old);
				}
			}
			else if(MouseDown(450, 310, 470, 330))
			{
				//选择 临近点插值法
				if (!nPatton)
				{
					;
				}
				else
				{
					nPatton = 0;
					MousePutBk(mouse_old.x, mouse_old.y);
					Bar(455, 265, 465, 275, White);
					Bar(455, 315, 465, 325, 0);
					MouseStatus(&mouse_old);
					MouseStoreBk(mouse_old.x, mouse_old.y);
					MouseDraw(mouse_old);
				}
			}
			else if (MouseDown(485, 225, 540, 285))
			{
				//确认
				MousePutBk(mouse_old.x, mouse_old.y);
				*patton = nPatton;
				BmpPut(248, 198, "DATA//BK6");
				return 0;
			}
			else if (MouseDown(485, 305, 540, 335))
			{
				//取消
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK6");
				return 0;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK6");
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

int ImageXY(int* position, int boundary, int origin)
{
	if (*position < 0)
	{
		*position = 0 + origin;
	}
	else if (*position > boundary)
	{
		*position = boundary + origin;
	}
	else
	{
		*position = *position + origin;
	}
	return 1;
}

u32 ImageRGB(int x1, int x2, int y1, int y2, double x, double y, u8 patton)
{
	int i;
	u32 color[4];
	RGB rgb[4];
	double r1,r2,r,g1,g2,g,b1,b2,b;

	color[0] = GetPixel(x1, y1);
	color[1] = GetPixel(x2, y1);
	color[2] = GetPixel(x1, y2);
	color[3] = GetPixel(x2, y2);

	for (i = 0; i < 4; i++)
	{
		rgb[i].r = (u8)((color[i] & 0xff0000) >> 16);
		rgb[i].g = (u8)((color[i] & 0x00ff00) >> 8);
		rgb[i].b = (u8)((color[i] & 0x0000ff));
	}

	if (patton)
	{
		//双线性内插法
		r1 = ((x2 - x) * rgb[0].r + (x - x1) * rgb[1].r) / (x2 - x1);
		r2 = ((x2 - x) * rgb[2].r + (x - x1) * rgb[3].r) / (x2 - x1);
		r = ((y2 - y) * r1 + (y - y1) * r2) / (y2 - y1);
		g1 = ((x2 - x) * rgb[0].g + (x - x1) * rgb[1].g) / (x2 - x1);
		g2 = ((x2 - x) * rgb[2].g + (x - x1) * rgb[3].g) / (x2 - x1);
		g = ((y2 - y) * g1 + (y - y1) * g2) / (y2 - y1);
		b1 = ((x2 - x) * rgb[0].b + (x - x1) * rgb[1].b) / (x2 - x1);
		b2 = ((x2 - x) * rgb[2].b + (x - x1) * rgb[3].b) / (x2 - x1);
		b = ((y2 - y) * b1 + (y - y1) * b2) / (y2 - y1);
	}

	else
	{
		//最邻近点插值法
		if (x >= x1 && x <= x1 + 0.5 && y >= y1 && y <= y1 + 0.5)
		{
			r = rgb[0].r;
			g = rgb[0].g;
			b = rgb[0].b;
		}
		else if (x > x1 + 0.5 && x <= x2 && y >= y1 && y <= y1 + 0.5)
		{
			r = rgb[1].r;
			g = rgb[1].g;
			b = rgb[1].b;
		}
		else if (x >= x1 && x <= x1 + 0.5 && y > y1 + 0.5 && y <= y2)
		{
			r = rgb[2].r;
			g = rgb[2].g;
			b = rgb[2].b;
		}
		else if (x > x1 + 0.5 && x <= x2 && y > y1 + 0.5 && y <= y2)
		{
			r = rgb[3].r;
			g = rgb[3].g;
			b = rgb[3].b;
		}
		else
		{
			return 0;
		}
	}

	return ((u32)r << 16) | ((u32)g << 8) | ((u32)b);
}

int ImageTailor(BMPATTR* bmpattr)
{
	int x1, y1, x2, y2;
	int flag = 0;
	MOUSE mouse_old, mouse_new;
	if (bmpattr->flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}
	Rectangle(72, 52, 128, 98, 0xff0000, 2);
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
			if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 0)
			{
				if (mouse_old.button == 1)
				{
					;
				}
				else
				{
					x1 = mouse_new.x;
					y1 = mouse_new.y;
					flag = 1;
				}
			}
			else if (MouseUp(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 1)
			{

				if (mouse_new.x == x1 && mouse_new.y == y1)
				{
					flag = 0;
				}
				else
				{
					x2 = mouse_new.x;
					y2 = mouse_new.y;
					flag = 0;

					MousePutBk(mouse_new.x, mouse_new.y);

					bmpattr->heigth = abs(y2 - y1);
					bmpattr->width = abs(x2 - x1);
					bmpattr->oWidth = bmpattr->width;
					bmpattr->oHeigth = bmpattr->heigth;
					bmpattr->x1 = SCR_WIDTH / 2 - bmpattr->width / 2;
					bmpattr->x2 = SCR_WIDTH / 2 + bmpattr->width / 2;
					bmpattr->y1 = SCR_HEIGHT / 2 - bmpattr->heigth / 2 + 35;
					bmpattr->y2 = SCR_HEIGHT / 2 + bmpattr->heigth / 2 + 35;

					BmpSave(x1, y1, x2, y2, "DATA//temp0");
					Bar(0, 100, 800, 570, White);
					BmpPut(bmpattr->x1, bmpattr->y1, "DATA//temp0");

					MouseStatus(&mouse_new);
					MouseStoreBk(mouse_new.x, mouse_new.y);
				}
			}
			else if (MouseUp(0, 0, 800, 600) && flag == 1)
			{
				flag = 0;
				continue;
			}
			else if (MouseDown(10, 0, 70, 50))
			{
				//打开
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 20;
			}
			else if (MouseDown(70, 0, 130, 50))
			{
				//保存
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 30;
			}
			else if (MouseDown(130, 0, 190, 50))
			{
				//新建
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 40;
			}
			else if (MouseDown(10, 50, 70, 100))
			{
				//画笔
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 50;
			}
			else if (MouseDown(70, 50, 130, 100))
			{
				//裁剪
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 0;
			}
			// else if(MouseDown(130,50,190,100))
			// {
				// Rectangle(72, 52, 128, 98, Gray, 2);
				// return 
			// }
			else if (MouseDown(700, 50, 750, 100))
			{
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 85;
			}
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 80;
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 100;
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 105;
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 90;
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(72, 52, 128, 98, Gray, 2);
				return 95;
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
			mouse_old = mouse_new;
		}
	}
}

int ImageRot(BMPATTR* bmpattr)
{
	int width, heigth;
	int i, j;
	int tx1 = bmpattr->x1;
	int tx2 = bmpattr->x2;
	int ty1 = bmpattr->y1;
	int ty2 = bmpattr->y2;
	u32 color24;
	FILE* fp;

	if (bmpattr->flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}

	if ((fp = fopen("DATA//temp3", "wb")) == NULL)
	{
		exit(0);
	}

	for (i = tx2; i >= tx1; i--)
	{
		for (j = ty1; j <= ty2; j++)
		{
			color24 = GetPixel(i, j);
			fwrite(&color24, 4, 1, fp);
		}
	}
	fclose(fp);

	if ((fp = fopen("DATA//temp3", "rb")) == NULL)
	{
		exit(0);
	}

	heigth = bmpattr->width;
	width = bmpattr->heigth;

	if (heigth > BMP_HEIGTH_MAX)
	{
		return 0;
	}
	if (width > BMP_WIDTH_MAX)
	{
		return 0;
	}

	tx1 = SCR_WIDTH / 2 - width / 2;
	tx2 = SCR_WIDTH / 2 + width / 2;
	ty1 = SCR_HEIGHT / 2 - heigth / 2 + 35;
	ty2 = SCR_HEIGHT / 2 + heigth / 2 + 35;

	Bar(0, 100, 800, 570, White);

	for (i = ty1; i <= ty2; i++)
	{
		for (j = tx1; j <= tx2; j++)
		{
			fread(&color24, 4, 1, fp);
			PutPixel(j, i, color24);
		}
	}
	fclose(fp);

	bmpattr->width = width;
	bmpattr->heigth = heigth;
	bmpattr->x1 = tx1;
	bmpattr->x2 = tx2;
	bmpattr->y1 = ty1;
	bmpattr->y2 = ty2;

	return 0;
}

int ImageMirror(BMPATTR bmpattr)
{
	int i, j;
	int tx1 = bmpattr.x1;
	int tx2 = bmpattr.x2;
	int ty1 = bmpattr.y1;
	int ty2 = bmpattr.y2;
	u32 color24;
	FILE* fp;


	if (bmpattr.flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}

	if ((fp = fopen("DATA//temp4", "wb")) == NULL)
	{
		exit(0);
	}

	for (i = ty1; i <= ty2; i++)
	{
		for (j = tx2; j >= tx1; j--)
		{
			color24 = GetPixel(j, i);
			fwrite(&color24, 4, 1, fp);
		}
	}
	fclose(fp);

	if ((fp = fopen("DATA//temp4", "rb")) == NULL)
	{
		exit(0);
	}

	Bar(0, 100, 800, 570, White);

	for (i = ty1; i <= ty2; i++)
	{
		for (j = tx1; j <= tx2; j++)
		{
			fread(&color24, 4, 1, fp);
			PutPixel(j, i, color24);
		}
	}
	fclose(fp);

	return 0;
}

int ImageFileZoom(FILEATTR fileattr)
{
	int i, j;
	FILE* fw, *fp;
	u32 color24;
	double x, y;
	int tx1, tx2, ty1, ty2;
	u32 linebytes;

	linebytes = (3 * fileattr.width) % 4;
	if (!linebytes)
	{
		linebytes = 3 * fileattr.width;
	}
	else
	{
		linebytes = 3 * fileattr.width + 4 - linebytes;
	}

	if ((fp = fopen(fileattr.name, "rb")) == NULL)
	{
		return 0;
	}
	
	if ((fw = fopen("DATA/temp5", "wb")) == NULL)
	{
		return 0;
	}

	for (i = 0; i < fileattr.nHeigth; i++)
	{
		y = (double)i / fileattr.scale;
		ty1 = (int)(y - 1);
		ty2 = (int)(y + 1);
		ImageXY(&ty1, fileattr.heigth, 0);
		ImageXY(&ty2, fileattr.heigth, 0);
		for (j = 0; j < fileattr.nWidth; j++)
		{
			x = (double)j / fileattr.scale;
			tx1 = (int)(x - 1);
			tx2 = (int)(x + 1);
			ImageXY(&tx1, fileattr.width, 0);
			ImageXY(&tx2, fileattr.width, 0);

			color24 = ImageFileRGB(fp, tx1, tx2, ty1, ty2, x, y, linebytes, fileattr.heigth);
			fwrite(&color24, 4, 1, fw);
		}
	}

	fclose(fp);
	fclose(fw);

	if ((fw = fopen("DATA/temp5", "rb")) == NULL)
	{
		return 0;
	}

	fseek(fw, 0, 0);

	for (i = 0; i < fileattr.nHeigth; i++)
	{
		for (j = 0; j < fileattr.nWidth; j++)
		{
			fread(&color24, 4, 1, fp);
			PutPixel(fileattr.x1+j, fileattr.y1 + i, color24);
		}
	}

	fclose(fw);
	return 1;
}

u32 ImageFileRGB(FILE* fp, int x1, int x2, int y1, int y2, double x, double y, u32 linebytes, u16 h)
{
	int i;
	BGR bgr[4];
	double r, g, b;

	fseek(fp, 54 + linebytes * (h - y1 - 1) + x1 * 3, 0);
	fread(&bgr[0], 3, 1, fp);

	fseek(fp, 54 + linebytes * (h - y1 - 1) + x2 * 3, 0);
	fread(&bgr[1], 3, 2, fp);

	fseek(fp, 54 + linebytes * (h - y2 - 1) + x1 * 3, 0);
	fread(&bgr[2], 3, 2, fp);

	fseek(fp, 54 + linebytes * (h - y2 - 1) + x2 * 3, 0);
	fread(&bgr[3], 3, 2, fp);


	//最邻近点插值法
	if (x >= x1 && x <= x1 + 0.5 && y >= y1 && y <= y1 + 0.5)
	{
		r = bgr[0].r;
		g = bgr[0].g;
		b = bgr[0].b;
	}
	else if (x > x1 + 0.5 && x <= x2 && y >= y1 && y <= y1 + 0.5)
	{
		r = bgr[1].r;
		g = bgr[1].g;
		b = bgr[1].b;
	}
	else if (x >= x1 && x <= x1 + 0.5 && y > y1 + 0.5 && y <= y2)
	{
		r = bgr[2].r;
		g = bgr[2].g;
		b = bgr[2].b;
	}
	else if (x > x1 + 0.5 && x <= x2 && y > y1 + 0.5 && y <= y2)
	{
		r = bgr[3].r;
		g = bgr[3].g;
		b = bgr[3].b;
	}
	else
	{
		return 0;
	}

	return ((u32)r << 16) | ((u32)g << 8) | ((u32)b);
}

int ImageContrast(BMPATTR attr,int value)
{
	int i, j;		//循环变量
	u32 oldcolor;	//色彩变量
	RGB rgb;		//色彩分量

	if (value >= -30 && value <= 30)
	{	//value的值范围限定为-30~30，而实际上应该是-63~63，这里为了减少画质损失因此缩小范围。
		for (i = attr.y1; i < attr.y2; i++)
		{
			for (j = attr.x1; j < attr.x2; j++)
			{
				oldcolor = GetPixel(j, i);
				U32TRGB(&rgb, oldcolor);
				//计算公式
				rgb.r = ContrastCalc(rgb.r, value);
				rgb.g = ContrastCalc(rgb.g, value);
				rgb.b = ContrastCalc(rgb.b, value);
				//类型转换
				oldcolor = RGB2U32(rgb.r, rgb.g, rgb.b);
				PutPixel(j, i, oldcolor);
			}
		}
	}
	else
	{
		//范围超出
		return -1;
	}
	return 0;
}

u8 ContrastCalc(u8 color,int value)
{
	int tcolor;
	tcolor = -1.29 * value * pow(color, 3) * 1e-6 + 4.93 * value * pow(color, 2) * 1e-4 + (1 - 4.18 * value * 1e-2) * color;
	//函数原型为：f(x)=a*x^3+bx^2+cx，通过此函数模拟“S”型灰度曲线。（具体推导见报告）
	if (tcolor > 255)
	{
		return 255;
	}
	else if (tcolor < 0)
	{
		return 0;
	}
	else
	{
		return tcolor;
	}
}

int ImageSaturation(BMPATTR attr, int value)
{
	int i, j;		//循环变量
	u32 oldcolor;	//色彩变量
	RGB rgb;		//色彩分量
	HSL hsl;		//色彩分量

	if (value >= -100 && value <= 100)
	{	//value的值范围限定为**************，而实际上应该是**************，这里为了减少画质损失因此缩小范围。
		for (i = attr.y1; i < attr.y2; i++)
		{
			for (j = attr.x1; j < attr.x2; j++)
			{
				oldcolor = GetPixel(j, i);
				//类型转换
				U32TRGB(&rgb, oldcolor);
				RGB2HSL(rgb, &hsl.h, &hsl.s, &hsl.l);
				//计算公式
				hsl.s = hsl.s * (1 + value / 100.0);
				if (hsl.s > 1)
				{
					hsl.s = 1.0;
				}
				else if (hsl.s < 0)
				{
					hsl.s = 0.0;
				}
				else
				{
					;
				}
				//类型转换
				HSL2RGB(&rgb.r, &rgb.g, &rgb.b, hsl);
				oldcolor = RGB2U32(rgb.r, rgb.g, rgb.b);

				PutPixel(j, i, oldcolor);
			}
		}
	}
	else
	{
		//范围超出
		return -1;
	}
	return 0;
}

int ImageLightness(BMPATTR attr, int value)
{
	int i, j;		//循环变量
	u32 oldcolor;	//色彩变量
	RGB rgb;		//色彩分量
	HSL hsl;		//色彩分量

	if (value >= -40 && value <= 40)
	{	//value的值范围限定为**************。
		for (i = attr.y1; i < attr.y2; i++)
		{
			for (j = attr.x1; j < attr.x2; j++)
			{
				oldcolor = GetPixel(j, i);
				//类型转换
				U32TRGB(&rgb, oldcolor);
				RGB2HSL(rgb, &hsl.h, &hsl.s, &hsl.l);
				//计算公式
				hsl.l = hsl.l * (1 + value / 100.0);
				if (hsl.l > 1)
				{
					hsl.l = 1.0;
				}
				else if (hsl.s < 0)
				{
					hsl.l = 0.0;
				}
				else
				{
					;
				}
				//类型转换
				HSL2RGB(&rgb.r, &rgb.g, &rgb.b, hsl);
				oldcolor = RGB2U32(rgb.r, rgb.g, rgb.b);

				PutPixel(j, i, oldcolor);
			}
		}
	}
	else
	{
		//范围超出
		return -1;
	}
	return 0;
}

int ImageAdjustment(BMPATTR* bmpattr)
{




}