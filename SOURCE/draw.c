#include "draw.h"

int DrawPen(BMPATTR bmpattr, MENUSTATE* state)
{
	MOUSE mouse_old, mouse_new;
	if (bmpattr.flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}

	ImgRectangle(12, 52, 68, 98, 0xff0000, 2);
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
				ImgDrawPixel(bmpattr, mouse_old.x, mouse_old.y, state->color, state->size);
			}
			else if (MouseDown(10, 0, 70, 50))
			{
				//打开
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 20;
			}
			else if (MouseDown(70, 0, 130, 50))
			{
				//保存
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 30;
			}
			else if (MouseDown(130, 0, 190, 50))
			{
				//新建
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 40;
			}
			else if (MouseDown(10, 50, 70, 100))
			{
				//画笔
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 0;
			}
			else if (MouseDown(70, 50, 130, 100))
			{
				//裁剪
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 60;
			}
			 //else if(MouseDown(130,50,190,100))
			 //{
				////图形
				//Rectangle(12, 52, 68, 98, ThemeColor2, 2);
				//return 65
			 //}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 70;
			}
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
			else if (MouseDown(703, 570, 735, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 85;
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 90;
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 95;
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 100;
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
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
					Bar(380, 260, 415, 290, ThemeColor2);
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
					Bar(380, 260, 415, 290, ThemeColor2);
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
					Bar(380, 300, 415, 330, ThemeColor2);
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
					Bar(380, 300, 415, 330, ThemeColor2);
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

int DrawPicture(BMPATTR bmpattr, MENUSTATE* state)
{
	MOUSE mouse_old, mouse_new;

	if (bmpattr.flag == 0)
	{
		WarnBox("图片未打开");
		return	0;
	}

	ImgRectangle(132, 52, 188, 98, 0xff0000, 2);
	Line(207, 61, 234, 89, 0x000000, 2);
	Triangle(275, 61, 256, 89, 293, 89, 0x000000, 2);
	ImgRectangle(322, 61, 371, 89, 0x000000, 2);
	Circle(418, 75, 14, 0x000000, 2);

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

			if (MouseDown(190, 50, 250, 100))
			{
				MousePutBk(mouse_new.x, mouse_new.y);
				DrawLine(bmpattr, state);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(250, 50, 300, 100))
			{
				MousePutBk(mouse_new.x, mouse_new.y);
				DrawTriangle(bmpattr, state);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(300, 50, 380, 100))
			{
				MousePutBk(mouse_new.x, mouse_new.y);
				DrawRectangle(bmpattr, state);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(380, 50, 450, 100))
			{
				MousePutBk(mouse_new.x, mouse_new.y);
				DrawCircle(bmpattr, state);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(10, 0, 70, 50))
			{
				//打开
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 20;
			}
			else if (MouseDown(70, 0, 130, 50))
			{
				//保存
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 30;
			}
			else if (MouseDown(130, 0, 190, 50))
			{
				//新建
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 40;
			}
			else if (MouseDown(10, 50, 70, 100))
			{
				//画笔
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 50;
			}
			else if (MouseDown(70, 50, 130, 100))
			{
				//裁剪
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 60;
			}
			else if (MouseDown(130, 50, 190, 100))
			{
				//图形
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 0;
			}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 70;
			}
			else if (MouseDown(700, 50, 750, 100))
			{
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectSize(&state->size, &state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&state->color);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(703, 570, 735, 600))
			{
				//设置
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 85;
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 90;
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 95;
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 100;
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
				Bar(192, 52, 448, 98, ThemeColor2);
				return 105;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
			mouse_old = mouse_new;
		}
	}
}

int DrawLine(BMPATTR bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2;
	int tx1, ty1, tx2, ty2;
	int flag = 0;
	MOUSE mouse_old, mouse_new;
	char xystring1[16];
	char xystring2[16];

	ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
	ImgRectangle(192, 52, 248, 98, 0xff0000, 2);
	ImgRectangle(252, 52, 298, 98, ThemeColor2, 2);
	ImgRectangle(302, 52, 378, 98, ThemeColor2, 2);
	ImgRectangle(382, 52, 448, 98, ThemeColor2, 2);

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

			if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr.x1;
				ty1 = y1 - bmpattr.y1;

				Bar(200, 570 + 1, 700, 600, ThemeColor2);
				sprintf(xystring1, "坐标1:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring1);
			}
			else if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 0;
				tx2 = x2 - bmpattr.x1;
				ty2 = y2 - bmpattr.y1;

				//Bar(400, 570, 600, 600, ThemeColor2);
				sprintf(xystring2, "坐标2:%d,%d", tx2, ty2);
				TextGB16(450, 580, 14, 0, xystring2);

				MousePutBk(mouse_new.x, mouse_new.y);
				ImgLine(bmpattr, x1, y1, x2, y2, state->color, state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(190, 50, 250, 100))
			{
				//再次点击，退出画线
				Bar(200, 570, 700, 600, ThemeColor2);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(192, 52, 248, 98, ThemeColor2, 2);
				ImgRectangle(132, 52, 188, 98, 0xff0000, 2);
				return 0;
			}
			else if (MouseDown(700, 50, 750, 100))
			{
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectSize(&state->size, &state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&state->color);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
			mouse_old = mouse_new;
		}
	}
}

int DrawTriangle(BMPATTR bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2, x3, y3;
	int tx1, ty1, tx2, ty2, tx3, ty3;
	int flag = 0;
	char xystring1[16];
	char xystring2[16];
	char xystring3[16];
	MOUSE mouse_old, mouse_new;

	ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
	ImgRectangle(192, 52, 248, 98, ThemeColor2, 2);
	ImgRectangle(252, 52, 298, 98, 0xff0000, 2);
	ImgRectangle(302, 52, 378, 98, ThemeColor2, 2);
	ImgRectangle(382, 52, 448, 98, ThemeColor2, 2);

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

			if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr.x1;
				ty1 = y1 - bmpattr.y1;

				Bar(200, 570, 600, 600, ThemeColor2);
				sprintf(xystring1, "点1:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring1);
			}
			else if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 2;
				tx2 = x2 - bmpattr.x1;
				ty2 = y2 - bmpattr.y1;

				//Bar(200, 570, 600, 600, ThemeColor2);
				sprintf(xystring2, "点2:%d,%d", tx2, ty2);
				TextGB16(350, 580, 14, 0, xystring2);
			}
			else if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 2)
			{
				x3 = mouse_new.x;
				y3 = mouse_new.y;
				flag = 0;
				tx3 = x3 - bmpattr.x1;
				ty3 = y3 - bmpattr.y1;

				//Bar(200, 570, 600, 600, ThemeColor2);
				sprintf(xystring3, "点3:%d,%d", tx3, ty3);
				TextGB16(500, 580, 14, 0, xystring3);

				MousePutBk(mouse_new.x, mouse_new.y);
				ImgTriangle(bmpattr, x1, y1, x2, y2, x3, y3, state->color, state->size2);
			}
			else if (MouseDown(250, 50, 300, 100))
			{
				//再次点击，退出画三角形
				Bar(200, 570, 700, 600, ThemeColor2);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(252, 52, 298, 98, ThemeColor2, 2);
				ImgRectangle(132, 52, 188, 98, 0xff0000, 2);
				return 0;
			}
			else if (MouseDown(700, 50, 750, 100))
			{
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectSize(&state->size, &state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&state->color);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
			mouse_old = mouse_new;
		}
	}
}

int DrawRectangle(BMPATTR bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2;
	int tx1, ty1, tx2, ty2;
	int flag = 0;
	char xystring1[16];
	char xystring2[16];
	MOUSE mouse_old, mouse_new;

	ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
	ImgRectangle(192, 52, 248, 98, ThemeColor2, 2);
	ImgRectangle(252, 52, 298, 98, ThemeColor2, 2);
	ImgRectangle(302, 52, 378, 98, 0xff0000, 2);
	ImgRectangle(382, 52, 448, 98, ThemeColor2, 2);

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

			if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr.x1;
				ty1 = y1 - bmpattr.y1;

				Bar(200, 570 + 1, 700, 600, ThemeColor2);
				sprintf(xystring1, "坐标1:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring1);
			}
			else if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 0;
				tx2 = x2 - bmpattr.x1;
				ty2 = y2 - bmpattr.y1;

				//Bar(200, 570, 600, 600, ThemeColor2);
				sprintf(xystring2, "坐标2:%d,%d", tx2, ty2);
				TextGB16(450, 580, 14, 0, xystring2);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(x1, y1, x2, y2, state->color, state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(300, 50, 380, 100))
			{
				//再次点击，退出画矩形
				Bar(200, 570, 700, 600, ThemeColor2);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(302, 52, 378, 98, ThemeColor2, 2);
				ImgRectangle(132, 52, 188, 98, 0xff0000, 2);
				return 0;
			}
			else if (MouseDown(700, 50, 750, 100))
			{
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectSize(&state->size, &state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&state->color);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
			mouse_old = mouse_new;
		}
	}
}

int DrawCircle(BMPATTR bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2;
	int tx1, ty1;
	int r;
	int flag = 0;
	char xystring[16];
	char rstring[16];
	MOUSE mouse_old, mouse_new;

	ImgRectangle(132, 52, 188, 98, ThemeColor2, 2);
	ImgRectangle(192, 52, 248, 98, ThemeColor2, 2);
	ImgRectangle(252, 52, 298, 98, ThemeColor2, 2);
	ImgRectangle(302, 52, 378, 98, ThemeColor2, 2);
	ImgRectangle(382, 52, 448, 98, 0xff0000, 2);

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

			if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr.x1;
				ty1 = y1 - bmpattr.y1;

				Bar(200, 570 + 1, 700, 600, ThemeColor2);
				sprintf(xystring, "坐标:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring);
			}
			else if (MouseDown(bmpattr.x1, bmpattr.y1, bmpattr.x2, bmpattr.y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 0;
				r = (int)sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));

				//Bar(200, 570, 600, 600, ThemeColor2);
				sprintf(rstring, "半径:%d", r);
				TextGB16(450, 580, 14, 0, rstring);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgCircle(bmpattr, x1, y1, r, state->color, state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(380, 50, 450, 100))
			{
				//再次点击，退出画圆
				Bar(200, 570, 700, 600, ThemeColor2);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(382, 52, 448, 98, ThemeColor2, 2);
				ImgRectangle(132, 52, 188, 98, 0xff0000, 2);
				return 0;
			}
			else if (MouseDown(700, 50, 750, 100))
			{
				//粗细
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectSize(&state->size, &state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 50, 800, 100))
			{
				//颜色
				MousePutBk(mouse_new.x, mouse_new.y);
				SelectColor(&state->color);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}
			mouse_old = mouse_new;
		}
	}
}