#include "draw.h"

int DrawPen(BMPATTR bmpattr, MENUSTATE* state)
{
	MOUSE mouse_old, mouse_new;
	if (bmpattr.flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}
	Rectangle(12, 52, 68, 98, 0xff0000, 2);
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
			mouse_old = mouse_new;
			if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2))
			{
				MouseStatus(&mouse_old);
				DrawPixel(bmpattr, mouse_old.x, mouse_old.y, state->color, state->size);
			}
			else if (MouseDown(10, 0, 70, 50))
			{
				//打开
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 20;
			}
			else if (MouseDown(70, 0, 130, 50))
			{
				//保存
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 30;
			}
			else if (MouseDown(130, 0, 190, 50))
			{
				//新建
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 40;
			}
			else if (MouseDown(10, 50, 70, 100))
			{
				//画笔
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 0;
			}
			else if (MouseDown(70, 50, 130, 100))
			{
				//裁剪
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 60;
			}
			// else if(MouseDown(130,50,190,100))
			// {
				//图形
				//Rectangle(12, 52, 68, 98, Gray, 2);
				// return 
			// }
			 else if(MouseDown(700,50,750,100))
			 {
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectSize(&state->size, &state->size2);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
			 }
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&state->color);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 90;
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 95;
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 100;
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				Rectangle(12, 52, 68, 98, Gray, 2);
				return 105;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
		}
	}
}

int DrawPixel(BMPATTR bmpattr, int x, int y, u32 color, u8 size)
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

int SelectSize(u8* size1, u8* size2)
{
	int s1 = *size1, s2 = *size2;
	char c1[2], c2[2];
	MOUSE mouse_old, mouse_new;

	BmpSave(248, 198, 552, 352, "DATA//BK4");
	DrawSizeBox();
	itoa(s1, c1, 10);
	itoa(s2, c2, 10);
	TextASC24(385, 260, 24, 0, c1);
	TextASC24(385, 300, 24, 0, c2);

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
			if (MouseDown(425, 265, 450, 285))
			{
				if (s1 < 8)
				{
					s1++;
					itoa(s1, c1, 10);
					Bar(380, 260, 415, 290, Gray);
					TextASC24(385, 260, 24, 0, c1);
				}
				else
				{
					;
				}
			}
			else if (MouseDown(455, 265, 480, 285))
			{
				if (s1 > 1)
				{
					s1--;
					itoa(s1, c1, 10);
					Bar(380, 260, 415, 290, Gray);
					TextASC24(385, 260, 24, 0, c1);
				}
				else
				{
					;
				}
			}
			else if (MouseDown(425, 305, 450, 325))
			{
				if (s2 < 5)
				{
					s2++;
					itoa(s2, c2, 10);
					Bar(380, 300, 415, 330, Gray);
					TextASC24(385, 300, 24, 0, c2);
				}
				else
				{
					;
				}
			}
			else if (MouseDown(455, 305, 480, 325))
			{
				if (s2 > 1)
				{
					s2--;
					itoa(s2, c2, 10);
					Bar(380, 300, 415, 330, Gray);
					TextASC24(385, 300, 24, 0, c2);
				}
				else
				{
					;
				}
			}
			else if (MouseDown(490, 265, 535, 285))
			{
				//确定
				*size1 = s1;
				*size2 = s2;
				MousePutBk(mouse_new.x, mouse_new.y);
				BmpPut(248, 198, "DATA//BK4");
				return 0;
			}
			else if (MouseDown(490, 305, 535, 325))
			{
				//取消
				MousePutBk(mouse_new.x, mouse_new.y);
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