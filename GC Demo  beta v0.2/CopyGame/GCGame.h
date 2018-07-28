#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "Character.h"
#include "Obstacle.h"
#include <Windows.h>
#include <iostream>
#include "Score.h"
#include "CMusic.h"
#include "Clock.h"

class Game {
private:
	//��ɫ����
	IMAGE catcher;	
	IMAGE co_catcher;

	IMAGE dreamer;
	//IMAGE co_dreamer;

	//����ͼƬ
	IMAGE backgroud;
	IMAGE dark_bk;

	//��½��������
	IMAGE growchange;

	CMusic cmusic;

	Clock clock;			//װ��ʱ��
	Score score;			//����
	Character character;	//����
	Obstacles obstacles;	//�ϰ���

	bool isOver;		//�ж���Ϸ�Ƿ����
	//bool NotFirst;

	STAGE stage;		//��Ϸ�׶�

	void bkDraw();		//��������
	void cutscenes();	//��������
	void Login();		//���ص�½����
	void endAnimation();	//��������

	void reSet(STAGE stage);	//������Ϸ�׶�������Ϸ
	void gameOver();		//ĳһ��Ϸ�׶ν������ж�
	void gameKernel();	//��Ϸ���Ļ���
	int collision();	//����������ϰ�״̬
public:
	Game();
	void startAnimation();	//��ʼ����
	
	
	
};

#endif GAME_H