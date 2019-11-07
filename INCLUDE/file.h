#ifndef FILE_H
#define FILE_H

#include "head.h"
#include "svga.h"
#include "mouse.h"	

#include "text.h"	//字体库
#include "bmp.h"	//基础库
#include "box.h"	//窗口库
#include "color.h"	//色彩库
#include "image.h"	//图像处理库

#include "dir.h"	//定义findfirst、findnext查找文件函数
#include "io.h"		//定义remove删除文件的函数

int FileList(BMPATTR* bmpattr);						//文件列表
int FileNew(BMPATTR* bmpattr);						//新建文件
int FileOpen(BMPATTR* bmpattr);						//打开文件
int FileSave(BMPATTR* bmpattr);						//保存文件
int FindFile(int n, struct ffblk* dir);				//查找文件
int FileInfo(FILEATTR* fileattr, char* filename);	//文件信息
int FileInfoShow(FILEATTR attr, struct ffblk dir);	//显示信息
int FindAllFile(int* n);							//遍历文件
int FileListShow(int i);							//显示列表



#endif
