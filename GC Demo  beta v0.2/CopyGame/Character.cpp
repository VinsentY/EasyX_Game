#include "Character.h"

Character::Character() {
	stage = kid;
	year = 20;
	naive = 10;
	
	reSet();	//初始化人物

	//加载跑动图像
	//kid阶段
	loadimage(&pic_move[0][0], _T("rc\\picture\\move8_1.jpg"), 70, 70);
	loadimage(&pic_move[1][0], _T("rc\\picture\\move8_2.jpg"), 70, 70);
	loadimage(&pic_move[2][0], _T("rc\\picture\\move8_3.jpg"), 70, 70);
	loadimage(&pic_move[3][0], _T("rc\\picture\\move8_4.jpg"), 70, 70);
	loadimage(&pic_move[4][0], _T("rc\\picture\\move8_5.jpg"), 70, 70);
	loadimage(&pic_move[5][0], _T("rc\\picture\\move8_6.jpg"), 70, 70);
	loadimage(&pic_move[6][0], _T("rc\\picture\\move8_7.jpg"), 70, 70);
	loadimage(&pic_move[7][0], _T("rc\\picture\\move8_8.jpg"), 70, 70);
	//boy阶段
	loadimage(&pic_move[0][1], _T("rc\\picture\\move8_1.Rain.jpg"), 70, 100);
	loadimage(&pic_move[1][1], _T("rc\\picture\\move8_2.Rain.jpg"), 70, 100);
	loadimage(&pic_move[2][1], _T("rc\\picture\\move8_3.Rain.jpg"), 70, 100);
	loadimage(&pic_move[3][1], _T("rc\\picture\\move8_4.Rain.jpg"), 70, 100);
	loadimage(&pic_move[4][1], _T("rc\\picture\\move8_5.Rain.jpg"), 70, 100);
	loadimage(&pic_move[5][1], _T("rc\\picture\\move8_6.Rain.jpg"), 70, 100);
	loadimage(&pic_move[6][1], _T("rc\\picture\\move8_7.Rain.jpg"), 70, 100);
	loadimage(&pic_move[7][1], _T("rc\\picture\\move8_8.Rain.jpg"), 70, 100);
	//teenager阶段
	loadimage(&pic_move[0][2], _T("rc\\picture\\01.jpg"), 70, 100);
	loadimage(&pic_move[1][2], _T("rc\\picture\\02.jpg"), 70, 100);
	loadimage(&pic_move[2][2], _T("rc\\picture\\03.jpg"), 70, 100);
	loadimage(&pic_move[3][2], _T("rc\\picture\\04.jpg"), 70, 100);
	loadimage(&pic_move[4][2], _T("rc\\picture\\05.jpg"), 70, 100);
	loadimage(&pic_move[5][2], _T("rc\\picture\\06.jpg"), 70, 100);
	loadimage(&pic_move[6][2], _T("rc\\picture\\07.jpg"), 70, 100);
	loadimage(&pic_move[7][2], _T("rc\\picture\\08.jpg"), 70, 100);
	//adults阶段
	loadimage(&pic_move[0][3], _T("rc\\picture\\01.jpg"), 70, 100);
	loadimage(&pic_move[1][3], _T("rc\\picture\\02.jpg"), 70, 100);
	loadimage(&pic_move[2][3], _T("rc\\picture\\03.jpg"), 70, 100);
	loadimage(&pic_move[3][3], _T("rc\\picture\\04.jpg"), 70, 100);
	loadimage(&pic_move[4][3], _T("rc\\picture\\05.jpg"), 70, 100);
	loadimage(&pic_move[5][3], _T("rc\\picture\\06.jpg"), 70, 100);
	loadimage(&pic_move[6][3], _T("rc\\picture\\07.jpg"), 70, 100);
	loadimage(&pic_move[7][3], _T("rc\\picture\\08.jpg"), 70, 100);

	// 加载滚动图像
	//kid阶段
	loadimage(&pic_roll[0][0], _T("rc\\picture\\gun8_1.jpg"), 50, 40);
	loadimage(&pic_roll[1][0], _T("rc\\picture\\gun8_2.jpg"), 50, 40);
	loadimage(&pic_roll[2][0], _T("rc\\picture\\gun8_3.jpg"), 50, 40);
	loadimage(&pic_roll[3][0], _T("rc\\picture\\gun8_4.jpg"), 50, 40);
	loadimage(&pic_roll[4][0], _T("rc\\picture\\gun8_5.jpg"), 50, 40);
	loadimage(&pic_roll[5][0], _T("rc\\picture\\gun8_6.jpg"), 50, 40);
	loadimage(&pic_roll[6][0], _T("rc\\picture\\gun8_7.jpg"), 50, 40);
	loadimage(&pic_roll[7][0], _T("rc\\picture\\gun8_8.jpg"), 50, 40);
	//boy阶段
	loadimage(&pic_roll[0][1], _T("rc\\picture\\gun8_1.Rain.jpg"), 50, 50);
	loadimage(&pic_roll[1][1], _T("rc\\picture\\gun8_2.Rain.jpg"), 50, 50);
	loadimage(&pic_roll[2][1], _T("rc\\picture\\gun8_3.Rain.jpg"), 50, 50);
	loadimage(&pic_roll[3][1], _T("rc\\picture\\gun8_4.Rain.jpg"), 50, 50);
	loadimage(&pic_roll[4][1], _T("rc\\picture\\gun8_5.Rain.jpg"), 50, 50);
	loadimage(&pic_roll[5][1], _T("rc\\picture\\gun8_6.Rain.jpg"), 50, 50);
	loadimage(&pic_roll[6][1], _T("rc\\picture\\gun8_7.Rain.jpg"), 50, 50);
	loadimage(&pic_roll[7][1], _T("rc\\picture\\gun8_8.Rain.jpg"), 50, 50);
	//teenager阶段
	loadimage(&pic_roll[0][2], _T("rc\\picture\\1.jpg"), 50, 50);
	loadimage(&pic_roll[1][2], _T("rc\\picture\\2.jpg"), 50, 50);
	loadimage(&pic_roll[2][2], _T("rc\\picture\\3.jpg"), 50, 50);
	loadimage(&pic_roll[3][2], _T("rc\\picture\\4.jpg"), 50, 50);
	loadimage(&pic_roll[4][2], _T("rc\\picture\\5.jpg"), 50, 50);
	loadimage(&pic_roll[5][2], _T("rc\\picture\\6.jpg"), 50, 50);
	loadimage(&pic_roll[6][2], _T("rc\\picture\\7.jpg"), 50, 50);
	loadimage(&pic_roll[7][2], _T("rc\\picture\\8.jpg"), 50, 50);
	//adults阶段
	loadimage(&pic_roll[0][3], _T("rc\\picture\\1.jpg"), 50, 50);
	loadimage(&pic_roll[1][3], _T("rc\\picture\\2.jpg"), 50, 50);
	loadimage(&pic_roll[2][3], _T("rc\\picture\\3.jpg"), 50, 50);
	loadimage(&pic_roll[3][3], _T("rc\\picture\\4.jpg"), 50, 50);
	loadimage(&pic_roll[4][3], _T("rc\\picture\\5.jpg"), 50, 50);
	loadimage(&pic_roll[5][3], _T("rc\\picture\\6.jpg"), 50, 50);
	loadimage(&pic_roll[6][3], _T("rc\\picture\\7.jpg"), 50, 50);
	loadimage(&pic_roll[7][3], _T("rc\\picture\\8.jpg"), 50, 50);

	//加载跳跃图像
	loadimage(&pic_jump[0], _T("rc\\picture\\move8_5.jpg"), 70, 70);
	loadimage(&pic_jump[1], _T("rc\\picture\\move8_5.Rain.jpg"), 70, 100);
	loadimage(&pic_jump[2], _T("rc\\picture\\05.jpg"), 70, 100);
	loadimage(&pic_jump[3], _T("rc\\picture\\05.jpg"), 70, 100);

}

int& Character::getLeft() {
	return left;
}

int& Character::getTop() {
	return top;
}

int& Character::getRight() {
	return right;
}

int& Character::getBottom() {
	return bottom;
}

int Character::getNavie() {
	return naive;
}


void Character::setStage(STAGE stage) {
	this->stage = stage;
}

void Character::setYear(int year) {
	this->year = year;
}

void Character::loseNaive() {
	naive--;
}

void Character::reSet() {
	
	//根据阶段不同，初始化状态也不同
	switch (stage) {
	case kid:
		move_width = 65;
		move_tall = 70;
		roll_tall = 40;
		roll_width = 50;

		left = 400;
		bottom = INITIAL_BOTTOM;
		right = left + move_width;
		top = bottom - move_tall;
		
		INITIAL_SPEED = 7;
		ROLL_TIME = 30;
		sleepTime = 0;
		break;
	case teenager:

		move_width = 65;
		move_tall = 100;
		roll_tall = 50;
		roll_width = 50;

		left = 300;
		bottom = INITIAL_BOTTOM;
		right = left + move_width;
		top = bottom - move_tall;

		INITIAL_SPEED = 6;
		ROLL_TIME = 18;
		sleepTime = 0;
		break;
	case adult:
		move_width = 65;
		move_tall = 100;
		roll_tall = 50;
		roll_width = 50;
		
		left = 300;
		bottom = INITIAL_BOTTOM;
		right = left + move_width;
		top = bottom - move_tall;

		INITIAL_SPEED = 6;
		ROLL_TIME = 30;
		sleepTime = 2;
		break;
	case loser:

		bottom = INITIAL_BOTTOM;
		top = bottom - move_tall;
		jump_speed = INITIAL_SPEED;
		
		move_width = 65;
		move_tall = 100;
		roll_tall = 50;
		roll_width = 50;

		left = 500 - year * 5;
		right = left + move_width;
		top = bottom - move_tall;

		INITIAL_SPEED = 5.5;
		ROLL_TIME = 15;
		sleepTime = 2;
		break;
	}

	activity = 0;
	
	roll_time = 0;

	jump_speed = INITIAL_SPEED;
	
	move_fps = 0;
	roll_fps = 0;
}

bool Character::jump() {
	jumpEnd = false;

	//状态改为跳跃状态
	activity = 1;
	//休眠时间
	Sleep(sleepTime);
	putimage(left, top, &pic_jump[stage]);		//输出帧图
	top = top - jump_speed;
	bottom = top + move_tall;

	//判断是否落地
	if (bottom > INITIAL_BOTTOM) {

		bottom = INITIAL_BOTTOM;
		top = bottom - move_tall;
		jump_speed = INITIAL_SPEED;
		jumpEnd = true;
		activity = 0;	//跳跃状态结束，变为奔跑状态
	}
	//v = v - gt 改变速度
	jump_speed = jump_speed - 20 * 0.02;
	
	return jumpEnd;
}

void Character::move() {
	//改变状态为移动状态
	activity = 0;

	putimage(left, top, &pic_move[move_fps][stage]);
	Sleep(sleepTime);
	move_fps++;
	if (move_fps == MOVE_FPS) {		//人物图片帧交换
		move_fps = 0;
	}
}



bool Character::roll() {
	rollEnd = false;

	//改变状态为滚动状态
	activity = -1;

	top = bottom - roll_tall;	//改变碰撞体积
	right = left + roll_width;
		
	
	putimage(left, top, &pic_roll[roll_fps][stage]);
	Sleep(sleepTime);
	roll_fps++;
	roll_time++;
	//人物图片帧交换
	if (roll_fps == ROLL_FPS) {
		roll_fps = 0;
	}
	//判定是否滚动结束
	if (roll_time >= ROLL_TIME) {
		roll_time = 0;
		rollEnd = true;
		top = bottom - move_tall;		//重置碰撞体积
		right = left + move_width;
		activity = 0;	
	}
	return rollEnd;
}

