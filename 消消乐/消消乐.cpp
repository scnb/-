//����������.cpp : �������̨Ӧ�ó������ڵ㡣
//ע������mciSendString�������ֵ�ʱ��һ��Ҫ���Ͼ���·������·������\\����
//V1.0Ŀǰ�������������������ţ���������С�����Ч����ֻ���ڵ�һ������ʱ���ų�����
//V1.1����˿�ͷͼƬ�����ߵ������Ϣ

#include "stdafx.h"
#include "game.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	mciSendString(_T("open F:\\���֮·\\������\\������\\������\\playing.mp3 alias playing"), 0, 0, 0);
	
	mciSendString(_T("play playing repeat"), 0, 0, 0);
	game_init();
	game_begin();
	game_play();
	game_over();
	game_close();
	return 0;
}

