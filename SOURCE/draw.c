#include "draw.h"

/**
*  函数名      DrawPen
*  传入参数    bmpattr    图片
			   state      菜单状态
*  函数功能    画笔
*  返回值      0          图片未打开
			   1          退出画笔函数
			   20         切换为打开功能
			   30         切换为保存功能
			   40         切换为新建功能
			   45         切换为图库功能
			   60         切换为裁剪功能
			   65         切换为画图形功能
			   70         切换为调整功能
			   85         切换为设置功能
			   90         切换为缩小功能
			   95         切换为放大功能
			   100        切换为旋转功能
			   105        切换为翻转功能
			   120        切换为滤镜功能
**/
int DrawPen(BMPATTR* bmpattr, MENUSTATE* state)
{
	MOUSE mouse_old, mouse_new;    //定义老鼠标和新鼠标

	/*若图片未打开，显示警告框，退出函数*/
	if (bmpattr->flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}

	ImgRectangle(12, 52, 68, 98, 0xff0000, 2);    //将画笔图案打上红框，提醒现在正处于画笔状态
	MouseStatus(&mouse_old);                      //获取老鼠标状态
	MouseStoreBk(mouse_old.x, mouse_old.y);       //记录老鼠标的背景图案
	MouseDraw(mouse_old);                         //画新鼠标

	/*移动鼠标，执行画笔功能*/
	while (1)
	{
		MouseStatus(&mouse_new);    //获取新鼠标状态

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
			mouse_old = mouse_new;                     //重置鼠标

			if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2))                     //如果在图片内部点击
			{
				MouseStatus(&mouse_old);                                                       //记录老鼠标的状态
				ImgDrawPixel(*bmpattr, mouse_old.x, mouse_old.y, state->color, state->size);    //以当前颜色和画笔粗细在鼠标处画一个点
			}

			/*功能切换*/
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
			else if (MouseDown(190, 0, 250, 50))
			{
				//图库
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 45;
			}
			else if (MouseDown(10, 50, 70, 100))
			{
				//画笔
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 1;
			}
			else if (MouseDown(70, 50, 130, 100))
			{
				//裁剪
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 60;
			}
			else if (MouseDown(130, 50, 190, 100))
			{
				//图形
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 65;
			}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 70;
			}
			else if (MouseDown(700, 50, 750, 100))
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
				//设置
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
			else if (MouseDown(84, 570, 126, 600))
			{
				//拾色器
				MousePutBk(mouse_new.x, mouse_new.y);
				PickColor(&state->color,0);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
			}
			else if (MouseDown(700, 0, 750, 50))
			{
				//滤镜
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(12, 52, 68, 98, ThemeColor2, 2);
				return 120;
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

/**
*  函数名      DrawPicture
*  传入参数    bmpattr    图片
			   state      菜单状态
*  功能        画图形
*  返回值      0          图片未打开
			   1          退出画图形函数
			   20         切换为打开功能
			   30         切换为保存功能
			   40         切换为新建功能
			   45         切换为图库功能
			   50         切换为画笔功能
			   60         切换为裁剪功能
			   70         切换为调整功能
			   85         切换为设置功能
			   90         切换为缩小功能
			   95         切换为放大功能
			   100        切换为旋转功能
			   105        切换为翻转功能
			   120        切换为滤镜功能
**/
int DrawPicture(BMPATTR* bmpattr, MENUSTATE* state)
{
	int flag = 0;                  //记录函数返回值
	MOUSE mouse_old, mouse_new;    //定义老鼠标和新鼠标

	/*若图片未打开，显示警告框，退出函数*/
	if (bmpattr->flag == 0)
	{
		WarnBox("图片未打开");
		return	0;
	}

	ImgRectangle(132, 52, 188, 98, 0xff0000, 2);         //将画笔图案打上红框，提醒现在正处于画笔状态
	Line(207, 61, 234, 89, 0x000000, 2);                 //显示画直线功能的图案
	Triangle(275, 61, 256, 89, 293, 89, 0x000000, 2);    //显示画三角形功能的图案
	ImgRectangle(322, 61, 371, 89, 0x000000, 2);         //显示画矩形功能的图案
	Circle(418, 75, 14, 0x000000, 2);                    //显示画圆功能的图案

	MouseStatus(&mouse_old);                   //获取老鼠标状态
	MouseStoreBk(mouse_old.x, mouse_old.y);    //记录老鼠标的背景图案
	MouseDraw(mouse_old);                      //画老鼠标

	/*移动鼠标，执行画图形功能*/
	while (1)
	{
		MouseStatus(&mouse_new);    //获取新鼠标状态

		/*如果鼠标状态未改变，不执行任何操作*/
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_new.button == mouse_old.button)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);          //擦去老鼠标
			MouseStoreBk(mouse_new.x, mouse_new.y);        //记录新鼠标的背景图案
			MouseDraw(mouse_new);                          //画新鼠标

			if (mouse_new.button == mouse_old.button)      //如果鼠标点击状态未改变，不执行画图形操作
			{
				mouse_old = mouse_new;
				continue;
			}

			if (MouseDown(190, 50, 250, 100) || flag == 125)              //如果点击直线图案，执行画直线操作
			{
				MousePutBk(mouse_new.x, mouse_new.y);      //擦去新鼠标
				flag = 125;           //调用画直线函数

				/*if (flag)
				{
					MousePutBk(mouse_new.x, mouse_new.y);
					ImgRectangle(132, 52, 188, 98, Gray, 2);
					switch (flag)
					{
						case 130:
							DrawTriangle(bmpattr, state);
							break;
						case 135:
							DrawRectangle(bmpattr, state);
							break;
						case 140:
							DrawCircle(bmpattr, state);
							break;
						default:
							Bar(192, 52, 518, 98, Gray);
							break;
					}
					return flag;
				}*/
			}
			else if (MouseDown(250, 50, 300, 100) || flag == 130)         //如果点击三角形图案，执行画三角形操作
			{
				MousePutBk(mouse_new.x, mouse_new.y);      //擦去新鼠标
				flag = 130;       //调用画三角形函数
			}
			else if (MouseDown(300, 50, 380, 100) || flag == 135)         //如果点击矩形图案，执行画矩形操作
			{
				MousePutBk(mouse_new.x, mouse_new.y);      //擦去新鼠标
				flag = 135;      //调用画矩形函数
			}
			else if (MouseDown(380, 50, 450, 100) || flag == 140)      //如果点击圆图案，执行画圆操作
			{
				MousePutBk(mouse_new.x, mouse_new.y);      //擦去新鼠标
				flag = 140;         //调用画圆函数
			}

			/*功能切换*/
			else if (MouseDown(10, 0, 70, 50))
			{
				//打开
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 20;
			}
			else if (MouseDown(70, 0, 130, 50))
			{
				//保存
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 30;
			}
			else if (MouseDown(130, 0, 190, 50))
			{
				//新建
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 40;
			}
			else if (MouseDown(190, 0, 250, 50))
			{
				//图库
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 45;
			}
			else if (MouseDown(10, 50, 70, 100))
			{
				//画笔
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 50;
			}
			else if (MouseDown(70, 50, 130, 100))
			{
				//裁剪
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 60;
			}
			else if (MouseDown(130, 50, 190, 100))
			{
				//图形
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 1;
			}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
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
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 85;
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 90;
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 95;
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 100;
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 105;
			}
			else if (MouseDown(84, 570, 126, 600))
			{
				//拾色器
				MousePutBk(mouse_new.x, mouse_new.y);
				PickColor(&state->color,1);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(700, 0, 750, 50))
			{
				//滤镜
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(132, 52, 188, 98, Gray, 2);
				Bar(192, 52, 518, 98, Gray);
				return 120;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				exit(0);
			}

			mouse_old = mouse_new;    //重置鼠标
		}
		if (flag)
		{
			switch (flag)
			{
			case 125:
				flag = DrawLine(bmpattr, state);
				MouseStatus(&mouse_new);                   //获取新鼠标的状态
				MouseStoreBk(mouse_new.x, mouse_new.y);    //记录新鼠标的背景图案
				break;
			case 130:
				flag = DrawTriangle(bmpattr, state);
				MouseStatus(&mouse_new);                   //获取新鼠标的状态
				MouseStoreBk(mouse_new.x, mouse_new.y);    //记录新鼠标的背景图案
				break;
			case 135:
				flag = DrawRectangle(bmpattr, state);
				MouseStatus(&mouse_new);                   //获取新鼠标的状态
				MouseStoreBk(mouse_new.x, mouse_new.y);    //记录新鼠标的背景图案
				break;
			case 140:
				flag = DrawCircle(bmpattr, state);
				MouseStatus(&mouse_new);                   //获取新鼠标的状态
				MouseStoreBk(mouse_new.x, mouse_new.y);    //记录新鼠标的背景图案
				break;
			default:
				Bar(192, 52, 518, 98, ThemeColor2);
				break;
			}
		}
	}
}

/**
*  函数名      DrawLine
*  输入参数    bmpattr    图片
			   state      菜单状态
*  功能        画直线
*  返回值      0          退出画直线函数
			   20         切换为打开功能
			   30         切换为保存功能
			   40         切换为新建功能
			   45         切换为图库功能
			   50         切换为画笔功能
			   60         切换为裁剪功能
			   65         切换为图形功能
**/
int DrawLine(BMPATTR* bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2;            //定义直线两个端点的x,y坐标
	int tx1, ty1, tx2, ty2;        //定义直线两个端点的x,y相对坐标
	int flag = 0;                  //记录鼠标点击的是直线的第几个端点
	MOUSE mouse_old, mouse_new;    //定义老鼠标和新鼠标
	char xystring1[16];            //用于存放第一个端点的显示信息的字符数组
	char xystring2[16];            //用于存放第二个端点的显示信息的字符数组

	/*将直线图案打上红框，提醒现在正处于画直线状态*/
	ImgRectangle(132, 52, 188, 98, Gray, 2);
	ImgRectangle(192, 52, 248, 98, 0xff0000, 2);
	ImgRectangle(252, 52, 298, 98, Gray, 2);
	ImgRectangle(302, 52, 378, 98, Gray, 2);
	ImgRectangle(382, 52, 448, 98, Gray, 2);

	MouseStatus(&mouse_old);                   //获取老鼠标状态
	MouseStoreBk(mouse_old.x, mouse_old.y);    //记录老鼠标的背景图案
	MouseDraw(mouse_old);                      //画老鼠标

	/*移动鼠标，执行画直线功能*/
	while (1)
	{
		MouseStatus(&mouse_new);    //获取新鼠标状态

		/*如果鼠标状态未改变，不执行任何操作*/
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_new.button == mouse_old.button)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);        //擦去老鼠标
			MouseStoreBk(mouse_new.x, mouse_new.y);      //记录新鼠标的背景图案
			MouseDraw(mouse_new);                        //画新鼠标

			if (mouse_new.button == mouse_old.button)    //如果鼠标点击状态未改变，不执行画直线操作
			{
				mouse_old = mouse_new;
				continue;
			}

			/*如果点击图片内部，记录直线的第一个端点坐标*/
			if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr->x1;
				ty1 = y1 - bmpattr->y1;

				/*显示直线第一个端点的坐标信息*/
				Bar(200, 570 + 1, 700, 600, Gray);
				sprintf(xystring1, "坐标1:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring1);
			}

			/*如果点击图片内部，记录直线的第二个端点坐标*/
			else if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 0;
				tx2 = x2 - bmpattr->x1;
				ty2 = y2 - bmpattr->y1;

				/*显示直线第二个端点的坐标信息*/
				sprintf(xystring2, "坐标2:%d,%d", tx2, ty2);
				TextGB16(450, 580, 14, 0, xystring2);

				MousePutBk(mouse_new.x, mouse_new.y);                            //擦去新鼠标
				ImgLine(*bmpattr, x1, y1, x2, y2, state->color, state->size2);    //在图片内画直线
				MouseStatus(&mouse_new);                                         //获取新鼠标的状态
				MouseStoreBk(mouse_new.x, mouse_new.y);                          //记录新鼠标的背景图案
			}
			else if (MouseDown(190, 50, 250, 100))
			{
				//再次点击，退出画线
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(192, 52, 248, 98, Gray, 2);
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
			else if (MouseDown(84, 570, 126, 600))
			{
				//拾色器
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				PickColor(&state->color,1);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			//else if (MouseDown(10, 0, 70, 50))
			//{
			//	//打开
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(192, 52, 248, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 20;
			//}
			//else if (MouseDown(70, 0, 130, 50))
			//{
			//	//保存
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(192, 52, 248, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 30;
			//}
			//else if (MouseDown(130, 0, 190, 50))
			//{
			//	//新建
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(192, 52, 248, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 40;
			//}
			//else if (MouseDown(190, 0, 250, 50))
			//{
			//	//图库
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(192, 52, 248, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 45;
			//}
			//else if (MouseDown(10, 50, 70, 100))
			//{
			//	//画笔
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(192, 52, 248, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 50;
			//}
			//else if (MouseDown(70, 50, 130, 100))
			//{
			//	//裁剪
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(192, 52, 248, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 60;
			//}
			//else if (MouseDown(130, 50, 190, 100))
			//{
			//	//图形
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(192, 52, 248, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 65;
			//}
			else if (MouseDown(250, 50, 300, 100))
			{
				//三角形
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(192, 52, 248, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 130;
			}
			else if (MouseDown(300, 50, 380, 100))
			{
				//矩形
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(192, 52, 248, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 135;
			}
			else if (MouseDown(380, 50, 450, 100))
			{
				//圆
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(192, 52, 248, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 140;
			}
			//else if (MouseDown(650, 50, 700, 100))
			//{
			//	//调整
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImageAdjustment(bmpattr);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//}
			//else if (MouseDown(0, 570, 42, 600))
			//{
			//	//旋转
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImageRot(bmpattr);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//}
			//else if (MouseDown(42, 570, 84, 600))
			//{
			//	//翻转
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImageMirror(bmpattr);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//}
			//else if (MouseDown(703, 570, 735, 600))
			//{
			//	//设置
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImageZoomSet(&state->patton);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//}
			//else if (MouseDown(735, 570, 767, 600))
			//{
			//	//缩小
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImageZoom(bmpattr, 0.8, state->patton);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//}
			//else if (MouseDown(767, 570, 800, 600))
			//{
			//	//放大
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImageZoom(bmpattr, 1.25, state->patton);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//}
			//else if (MouseDown(700, 0, 750, 50))
			//{
			//	//滤镜
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	DrawShading(bmpattr);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				Exit(bmpattr);
			}

			mouse_old = mouse_new;    //重置鼠标
		}
	}
}

/**
*  函数名      DrawTriangle
*  输入参数    bmpattr    图片
			   state      菜单状态
*  功能        画三角形
*  返回值      0          退出画三角形函数
**/
int DrawTriangle(BMPATTR* bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2, x3, y3;
	int tx1, ty1, tx2, ty2, tx3, ty3;
	int flag = 0;
	char xystring1[16];
	char xystring2[16];
	char xystring3[16];
	MOUSE mouse_old, mouse_new;

	ImgRectangle(132, 52, 188, 98, Gray, 2);
	ImgRectangle(192, 52, 248, 98, Gray, 2);
	ImgRectangle(252, 52, 298, 98, 0xff0000, 2);
	ImgRectangle(302, 52, 378, 98, Gray, 2);
	ImgRectangle(382, 52, 448, 98, Gray, 2);

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

			if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr->x1;
				ty1 = y1 - bmpattr->y1;

				Bar(200, 570 + 1, 600, 600, Gray);
				sprintf(xystring1, "点1:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring1);
			}
			else if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 2;
				tx2 = x2 - bmpattr->x1;
				ty2 = y2 - bmpattr->y1;

				sprintf(xystring2, "点2:%d,%d", tx2, ty2);
				TextGB16(350, 580, 14, 0, xystring2);
			}
			else if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 2)
			{
				x3 = mouse_new.x;
				y3 = mouse_new.y;
				flag = 0;
				tx3 = x3 - bmpattr->x1;
				ty3 = y3 - bmpattr->y1;

				sprintf(xystring3, "点3:%d,%d", tx3, ty3);
				TextGB16(500, 580, 14, 0, xystring3);

				MousePutBk(mouse_new.x, mouse_new.y);
				ImgTriangle(*bmpattr, x1, y1, x2, y2, x3, y3, state->color, state->size2);
			}
			else if (MouseDown(250, 50, 300, 100))
			{
				//再次点击，退出画三角形
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(252, 52, 298, 98, Gray, 2);
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
			else if (MouseDown(84, 570, 126, 600))
			{
				//拾色器
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				PickColor(&state->color,1);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			//else if (MouseDown(10, 0, 70, 50))
			//{
			//	//打开
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(252, 52, 298, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 20;
			//}
			//else if (MouseDown(70, 0, 130, 50))
			//{
			//	//保存
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(252, 52, 298, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 30;
			//}
			//else if (MouseDown(130, 0, 190, 50))
			//{
			//	//新建
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(252, 52, 298, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 40;
			//}
			//else if (MouseDown(190, 0, 250, 50))
			//{
			//	//图库
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(252, 52, 298, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 45;
			//}
			//else if (MouseDown(10, 50, 70, 100))
			//{
			//	//画笔
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(252, 52, 298, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 50;
			//}
			//else if (MouseDown(70, 50, 130, 100))
			//{
			//	//裁剪
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(252, 52, 298, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 60;
			//}
			//else if (MouseDown(130, 50, 190, 100))
			//{
			//	//图形
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(252, 52, 298, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 65;
			//}
			else if (MouseDown(190, 50, 250, 100))
			{
				//直线
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(252, 52, 298, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 125;
			}
			else if (MouseDown(300, 50, 380, 100))
			{
				//矩形
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(252, 52, 298, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 135;
			}
			else if (MouseDown(380, 50, 450, 100))
			{
				//圆
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(252, 52, 298, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 140;
			}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageAdjustment(bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageRot(bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageMirror(*bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(703, 570, 735, 600))
			{
				//设置
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoomSet(&state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoom(bmpattr, 0.8, state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoom(bmpattr, 1.25, state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(700, 0, 750, 50))
			{
				//滤镜
				MousePutBk(mouse_new.x, mouse_new.y);
				DrawShading(bmpattr);
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

/**
*  函数名      DrawRectangle
*  输入参数    bmpattr    图片
			   state      菜单状态
*  功能        画矩形
*  返回值      0          退出画矩形函数
**/
int DrawRectangle(BMPATTR* bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2;
	int tx1, ty1, tx2, ty2;
	int flag = 0;
	char xystring1[16];
	char xystring2[16];
	MOUSE mouse_old, mouse_new;

	ImgRectangle(132, 52, 188, 98, Gray, 2);
	ImgRectangle(192, 52, 248, 98, Gray, 2);
	ImgRectangle(252, 52, 298, 98, Gray, 2);
	ImgRectangle(302, 52, 378, 98, 0xff0000, 2);
	ImgRectangle(382, 52, 448, 98, Gray, 2);

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

			if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr->x1;
				ty1 = y1 - bmpattr->y1;

				Bar(200, 570 + 1, 700, 600, Gray);
				sprintf(xystring1, "坐标1:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring1);
			}
			else if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 0;
				tx2 = x2 - bmpattr->x1;
				ty2 = y2 - bmpattr->y1;

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
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(302, 52, 378, 98, Gray, 2);
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
			else if (MouseDown(84, 570, 126, 600))
			{
				//拾色器
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				PickColor(&state->color,1);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			//else if (MouseDown(10, 0, 70, 50))
			//{
			//	//打开
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(302, 52, 378, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 20;
			//}
			//else if (MouseDown(70, 0, 130, 50))
			//{
			//	//保存
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(302, 52, 378, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 30;
			//}
			//else if (MouseDown(130, 0, 190, 50))
			//{
			//	//新建
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(302, 52, 378, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 40;
			//}
			//else if (MouseDown(190, 0, 250, 50))
			//{
			//	//图库
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(302, 52, 378, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 45;
			//}
			//else if (MouseDown(10, 50, 70, 100))
			//{
			//	//画笔
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(302, 52, 378, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 50;
			//}
			//else if (MouseDown(70, 50, 130, 100))
			//{
			//	//裁剪
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(302, 52, 378, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 60;
			//}
			//else if (MouseDown(130, 50, 190, 100))
			//{
			//	//图形
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(302, 52, 378, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 65;
			//}
			else if (MouseDown(190, 50, 250, 100))
			{
				//直线
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(302, 52, 378, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 125;
			}
			else if (MouseDown(250, 50, 300, 100))
			{
				//三角形
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(302, 52, 378, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 130;
			}
			else if (MouseDown(380, 50, 450, 100))
			{
				//圆
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(302, 52, 378, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 140;
			}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageAdjustment(bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageRot(bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageMirror(*bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(703, 570, 735, 600))
			{
				//设置
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoomSet(&state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoom(bmpattr, 0.8, state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoom(bmpattr, 1.25, state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(700, 0, 750, 50))
			{
				//滤镜
				MousePutBk(mouse_new.x, mouse_new.y);
				DrawShading(bmpattr);
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

/**
*  函数名      DrawCircle
*  输入参数    bmpattr    图片
			   state      菜单状态
*  功能        画圆
*  返回值      0          退出画圆函数
**/
int DrawCircle(BMPATTR* bmpattr, MENUSTATE* state)
{
	int x1, y1, x2, y2;
	int tx1, ty1;
	int r;
	int flag = 0;
	char xystring[16];
	char rstring[16];
	MOUSE mouse_old, mouse_new;

	ImgRectangle(132, 52, 188, 98, Gray, 2);
	ImgRectangle(192, 52, 248, 98, Gray, 2);
	ImgRectangle(252, 52, 298, 98, Gray, 2);
	ImgRectangle(302, 52, 378, 98, Gray, 2);
	ImgRectangle(382, 52, 448, 98, 0xff0000, 2);
	ImgRectangle(452, 52, 518, 98, Gray, 2);

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

			if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 0)
			{
				x1 = mouse_new.x;
				y1 = mouse_new.y;
				flag = 1;
				tx1 = x1 - bmpattr->x1;
				ty1 = y1 - bmpattr->y1;

				Bar(200, 570 + 1, 700, 600, Gray);
				sprintf(xystring, "坐标:%d,%d", tx1, ty1);
				TextGB16(200, 580, 14, 0, xystring);
			}
			else if (MouseDown(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2) && flag == 1)
			{
				x2 = mouse_new.x;
				y2 = mouse_new.y;
				flag = 0;
				r = (int)sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));

				sprintf(rstring, "半径:%d", r);
				TextGB16(450, 580, 14, 0, rstring);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgCircle(*bmpattr, x1, y1, r, state->color, state->size2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(380, 50, 450, 100))
			{
				//再次点击，退出画圆
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(382, 52, 448, 98, Gray, 2);
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
			else if (MouseDown(84, 570, 126, 600))
			{
				//拾色器
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				PickColor(&state->color,1);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			//else if (MouseDown(10, 0, 70, 50))
			//{
			//	//打开
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(382, 52, 448, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 20;
			//}
			//else if (MouseDown(70, 0, 130, 50))
			//{
			//	//保存
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(382, 52, 448, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 30;
			//}
			//else if (MouseDown(130, 0, 190, 50))
			//{
			//	//新建
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(382, 52, 448, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 40;
			//}
			//else if (MouseDown(190, 0, 250, 50))
			//{
			//	//图库
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(382, 52, 448, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 45;
			//}
			//else if (MouseDown(10, 50, 70, 100))
			//{
			//	//画笔
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(382, 52, 448, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 50;
			//}
			//else if (MouseDown(70, 50, 130, 100))
			//{
			//	//裁剪
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(382, 52, 448, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 60;
			//}
			//else if (MouseDown(130, 50, 190, 100))
			//{
			//	//图形
			//	Bar(200, 570 + 1, 700, 600, Gray);
			//	MousePutBk(mouse_new.x, mouse_new.y);
			//	ImgRectangle(382, 52, 448, 98, Gray, 2);
			//	MouseStatus(&mouse_new);
			//	MouseStoreBk(mouse_new.x, mouse_new.y);
			//	return 65;
			//}
			else if (MouseDown(190, 50, 250, 100))
			{
				//直线
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(382, 52, 448, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 125;
			}
			else if (MouseDown(250, 50, 300, 100))
			{
				//三角形
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(382, 52, 448, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 130;
			}
			else if (MouseDown(300, 50, 380, 100))
			{
				//矩形
				Bar(200, 570 + 1, 700, 600, Gray);
				MousePutBk(mouse_new.x, mouse_new.y);
				ImgRectangle(382, 52, 448, 98, Gray, 2);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
				return 135;
			}
			else if (MouseDown(650, 50, 700, 100))
			{
				//调整
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageAdjustment(bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(0, 570, 42, 600))
			{
				//旋转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageRot(bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(42, 570, 84, 600))
			{
				//翻转
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageMirror(*bmpattr);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(703, 570, 735, 600))
			{
				//设置
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoomSet(&state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(735, 570, 767, 600))
			{
				//缩小
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoom(bmpattr, 0.8, state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(767, 570, 800, 600))
			{
				//放大
				MousePutBk(mouse_new.x, mouse_new.y);
				ImageZoom(bmpattr, 1.25, state->patton);
				MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);
			}
			else if (MouseDown(700, 0, 750, 50))
			{
				//滤镜
				MousePutBk(mouse_new.x, mouse_new.y);
				DrawShading(bmpattr);
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

/**
*  函数名      DrawShading
*  输入参数    bmpattr    图片

*  功能        滤镜
*  返回值      0          图片未打开
               -1         取消
			   -2         关闭
			   1          成功画滤镜
**/
int DrawShading(BMPATTR* bmpattr)
{
	u32 color1, color2;                 //用于存储用于渐变的颜色值的临时变量
	const u32 ColorStart = 0x7ecef4;    //滤镜默认值
	const u32 ColorEnd = 0xf09fc3;      //滤镜默认值
	MOUSE mouse_old, mouse_new;

	/*若图片未打开，显示警告框，退出函数*/
	if (bmpattr->flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}

	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
	MouseDraw(mouse_old);

	color1 = ColorStart;
	color2 = ColorEnd;
	
	BmpSave(248, 198, 552, 352, "DATA//BK8");    //保存显示框下方的图片
	DrawShadingBox();                            //显示框

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
				BmpPut(248, 198, "DATA//BK8");                                             //显示之前保存的图片
				ImgMix(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2, color1, color2);    //画滤镜
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
				//退出
				exit(0);
			}
			mouse_old = mouse_new;
		}
	}
}