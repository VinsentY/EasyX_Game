#include "GCGame.h"
using namespace std;

#define WIDTH 640
#define HEIGHT 400

int score = 0;
int max_s = 0;


int main() {
	initgraph(WIDTH, HEIGHT);				// 窗口初始化大小

	Game game;
	game.startAnimation();

	closegraph();
	return 0;
}

void Game::Login() {
	cleardevice();
	//登陆界面
	putimage(75, 50, &growchange);
	rectangle(240, 180, 380, 230);
	rectangle(240, 240, 380, 290);
	settextcolor(BLACK);					

	outtextxy(260, 193, "开始游戏");
	outtextxy(260, 253, "退出游戏");

	rectangle(0, 360, 640, 400);

	//检测鼠标区域及按键情况
	MOUSEMSG m;
	while (isOver != true) {
		m = GetMouseMsg();				// 判断是否按下鼠标
		if (m.x >= 240 && m.x <= 380 && m.y >= 180 && m.y <= 230) {
			setlinecolor(RED);			// 选中框框线条颜色
			rectangle(235, 175, 385, 235);
			if (m.uMsg == WM_LBUTTONDOWN) {	
				setbkcolor(WHITE);
				cleardevice();
				cutscenes();	// 过程动画
				gameKernel();	//进入游戏
			}
		} else if (m.x >= 240 && m.x <= 380 && m.y >= 240 && m.y <= 290) {
			setlinecolor(RED);			// 选中框框线条颜色
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


//两物体有三种状态，接近，碰撞、远离。
int Game::collision() {

	//获得人物和障碍的位置
	int &cha_left = character.getLeft();
	int &cha_right = character.getRight();
	int &cha_top = character.getTop();
	int &cha_bottom = character.getBottom();

	int &obs_left = obstacles.getMonObj().getLeft();
	int &obs_right = obstacles.getMonObj().getRight();
	int &obs_top = obstacles.getMonObj().getTop();
	int &obs_bottom = obstacles.getMonObj().getBottom();

	int state = -1;

	//碰撞算法
	if ((max(cha_left, obs_left) < min(cha_right, obs_right) && max(cha_top, obs_top) < min(cha_bottom, obs_bottom))) {
		state = 1;
	}

	//成功越过当前监视方块
	if (cha_left >= obs_right) {
		state = 0;
	}

	//1状态表示碰撞，0表示切换监视者
	return state;
}

void Game::gameOver() {
	FlushMouseMsgBuffer();		//清空鼠标缓存区
	if (stage == loser) {
		isOver = true;
		endAnimation();	//结束动画
	} else {
		
		//如果该阶段达到了目标分数，则进入下一阶段
		if (score.getCurScore() >= score.getMaxScore()) {
			stage = (STAGE)(stage + 1);	//进入下一阶段
			//NotFirst = false;
		} else {
			score.getCurScore() = score.getLastScore();	//将目前的分数变为上一阶段的结束分数
		}

		//根据阶段重置游戏
		reSet(stage);
		//if (NotFirst == false) {
			cutscenes();
		//}
		gameKernel();
		
	}
}

void Game::startAnimation() {

	cmusic.setMediaName("rc\\music\\Ori原声.mp3");
	cmusic.Play();

	settextstyle(45, 0, _T("华文楷体"));	// 字体样式大小
	BeginBatchDraw();

	//实现渐变背景及渐变文字
	for (int i = 0; i < 130; i++) {
		int j = 255 - i;
		setbkcolor(RGB(i, i, i));
		settextcolor(RGB(j, j, j));


		outtextxy(80, 50, "建议打开音量   或佩戴耳机 ");

		outtextxy(125, 250, "（假装很正式的样子）");


		FlushBatchDraw();
		cleardevice();

		Sleep(20);//60
	}
	EndBatchDraw();

	settextstyle(25, 0, _T("宋体"));	// 字体样式大小
	setbkcolor(WHITE);
	cleardevice();

	
	Login();//登陆界面

}

void Game::endAnimation() {
	int i = 200;
	int j = -150;
	bool goUp = true;

	while (true) {
		//实现海浪上下摇摆
		if (goUp) {
			i--;
		} else {
			i++;
		}
		if (i > 200) {
			goUp = true;

		} else if (i < 80) {
			//当海浪越过整个屏幕，则停止摇摆，径直上升
			if (j <= 800) {
				goUp = false;
			}
		}

		Sleep(10);
		putimage(j, i, &catcher);	//正向海浪
		putimage(j - 400, i, &co_catcher);	//反向海浪
		solidrectangle(j - 5000, i, j - 300, i + 1000);		//跟随海浪的矩形
		solidrectangle(0, 327, WIDTH, HEIGHT);		//底部矩形
		j = j + 2;	//海浪移动
		if (j >= 1100) {
			goUp = true;
		}
		//第一阶段动画结束，第二阶段开始
		if (i < -50) {
			setbkcolor(BLACK);
			cleardevice();
			int j = 1;
			settextstyle(45, 0, _T("华文楷体"));	// 字体样式大小

			//同样的渐变字体、背景
			for (int j = 0; j < 316; j++) {
				if (j < 256) {
					settextcolor(RGB(j, j, j));
				} else {
					settextcolor(RGB(255, 255, 255));
				}

				outtextxy(185, 5, "G           C");
				//实现字体先后出现效果
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

			//走马灯动画
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


				outtextxy(130, 120 + 115 * index++ - x, "GamePlanner ： Vinsent");
				outtextxy(160, 120 + 115 * index++ - x, "GameArtist ： Vinsent");
				outtextxy(160, 120 + 115 * index++ - x, "                      Mrs.Wang");
				outtextxy(160, 120 + 115 * index++ - x, "                      Gavin");
				outtextxy(40, 120 + 115 * index++ - x, "GameDevelopment ： Vinsent");
				outtextxy(150, 120 + 115 * index++ - x, "GameEditor ： Vinsent");
				outtextxy(170, 120 + 115 * index++ - x, "GameTest ： Vinsent");
				outtextxy(160, 120 + 115 * index++ - x, "                      Gavin");
				outtextxy(160, 120 + 115 * index++ - x, "                     RawEgg");
				outtextxy(90, 120 + 115 * index++ - x, "SpecialThanks ： Mrs.Wang");
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
	//根据阶段重设游戏中的人物、障碍。
	obstacles.getMonitor() = 0;
	character.setStage(stage);
	character.reSet();
	obstacles.setStage(stage);
	score.setStage(stage);
	obstacles.reSet();
}

Game::Game() {

	setbkcolor(BLACK);					// 设置背景颜色
	cleardevice();
	setlinecolor(BLACK);				// 设置绘图颜色
	settextcolor(LIGHTBLUE);				// 设置文字颜色
	setfillcolor(LIGHTBLUE);			// 设置填充颜色
	settextstyle(25, 0, _T("宋体"));	// 字体样式大小
	srand((unsigned int)time(NULL));	// 设置随机种子

	loadimage(&dreamer, _T("rc\\picture\\海浪.jpg"), 400, 400);
	//loadimage(&co_dreamer, _T("rc\\picture\\海浪掩码图.jpg"), 400, 400);
	loadimage(&catcher, _T("rc\\picture\\黑色海浪.jpg"), 400, 400);
	loadimage(&backgroud, _T("rc\\picture\\像素背景.jpg"), 640, 400);
	loadimage(&co_catcher, _T("rc\\picture\\黑色海浪2.jpg"), 400, 400);
	loadimage(&dark_bk, _T("rc\\picture\\像素下雨背景.jpg"), 640, 400);
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

	//根据不同阶段绘制不同背景
	switch (stage) {
	case kid:
		//实现背景循环移动
		if (j >= WIDTH) {
			j = 0;
		} else {
			j++;
		}
		putimage(-j, 0, &backgroud);
		putimage(-j + WIDTH, 0, &backgroud);	//在窗口上绘制背景图片
		//putimage(-250, 50, &co_dreamer, NOTSRCERASE);//SRCAND
		//putimage(-250, 50, &dreamer, SRCINVERT);//SRCPAINT	//無法實現

		settextstyle(15, 0, _T("宋体"));	// 字体样式大小
		setbkcolor(RGB(90, 180, 206));
		settextcolor(WHITE);

		outtextxy(480, 200, "↑键 = 跳跃");
		outtextxy(480, 225, "↓键 = 滚动");

		break;
	case teenager:
		if (j >= WIDTH) {
			j = 0;
		} else {
			j = j + 4;
		}
		putimage(-j, 0, &dark_bk);
		putimage(-j + WIDTH, 0, &dark_bk);	//在窗口上绘制背景图片
	
		//下雨粒子效果
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
		//海浪上下翻滚动画效果
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
	settextstyle(45, 0, _T("华文楷体"));	// 字体样式大小

	//过场动画音效
	switch (stage) {
	case kid:
// 		cmusic.setMediaName("rc\\music\\Ori原声.mp3");
// 		cmusic.Play();		移动到游戏开始播放
		break;
	case teenager:
		cmusic.setMediaName("rc\\music\\过渡音效.mp3");
		cmusic.Play();
		break;
	case adult:
		cmusic.setMediaName("rc\\music\\过渡音效2.mp3");
		cmusic.Play();
		break;
	case loser:
		cmusic.setMediaName("rc\\music\\过渡音效3.mp3");
		cmusic.Play();
		break;
	default:
		break;
	}

	BeginBatchDraw();
	//文字、背景渐变效果
	for (int i = 0; i < 130; i++) {
		int j = 255 - i;
		settextcolor(RGB(j, j, j));

		switch (stage) {
		case kid:
			
			
			break;
		case teenager:

			outtextxy(100, 60, "如果 ");

			outtextxy(270, 170, "能不长大就好了啊");

			outtextxy(100, 290, "可是时光挡住你的路");


			break;
		case adult:
			outtextxy(200, 60, "你既有所求");

			outtextxy(270, 170, "那");

			outtextxy(140, 290, "就拿你的天真来换吧");

			break;
		case loser:
			outtextxy(80, 120, "前已无通路");

			outtextxy(360, 290, "后不见归途");
			break;
		}

		setbkcolor(RGB(i, i, i));

		FlushBatchDraw();
		if (i != 254) {
			cleardevice();
		}

		Sleep(60);//60
	}
	//过程动画结束后音效
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

void Game::gameKernel() {		//核心算法

	char keydown = '0';

	bool canType = true;
	//检测按键情况
	while (isOver != true) {

		while (!kbhit()) {

			BeginBatchDraw();
			bkDraw();	//绘制背景
			obstacles.move();	//障碍保持移动		

			switch (keydown) {
			case 72:
				//当人物跳跃结束，则清空按键输入
				if (character.jump()) {
					keydown = '0';
					canType = true;
				} else {
					canType = false;
				}
				break;
			case 80:
				//当人物滚动结束，则清空按键输入
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

			//分数变化
			score.addScore();
			score.putScore();

			FlushBatchDraw();
			cleardevice();

			//loser阶段相关数据
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
					//当年龄到达25，开始音乐媒体播放
					if (times == 36) {
						cmusic.setMediaName("rc\\music\\GrowChange.mp3");
						cmusic.Play();
					}
					times++;	//发生碰撞则年龄增加
					character.setYear(times);	//改变人物的年龄
					if (times >= 56) {
						//年龄到达56则游戏结束
						gameOver();
					}
					//beforekey = keydown;
					keydown = '0';
					//重置游戏
					reSet(stage);
				}
				break;
			}

			if (collision() == 0) {	//0表示切换监视者

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
