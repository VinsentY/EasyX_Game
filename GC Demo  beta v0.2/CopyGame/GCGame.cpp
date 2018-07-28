#include "GCGame.h"
using namespace std;

#define WIDTH 640
#define HEIGHT 400

int score = 0;
int max_s = 0;


int main() {
	initgraph(WIDTH, HEIGHT);				// ���ڳ�ʼ����С

	Game game;
	game.startAnimation();

	closegraph();
	return 0;
}

void Game::Login() {
	cleardevice();
	//��½����
	putimage(75, 50, &growchange);
	rectangle(240, 180, 380, 230);
	rectangle(240, 240, 380, 290);
	settextcolor(BLACK);					

	outtextxy(260, 193, "��ʼ��Ϸ");
	outtextxy(260, 253, "�˳���Ϸ");

	rectangle(0, 360, 640, 400);

	//���������򼰰������
	MOUSEMSG m;
	while (isOver != true) {
		m = GetMouseMsg();				// �ж��Ƿ������
		if (m.x >= 240 && m.x <= 380 && m.y >= 180 && m.y <= 230) {
			setlinecolor(RED);			// ѡ�п��������ɫ
			rectangle(235, 175, 385, 235);
			if (m.uMsg == WM_LBUTTONDOWN) {	
				setbkcolor(WHITE);
				cleardevice();
				cutscenes();	// ���̶���
				gameKernel();	//������Ϸ
			}
		} else if (m.x >= 240 && m.x <= 380 && m.y >= 240 && m.y <= 290) {
			setlinecolor(RED);			// ѡ�п��������ɫ
			rectangle(235, 235, 385, 295);
			if (m.uMsg == WM_LBUTTONDOWN) {
				exit(1);
			}
			setfillstyle(BS_SOLID);
		} else {
			setlinecolor(WHITE);
			rectangle(235, 175, 385, 235);
			rectangle(235, 235, 385, 295);
		}
	}
}


//������������״̬���ӽ�����ײ��Զ�롣
int Game::collision() {

	//���������ϰ���λ��
	int &cha_left = character.getLeft();
	int &cha_right = character.getRight();
	int &cha_top = character.getTop();
	int &cha_bottom = character.getBottom();

	int &obs_left = obstacles.getMonObj().getLeft();
	int &obs_right = obstacles.getMonObj().getRight();
	int &obs_top = obstacles.getMonObj().getTop();
	int &obs_bottom = obstacles.getMonObj().getBottom();

	int state = -1;

	//��ײ�㷨
	if ((max(cha_left, obs_left) < min(cha_right, obs_right) && max(cha_top, obs_top) < min(cha_bottom, obs_bottom))) {
		state = 1;
	}

	//�ɹ�Խ����ǰ���ӷ���
	if (cha_left >= obs_right) {
		state = 0;
	}

	//1״̬��ʾ��ײ��0��ʾ�л�������
	return state;
}

void Game::gameOver() {
	FlushMouseMsgBuffer();		//�����껺����
	if (stage == loser) {
		isOver = true;
		endAnimation();	//��������
	} else {
		
		//����ý׶δﵽ��Ŀ��������������һ�׶�
		if (score.getCurScore() >= score.getMaxScore()) {
			stage = (STAGE)(stage + 1);	//������һ�׶�
			//NotFirst = false;
		} else {
			score.getCurScore() = score.getLastScore();	//��Ŀǰ�ķ�����Ϊ��һ�׶εĽ�������
		}

		//���ݽ׶�������Ϸ
		reSet(stage);
		//if (NotFirst == false) {
			cutscenes();
		//}
		gameKernel();
		
	}
}

void Game::startAnimation() {

	cmusic.setMediaName("rc\\music\\Oriԭ��.mp3");
	cmusic.Play();

	settextstyle(45, 0, _T("���Ŀ���"));	// ������ʽ��С
	BeginBatchDraw();

	//ʵ�ֽ��䱳������������
	for (int i = 0; i < 130; i++) {
		int j = 255 - i;
		setbkcolor(RGB(i, i, i));
		settextcolor(RGB(j, j, j));


		outtextxy(80, 50, "���������   ��������� ");

		outtextxy(125, 250, "����װ����ʽ�����ӣ�");


		FlushBatchDraw();
		cleardevice();

		Sleep(20);//60
	}
	EndBatchDraw();

	settextstyle(25, 0, _T("����"));	// ������ʽ��С
	setbkcolor(WHITE);
	cleardevice();

	
	Login();//��½����

}

void Game::endAnimation() {
	int i = 200;
	int j = -150;
	bool goUp = true;

	while (true) {
		//ʵ�ֺ�������ҡ��
		if (goUp) {
			i--;
		} else {
			i++;
		}
		if (i > 200) {
			goUp = true;

		} else if (i < 80) {
			//������Խ��������Ļ����ֹͣҡ�ڣ���ֱ����
			if (j <= 800) {
				goUp = false;
			}
		}

		Sleep(10);
		putimage(j, i, &catcher);	//������
		putimage(j - 400, i, &co_catcher);	//������
		solidrectangle(j - 5000, i, j - 300, i + 1000);		//���溣�˵ľ���
		solidrectangle(0, 327, WIDTH, HEIGHT);		//�ײ�����
		j = j + 2;	//�����ƶ�
		if (j >= 1100) {
			goUp = true;
		}
		//��һ�׶ζ����������ڶ��׶ο�ʼ
		if (i < -50) {
			setbkcolor(BLACK);
			cleardevice();
			int j = 1;
			settextstyle(45, 0, _T("���Ŀ���"));	// ������ʽ��С

			//ͬ���Ľ������塢����
			for (int j = 0; j < 316; j++) {
				if (j < 256) {
					settextcolor(RGB(j, j, j));
				} else {
					settextcolor(RGB(255, 255, 255));
				}

				outtextxy(185, 5, "G           C");
				//ʵ�������Ⱥ����Ч��
				if (j >= 60) {
					settextcolor(RGB(j - 60, j - 60, j - 60));
					outtextxy(215, 5, "row");
					outtextxy(350, 5, "hange");
				}

				FlushBatchDraw();
				Sleep(10);
			}
			j = 0;
			int x = 0;
			Sleep(1500);


			char key = ' ';

			score.scoreBoard();
			score.record();

			//����ƶ���
			while (true) {

				int i = 1;
				int index = 5;
				
				vector<Data> data = score.getData();

				settextcolor(RGB(255, 255, 255));
				outtextxy(185, 5 - x, "Grow    Change");
				if (j < 255) {
					settextcolor(RGB(j, j, j));
					j++;
					Sleep(10);
				}

				settextcolor(RGB(255, 255, 255));
				setfillcolor(BLACK);
				fillrectangle(140, 100 - x, 500, 165 - x);
				fillrectangle(140, 165 - x, 500, 370 - x);

				for (auto temp = data.begin(); temp != data.end(); temp++) {

					char str[30];
					sprintf(str, "%d: %s          %d", i, temp->getName(), temp->getScore());

					outtextxy(250, 110 - x, "Ranking");
					outtextxy(150, 120 + i * 50 - x, str);
					i++;
				}


				outtextxy(130, 120 + 115 * index++ - x, "GamePlanner �� Vinsent");
				outtextxy(160, 120 + 115 * index++ - x, "GameArtist �� Vinsent");
				outtextxy(160, 120 + 115 * index++ - x, "                      Mrs.Wang");
				outtextxy(160, 120 + 115 * index++ - x, "                      Gavin");
				outtextxy(40, 120 + 115 * index++ - x, "GameDevelopment �� Vinsent");
				outtextxy(150, 120 + 115 * index++ - x, "GameEditor �� Vinsent");
				outtextxy(170, 120 + 115 * index++ - x, "GameTest �� Vinsent");
				outtextxy(160, 120 + 115 * index++ - x, "                      Gavin");
				outtextxy(160, 120 + 115 * index++ - x, "                     RawEgg");
				outtextxy(90, 120 + 115 * index++ - x, "SpecialThanks �� Mrs.Wang");
				outtextxy(160, 120 + 115 * index++ - x, "                      Mrs.Whale");
				outtextxy(160, 120 + 115 * index++ - x, "                      Mr.2U");

				outtextxy(15, 120 + 115 * index++ - x, "It's my first time to make a simple game");
				outtextxy(25, 120 + 115 * index++ - x, "If you feel bad just throw banana to me");
				outtextxy(50, 120 + 115 * index++ - x, "It's my honor you like this Demo");
				FlushBatchDraw();
				cleardevice();
				Sleep(50);//50
				x++;

				if (kbhit()) {
					if (getch() == 27) {
						EndBatchDraw();
						cleardevice();
						Login();
					}
				}
			}		
		}
		FlushBatchDraw();
		cleardevice();
	}
}


void Game::reSet(STAGE stage) {
	//���ݽ׶�������Ϸ�е�����ϰ���
	obstacles.getMonitor() = 0;
	character.setStage(stage);
	character.reSet();
	obstacles.setStage(stage);
	score.setStage(stage);
	obstacles.reSet();
}

Game::Game() {

	setbkcolor(BLACK);					// ���ñ�����ɫ
	cleardevice();
	setlinecolor(BLACK);				// ���û�ͼ��ɫ
	settextcolor(LIGHTBLUE);				// ����������ɫ
	setfillcolor(LIGHTBLUE);			// ���������ɫ
	settextstyle(25, 0, _T("����"));	// ������ʽ��С
	srand((unsigned int)time(NULL));	// �����������

	loadimage(&dreamer, _T("rc\\picture\\����.jpg"), 400, 400);
	//loadimage(&co_dreamer, _T("rc\\picture\\��������ͼ.jpg"), 400, 400);
	loadimage(&catcher, _T("rc\\picture\\��ɫ����.jpg"), 400, 400);
	loadimage(&backgroud, _T("rc\\picture\\���ر���.jpg"), 640, 400);
	loadimage(&co_catcher, _T("rc\\picture\\��ɫ����2.jpg"), 400, 400);
	loadimage(&dark_bk, _T("rc\\picture\\�������걳��.jpg"), 640, 400);
	loadimage(&growchange, _T("rc\\picture\\GrowChange.jpg"), 480, 84);

	isOver = false;
	//NotFirst = false;
	stage = kid;
}

void Game::bkDraw() {
	static float i = 200;
	static int j = 0;
	static bool goUp = true;
	static int x = 0;
	static float l = -305;

	//���ݲ�ͬ�׶λ��Ʋ�ͬ����
	switch (stage) {
	case kid:
		//ʵ�ֱ���ѭ���ƶ�
		if (j >= WIDTH) {
			j = 0;
		} else {
			j++;
		}
		putimage(-j, 0, &backgroud);
		putimage(-j + WIDTH, 0, &backgroud);	//�ڴ����ϻ��Ʊ���ͼƬ
		//putimage(-250, 50, &co_dreamer, NOTSRCERASE);//SRCAND
		//putimage(-250, 50, &dreamer, SRCINVERT);//SRCPAINT	//�o�����F

		settextstyle(15, 0, _T("����"));	// ������ʽ��С
		setbkcolor(RGB(90, 180, 206));
		settextcolor(WHITE);

		outtextxy(480, 200, "���� = ��Ծ");
		outtextxy(480, 225, "���� = ����");

		break;
	case teenager:
		if (j >= WIDTH) {
			j = 0;
		} else {
			j = j + 4;
		}
		putimage(-j, 0, &dark_bk);
		putimage(-j + WIDTH, 0, &dark_bk);	//�ڴ����ϻ��Ʊ���ͼƬ
	
		//��������Ч��
		setlinecolor(BLUE);
		for (int i = 1; i < 1000; i = i + 40) {
			for (int j = 1; j < 800; j = j + 40) {

				if (x == 20) {
					x = 0;
				}
				line(i - x, j + x, i - 30 - x, j + 30 + x);	
			}
		}
		x++;
		Sleep(10);

		break;
	case adult:
		putimage(l + 22 * character.getNavie(), 100, &dreamer);

		setfillcolor(RGB(128, 138, 135));
		solidrectangle(0, 327, WIDTH, HEIGHT);
		l = l + 0.2;
		break;
	case loser:
		//�������·�������Ч��
		if (goUp) {
			i--;
		} else {
			i++;
		}
		if (i > 200) {
			goUp = true;
		} else if (i < 80) {
			goUp = false;
		}
		putimage(-150, i, &catcher);
		clock.move();
		solidrectangle(0, 327, WIDTH, HEIGHT);
		break;
	}


}

void Game::cutscenes() {
	settextstyle(45, 0, _T("���Ŀ���"));	// ������ʽ��С

	//����������Ч
	switch (stage) {
	case kid:
// 		cmusic.setMediaName("rc\\music\\Oriԭ��.mp3");
// 		cmusic.Play();		�ƶ�����Ϸ��ʼ����
		break;
	case teenager:
		cmusic.setMediaName("rc\\music\\������Ч.mp3");
		cmusic.Play();
		break;
	case adult:
		cmusic.setMediaName("rc\\music\\������Ч2.mp3");
		cmusic.Play();
		break;
	case loser:
		cmusic.setMediaName("rc\\music\\������Ч3.mp3");
		cmusic.Play();
		break;
	default:
		break;
	}

	BeginBatchDraw();
	//���֡���������Ч��
	for (int i = 0; i < 130; i++) {
		int j = 255 - i;
		settextcolor(RGB(j, j, j));

		switch (stage) {
		case kid:
			
			
			break;
		case teenager:

			outtextxy(100, 60, "��� ");

			outtextxy(270, 170, "�ܲ�����ͺ��˰�");

			outtextxy(100, 290, "����ʱ�⵲ס���·");


			break;
		case adult:
			outtextxy(200, 60, "���������");

			outtextxy(270, 170, "��");

			outtextxy(140, 290, "�����������������");

			break;
		case loser:
			outtextxy(80, 120, "ǰ����ͨ·");

			outtextxy(360, 290, "�󲻼���;");
			break;
		}

		setbkcolor(RGB(i, i, i));

		FlushBatchDraw();
		if (i != 254) {
			cleardevice();
		}

		Sleep(60);//60
	}
	//���̶�����������Ч
	switch (stage) {
	case kid:
		break;
	case teenager:
		cmusic.setMediaName("rc\\music\\Thunder.mp3");
		cmusic.Play();
		break;
	case adult:
		break;
	case loser:
		break;
	default:
		break;
	}
	setbkcolor(WHITE);
	EndBatchDraw();
	//NotFirst = true;
}

void Game::gameKernel() {		//�����㷨

	char keydown = '0';

	bool canType = true;
	//��ⰴ�����
	while (isOver != true) {

		while (!kbhit()) {

			BeginBatchDraw();
			bkDraw();	//���Ʊ���
			obstacles.move();	//�ϰ������ƶ�		

			switch (keydown) {
			case 72:
				//��������Ծ����������հ�������
				if (character.jump()) {
					keydown = '0';
					canType = true;
				} else {
					canType = false;
				}
				break;
			case 80:
				//�������������������հ�������
				if (character.roll()) {
					keydown = '0';
					canType = true;
				} else {
					canType = false;
				}
				break;
			default:
				keydown = ' ';
				character.move();
				break;
			}

			//�����仯
			score.addScore();
			score.putScore();

			FlushBatchDraw();
			cleardevice();

			//loser�׶��������
			static int times = 20;
			static char ch[10];

			switch (stage) {
			case kid:
				if (collision() == 1) {
					keydown = '0';
					gameOver();
				}

				break;
			case teenager:
				if (collision() == 1) {
					keydown = '0';
					gameOver();
				}

				
				break;
			case adult:
				if (collision() == 1) {
					keydown = '0';
					gameOver();
					break;
				}

				if (collision() == 0 || collision() == 1) {
					character.loseNaive();
				}
				break;
			case loser:
				
				sprintf(ch, "%d", times);
				outtextxy(535, 160, ch);

				if (collision() == 1) {
					canType = true;
					//�����䵽��25����ʼ����ý�岥��
					if (times == 36) {
						cmusic.setMediaName("rc\\music\\GrowChange.mp3");
						cmusic.Play();
					}
					times++;	//������ײ����������
					character.setYear(times);	//�ı����������
					if (times >= 56) {
						//���䵽��56����Ϸ����
						gameOver();
					}
					//beforekey = keydown;
					keydown = '0';
					//������Ϸ
					reSet(stage);
				}
				break;
			}

			if (collision() == 0) {	//0��ʾ�л�������

				++obstacles.getMonitor();
			}
			
		}
		if (canType) {
			keydown = getch();
		} else {
			getch();
		}
		
		
	}
}
