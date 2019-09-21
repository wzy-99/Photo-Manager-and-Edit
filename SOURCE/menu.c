#include "menu.h"

void DrawMenu()
{
	BmpPut(0, 0, "UI//MENU");
}

void MenuManager()
{
	int message = 0;
	BMPATTR bmpattr = { 0,"",1.0,0,0,0,0,0,0,0,0 };
	MENUSTATE state = { 5,1,0,0 };
	MOUSE mouse_old, mouse_new;
	MouseStatus(&mouse_old);
	MouseStoreBk(mouse_old.x, mouse_old.y);
	while (1)
	{
		MouseStatus(&mouse_new);
		if (mouse_new.x == mouse_old.x && mouse_new.y == mouse_old.y && mouse_old.button == mouse_new.button)
			continue;
		else
		{
			MousePutBk(mouse_old.x, mouse_old.y);
			MouseStoreBk(mouse_new.x, mouse_new.y);
			MouseDraw(mouse_new);
			mouse_old = mouse_new;
			if (MouseDown(10, 0, 70, 50) || message == 20)
			{
				//��
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 20;
			}
			else if (MouseDown(70, 0, 130, 50) || message == 30)
			{
				//����
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 30;
			}
			else if (MouseDown(130, 0, 190, 50) || message == 40)
			{
				//�½�
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 40;
			}
			else if (MouseDown(190, 0, 250, 50) || message == 45)
			{
				//ͼ��
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 45;
			}
			else if (MouseDown(10, 50, 70, 100) || message == 50)
			{
				//����
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 50;
			}
			else if (MouseDown(70, 50, 130, 100) || message == 60)
			{
				//�ü�
				MousePutBk(mouse_old.x, mouse_old.y);
				message=60;
			}
			else if (MouseDown(130, 50, 190, 100))
			{
				//ͼ��
				;
			}
			else if (MouseDown(750, 50, 800, 100) || message == 80)
			{
				//��ɫ��
				MousePutBk(mouse_old.x, mouse_old.y);
				message=80;
			}
			else if (MouseDown(700, 50, 750, 100) || message == 85)
			{
				//��ϸ
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 85;
			}
			else if (MouseDown(735, 570, 767, 600) || message == 90)
			{
				//��С
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 90;
			}
			else if (MouseDown(767, 570, 800, 600) || message == 95)
			{
				//�Ŵ�
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 95;
			}
			else if (MouseDown(703, 570, 735, 600) || message == 110)
			{
				//��С
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 110;
			}
			else if (MouseDown(0, 570, 42, 600) || message == 100)
			{
				//��ת
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 100;
			}
			else if (MouseDown(42, 570, 84, 600) || message == 105)
			{
				//��ת
				MousePutBk(mouse_old.x, mouse_old.y);
				message = 105;
			}
			else if (MouseDown(750, 0, 800, 50))
			{
				//�˳�
				exit(0);
			}
			else
			{
				;
			}
		}
		switch (message)
		{
			case 0:
				break;
			case 20:
				message = FileOpen(&bmpattr);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 30:
				message = FileSave(&bmpattr);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 40:
				message = FileNew(&bmpattr);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 45:
				message = FileList(&bmpattr);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 50:
				message = DrawPen(bmpattr, &state);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 60:
				message = ImageTailor(&bmpattr);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 80:
				message = SelectColor(&state.color);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 85:
				message = SelectSize(&state.size, &state.size2);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 90:
				//��С
				message = ImageZoom(&bmpattr, 0.8, state.patton);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 95:
				//�Ŵ�
				message = ImageZoom(&bmpattr, 1.25, state.patton);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 100:
				//��ת
				message = ImageRot(&bmpattr);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 105:
				//��ת
				message = ImageMirror(bmpattr);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			case 110:
				//����
				message = ImageZoomSet(&state.patton);
				MouseStatus(&mouse_old);
				MouseStoreBk(mouse_old.x, mouse_old.y);
				break;
			default:
				break;
		}
	}
}
