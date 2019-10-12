#include "pic.h"

int ImgRectangle(int x1, int y1, int x2, int y2, u32 color, u8 size)
{
	int temp1, temp2;
	int i, j;
	if (x1 > x2)
	{
		temp1 = x1;
		x1 = x2;
		x2 = temp1;
	}
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

int ImgLine(BMPATTR bmpattr, int x1, int y1, int x2, int y2, u32 color, u8 size)
{
	int x, y;
	int dx, dy;
	int s1, s2;
	int p;
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

	p = 2 * dy - dx;
	for (i = 1; i <= dx; i++)
	{
		ImgDrawPixel(bmpattr, x, y, color, size);
		if (p >= 0)
		{
			if (interchange == 0)
			{
				y = y + s2;
			}
			else
			{
				x = x + s1;
			}
			p = p - 2 * dx;
		}
		if (interchange == 0)
		{
			x = x + s1;
		}
		else
		{
			y = y + s2;
		}
		p = p + 2 * dy;
	}
	return 1;
}

int Line(int x1, int y1, int x2, int y2, u32 color, u8 size)
{
	int x, y;
	int dx, dy;
	int s1, s2;
	int p;
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

	p = 2 * dy - dx;
	for (i = 1; i <= dx; i++)
	{
		DrawPixel(x, y, color, size);
		if (p >= 0)
		{
			if (interchange == 0)
			{
				y = y + s2;
			}
			else
			{
				x = x + s1;
			}
			p = p - 2 * dx;
		}
		if (interchange == 0)
		{
			x = x + s1;
		}
		else
		{
			y = y + s2;
		}
		p = p + 2 * dy;
	}
	return 1;
}

int ImgTriangle(BMPATTR bmpattr, int x1, int y1, int x2, int y2, int x3, int y3, u32 color, u8 size)
{
	ImgLine(bmpattr, x1, y1, x2, y2, color, size);
	ImgLine(bmpattr, x1, y1, x3, y3, color, size);
	ImgLine(bmpattr, x2, y2, x3, y3, color, size);
	return 1;
}

int Triangle(int x1, int y1, int x2, int y2, int x3, int y3, u32 color, u8 size)
{
	Line(x1, y1, x2, y2, color, size);
	Line(x1, y1, x3, y3, color, size);
	Line(x2, y2, x3, y3, color, size);
	return 1;
}

int ImgCircle(BMPATTR bmpattr, int x, int y, int r, u32 color, u8 size)
{
	int a = 0;
	int	b = r;
	int	d = 3 - 2 * r;
	// 如果圆在图片可见区域外，直接退出
	if (x - r < bmpattr.x1 || x + r > bmpattr.x1 + bmpattr.width || y - r < bmpattr.y1 || y + r > bmpattr.y1 + bmpattr.heigth)
	{
		return 0;
	}
	while (a <= b)
	{
		DrawImgCircle_8(bmpattr, x, y, a, b, color, size);
		if (d < 0)
		{
			d = d + 4 * a + 6;
		}
		else
		{
			d = d + 4 * (a - b) + 10;
			b--;
		}
		a++;
	}
	return 1;
}

int Circle(int x, int y, int r, u32 color, u8 size)
{
	int a = 0;
	int	b = r;
	int	d = 3 - 2 * r;
	while (a <= b)
	{
		DrawCircle_8(x, y, a, b, color, size);
		if (d < 0)
		{
			d = d + 4 * a + 6;
		}
		else
		{
			d = d + 4 * (a - b) + 10;
			b--;
		}
		a++;
	}
	return 1;
}

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

int ImgDrawPixel(BMPATTR bmpattr, int x, int y, u32 color, u8 size)
{
	int i = bmpattr.x1;
	int j = bmpattr.y1;
	if (i < x - size)
	{
		i = x - size;
	}
	if (j < y - size)
	{
		j = y - size;
	}
	Bar(i, j, x, y, color);
	return 1;
}

int DrawPixel(int x, int y, u32 color, u8 size)
{
	int i = x - size;
	int j = y - size;
	Bar(i, j, x, y, color);
	return 1;
}
