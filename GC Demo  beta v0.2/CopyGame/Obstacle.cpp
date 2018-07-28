#include "Obstacle.h"

//Obstacle类

int& Obstacle::getLeft() {
	return left;
}

int& Obstacle::getTop() {
	return top;
}

int& Obstacle::getRight() {
	return right;
}

int& Obstacle::getBottom() {
	return bottom;
}

void Obstacle::setObs(Obstacle o) {
	//设定障碍风格
	style();

	//根据障碍o重置当前障碍
	left = o.left + o.r;
	right = o.right + o.obs_length;
	r = rand() % 200 + r_init;

}

void Obstacle::reSet() {
	
	style();
	left = 740;		//将方块初始化至画面最右侧
	right = left + obs_length;
	r = rand() % 200 + r_init;

}

void Obstacle::setStage(STAGE stage) {
	this->stage = stage;
}

void Obstacle::move() {
	left -= obsSpeed;
	right = left + obs_length;
}
void Obstacle::draw() {

	//根据阶段不同，绘制不同的障碍
	switch (stage) {
	case kid:
		srand(time(NULL));
		switch (rand()%12 + 1) {
		case 1:
		case 2:
			setfillcolor(RGB(255, 192, 203));	//粉红
			break;
		case 3:			
			setfillcolor(RGB(0, 255, 255));		//青色
			break;
		case 4:
			setfillcolor(RGB(218, 112, 214));	//淡紫色
			break;
		case 5:
			setfillcolor(RGB(0, 199, 140));		//土耳其蓝
			break;
		case 6:
			setfillcolor(RGB(188, 143, 143));	//玫瑰红
			break;
		case 7:
			setfillcolor(RGB(255, 128, 0));		//橘黄
			break;
		case 8:
		case 9:
			setfillcolor(RGB(0, 191, 255));		//深天蓝
			break;
		case 10:
			setfillcolor(RGB(255, 255, 0));		//纯黄
			break;
		case 11:
		case 12:
			setfillcolor(RGB(255, 255, 240));	//象牙色
			break;		
		}
		break;
	case teenager:
		setfillcolor(RGB(135, 206, 250));
		break;
	case adult:
		setfillcolor(RGB(128, 138, 135));
		break;
	case loser:
		setfillcolor(BLACK);
		break;
	default:
		break;
	}
	solidrectangle(left, top, right, bottom);	//绘制该障碍方块

}
	

bool Obstacle::disappear() {
	return left + 40 <= 0;
}

void Obstacle::style() {

	//根据阶段不同，设置不同的障碍风格
	srand(time(NULL));
	static int i = 1;
	switch (stage) {
	case kid:
		//该阶段直至第18个方块才会产生底部方块
		i++;
		obsSpeed = 2.5;
		switch (i) {			
		case 9://10
			obs_length = 40;
			top = 297;
			bottom = top + 30;	//底部方块
			break;
		default:
			obs_length = 125;
			top = 150;
			bottom = top + 30;	//顶部方块
			break;
		}
		break;
	case teenager:
		//设置障碍速度
		obsSpeed = 8;
		//随机产生方块
		switch (rand() % 10 + 1) {
		case 1:
		case 2:
		case 3:
			obs_length = 40;
			top = 300;
			bottom = top + 30;	//底部方块
			break;
		default:
			obs_length = 40;
			top = 225;
			bottom = top + 30;	//顶部方块
			break;
		}
		break;
	case adult:
		obsSpeed = 7.5;
		r_init = 300;
		switch (rand() % 6 + 1) {
		case 1:
		case 2:
		case 3:
			top = 225;
			bottom = top + 30;	//顶部方块
			break;
		case 4:	
		case 5:
		case 6:
			top = 300;
			bottom = top + 30;	//底部方块
			break;
		}
		break;
	case loser:
		obsSpeed = 12;
		switch (rand() % 6 + 1) {
		case 1:
		case 2:						
		case 3:
			top = 225;
			bottom = top + 30;	//顶部方块
			break;
		case 4:		
		case 5:
		case 6:
			top = 300;
			bottom = top + 30;	//底部方块
			break;
		}
		break; 
	}
	
}

//////////////////////////////////////////////////////////////////////////
//Obstacles类

Obstacle Obstacles::getMonObj() {
	return obs[monitor];
}

Monitor& Obstacles::getMonitor() {
	return monitor;
}


void Obstacles::reSet() {
	//先初始化第一个方块
	obs[0].reSet();
	//之后的方块根据前一个方块进行位置设定
	for (int i = 1; i < Monitor::OBSNUM; i++) {		
		obs[i].setObs(obs[i - 1]);
	}
}

void Obstacles::setStage(STAGE stage) {
	//更改障碍体中的所有障碍的游戏阶段
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		obs[i].setStage(stage);
	}
}

Obstacles::Obstacles() {
	//设定开始游戏阶段为kids
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		obs[i].setStage(kid);
	}
	//初始化所有障碍
	reSet();	
	
}

Obstacle::Obstacle() {
	obsSpeed = 6;
	r_init = 200;
	reSet();	//通过调用reset()方法来构造对象
}



void Obstacles::move() {

	//将每一个障碍都重绘并移动
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		obs[i].draw();	
		obs[i].move();
	}

	
	//判断障碍是否消失
	Monitor temp;
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		if (obs[i].disappear()) {
			temp = i;
			obs[temp].setObs(obs[temp-1]);		//障碍若消失，便重置该障碍
		}
	
	}
	Sleep(20);
}

//通过运算符重载实现循环监视

int Monitor::operator+(int num) {
	if (cnt + num >= OBSNUM) {
		return cnt + num - OBSNUM;
	} else {
		return cnt + num;
	}
}

int Monitor::operator-(int num) {
	if (cnt - num < 0) {
		return cnt - num + OBSNUM;
	} else {
		return  cnt - num;
	}
}

Monitor & Monitor::operator++() {
	if (cnt + 1 >= OBSNUM) {
		cnt = cnt + 1 - OBSNUM;
	} else {
		cnt++;
	}

	return *this;
}

Monitor& Monitor::operator=(int i) {
	cnt = i;
	return *this;
}
