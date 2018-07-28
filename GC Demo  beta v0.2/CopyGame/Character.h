#pragma once

#ifndef CHARACTER_H
#define  CHARACTER_H

#include "Obstacle.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>

//������
class Character {
public:
	static const int MOVE_FPS = 8;		//�����ܹ����ƶ�֡��
	static const int ROLL_FPS = 8;		//�����ܹ��Ĺ���֡��

	static const int INITIAL_BOTTOM = 327;		//�������Ӵ�λ��

private:
	int ROLL_TIME;		//����ʱ��

	float INITIAL_SPEED;		//������Ծ��ʼ�����ٶ�

	int activity;		//��ǰ����״̬����������Ծ���ܶ���

	int move_fps;		//���ﵱǰ�ƶ�֡��
	int roll_fps;		//���ﵱǰ����֡��
	int sleepTime;		//ÿ֡ͼƬ����ʱ��

	float jump_speed;		//������Ծ�������ٶ�
	bool jumpEnd;			//�ж���Ծ״̬

	float roll_time;		//�������ʱ��
	bool rollEnd;			//�жϹ���״̬

							//�ܶ�������״̬�����Ӧ��ײ���
	int move_tall;
	int roll_tall;
	int roll_width;
	int move_width;

	//����׶Σ�kid��teenager��adult��loser��
	STAGE stage;

	//loser�׶Σ������ײ��
	int year;

	//adult�׶Σ�ÿԽ��һ���ϰ���naive��Ӧ��С
	int naive;

	int left;
	int top;
	int right;
	int bottom;			//����λ��

	IMAGE pic_move[MOVE_FPS][4];
	IMAGE pic_roll[ROLL_FPS][4];
	IMAGE pic_jump[4];		//����ͼƬ
public:
	Character();

	int getActivity() { return activity; }		//��õ�ǰ����״̬

												//��ò��ı䵱ǰ����λ��
	int& getLeft();
	int& getTop();
	int& getRight();
	int& getBottom();

	int getNavie();		//��������ֵ
	void loseNaive();	//����ֵ��С

						//�ı�����׶�
	void setStage(STAGE stage);

	//�ı���������
	void setYear(int year);

	//��ʼ��������
	void reSet();

	bool jump();	//������Ծ
	void move();	//�����ƶ�
	bool roll();	//�������

};

#endif // !CHARACTER_H