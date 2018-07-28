#pragma once
#include <fstream>
#include <iostream>
#include <conio.h>
#include <graphics.h>
#include "Obstacle.h"
#include "CMusic.h"
#include <vector>
#include <algorithm>
#include<functional>

class Data {
private:

	int score;
	char *name;

public:
	Data() {
		name = new char[4];
	}

	Data(char* name, int score) {
		this->score = score;
		this->name = new char[4];
		strcpy(this->name, name);
	}

	int getScore() const {
		return score;
	}
	char* getName() const {
		return name;
	}

	void setScore(int score) {
		this->score = score;
	}

	void setName(char name[4]) {
		strcpy(this->name, name);
	}

	bool operator >(const Data &other) const {
		return score > other.getScore();
	}

};

//分数类
class Score {
private:
	int max_score;	//目标分数
	int cur_score;	//当前分数
	int last_score;	//上一阶段分数

	STAGE stage;	//游戏阶段
	
	vector<Data> data;

	void cursorJump(int index);

public:
	Score();

	int& getCurScore();	//得到当前分数
	int getMaxScore();	//得到目标分数
	int getLastScore();	//得到上一阶段分数

	void getRecord();	//从文件中读取纪录分数
	void setStage(STAGE stage);	//改变阶段
	void addScore();	//增加分数
	void putScore();	//绘制分数

	void record();
	
	void scoreBoard();

	const vector<Data>& getData();

};