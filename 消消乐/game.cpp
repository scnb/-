#include "stdafx.h"
#include "game.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <time.h>
/*Ҫ�������֣������������������ļ�*/
#include <mmsystem.h>
#include <Windows.h>
#pragma comment (lib,"Winmm.lib") 


using std::cin;
using std::cout;
using std::endl;

COLORREF color_arr[6] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255),RGB(255,255,0),RGB(255,0,255),RGB(0,255,255) };

PosCur pos_arr[1000];//��¼��ͬС�������

int index;//��¼��һ��С����Χ�ж��ٸ���ͬ��С��

int score = 0;

PosCur cur;//��¼ȫ�ֵ�ǰ����λ��

IMAGE img;

void game_init(void)
{
	initgraph(1000, 700);
	
	loadimage(&img, _T("F:\\���֮·\\������\\������\\������\\pic.jpg"));//  F:\\pic.jpg"));
	putimage(200, 119, &img);
	Author_Verion();
	srand((unsigned int)time(NULL));
	settextcolor(YELLOW);
	settextstyle(40, 0, _T("����"));
	outtextxy(230, 32, _T("Loading����"));
	Sleep(3000);
	cleardevice();
}

void Author_Verion(void)
{
	settextcolor(WHITE);
	settextstyle(24, 0, _T("����"));
	/*������ֱ���Ҫ��sprintf����������ת�����ַ�������ʽ*/
	outtextxy(200, 600, _T("������ѧ�ػʵ���У"));
	outtextxy(200, 630, _T("�� ��"));
	outtextxy(200,660,_T("3154501"));//���������ֱ��������С�������ϸ����������
	settextstyle(32, 0, _T("΢���ź�"));
	outtextxy(760, 600, _T("V1.0"));
}

void game_begin(void)
{
	/*���Ʊ߿�*/
	setlinestyle(PS_SOLID, 10);//����������Ϊ10���ش�
	setlinecolor(RGB(50,50,50));//���û�����ɫΪ��ɫ
	rectangle(255, 45, 745, 655);//���ƾ���
	/*����С��Բ�Σ�*/
	setlinestyle(PS_SOLID);//��������������ΪĬ��ֵ����1����
	for (int x = 280;x < 740;x += 40)
	{
		for(int y=70;y<650;y+=40)
		{
			/*���û�����ɫ*/
			COLORREF cl;
			cl = color_arr[rand() % 6];
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(x, y, 18);
		}
	}
	/*���ƹ�꣬��ÿ�ν�����Ϸʱ����ʼ������������ͬһ�����ʵ�λ��*/
	cur.x = 480;
	cur.y = 350;
	DrawCursor(cur,WHITE);
	/*����ʱ��*/
	DrawTime(100);
	/*���Ƶ÷�*/
	DrawScore(0);
}

void game_play(void)
{
	for (int i = 999;i > -1;i--)
	{
		if (i % 10 == 0)
		{
			DrawTime(i / 10);
		}
		if (KEY_DOWN(VK_UP) && cur.y > 70)
		{
			DrawCursor(cur, BLACK);
			cur.y -= 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_DOWN) && cur.y < 630)
		{
			DrawCursor(cur, BLACK);
			cur.y += 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_LEFT) && cur.x > 280)
		{
			DrawCursor(cur, BLACK);
			cur.x -= 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_RIGHT) && cur.x < 720)
		{
			DrawCursor(cur, BLACK);
			cur.x += 40;
			DrawCursor(cur, WHITE);
		}
		else if (KEY_DOWN(VK_SPACE)||KEY_DOWN(VK_RETURN))
		{
			/*���ҵ���С����Χ������ɫ��ͬ��С�򣬽���������������У�����¼����*/
			mciSendString(_T("open F:\\���֮·\\������\\������\\������\\delete.mp3 alias delete"), 0, 0, 0);
			mciSendString(_T("play delete"), 0, 0, 0);
			mciSendString(_T("resume delete"),0, 0, 0);
			GetSameColor(cur, getpixel(cur.x, cur.y));

			/*�ٰ���ЩС��ı߿����óɺ�ɫ*/
			if (index > 1)
			{
				/*ֻҪ�ڶ���1��Բ��ʱ����ܱ�ɾ��*/
				for (int i = 0;i < index;i++)
				{
					setlinecolor(BLACK);
					setfillcolor(BLACK);
					fillcircle(pos_arr[i].x, pos_arr[i].y, 18);
				}
				Sleep(200);
				BallsFall();
				score += index;
				Increment(index);
				DrawScore(score);
				
			}
			index = 0;

			/*ʹ�����С��������������ȱ��λ��*/
		}
		Sleep(120);//��ʱ120ms����ֹ��whileѭ���ж���ж�
	}
	mciSendString(_T("stop delete"), 0, 0, 0);
}

void game_over(void)
{
	cleardevice();
	settextcolor(RED);
	TCHAR game_over[] = _T("GAME   OVER!");
	settextstyle(150, 0, _T("΢���ź�"));
	outtextxy(85, 280, game_over);
	DrawScore(score);
	mciSendString(_T("stop playing"), NULL, 0, NULL);
	mciSendString(_T("close playing"), NULL, 0, NULL);
	Sleep(2000);
}

void game_close(void)
{
	getchar();
	closegraph();
}

void DrawCursor(PosCur pos, COLORREF cl)
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(cl);
	rectangle(pos.x - 20, pos.y - 20,pos.x + 20,pos.y + 20);
}

void DrawTime(int sec)
{
	TCHAR time[30];
	settextcolor(RED);
	settextstyle(32, 0, _T("΢���ź�"));
	/*������ֱ���Ҫ��sprintf����������ת�����ַ�������ʽ*/
	_stprintf(time, _T("ʣ��ʱ�䣺%3d"), sec); // �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(10, 150, time);//���������ֱ��������С�������ϸ����������
	outtextxy(185, 150, 's');
}



void DrawScore(int score)
{
	TCHAR str[30];
	settextcolor(YELLOW);
	settextstyle(32, 0, _T("΢���ź�"));
	/*������ֱ���Ҫ��sprintf����������ת�����ַ�������ʽ*/
	_stprintf(str, _T("�÷֣�%d ��"), score);        // �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(10, 500, str);
}

void GetSameColor(PosCur cur, COLORREF cl)
{
	pos_arr[index].x = cur.x;
	pos_arr[index].y = cur.y;
	index++;
	PosCur temp;
	for (int k = 0;k < 4;k++)
	{
		switch (k)
		{
		case 0:temp.x = cur.x;temp.y = cur.y - 40;break;//��������Բ
		case 1:temp.x = cur.x;temp.y = cur.y + 40;break;//��������Բ
		case 2:temp.x = cur.x - 40;temp.y = cur.y;break;//��������Բ
		case 3:temp.x = cur.x + 40;temp.y = cur.y;break;//��������Բ
		}
		if (IsValid(temp, cl))
		{
			GetSameColor(temp,cl);
		}
	}
}

void Increment(int score)
{
	TCHAR str[10];
	settextcolor(YELLOW);
	settextstyle(50, 0, _T("��Բ"));
	_stprintf(str, _T("+ %d ��"), score);
	outtextxy(820, 330, str);
	Sleep(500);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	clearrectangle(820, 330, 1000, 400);
}

int IsValid(PosCur cur, COLORREF cl)
{
	if (getpixel(cur.x, cur.y) != cl)//�����ɫ��ͬ����϶���Ч��ֱ���˳�
	{
		return 0;
	}
	else
	{
		/*Ҫ�ж�һ���Ƿ���pos_arr�������Ѿ����ڸ�Բ��*/
		for (int i = 0;i < index;i++)
		{
			if (cur.x == pos_arr[i].x && cur.y == pos_arr[i].y)
			{
				return 0;
			}
		}
		return 1;
	}
}

void turn()//����Ҫ��pos_arr�����еĵ㰴�մ�С�����˳�����ţ��Ų��ᵼ����һ�������ϣ��������ĵ㸴����������С�ĵ����ɫ������ɫ���������޷���ʾ
{
	for (int i = 0;i < index;i++)
	{
		for (int j = 0;j < index - i - 1;j++)
		{
			if (pos_arr[j].x > pos_arr[j + 1].x)
			{
				PosCur temp;
				temp = pos_arr[j];
				pos_arr[j] = pos_arr[j + 1];
				pos_arr[j + 1] = temp;
			}
			if (pos_arr[j].y > pos_arr[j + 1].y)
			{
				PosCur temp;
				temp = pos_arr[j];
				pos_arr[j] = pos_arr[j + 1];
				pos_arr[j + 1] = temp;
			}
		}
	}
}

void BallsFall()
{
	COLORREF cl;
	turn();
	for (int i = 0;i < index;i++)
	{
		for (int k = pos_arr[i].y;k > 70;k -= 40)
		{
			cl = getpixel(pos_arr[i].x, k - 40);
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(pos_arr[i].x, k, 18);
		}
		cl = color_arr[rand() % 6];
		setlinecolor(cl);
		setfillcolor(cl);
		fillcircle(pos_arr[i].x, 70, 18);
	}
	
}
