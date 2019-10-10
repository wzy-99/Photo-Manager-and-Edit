#include "file.h"

int FileNameInput(char* filename)
{
	unsigned int key;
	unsigned int len = strlen(filename);
	key = bioskey(0);
	if (key == Backspace)
	{
		if (len > 0)
		{
			len--;
			filename[len] = '\0';
			Bar(265, 260, 460, 305, White);
			TextASC24(275, 270, 14, 0, filename);
		}
		else
		{
			;
		}
	}
	else if (key == ESC)
	{
		//退出取消：10
		return 10;
	}
	else if (key == Enter)
	{
		//回车确认：20
		return 20;
	}
	else if ((key & 0xff) != 0 && len < 12)
	{
		filename[len] = key & 0xff;
		filename[len + 1] = '\0';
		len++;
		TextASC24(275, 270, 14, 0, filename);
	}
	return 0;
}

int FileScaleInput(char* scale, int type)
{
	unsigned int key;
	unsigned int asc;
	unsigned int len = strlen(scale);
	key = bioskey(0);
	asc = key & 0xff;
	if (key == Backspace)
	{
		if (len > 0)
		{
			len--;
			scale[len] = '\0';
			if (type == 0)
			{
				Bar(330, 255, 450, 290, White);
				TextASC24(335, 260, 14, 0, scale);
			}
			else if (type == 1)
			{
				Bar(330, 305, 450, 335, White);
				TextASC24(335, 310, 14, 0, scale);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			;
		}
	}
	else if (key == ESC)
	{
		//退出取消：10
		return 10;
	}
	else if (key == Enter)
	{
		//回车确认：20
		return 20;
	}
	else if (key == Tab)
	{
		//Tab切换：30
		return 30;
	}
	else if (asc >= 48 && asc <= 57 && len < 3)
	{
		scale[len] = asc;
		scale[len + 1] = '\0';
		len++;
		if (type == 0)
		{
			//宽度
			TextASC24(335, 260, 14, 0, scale);
		}
		else if (type == 1)
		{
			//高度
			TextASC24(335, 310, 14, 0, scale);
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int FileOpen(BMPATTR* bmpattr)
{
	int flag = 0;
	int SpecialKey = 0;
	char filename[18] = "";
	MOUSE mouse_old, mouse_new;
	BmpSave(248, 198, 552, 352, "DATA//BK0");
	DrawOpenBox();
	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
	while (1)
	{
		MouseStatus(&mouse_new);
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_old.button == mouse_new.button && SpecialKey == 0)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);
			MouseStoreBk(mouse_new.x, mouse_new.y);
			MouseDraw(mouse_new);
			mouse_old = mouse_new;
			if (MouseDown(475, 260, 540, 305) || SpecialKey == 20)
			{
				//确认
				MousePutBk(mouse_old.x, mouse_old.y);
				flag = BmpInfo(bmpattr, filename);
				if (flag)
				{
					Bar(0, 100, 800, 570, White);
					BmpPut(bmpattr->x1, bmpattr->y1, bmpattr->name);
					return 0;
				}
				else
				{
					WarnBox("无法打开");
					MouseStatus(&mouse_old);
					MouseStoreBk(mouse_old.x, mouse_old.y);
				}
			}
			else if (MouseDown(500, 200, 550, 240) || SpecialKey == 10)
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK0");
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
			SpecialKey = 0;
		}
		if (bioskey(1))
		{
			SpecialKey = FileNameInput(filename);
		}
		else
		{
			;
		}
	}
}

int FileSave(BMPATTR* bmpattr)
{
	int SpecialKey = 0;
	char filename[18] = "";
	MOUSE mouse_old, mouse_new;

	if (bmpattr->flag == 0)
	{
		WarnBox("图片未打开");
		return 0;
	}

	BmpSave(248, 198, 552, 352, "DATA//BK1");
	DrawSaveBox();
	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
	while (1)
	{
		MouseStatus(&mouse_new);
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_old.button == mouse_new.button && SpecialKey == 0)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);
			MouseStoreBk(mouse_new.x, mouse_new.y);
			MouseDraw(mouse_new);
			mouse_old = mouse_new;
			if (MouseDown(475, 260, 540, 305) || SpecialKey == 20)
			{
				//确认
				if (strlen(filename) == 0)
				{
					MousePutBk(mouse_new.x, mouse_new.y);
					WarnBox("名字不能为空");
					MouseStatus(&mouse_old);
					MouseStoreBk(mouse_old.x, mouse_old.y);
				}
				else
				{
					MousePutBk(mouse_old.x, mouse_old.y);
					BmpName(filename);
					BmpPut(248, 198, "DATA//BK1");
					BmpSave(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2, filename);
					return 0;
				}
			}
			else if (MouseDown(500, 200, 550, 240) || SpecialKey == 10)
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK1");
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
			SpecialKey = 0;
		}
		if (bioskey(1))
		{
			SpecialKey = FileNameInput(filename);
		}
		else
		{
			;
		}
	}
}

int FileNew(BMPATTR* bmpattr)
{
	int type = 0;
	u32 color = 0;
	int SpecialKey = 0;
	int width = 0, heigth = 0;
	char cWidth[6] = "";
	char cHeigth[6] = "";
	MOUSE mouse_old, mouse_new;
	BmpSave(248, 198, 552, 352, "DATA//BK2");
	DrawNewBox();
	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
	while (1)
	{
		MouseStatus(&mouse_new);
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_old.button == mouse_new.button && SpecialKey == 0)
		{
			;
		}
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);
			MouseStoreBk(mouse_new.x, mouse_new.y);
			MouseDraw(mouse_new);
			mouse_old = mouse_new;
			if (MouseDown(475, 255, 535, 290) || SpecialKey == 20)
			{
				//确认
				MousePutBk(mouse_old.x, mouse_old.y);
				width = atoi(cWidth);
				heigth = atoi(cHeigth);
				if (width > BMP_WIDTH_MAX || width < BMP_WIDTH_MIN)
				{
					MousePutBk(mouse_new.x, mouse_new.y);
					WarnBox("宽度超出或不足");
					MouseStatus(&mouse_old);
					MouseStoreBk(mouse_old.x, mouse_old.y);
				}
				else if (heigth > BMP_HEIGTH_MAX || heigth < BMP_HEIGTH_MIN)
				{
					MousePutBk(mouse_new.x, mouse_new.y);
					WarnBox("高度超出或不足");
					MouseStatus(&mouse_old);
					MouseStoreBk(mouse_old.x, mouse_old.y);
				}
				else
				{
					bmpattr->flag = 1;
					bmpattr->scale = 1.0;
					bmpattr->width = width;
					bmpattr->oWidth = width;
					bmpattr->heigth = heigth;
					bmpattr->oHeigth = heigth;
					bmpattr->x1 = SCR_WIDTH / 2 - width / 2;
					bmpattr->x2 = SCR_WIDTH / 2 + width / 2;
					bmpattr->y1 = SCR_HEIGHT / 2 - heigth / 2 + 35;
					bmpattr->y2 = SCR_HEIGHT / 2 + heigth / 2 + 35;
					Bar(0, 100, 800, 570, White);
					Bar(bmpattr->x1, bmpattr->y1, bmpattr->x2, bmpattr->y2, color);
					return 0;
				}
			}
			else if (MouseDown(475, 305, 535, 335))
			{
				//选色
				MousePutBk(mouse_old.x, mouse_old.y);
				SelectColor(&color);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
			}
			else if (MouseDown(330, 250, 450, 290))
			{
				//宽度
				type = 0;
			}
			else if (MouseDown(330, 305, 450, 335))
			{
				//高度
				type = 1;
			}
			else if (MouseDown(500, 200, 550, 240) || SpecialKey == 10)
			{
				//关闭
				MousePutBk(mouse_old.x, mouse_old.y);
				BmpPut(248, 198, "DATA//BK2");
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
			SpecialKey = 0;
		}
		if (bioskey(1))
		{
			if (type == 0)
			{
				SpecialKey = FileScaleInput(cWidth, 0);
			}
			else if (type == 1)
			{
				SpecialKey = FileScaleInput(cHeigth, 1);
			}
			else
			{
				;
			}
			if (SpecialKey == 30)
			{
				//如果为1则改变为0，如果为0则改变为1
				type = 1 - type;
			}
		}
		else
		{
			;
		}
	}
}

int FileList(BMPATTR* bmpattr)
{
	int page = 1, number = 0, k = 0;
	struct ffblk dir;
	char filepath[18] = "";
	FILEATTR fileattr = { 0,"",1.0,0,0,0,0,0,0};
	MOUSE mouse_old, mouse_new;

	BmpSave(150, 150, 650, 500, "DATA//BK5");
	DrawListBox();
	FindAllFile(&number);
	FileListShow(page);

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
			if (MouseDown(180, 246, 280, 457))
			{
				//点击文件
				k = (mouse_new.y - 246) / 19 + page;	//获取点击的文件序号
				if (k <= number)
				{
					FindFile(k, &dir);
					sprintf(filepath, "BMP/%s", dir.ff_name);
					FileInfo(&fileattr, filepath);
					if (fileattr.flag == 1)		//读取成功
					{
						FileInfoShow(fileattr, dir);
					}
				}
				else
				{
					//擦除
					fileattr.flag = 0;	//未读取
					Bar(290, 220, 460, 390, Silvery);
					Bar(545, 220, 620, 479, Silvery);
					Bar(470, 345, 620, 415, Silvery);
				}
			}
			else if (MouseDown(180, 457, 230, 480))
			{
				//上翻
				if (page > 1)
				{
					page--;
					FileListShow(page);
				}
			}
			else if (MouseDown(230, 457, 280, 480))
			{
				//下翻
				if (page + 10 < number)
				{
					page++;
					FileListShow(page);
				}
			}
			else if (MouseDown(295, 435, 370, 475))
			{
				//打开
				if (fileattr.flag == 1)
				{
					Bar(0, 100, 800, 570, White);
					BmpInfo(bmpattr, fileattr.name);	//将信息传递给bmpattr
					BmpPut(bmpattr->x1, bmpattr->y1, bmpattr->name);
					return 0;
				}
				else	//未读取或读取失败
				{
					MousePutBk(mouse_new.x, mouse_new.y);
					WarnBox("无法打开");
					MouseStatus(&mouse_old);
					MouseStoreBk(mouse_old.x, mouse_old.y);
				}
			}
			else if (MouseDown(380, 435, 460, 475))
			{
				//删除
				if (fileattr.flag == 1)
				{
					fileattr.flag = 0;
					Bar(290, 220, 460, 420, Silvery);
					Bar(545, 220, 620, 479, Silvery);
					Bar(470, 345, 620, 415, Silvery);
					remove(filepath);
					number--;
					FileListShow(page);
				}
			}
			else if (MouseDown(600, 150, 650, 200))
			{
				//关闭
				MousePutBk(mouse_new.x, mouse_new.y);
				BmpPut(150, 150, "DATA//BK5");
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

int FindFile(int n, struct ffblk* dir)
{
	int i;
	if (!findfirst("BMP/*.bmp", dir, 0))	//找到返回值为0
	{
		i = 1;
		for (; i < n; i++)
		{
			if (!findnext(dir))	//找到返回值为0
			{
				;
			}
			else
			{
				//已经没有文件了
				dir->ff_name[0] = '\0';
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

int FindAllFile(int* number)
{
	int i = 0;
	struct ffblk dir;
	if (!findfirst("BMP/*.bmp", &dir, 0))	//找到返回值为0
	{
		i = 1;
		while (!findnext(&dir))	//找到返回值为0
		{
			i++;
		}
	}
	*number = i;
	return i;
}

int FileListShow(int page)
{
	int j;
	char* p;
	char simplename[12];
	struct ffblk dir;

	Bar(180, 246, 279, 265, White);
	Bar(180, 265, 279, 285, Silvery);
	Bar(180, 285, 279, 304, White);
	Bar(180, 304, 279, 322, Silvery);
	Bar(180, 322, 279, 340, White);
	Bar(180, 340, 279, 361, Silvery);
	Bar(180, 361, 279, 380, White);
	Bar(180, 380, 279, 400, Silvery);
	Bar(180, 400, 279, 419, White);
	Bar(180, 419, 279, 438, Silvery);
	Bar(180, 438, 279, 457, White);

	for (j = 0; j < 11; j++)
	{
		if (FindFile(page + j, &dir))		//如果第i个文件存在
		{
			stpcpy(simplename, dir.ff_name);
			p = strchr(simplename, '.');
			p[0] = '\0';
			TextASC16(184, 249 + 19 * j, 12, 0, simplename);
		}
		else
		{
			break;
		}
	}
	return 0;
}

int FileInfoShow(FILEATTR attr, struct ffblk dir)
{
	char* p;
	const int part = 14;
	char name[18];
	char data[12], time[12];
	char cWidth[10], cHeigth[10], cSize[8];
	int year, month, day, hour, min, second;
	unsigned long int size;

	Bar(290, 220, 460, 390, Silvery);
	Bar(545, 220, 620, 479, Silvery);
	Bar(470, 345, 620, 415, Silvery);

	year = ((dir.ff_fdate & 0xFE00) >> 9) + 1980;	//注意优先级
	month = (dir.ff_fdate & 0x1E0) >> 5;
	day = dir.ff_fdate & 0x1F;
	hour = (dir.ff_ftime & 0xF800) >> 11;
	min = (dir.ff_ftime & 0x7E0) >> 5;
	second = (dir.ff_ftime & 0x1F) * 2;
	size = dir.ff_fsize >> 10;	//1024

	sprintf(data, "%d.%d.%d", year, month, day);
	sprintf(time, "%d:%d:%d", hour, min, second);
	sprintf(cSize, "%ldkB", size);
	sprintf(cWidth, "%d像素", attr.width);
	sprintf(cHeigth, "%d像素", attr.heigth);

	strcpy(name, dir.ff_name);
	p = strchr(name, '.');
	p[0] = '\0';
	
	TextGB16(545, 227, part, 0, name);
	TextGB16(545, 260, part, 0, "BMP");
	TextGB16(545, 293, part, 0, cSize);
	TextGB16(485, 355, part, 0, data);
	TextGB16(485, 385, part, 0, time);
	TextGB16(545, 420, part, 0, cWidth);
	TextGB16(545, 450, part, 0, cHeigth);

	TextASC16(320, 300, 12, 0, "Waiting...");	//显示等待信息

	ImageFileZoom(attr);
	return 0;
}

int FileInfo(FILEATTR* fileattr, char* filename)
{
	FILE* fp;
	double t1, t2;
	u16 bit;			//位深
	u32 compression;	//压缩

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		return 0;
	}
	else
	{
		//位深
		fseek(fp, 28L, 0);
		fread(&bit, 2, 1, fp);
		if (bit != 24U)
		{
			fclose(fp);
			return 0;
		}
		//压缩
		fseek(fp, 30L, 0);
		fread(&compression, 4, 1, fp);
		if (compression != 0UL)
		{
			fclose(fp);
			return 0;
		}
		//宽度
		fseek(fp, 18L, 0);
		fread(&fileattr->width, 4, 1, fp);
		if (fileattr->width > BMP_WIDTH_MAX || fileattr->width < BMP_WIDTH_MIN)
		{
			fclose(fp);
			return 0;
		}
		//高度
		fread(&fileattr->heigth, 4, 1, fp);
		if (fileattr->heigth > BMP_HEIGTH_MAX || fileattr->heigth < BMP_HEIGTH_MIN)
		{
			fclose(fp);
			return 0;
		}

		//状态改变
		fileattr->flag = 1;

		//计算比例
		t1 = 160.0 / (double)fileattr->width;
		t2 = 160.0 / (double)fileattr->heigth;

		//放缩改变
		fileattr->scale = t1 < t2 ? t1 : t2;

		//计算长宽
		fileattr->nWidth = fileattr->width * fileattr->scale;
		fileattr->nHeigth = fileattr->heigth * fileattr->scale;

		//计算坐标
		fileattr->x1 = 375 - fileattr->nWidth / 2;
		fileattr->y1 = 305 - fileattr->nHeigth / 2;

		//复制名称
		strcpy(fileattr->name, filename);

		fclose(fp);
	}
	return 1;
}