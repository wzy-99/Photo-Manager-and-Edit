#include "text.h"

int TextASC24(int x, int y, int part, u32 color,unsigned char* str)
{
	int i, j;
	unsigned int offset, bytes;
	FILE* fp= fopen("ZK//ASCST24", "rb");
	if(fp)
	{
		while (*str != '\0')
		{
			if (*str <= 127)
			{
				offset = *str * 48;
				fseek(fp, offset, 0);
				for (i = 0; i < 24; i++)
				{
					fread(&bytes, 2, 1, fp);
					for (j = 0; j < 16; j++)
					{
						if (bytes & (1 << j))
						{
							PutPixel(x + j, y + i, color);
						}
					}
				}
				x = x + part;
				str++;
			}
			else
			{
				str = str + 2;
			}
		}
		fclose(fp);
	}
	else
	{
		exit(0);
	}
	return 1;
}


int TextASC16(int x, int y, int part, u32 color, unsigned char* str)
{
	int i, j;
	unsigned int offset;
	unsigned int bytes;
	FILE* fp = fopen("ZK//ASCST16", "rb");
	if (fp)
	{
		while (*str != '\0')
		{
			if (*str <= 127)
			{
				offset = *str * 32;
				fseek(fp, offset, 0);
				for (i = 0; i < 16; i++)
				{
					fread(&bytes, 2, 1, fp);
					for (j = 0; j < 16; j++)
					{
						if (bytes & (1 << j))
						{
							PutPixel(x + j, y + i, color);
						}
					}
				}
				x = x + part;
				str++;
			}
			else
			{
				str = str + 2;
			}
		}
		fclose(fp);
	}
	else
	{
		exit(0);
	}
	return 1;
}

int TextASC12(int x, int y, int part, u32 color, unsigned char* str)
{
	int i, j;
	unsigned int offset;
	unsigned int bytes;
	FILE* fp = fopen("ZK//ASCST12", "rb");
	if (fp)
	{
		while (*str != '\0')
		{
			if (*str <= 127)
			{
				offset = *str * 24;
				fseek(fp, offset, 0);
				for (i = 0; i < 12; i++)
				{
					//虽然长为12但实际上是16位故2字节
					fread(&bytes, 2, 1, fp);
					for (j = 0; j < 12; j++)
					{
						if (bytes & (1 << j))
						{
							PutPixel(x + j, y + i, color);
						}
					}
				}
				x = x + part;
				str++;
			}
			else
			{
				str = str + 2;
			}
		}
		fclose(fp);
	}
	else
	{
		exit(0);
	}
	return 1;
}

int TextGB16(int x, int y, int part, u32 color, unsigned char* str)
{
	int i, j;
	char asc[2] = { '\0','\0' };
	unsigned char hBytes, lBytes;
	unsigned long int offset;
	unsigned int bytes;
	FILE* fp = fopen("ZK//GBST16", "rb");
	if (fp)
	{
		while (*str != '\0')
		{
			if (*str <= 127)
			{
				asc[0] = *str;
				TextASC16(x, y, part, color, asc);
				str++;
			}
			else
			{
				hBytes = *str - 0XA1;
				lBytes = *(str + 1) - 0XA1;
				offset = (hBytes * 94 + lBytes) * 32l;	//长整型
				fseek(fp, offset, 0);
				for (i = 0; i < 16; i++)
				{
					fread(&bytes, 2, 1, fp);
					for (j = 0; j < 16; j++)
					{
						if (bytes & (1 << j))
						{
							PutPixel(x + j, y + i, color);
						}
					}
				}
				str = str + 2;
			}
			x = x + part;
		}
		fclose(fp);
	}
	else
	{
		exit(0);
	}
	return 1;
}

int TextGB32(int x, int y, int part, u32 color, unsigned char* str)		//使用uchar因为位码、段码的值大于127
{
	int i, j;
	//char asc[2] = { '\0','\0' };
	unsigned char hBytes, lBytes;
	unsigned long int offset;
	unsigned long int bytes;
	FILE* fp = fopen("ZK//GBHT32", "rb");
	if (fp)
	{
		while (*str != '\0')
		{
			if (*str <= 127)
			{
				//忽略
				str++;
			}
			else
			{
				hBytes = *str - 0XA1;
				lBytes = *(str + 1) - 0XA1;
				offset = (hBytes * 94 + lBytes) * 128l;	//长整型
				fseek(fp, offset, 0);
				for (i = 0; i < 32; i++)
				{
					fread(&bytes, 4, 1, fp);
					for (j = 0; j < 32; j++)
					{
						if (bytes & (1l << j))	//长整型
						{
							PutPixel(x + j, y + i, color);
						}
					}
				}
				str = str + 2;
			}
			x = x + part;
		}
		fclose(fp);
	}
	else
	{
		exit(0);
	}
	return 1;
}