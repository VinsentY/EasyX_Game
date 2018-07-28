#pragma once
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define PI 3.1415926535

class Clock {
private:
	//ת���Ƕ�
	float angle;

	//Բ�����꼰�뾶
	int x; 
	int y;
	int r;

	int move_x_min;
	int move_y_min;

	int move_x_hour;
	int move_y_hour;
public:
	Clock(int x = 550, int y = 110, int r = 35) {
		this->x = x;
		this->y = y;
		this->r = r;
		angle = PI / 2;
	}

	void move();
};