#include "box.h"

#define BMPPUT

#ifdef BMPPUT

int WarnBox(char* error)
{
	double lenth = strlen(error) / 4.0;
	int x = SCR_WIDTH / 2 - lenth * 40;
	MOUSE mouse_old, mouse_new;
	BmpSave(248, 198, 552, 352, "DATA//BK3");
	BmpPut(248, 198, "UI//ERROR");
	TextGB32(x, 260, 40, 0, error);
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
			if (MouseDown(250, 320, 405, 350))
			{
				//确认
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				return 1;
			}
			else if (MouseDown(405, 320, 550, 350))
			{
				//取消
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				return -1;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				return 0;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//退出
				delay(100);
				exit(0);
			}
			else
			{
				;
			}
		}
	}
}

void DrawZoomSettingBox(u8 patton)
{
	BmpPut(248, 198, "UI/ZOOM");

	if (patton)
	{
		Bar(455, 265, 465, 275, 0);
		Bar(455, 315, 465, 325, White);
	}
	else
	{
		Bar(455, 265, 465, 275, White);
		Bar(455, 315, 465, 325, 0);
	}
}

void DrawOpenBox()
{
	BmpPut(248, 198, "UI//OPEN");
}

void DrawNewBox()
{
	BmpPut(248, 198, "UI//NEW");
}

void DrawSaveBox()
{
	BmpPut(248, 198, "UI//SAVE");
}

void DrawListBox()
{
	BmpPut(150, 150, "UI//LIST");
}

void DrawSizeBox()
{
	BmpPut(248, 198, "UI//SIZE");
}

void DrawAdjustBox()
{
	BmpPut(248, 198, "UI//ADST");	//ADST:adjust
}

void DrawShadingBox()
{
	BmpPut(248, 198, "UI//FITER");
}

#endif



#ifndef BMPPUT

void DrawBox(void)
{
	Bar(250, 200, 500, 240, ThemeColor1);
	Bar(250, 240, 550, 350, ThemeColor2);
	Bar(500, 200, 550, 240, ThemeColor3);
	Line(510, 205, 540, 235, 0, 1);
	Line(510, 235, 540, 205, 0, 1);
}

void DrawWarnBox(void)
{
	DrawBox();
	Bar(250, 320, 550, 350, 0xa8afb5);
	Line(250, 320, 550, 320, 0x93999f, 2);
	Line(405, 320, 405, 350, 0x93999f, 2);
	TextGB32(359, 201, 30, 0, "警告");
	TextGB16(304, 325, 14, 0, "确认");
	TextGB16(458, 325, 14, 0, "取消");
}

int WarnBox(char* error)
{
	double lenth = strlen(error) / 4.0;
	int x = SCR_WIDTH / 2 - lenth * 40;
	MOUSE mouse_old, mouse_new;
	BmpSave(248, 198, 552, 352, "DATA//BK3");

	DrawWarnBox();

	TextGB32(x, 260, 40, 0, error);
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
			if (MouseDown(250, 320, 405, 350))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 1;
			}
			else if (MouseDown(405, 320, 550, 350))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
				return 0;
			}
			else if (MouseDown(500, 200, 550, 240))
			{
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK3");
				/*MouseStatus(&mouse_new);
				MouseStoreBk(mouse_new.x, mouse_new.y);*/
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

void DrawZoomSettingBox(u8 patton)
{
	DrawBox();
	Bar(450, 260, 470, 280, 0xffffff);
	Bar(485, 255, 540, 285, 0xffffff);
	Bar(450, 310, 470, 330, 0xffffff);
	Bar(485, 305, 540, 335, 0xffffff);
	TextGB32(325, 205, 30, 0, "放缩模式");
	TextGB32(270, 255, 30, 0, "双线性内插法");
	TextGB32(270, 305, 30, 0, "邻近点插值法");
	TextGB16(490, 260, 14, 0, "确认");
	TextGB16(490, 310, 14, 0, "取消");

	if (patton)
	{
		Bar(455, 265, 465, 275, 0);
		Bar(455, 315, 465, 325, White);
	}
	else
	{
		Bar(455, 265, 465, 275, White);
		Bar(455, 315, 465, 325, 0);
	}
}

void DrawOpenBox()
{
	DrawBox();
	Bar(265, 260, 460, 305, 0xffffff);
	Bar(475, 260, 540, 305, 0xffffff);
	Bar(265, 315, 540, 340, 0xcfcccc);
	TextGB32(325, 205, 30, 0, "打开文件");
	TextGB32(480, 270, 30, 0, "确认");
	TextGB16(273, 320, 14, 0xfc1c1c, "注意：");
	TextGB16(320, 320, 14, 0, "文件格式必须为24位BMP位图");
}

void DrawNewBox()
{
	DrawBox();
	Bar(330, 255, 450, 290, 0xffffff);
	Bar(475, 255, 535, 290, 0xffffff);
	Bar(330, 305, 450, 335, 0xffffff);
	Bar(475, 305, 535, 335, 0xffffff);
	TextGB32(325, 205, 30, 0, "新建文件");
	TextGB16(480, 260, 14, 0, "确认");
	TextGB16(480, 310, 14, 0, "选色");
	TextGB16(260, 260, 14, 0, "宽度：");
	TextGB16(260, 305, 14, 0, "高度：");
}

void DrawSaveBox()
{
	DrawBox();
	Bar(265, 260, 460, 305, 0xffffff);
	Bar(475, 260, 540, 305, 0xffffff);
	Bar(265, 315, 540, 340, 0xcfcccc);
	TextGB32(325, 205, 30, 0, "保存文件");
	TextGB32(480, 270, 30, 0, "确认");
	TextGB16(273, 320, 14, 0xfc1c1c, "注意：");
	TextGB16(320, 320, 14, 0, "文件格式必须为24位BMP位图");
}

void DrawListBox()
{
	BmpPut(150, 150, "UI//LIST");
}

void DrawSizeBox()
{
	DrawBox();
	Bar(425, 265, 450, 285, 0xffffff);
	Bar(455, 265, 480, 285, 0xffffff);
	Bar(490, 265, 535, 285, 0xffffff);
	Bar(425, 305, 450, 325, 0xffffff);
	Bar(455, 305, 480, 325, 0xffffff);
	Bar(490, 305, 535, 325, 0xffffff);
	TextGB32(325, 205, 30, 0, "粗细调整");
	TextGB16(270, 265, 14, 0, "画笔粗细：");
	TextGB16(430, 267, 14, 0, "+");
	TextGB16(460, 267, 14, 0, "-");
	TextGB16(500, 270, 14, 0, "确认");
	TextGB16(270, 305, 14, 0, "图形粗细");
	TextGB16(430, 307, 14, 0, "+");
	TextGB16(460, 307, 14, 0, "-");
	TextGB16(500, 310, 14, 0, "取消");
}

void DrawAdjustBox()
{
	DrawBox();
	Bar(485, 255, 540, 285, 0xffffff);
	Bar(485, 305, 540, 335, 0xffffff);
	Line(345, 265, 445, 265, 0xd6dadf, 2);
	Line(345, 295, 445, 295, 0xd6dadf, 2);
	Line(345, 325, 445, 325, 0xd6dadf, 2);
	TextGB32(325, 205, 30, 0, "图像调整");
	TextGB16(265, 250, 14, 0, "对比度");
	TextGB16(265, 280, 14, 0, "饱和度");
	TextGB16(265, 310, 14, 0, "亮 度");
	TextGB16(490, 260, 14, 0, "确认");
	TextGB16(490, 310, 14, 0, "取消");
}

void DrawShadingBox()
{
	DrawBox();
	Bar(348, 260, 400, 282, 0xffffff);
	Bar(455, 260, 512, 282, 0xffffff);
	Bar(348, 300, 400, 325, 0xffffff);
	Bar(455, 300, 512, 325, 0xffffff);
	TextGB32(324, 204, 30, 0, "图像滤镜");
	TextGB16(280, 262, 14, 0, "颜色一：");
	TextGB16(280, 302, 14, 0, "颜色二：");
	TextGB16(468, 262, 14, 0, "确认");
	TextGB16(468, 302, 14, 0, "取消");
}

#endif

void Welcome()
{
	const u32 ColorStart = 0x7ecef4;
	const u32 ColorEnd = 0xf09fc3;
	
	ImgShading(0, 0, 800, 600, ColorStart, ColorEnd);

	Bar(100, 100, 250, 100+2, White);
	Bar(100, 100, 100+2, 175, White);
	Bar(550, 250-2, 700, 250, White);
	Bar(700-2, 175, 700, 250, White);

	TextASC128(200+30, 100, 64, White, "Phot", 2);
	TextASC128(445+30, 100, 64, White, "o", 2);

	TextASC64(160-60, 250, 32, White, "M", 2);
	TextASC64(205-60, 250, 32, White, "anger And Edi", 2);
	TextASC64(600-60, 250, 32, White, "ting", 2);

	TextGB16(650, 550, 14, White, "按任意键进入");

	getch();
}


int Exit(BMPATTR* bmpattr)
{
	int msg = 0;
	if (bmpattr->flag == 0)
	{	//如果图像未打开
		delay(100);
		exit(0);
	}
	else
	{
		if (bmpattr->save == 1)
		{	//如果图像已保存
			delay(100);
			exit(0);
		}
		else
		{
			//如果图像未保存
			msg = WarnBox("是否保存");
			if (msg == 0)
			{	//不报存,退出
				delay(100);
				exit(0);
			}
			else if(msg == -1)
			{
				//不报存,退出
				delay(100);
				exit(0);
			}
			else
			{	//保存
				msg = FileSave(bmpattr);
				delay(100);
				exit(0);
			}
		}
	}
	return 0;
}