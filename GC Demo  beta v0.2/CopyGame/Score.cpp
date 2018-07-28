#include "Score.h"

using namespace std;

void Score::cursorJump(int index) {

	static int y = 360;
	static int x = 150;
	static time_t before = GetTickCount();
	static time_t after = before + 750;

	static bool isLighted = true;

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 6);
	setlinecolor(WHITE);
	 
	before = GetTickCount();
	if (before <= after) {
		isLighted = true;
	} else if (before > after && before < after + 750) {
		isLighted = false;
	} else if (before > after + 750) {
		after = before + 750;
	}
	switch (index) {
	case 0:
		if (isLighted) {
			line(x, y, x + 30, y);
		}

		line(x + 40, y, x + 70, y);
		line(x + 80, y, x + 110, y);
		break;
	case 1:
		line(x, y, x + 30, y);
		if (isLighted) {
			line(x + 40, y, x + 70, y);
		}
		line(x + 80, y, x + 110, y);
		break;
	case 2:
		line(x, y, x + 30, y);
		line(x + 40, y, x + 70, y);
		if (isLighted) {
			line(x + 80, y, x + 110, y);
		}
		break;
	default:
		if (isLighted) {
			line(x, y, x + 30, y);
			line(x + 40, y, x + 70, y);
			line(x + 80, y, x + 110, y);
		}
		break;
	}
}

Score::Score() {
	stage = kid;
	cur_score = 0;
	last_score = 0;

	ifstream in("Score.txt");
	int index = 0;

	while (!in.eof()) {
		Data temp;
		char name[4];
		int score;

		in >> name >> score;
		temp.setName(name);
		temp.setScore(score);

		data.push_back(temp);
		index++;
	}
	data.erase(data.end() - 1);
	in.close();
}

int& Score::getCurScore() {
	return cur_score;
}

int Score::getMaxScore() {
	return max_score;
}

int Score::getLastScore() {
	return last_score;
}

void Score::putScore() {
	//根据不同阶段设定目标分数
	switch (stage) {
	case kid:
		setbkcolor(RGB(90,180,206));
		settextcolor(WHITE);

		//在构造函数中设定max_score，在此
		max_score = 500;//500

		break;
	case teenager:
		setbkcolor(RGB(52, 108, 133));
		settextcolor(WHITE);
		max_score = 900;//1100
		break;
	case adult:
		setbkcolor(WHITE);
		settextcolor(BLACK);
		max_score = 1400;//1500
		break;
	case loser:
		setbkcolor(WHITE);
		settextcolor(BLACK);
		max_score = cur_score + 500;
		break;
	default:
		break;
	}
	settextstyle(25, 0, _T("宋体"));
	
	char score[10];
	char max[10];
	//分数绘制
	sprintf(max, "%d", max_score);	
	sprintf(score, "%d", cur_score);	

	outtextxy(58, 10, "分数:0");
	outtextxy(400, 10, "目标分数:");
	outtextxy(120, 10, score);		
	outtextxy(510, 10, max);		
	
}

void Score::record() {
	ofstream out("score.txt");
	for (auto temp = data.begin(); temp != data.end(); temp++) {
		out << temp->getName() << "   " << temp->getScore() << endl;
	}

}

void Score::scoreBoard() {

	cleardevice();
	char name[4] = "   ";
	char score[10];
	sprintf(score, "%d", cur_score);

	int cnt = 0;
	
	while (true) {

		while (!kbhit()) {
			int x = 150;

			if (cnt == 3) {
				if (name[cnt] == 13) {
					name[cnt] = '\0';
					Data add(name, cur_score);
					data.push_back(add);
					sort(data.begin(), data.end(), greater<Data>());
					goto out;
				}
			} else if (name[cnt] != ' ' && ((name[cnt] >= 'A' && name[cnt] <= 'Z') || (name[cnt] > 'a' && name[cnt] < 'z'))) {
				strupr(name);
				cnt++;
			}

			for (int i = 0; i < cnt; i++) {
				outtextxy(x, 310, name[i]);
				x += 40;
			}
			outtextxy(185, 5 - x, "Grow    Change");

			outtextxy(30, 310, "Name:");
			outtextxy(370, 310, "Score:");
			outtextxy(480, 310, score);
			cursorJump(cnt);
			FlushBatchDraw();
			cleardevice();		
		}
		name[cnt] = getch();
	}
out: return;
}

const vector<Data>& Score::getData() {
	return data;
}

void Score::getRecord() {
	ifstream in("score.txt");

	if (!in) {
		cout << "open error!" << endl;
		exit(1);
	}
	in >> max_score;
	in.close();
}

void Score::setStage(STAGE stage) {
	//设定阶段的同时，初始化分数
	this->stage = stage;
	last_score = cur_score;
}

void Score::addScore() {
	cur_score++;
}
