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
	//黑色海浪
	IMAGE catcher;	
	IMAGE co_catcher;

	IMAGE dreamer;
	//IMAGE co_dreamer;

	//背景图片
	IMAGE backgroud;
	IMAGE dark_bk;

	//登陆界面文字
	IMAGE growchange;

	CMusic cmusic;

	Clock clock;			//装饰时钟
	Score score;			//分数
	Character character;	//人物
	Obstacles obstacles;	//障碍体

	bool isOver;		//判断游戏是否结束
	//bool NotFirst;

	STAGE stage;		//游戏阶段

	void bkDraw();		//背景绘制
	void cutscenes();	//过场动画
	void Login();		//加载登陆界面
	void endAnimation();	//结束动画

	void reSet(STAGE stage);	//根据游戏阶段重置游戏
	void gameOver();		//某一游戏阶段结束后判断
	void gameKernel();	//游戏核心机制
	int collision();	//检测人物与障碍状态
public:
	Game();
	void startAnimation();	//开始动画
	
	
	
};

#endif GAME_H