#ifndef BMP_H
#define BMP_H

#include "head.h"
#include "svga.h"

typedef struct tagBITMAPFILEHEADER
{
	UINT16 bfType;
	DWORD bfSize;
	UINT16 bfReserved1;
	UINT16 bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;

int BmpPut(int x, int y, char* path);						//打开图片
int BmpSave(int x1, int y1, int x2, int y2, char* path);	//文件保存
int BmpInfo(BMPATTR* bmpattr, char* filename);				//获取并判断文件信息等
int BmpName(char* filename);								//检查并补全文件扩展名（后缀.bmp）
int DataSave(BMPATTR* bmpattr,const char* path);					//数据储存

#endif