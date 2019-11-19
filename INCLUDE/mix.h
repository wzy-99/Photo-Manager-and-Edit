#ifndef MIX_H
#define MIX_H

#include "head.h"
#include "mouse.h"
#include "svga.h"
#include "bmp.h"
#include "box.h"
#include "image.h"

#include "color.h"



void DrawShading(int x1, int y1, int x2, int y2, u32 color1, u32 color2);
int Shading(BMPATTR* bmpattr);

int OldSFX(BMPATTR* bmpattr);
int ComicSFX(BMPATTR* bmpattr);
int GraySFX(BMPATTR* bmpattr);
int CastingSFX(BMPATTR* bmpattr);
int FrozenSFX(BMPATTR* bmpattr);
int GlassSFX(BMPATTR* bmpattr);
int NegativeSFX(BMPATTR* bmpattr);
int InstagramSFX(BMPATTR* bmpattr);
int FreshSFX(BMPATTR* bmpattr);

int ImgSFX(BMPATTR* bmpattr);

void ImgMix(BMPATTR* bmpattr, const char* path, double percent, int patton);

u8 SoftLight(u8 color_base, u8 color_mix);
u8 Superpose(u8 color_base, u8 color_mix);



#endif // !MIX_H
