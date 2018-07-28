#include "Obstacle.h"

//Obstacle��

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
	//�趨�ϰ����
	style();

	//�����ϰ�o���õ�ǰ�ϰ�
	left = o.left + o.r;
	right = o.right + o.obs_length;
	r = rand() % 200 + r_init;

}

void Obstacle::reSet() {
	
	style();
	left = 740;		//�������ʼ�����������Ҳ�
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

	//���ݽ׶β�ͬ�����Ʋ�ͬ���ϰ�
	switch (stage) {
	case kid:
		srand(time(NULL));
		switch (rand()%12 + 1) {
		case 1:
		case 2:
			setfillcolor(RGB(255, 192, 203));	//�ۺ�
			break;
		case 3:			
			setfillcolor(RGB(0, 255, 255));		//��ɫ
			break;
		case 4:
			setfillcolor(RGB(218, 112, 214));	//����ɫ
			break;
		case 5:
			setfillcolor(RGB(0, 199, 140));		//��������
			break;
		case 6:
			setfillcolor(RGB(188, 143, 143));	//õ���
			break;
		case 7:
			setfillcolor(RGB(255, 128, 0));		//�ٻ�
			break;
		case 8:
		case 9:
			setfillcolor(RGB(0, 191, 255));		//������
			break;
		case 10:
			setfillcolor(RGB(255, 255, 0));		//����
			break;
		case 11:
		case 12:
			setfillcolor(RGB(255, 255, 240));	//����ɫ
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
	solidrectangle(left, top, right, bottom);	//���Ƹ��ϰ�����

}
	

bool Obstacle::disappear() {
	return left + 40 <= 0;
}

void Obstacle::style() {

	//���ݽ׶β�ͬ�����ò�ͬ���ϰ����
	srand(time(NULL));
	static int i = 1;
	switch (stage) {
	case kid:
		//�ý׶�ֱ����18������Ż�����ײ�����
		i++;
		obsSpeed = 2.5;
		switch (i) {			
		case 9://10
			obs_length = 40;
			top = 297;
			bottom = top + 30;	//�ײ�����
			break;
		default:
			obs_length = 125;
			top = 150;
			bottom = top + 30;	//��������
			break;
		}
		break;
	case teenager:
		//�����ϰ��ٶ�
		obsSpeed = 8;
		//�����������
		switch (rand() % 10 + 1) {
		case 1:
		case 2:
		case 3:
			obs_length = 40;
			top = 300;
			bottom = top + 30;	//�ײ�����
			break;
		default:
			obs_length = 40;
			top = 225;
			bottom = top + 30;	//��������
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
			bottom = top + 30;	//��������
			break;
		case 4:	
		case 5:
		case 6:
			top = 300;
			bottom = top + 30;	//�ײ�����
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
			bottom = top + 30;	//��������
			break;
		case 4:		
		case 5:
		case 6:
			top = 300;
			bottom = top + 30;	//�ײ�����
			break;
		}
		break; 
	}
	
}

//////////////////////////////////////////////////////////////////////////
//Obstacles��

Obstacle Obstacles::getMonObj() {
	return obs[monitor];
}

Monitor& Obstacles::getMonitor() {
	return monitor;
}


void Obstacles::reSet() {
	//�ȳ�ʼ����һ������
	obs[0].reSet();
	//֮��ķ������ǰһ���������λ���趨
	for (int i = 1; i < Monitor::OBSNUM; i++) {		
		obs[i].setObs(obs[i - 1]);
	}
}

void Obstacles::setStage(STAGE stage) {
	//�����ϰ����е������ϰ�����Ϸ�׶�
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		obs[i].setStage(stage);
	}
}

Obstacles::Obstacles() {
	//�趨��ʼ��Ϸ�׶�Ϊkids
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		obs[i].setStage(kid);
	}
	//��ʼ�������ϰ�
	reSet();	
	
}

Obstacle::Obstacle() {
	obsSpeed = 6;
	r_init = 200;
	reSet();	//ͨ������reset()�������������
}



void Obstacles::move() {

	//��ÿһ���ϰ����ػ沢�ƶ�
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		obs[i].draw();	
		obs[i].move();
	}

	
	//�ж��ϰ��Ƿ���ʧ
	Monitor temp;
	for (int i = 0; i < Monitor::OBSNUM; i++) {
		if (obs[i].disappear()) {
			temp = i;
			obs[temp].setObs(obs[temp-1]);		//�ϰ�����ʧ�������ø��ϰ�
		}
	
	}
	Sleep(20);
}

//ͨ�����������ʵ��ѭ������

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
