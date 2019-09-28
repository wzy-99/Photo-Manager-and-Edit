#include "pic.h"

int Rectangle(int x1, int y1, int x2, int y2, u32 color, u8 size)
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
		//size¹ý´ó
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