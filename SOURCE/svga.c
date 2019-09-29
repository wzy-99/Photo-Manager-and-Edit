#include "svga.h"

void SetSVGA()
{
	union REGS r;

	r.x.ax = 0x4f02;
	r.x.bx = 0x115;
	int86(0x10, &r, &r);

	//SVGA模式设置失败
	if (r.x.ax != 0x004f)
	{
		printf("SET SVGA ERROR!\n");
		delay(5000);
		exit(1);
	}
}

void SelectPage(register u8 page)
{
	union REGS r;
	static unsigned char old_page = 0;
	static unsigned char flag = 0;

	r.x.ax = 0x4f05;
	r.x.bx = 0;

	//初始选页
	if (flag == 0)
	{
		old_page = page;
		r.x.dx = page;
		int86(0x10, &r, &r);
		flag++;
	}

	//页面改变时进行换页
	if (page != old_page)
	{
		old_page = page;
		r.x.dx = page;
		int86(0x10, &r, &r);
	}
}

void PutPixel(int x, int y, u32 color)
{
	//显存指针
	u32 far* const buf = (u32 far*)0xa0000000L;

	u8  new_page;
	u32 page;

	//超界退出
	if (x < 0 || x >(SCR_WIDTH - 1) || y < 0 || y >(SCR_HEIGHT - 1))
	{
		return;
	}

	//每64K÷4=2^14个像素换页
	page = ((u32)y * 800) + x;
	new_page = page >> 14;

	SelectPage(new_page);

	//显存赋值
	buf[page] = color;
}

u32 GetPixel(int x, int y)
{
	u32 far* const buf = (u32 far*)0xa0000000L;

	u8 new_page;
	u32 page;

	if (x < 0 || x >(SCR_WIDTH - 1) || y < 0 || y >(SCR_HEIGHT - 1))
	{
		return 0;
	}

	page = ((u32)y * 800) + x;
	new_page = page >> 14;
	SelectPage(new_page);

	return buf[page];
}


void Bar(int x1, int y1, int x2, int y2, u32 color)
{
	int i, j;
	int temp;

	//交换数值
	if (x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	//超界
	if (x1 < 0  )
	{
		x1 = 0;
	}
	if (x2 > (SCR_WIDTH - 1))
	{
		x2 = SCR_WIDTH - 1;
	}
	if (y1 < 0)
	{
		y1 = 0;
	}
	if (y2 > (SCR_HEIGHT - 1))
	{
		y2 = SCR_HEIGHT - 1;
	}

	//逐列画点
	for (i = x1; i <= x2; i++)
	{
		for (j = y1; j <= y2; j++)
		{
			PutPixel(i, j, color);
		}
	}
}

//void Line(int x1, int y1, int x2, int y2, u32 color)
//{
//	int	dx, dy;
//	int dx2, dy2;
//	int xinc, yinc;
//	int d, dxy;
//	int i;
//	dx = abs(x2 - x1);
//	dx2 = dx << 1;
//	dy = abs(y2 - y1);
//	dy2 = dy << 1;
//	if (x2 > x1)
//	{
//		xinc = 1;
//	}
//	else if (x2 == x1)
//	{
//		if (y1 > y2)
//		{
//			dx = y1;
//			y1 = y2;
//			y2 = dx;
//		}
//		for (dx = y1; dx <= y2; dx++)
//		{
//			PutPixel(x1, dx, color);
//		}
//
//		return;
//	}
//	else
//	{
//		xinc = -1;
//	}
//	if (y2 > y1)
//	{
//		yinc = 1;
//	}
//	else if (y2 == y1)
//	{
//		for (i = x1; i <= x2; i++)
//		{
//			PutPixel(i, y1, color);
//		}
//		return;
//	}
//	else
//	{
//		yinc = -1;
//	}
//	/*******************************
//	以下运用Bresenham算法生成直线。
//	该算法是得到公认的成熟的快速算法。
//	具体细节略去。
//	*******************************/
//	PutPixel(x1, y1, color);
//	if (dx >= dy)
//	{
//		d = dy2 - dx;
//		dxy = dy2 - dx2;
//		while (dx--)
//		{
//			if (d <= 0)
//			{
//				d += dy2;
//			}
//			else
//			{
//				d += dxy;
//				y1 += yinc;
//			}
//			x1 += xinc;
//			PutPixel(x1, y1, color);
//		}
//	}
//	else
//	{
//		d = dx2 - dy;
//		dxy = dx2 - dy2;
//		while (dy--)
//		{
//			if (d <= 0)
//			{
//				d += dx2;
//			}
//			else
//			{
//				d += dxy;
//				x1 += xinc;
//			}
//			y1 += yinc;
//			PutPixel(x1, y1, color);
//		}
//	}
//}


//设置逻辑扫描长度
//void SetLogicalLine(u16 pixels)
//{
//	union REGS r;
//	r.x.ax = 0x4f06;
//	r.x.bx = 0;
//	r.x.cx = pixels;
//
//	int86(0x10, &r, &r);
//}
