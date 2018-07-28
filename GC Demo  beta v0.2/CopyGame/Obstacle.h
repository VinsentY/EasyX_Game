#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "CMusic.h"

enum STAGE { kid, teenager, adult, loser };


//单个障碍类
class Obstacle {
private:		
	int left;
	int top;
	int right;
	int bottom;		//障碍位置

	int r;			//与其他障碍的距离
	int r_init;		//r = rand() % 200 + r_init;

	int obs_length;	//障碍长度

	CMusic cmusic;

	STAGE stage;	//游戏阶段

	float obsSpeed;	// 障碍移动速度

public:
	Obstacle();
	void style();		//设置障碍风格

	int& getLeft();		//获得当前人物位置
	int& getTop();
	int& getRight();
	int& getBottom();

	void setObs(Obstacle o);	//根据下一障碍设置当前障碍
	void reSet();
	void setStage(STAGE stage);

	void move();	//障碍移动
	void draw();	//绘制障碍物
	bool disappear();	//检测障碍是否超出显示区域
};

//监视者类，主要监视目前活动障碍

class Monitor {
private:
	int cnt = 0;
public:
	static const int OBSNUM = 3;	//总监视物体数目

	int operator+ (int num);
	int operator- (int num);

	Monitor& operator++ ();

	operator int() { return cnt; }		
	Monitor& operator= (int i);		 // 重载操作符实现监视功能
};

//多个障碍组成的障碍体
class Obstacles {
private:
	Monitor monitor;	//障碍监视器

	Obstacle obs[Monitor::OBSNUM];	//将多个障碍看作整体来处理
public:
	Obstacles();

	Obstacle getMonObj();		//获得当前监视的障碍对象
	Monitor& getMonitor();		//获得监视器

	//重置障碍
	void reSet();

	//设置游戏阶段
	void setStage(STAGE stage);

	void move();	//障碍体整体移动
};

#endif // !OBSTACLE_H