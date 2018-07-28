#pragma once

#ifndef CHARACTER_H
#define  CHARACTER_H

#include "Obstacle.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>

//人物类
class Character {
public:
	static const int MOVE_FPS = 8;		//人物总共的移动帧数
	static const int ROLL_FPS = 8;		//人物总共的滚动帧数

	static const int INITIAL_BOTTOM = 327;		//人物地面接触位置

private:
	int ROLL_TIME;		//滚动时长

	float INITIAL_SPEED;		//人物跳跃初始上升速度

	int activity;		//当前人物状态（滚动、跳跃、跑动）

	int move_fps;		//人物当前移动帧数
	int roll_fps;		//人物当前滚动帧数
	int sleepTime;		//每帧图片存在时间

	float jump_speed;		//人物跳跃上升的速度
	bool jumpEnd;			//判断跳跃状态

	float roll_time;		//人物滚动时间
	bool rollEnd;			//判断滚动状态

							//跑动、滚动状态人物对应碰撞体积
	int move_tall;
	int roll_tall;
	int roll_width;
	int move_width;

	//人物阶段（kid，teenager，adult，loser）
	STAGE stage;

	//loser阶段，最大碰撞数
	int year;

	//adult阶段，每越过一个障碍，naive对应减小
	int naive;

	int left;
	int top;
	int right;
	int bottom;			//人物位置

	IMAGE pic_move[MOVE_FPS][4];
	IMAGE pic_roll[ROLL_FPS][4];
	IMAGE pic_jump[4];		//人物图片
public:
	Character();

	int getActivity() { return activity; }		//获得当前人物状态

												//获得并改变当前人物位置
	int& getLeft();
	int& getTop();
	int& getRight();
	int& getBottom();

	int getNavie();		//返回天真值
	void loseNaive();	//天真值减小

						//改变人物阶段
	void setStage(STAGE stage);

	//改变人物岁数
	void setYear(int year);

	//初始人物数据
	void reSet();

	bool jump();	//人物跳跃
	void move();	//人物移动
	bool roll();	//人物滚动

};

#endif // !CHARACTER_H