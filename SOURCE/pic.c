#include "pic.h"

/**
*  函数名      ImgRectangle
*  传入参数    x1       矩形一个顶点的横坐标
			   y1       矩形一个顶点的纵坐标
			   x2       矩形另一个对角顶点的横坐标
			   y2       矩形另一个对角顶点的纵坐标
			   color    当前颜色值
			   size     当前图形粗细值
*  功能        画矩形
*  返回值      0           size过大
			   1           函数成功运行
**/
int ImgRectangle(int x1, int y1, int x2, int y2, u32 color, u8 size)
{
	int temp1, temp2;    //用于交换的临时变量
	int i, j;            //循环变量

	/*确保x1 < x2*/
	if (x1 > x2)
	{
		temp1 = x1;
		x1 = x2;
		x2 = temp1;
	}

	/*确保y1 < y2*/
	if (y1 > y2)
	{
		temp2 = y1;
		y1 = y2;
		y2 = temp2;
	}

	if (2 * size > x2 - x1 || 2 * size > y2 - y1)
	{
		//size过大
		return 0;
	}

	/*逐点将矩形画出*/
	for (j = y1; j <= y2; j++)
	{
		for (i = x1; i <= x2; i++)
		{
			if (i > x1 + size && i < x2 - size && j > y1 + size && j < y2 - size)
			{
				continue;
			}
			PutPixel(i, j, color);
		}
	}

	return 1;
}

/**
*  函数名      ImgLine
*  传入参数    bmpattr    图片
			   x1         直线一个端点的横坐标
			   y1         直线一个端点的纵坐标
			   x2         直线另一个端点的横坐标
			   y2         直线另一个端点的纵坐标
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        在图片内画直线
*  返回值      1           函数成功运行
**/
int ImgLine(BMPATTR bmpattr, int x1, int y1, int x2, int y2, u32 color, u8 size)
{
	int x, y;             //下一个要画的点的坐标
	int dx, dy;           //x,y距离x2,y2（终点）分别还有多远
	int s1, s2;           //下一个要画的点的方向
	int error;                //误差判别变量
	int temp;             //用于交换dx，dy的临时变量
	int interchange;      //是否交换
	int i;                //循环变量

	x = x1;               //所画的第一个点为直线的一个端点
	y = y1;
	dx = abs(x2 - x1);    //x方向到终点距离的初始值
	dy = abs(y2 - y1);    //y方向到终点距离的初始值

	/*如果x2 > x1, 向右画点*/
	if (x2 > x1)
	{
		s1 = 1;
	}

	/*否则，向左画点*/
	else
	{
		s1 = -1;
	}

	/*如果y2 > y1, 向下画点*/
	if (y2 > y1)
	{
		s2 = 1;
	}

	/*否则，向上画点*/
	else
	{
		s2 = -1;
	}

	/*如果y方向距离终点更远，将dx,dy交换*/
	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	else
	{
		interchange = 0;
	}

	error = 2 * dy - dx;    //误差判别变量的初始值

	/*依次画出每一个点，共dx个，即得到从(x1,y1)到(x2,y2)的直线*/
	for (i = 1; i <= dx; i++)
	{
		ImgDrawPixel(bmpattr, x, y, color, size);    //在图片内画点

		/*如果误差判别变量大于0，则需在距离终点较近的方向向前移动一步*/
		if (error >= 0)
		{
			/*若dx，dy未交换，则在y方向移动一步，否则在x方向移动一步*/
			/*即在距离较近的方向移动一步*/
			if (interchange == 0)
			{
				y = y + s2;
			}
			else
			{
				x = x + s1;
			}

			/*此时的误差判别变量为*/
			error = error - 2 * dx;
		}

		/*若dx，dy未交换，则在x方向移动一步，否则在y方向移动一步*/
		/*即每一次循环，均在距离较远的方向移动一步*/
		if (interchange == 0)
		{
			x = x + s1;
		}
		else
		{
			y = y + s2;
		}

		/*每一次循环，误差判别变量变为*/
		error = error + 2 * dy;
	}

	return 1;
}

/**
*  函数名      Line
*  传入参数    x1         直线一个端点的横坐标
			   y1         直线一个端点的纵坐标
			   x2         直线另一个端点的横坐标
			   y2         直线另一个端点的纵坐标
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        画直线
*  返回值      1           函数成功运行
**/
int Line(int x1, int y1, int x2, int y2, u32 color, u8 size)
{
	int x, y;
	int dx, dy;
	int s1, s2;
	int error;
	int temp;
	int interchange;
	int i;

	x = x1;
	y = y1;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	if (x2 > x1)
	{
		s1 = 1;
	}
	else
	{
		s1 = -1;
	}

	if (y2 > y1)
	{
		s2 = 1;
	}
	else
	{
		s2 = -1;
	}

	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	else
	{
		interchange = 0;
	}

	error = 2 * dy - dx;

	for (i = 1; i <= dx; i++)
	{
		DrawPixel(x, y, color, size);    //画点

		if (error >= 0)
		{
			if (interchange == 0)
			{
				y = y + s2;
			}
			else
			{
				x = x + s1;
			}

			error = error - 2 * dx;
		}

		if (interchange == 0)
		{
			x = x + s1;
		}
		else
		{
			y = y + s2;
		}

		error = error + 2 * dy;
	}

	return 1;
}

/**
*  函数名      ImgTriangle
*  传入参数    bmpattr    图片
			   x1         三角形第一个顶点的横坐标
			   y1         三角形第一个顶点的纵坐标
			   x2         三角形第二个顶点的横坐标
			   y2         三角形第二个顶点的纵坐标
			   x3         三角形第三个顶点的横坐标
			   y3         三角形第三个顶点的纵坐标
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        在图片内画三角形
*  返回值      1           函数成功运行
**/
int ImgTriangle(BMPATTR bmpattr, int x1, int y1, int x2, int y2, int x3, int y3, u32 color, u8 size)
{
	ImgLine(bmpattr, x1, y1, x2, y2, color, size);
	ImgLine(bmpattr, x1, y1, x3, y3, color, size);
	ImgLine(bmpattr, x2, y2, x3, y3, color, size);
	return 1;
}

/**
*  函数名      Triangle
*  传入参数    bmpattr    图片
			   x1         三角形第一个顶点的横坐标
			   y1         三角形第一个顶点的纵坐标
			   x2         三角形第二个顶点的横坐标
			   y2         三角形第二个顶点的纵坐标
			   x3         三角形第三个顶点的横坐标
			   y3         三角形第三个顶点的纵坐标
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        画三角形
*  返回值      1           函数成功运行
**/
int Triangle(int x1, int y1, int x2, int y2, int x3, int y3, u32 color, u8 size)
{
	Line(x1, y1, x2, y2, color, size);
	Line(x1, y1, x3, y3, color, size);
	Line(x2, y2, x3, y3, color, size);
	return 1;
}

/**
*  函数名      ImgCircle
*  传入参数    bmpattr    图片
			   x          圆心的横坐标
			   y          圆心的纵坐标
			   r          圆的半径
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        在图片内画圆
*  返回值      1           函数成功运行
**/
int ImgCircle(BMPATTR bmpattr, int x, int y, int r, u32 color, u8 size)
{
	int a = 0;            //定义所画点位置相对于圆心的横坐标，并赋初值（首先画圆心正下方距离半径处的那个点）
	int	b = r;            //定义所画点位置相对于圆心的纵坐标，并赋初值（首先画圆心正下方距离半径处的那个点）
	int	error = 3 - 2 * r;    //定义误差判别变量，并赋初值

	// 如果圆在图片可见区域外，直接退出
	if (x - r < bmpattr.x1 || x + r > bmpattr.x1 + bmpattr.width || y - r < bmpattr.y1 || y + r > bmpattr.y1 + bmpattr.heigth)
	{
		return 0;
	}

	/*在一个1/8圆弧上逐点画圆（一次画8个点）*/
	while (a <= b)
	{
		DrawImgCircle_8(bmpattr, x, y, a, b, color, size);    //根据圆的八对称性在图片内画圆

		/*如果误差判别变量小于0，直接将误差判别变量修改为*/
		if (error < 0)
		{
			error = error + 4 * a + 6;
		}

		/*否则，将误差判别变量修改为*/
		/*并将所画点位置的纵坐标-1*/
		else
		{
			error = error + 4 * (a - b) + 10;
			b--;
		}

		/*每一次循环，所画点位置的横坐标+1*/
		a++;
	}

	return 1;
}

/**
*  函数名      Circle
*  传入参数    x          圆心的横坐标
			   y          圆心的纵坐标
			   r          圆的半径
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        在图片内画圆
*  返回值      1           函数成功运行
**/
int Circle(int x, int y, int r, u32 color, u8 size)
{
	int a = 0;
	int	b = r;
	int	error = 3 - 2 * r;

	while (a <= b)
	{
		DrawCircle_8(x, y, a, b, color, size);

		if (error < 0)
		{
			error = error + 4 * a + 6;
		}
		else
		{
			error = error + 4 * (a - b) + 10;
			b--;
		}

		a++;
	}

	return 1;
}

/**
*  函数名      DrawImgCircle_8
*  传入参数    bmpattr    图片
			   x          圆心的横坐标
			   y          圆心的纵坐标
			   a          所画点位置相对于圆心的横坐标
			   b          所画点位置相对于圆心的纵坐标
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        根据圆的八对称性画出8个点
*  返回值      无
**/
void DrawImgCircle_8(BMPATTR bmpattr, int x, int y, int a, int b, u32 color, u8 size)
{
	ImgDrawPixel(bmpattr, x + a, y + b, color, size);
	ImgDrawPixel(bmpattr, x - a, y + b, color, size);
	ImgDrawPixel(bmpattr, x + a, y - b, color, size);
	ImgDrawPixel(bmpattr, x - a, y - b, color, size);
	ImgDrawPixel(bmpattr, x + b, y + a, color, size);
	ImgDrawPixel(bmpattr, x - b, y + a, color, size);
	ImgDrawPixel(bmpattr, x + b, y - a, color, size);
	ImgDrawPixel(bmpattr, x - b, y - a, color, size);
}

/**
*  函数名      DrawCircle_8
*  传入参数    x          圆心的横坐标
			   y          圆心的纵坐标
			   a          所画点位置相对于圆心的横坐标
			   b          所画点位置相对于圆心的纵坐标
			   color      当前颜色值
			   size       当前图形粗细值
*  功能        根据圆的八对称性画出8个点
*  返回值      无
**/
void DrawCircle_8(int x, int y, int a, int b, u32 color, u8 size)
{
	DrawPixel(x + a, y + b, color, size);
	DrawPixel(x - a, y + b, color, size);
	DrawPixel(x + a, y - b, color, size);
	DrawPixel(x - a, y - b, color, size);
	DrawPixel(x + b, y + a, color, size);
	DrawPixel(x - b, y + a, color, size);
	DrawPixel(x + b, y - a, color, size);
	DrawPixel(x - b, y - a, color, size);
}

/**
*  函数名      ImgDrawPixel
*  传入参数    bmpattr    图片
			   x          所画点位置的横坐标
			   y          所画点位置的纵坐标
			   color    当前颜色值
			   size     当前画笔（图形）粗细值
*  功能        在图片内画点
*  返回值      1           函数成功运行
**/
int ImgDrawPixel(BMPATTR bmpattr, int x, int y, u32 color, u8 size)
{
	int rx = bmpattr.x1;    //定义所画点（实心矩形）的另一个顶点的横坐标，并赋初值为图片左上角的横坐标
	int ry = bmpattr.y1;    //定义所画点（实心矩形）的另一个顶点的纵坐标，并赋初值为图片左上角的纵坐标

	/*如果size没有超出图片左边缘，则将所画矩形的宽改为正常的size*/
	if (rx < x - size)
	{
		rx = x - size;
	}

	/*如果size没有超出图片上边缘，则将所画矩形的高改为正常的size*/
	if (ry < y - size)
	{
		ry = y - size;
	}

	/*在(x,y)处画出该点（实心矩形）*/
	Bar(rx, ry, x, y, color);
	return 1;
}

/**
*  函数名      DrawPixel
*  传入参数    x          所画点位置的横坐标
			   y          所画点位置的纵坐标
			   color    当前颜色值
			   size     当前画笔（图形）粗细值
*  功能        画点
*  返回值      1           函数成功运行
**/
int DrawPixel(int x, int y, u32 color, u8 size)
{
	int rx = x - size;
	int ry = y - size;
	Bar(rx, ry, x, y, color);
	return 1;
}

/**
*  函数名      ImgShading
*  传入参数    x1        矩形一个顶点的横坐标
			   y1        矩形一个顶点的纵坐标
			   x2        矩形另一个对角顶点的横坐标
			   y2        矩形另一个对角顶点的纵坐标
			   color1    用于渐变的颜色值
			   color2    渐变结束的颜色值
*  功能        画渐变矩形
*  返回值      无
**/
void ImgShading(int x1, int y1, int x2, int y2, u32 color1, u32 color2)
{
	int i = 0, j = 0;           //循环变量
	int temp1, temp2;           //用于交换的临时变量
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

	/*确保x1 < x2*/
	if (x1 > x2)
	{
		temp1 = x1;
		x1 = x2;
		x2 = temp1;
	}

	/*确保y1 < y2*/
	if (y1 > y2)
	{
		temp2 = y1;
		y1 = y2;
		y2 = temp2;
	}

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
*  函数名      ImgMix
*  传入参数    x1        混合矩形区域一个顶点的横坐标
			   y1        混合矩形区域一个顶点的纵坐标
			   x2        混合矩形区域另一个对角顶点的横坐标
			   y2        混合矩形区域另一个对角顶点的纵坐标
			   color1    用于渐变的颜色值
			   color2    渐变结束的颜色值
*  功能        将渐变矩形与图片背景混合
*  返回值      无
**/
void ImgMix(int x1, int y1, int x2, int y2, u32 color1, u32 color2)
{
	int i, j;                      //循环变量
	int temp1, temp2;              //用于交换的临时变量
	const double percent = 0.7;    //混合时背景图案所占的比例
	u32 color_scr1;                //用于获取背景图案的颜色值
	u32	color_scr2;                //用于获取渐变矩形的颜色值
	u32 color_dst;                 //用于计算所得结果的颜色值
	RGB tRGB;                      //将计算结果的颜色值转化为RGB
	RGB tRGB1;                     //将背景图案的颜色值转化为RGB
	RGB tRGB2;                     //将渐变矩形的颜色值转化为RGB
	FILE* fp;                      //将背景图案每一点的颜色值读取出来存入文件中，再从文件中读取颜色值用于计算

	/*以二进制只写模式打开临时文件，如果文件打开失败，退出*/
	if ((fp = fopen("DATA//temp2", "wb")) == NULL)
	{
		exit(0);
	}

	/*确保x1 < x2*/
	if (x1 > x2)
	{
		temp1 = x1;
		x1 = x2;
		x2 = temp1;
	}

	/*确保y1 < y2*/
	if (y1 > y2)
	{
		temp2 = y1;
		y1 = y2;
		y2 = temp2;
	}

	/*读取每一点的颜色值，并写入文件*/
	for (j = y1; j <= y2; j++)
	{
		for (i = x1; i <= x2; i++)
		{
			color_scr1 = GetPixel(i, j);
			fwrite(&color_scr1, 4, 1, fp);
		}
	}

	fclose(fp);    //关闭文件

	ImgShading(x1, y1, x2, y2, color1, color2);    //画渐变矩形

	/*以二进制只读模式打开临时文件，如果文件打开失败，退出*/
	if ((fp = fopen("DATA//temp2", "rb")) == NULL)
	{
		exit(0);
	}

	/*将背景图案的颜色值读出后，与渐变矩形的RGB按一定比例混合*/
	for (j = y1; j <= y2; j++)
	{
		for (i = x1; i <= x2; i++)
		{
			/*分别获取背景图案和渐变矩形的颜色值，并将其转化为RGB*/
			fread(&color_scr1, 4, 1, fp);
			color_scr2 = GetPixel(i, j);
			U32TRGB(&tRGB1, color_scr1);
			U32TRGB(&tRGB2, color_scr2);

			/*计算混合后的RGB*/
			if (tRGB1.r <= 128)
			{
				tRGB.r = (unsigned char)(tRGB1.r * tRGB2.r / 128);
			}
			else
			{
				tRGB.r = (unsigned char)(255 - (255 - tRGB1.r) * (255 - tRGB2.r) / 128);
			}

			if (tRGB1.g <= 128)
			{
				tRGB.g = (unsigned char)(tRGB1.g * tRGB2.g / 128);
			}
			else
			{
				tRGB.g = (unsigned char)(255 - (255 - tRGB1.g) * (255 - tRGB2.g) / 128);
			}

			if (tRGB1.b <= 128)
			{
				tRGB.b = (unsigned char)(tRGB1.b * tRGB2.b / 128);
			}
			else
			{
				tRGB.b = (unsigned char)(255 - (255 - tRGB1.b) * (255 - tRGB2.b) / 128);
			}

			//tRGB.r = (unsigned char)(percent * tRGB1.r + (1 - percent) * tRGB2.r);
			//tRGB.g = (unsigned char)(percent * tRGB1.g + (1 - percent) * tRGB2.g);
			//tRGB.b = (unsigned char)(percent * tRGB1.b + (1 - percent) * tRGB2.b);

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