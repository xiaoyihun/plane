#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h >


#include<graphics.h>
#include<easyx.h>
#include <tchar.h>

#include<iostream>
using namespace std;
#include<list>



//引用Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

#define High 600 // 游戏画面尺寸
#define Width 512

/*
	1//图片和界面初始化
	void startup();

	2//初始化游戏菜单界面
	void startMenu()

	3//显示游戏界面
	void show();

	4//飞机跟随鼠标移动
	updateWithlnput();

	5//子弹和敌机自由移动，死亡
	updateWithoutlnput();

	6.//游戏结束处理
	gameover()

*/

typedef struct Bullet
{
	int bx;
	int by;
}Bullt;

list<Bullt> bullt;//存储子弹链表

float position_x, position_y;//飞机位置
float bullet_x, bullet_y;//子弹位置
float enemy_x, enemy_y;//敌机位置
float enemy2_x, enemy2_y;//敌机位置
float enemy3_x, enemy3_y;//敌机位置

IMAGE img_bk;//背景图片
IMAGE img_planeNormal1, img_planeNormal2;//正常飞机图片
IMAGE img_planeExplode1, img_planeExplode2;//爆炸飞机图片
IMAGE img_bullet1, img_bullet2;//子弹图片
IMAGE img_enemyPlane1, img_enemyPlane2, img_enemyPlane3, img_enemyPlane4;//敌机图片

int isExpolde = 0;//飞机是否爆炸
int shengming = 3;//生命
int score = 0;//得分
int guanka = 1;//关卡
int temp=2;
int gameStatus = 0;//游戏状态,0为初始菜单界面,1为正常游戏,2为结束游戏状态,3为游戏暂停

void startMenu();//初始菜单界面
void pauseMenu();//游戏暂停后菜单界面，一般按ESC键后启动该界面
void startup();//数据初始化
void show();//显示界面
void updateWithoutlnput();//与用户输入无关的更新
void updateWithlnput();//与用户输入有关的更新updateWithlnput

void gameover();//游戏结束、后续处理



//void readRecordFile();//读取游戏数据文件存档


//1.初始画游戏界面
void startMenu()
{
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.3, High * 0.3,_T("1 新游戏"));
	outtextxy(Width * 0.3, High * 0.4, _T("2 读取游戏存档"));
	outtextxy(Width * 0.3, High * 0.5, _T("3 退出"));

	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(Width * 0.25, High * 0.6, _T("鼠标移动控制飞机移动"));
	outtextxy(Width * 0.25, High * 0.65, _T("鼠标左键发射子弹"));
	outtextxy(Width * 0.25, High * 0.7, _T("ESC暂停游戏"));
	outtextxy(Width * 0.25, High * 0.75, _T("撞击后按任意键重新开始"));
	FlushBatchDraw();//BeginBatchDraw直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出。
	Sleep(2);

	char input;
	if (_kbhit())//判断是否有输入
	{
		input = _getch();//根据用户的不同输入来移动，不必输入回车
		if (input == '1')
		{
			gameStatus = 1;
		}
		else if (input == '2')
		{
			//readRecordFile();
			gameStatus = 1;
		}
		else if (input == '3')
		{
			gameStatus = 2;
			exit(0);
		}
	}
}

//2.游戏暂停后菜单界面,一般按ESC键后启动该界面
void pauseMenu()
{
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.3, High * 0.3, _T("1 新游戏"));
	outtextxy(Width * 0.3, High * 0.4, _T("2 读取游戏存档"));
	outtextxy(Width * 0.3, High * 0.5, _T("3 退出"));

	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(Width * 0.25, High * 0.6, _T("鼠标移动控制飞机移动"));
	outtextxy(Width * 0.25, High * 0.65, _T("鼠标左键发射子弹"));
	outtextxy(Width * 0.25, High * 0.7, _T("ESC暂停游戏"));
	outtextxy(Width * 0.25, High * 0.75, _T("撞击后按任意键重新开始"));
	FlushBatchDraw();//BeginBatchDraw直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出。
	Sleep(2);

	
	char input;
	if (_kbhit())//判断是否有输入
	{
		input = _getch();//根据用户的不同输入来移动，不必输入回车
		if (input == '1')
		{
			gameStatus = 1;
		}
		else if (input == '2')
		{
			//writeRecordFile();
			gameStatus = 1;
		}
		else if (input == '3')
		{
			gameStatus = 2;
			exit(0);
		}
	}
}

//设置图片存储位置
void startup()
{
	//初始化图形系统
	initgraph(Width, High); 
	//获取窗口句柄
	HWND hwnd = GetHWnd();
	//设置窗口标题文字
	SetWindowText(hwnd, _T("数据结构小游戏开发-飞机打针"));
	

	loadimage(&img_bk, _T("./res/images/background.jpg"));//背景图片
	loadimage(&img_planeNormal1, _T("./res/images/hero.png"),150,100,true);//正常飞机
	loadimage(&img_planeNormal2, _T("./res/images/hero1.png"),150,100,true);//正常飞机

	loadimage(&img_bullet1, _T("./res/images/bullet2.png"));//子弹
	loadimage(&img_bullet2, _T("./res/images/bullet2-1.png"));//子弹

	loadimage(&img_enemyPlane1, _T("./res/images/enemy1.png"),150,100);//敌机
	loadimage(&img_enemyPlane2, _T("./res/images/smallenemy.png"),150,100);//敌机

	loadimage(&img_enemyPlane3, _T("./res/images/Boss.png"), 150, 100);//BOSS敌机
	loadimage(&img_enemyPlane4, _T("./res/images/Boss1.png"), 150, 100);//BOSS敌机

	loadimage(&img_planeExplode1, _T("./res/images/hero1.png"),150,100);//爆炸飞机
	loadimage(&img_planeExplode2, _T("./res/image/hero.png"),150,100);//爆炸飞机


	position_x = Width * 0.5;//飞机位置
	position_y = High * 0.9;//飞机位置


	bullet_x = position_x+20;//子弹位置
	bullet_y = -40;//子弹位置

	enemy_x = Width * 0.5;//敌机位置
	enemy_y = 10;//敌机位置


	BeginBatchDraw();

	while (gameStatus == 0)
		startMenu();//初始菜单界面
			
}

void startup2()
{
	loadimage(&img_bk, _T("./res/images/background.jpg"));//背景图片
	loadimage(&img_planeNormal1, _T("./res/images/hero.png"), 150, 100, true);//正常飞机
	loadimage(&img_planeNormal2, _T("./res/images/hero1.png"), 150, 100, true);//正常飞机

	loadimage(&img_bullet1, _T("./res/images/bullet2.png"), 150, 100);//子弹
	loadimage(&img_bullet2, _T("./res/images/bullet2-1.png"), 150, 100);//子弹

	loadimage(&img_enemyPlane1, _T("./res/images/enemy1.png"), 150, 100);//敌机
	loadimage(&img_enemyPlane2, _T("./res/images/smallenemy.png"), 150, 100);//敌机

	loadimage(&img_enemyPlane3, _T("./res/images/Boss.png"),150, 100);//BOSS敌机
	loadimage(&img_enemyPlane4, _T("./res/images/Boss1.png"), 150, 100);//BOSS敌机

	loadimage(&img_planeExplode1, _T("./res/images/hero1.png"),150,100);//爆炸飞机
	loadimage(&img_planeExplode2, _T("./res/image/hero.png"),150,100);//爆炸飞机


	position_x = Width * 0.5;//飞机位置
	position_y = High * 0.9;//飞机位置


	bullet_x = position_x;//子弹位置
	bullet_y = -25;//子弹位置

	enemy_x = Width * 0.5;//敌机位置
	enemy_y = 10;//敌机位置


	BeginBatchDraw();
}

//显示界面
void show()
{
	while (gameStatus == 3)
		pauseMenu();//游戏暂停后菜单界面,一般按ESC键后启动该界面

	putimage(0, 0, &img_bk);//显示背景
	
	//判断飞机是否挂了
	if (isExpolde <= 4)
	{
		putimage(position_x - 50, position_y - 70, &img_planeNormal2, SRCAND);//掩码图
		putimage(position_x - 50, position_y - 70, &img_planeNormal1, SRCPAINT);//显示正常飞机
		

		for (list<Bullet>::iterator it = bullt.begin(); it != bullt.end(); it++)
		{
			putimage(it->bx - 7, it->by, &img_bullet2, SRCAND);//掩码图
			putimage(it->bx - 7, it->by, &img_bullet1, SRCPAINT);//显示子弹
		}
		
		

		putimage(enemy_x, enemy_y, &img_enemyPlane2, SRCAND);
		putimage(enemy_x, enemy_y, &img_enemyPlane1, SRCPAINT);//显示敌机
		


		if (guanka >= 2)
		{
			if (score == 10)
				temp=1;
			if (temp == 1)
			{
				putimage(enemy2_x, enemy2_y, &img_enemyPlane4, SRCAND);
				putimage(enemy2_x, enemy2_y, &img_enemyPlane3, SRCPAINT);//显示敌机BOSS
				
			}

			putimage(enemy3_x, enemy3_y, &img_enemyPlane2, SRCAND);
			putimage(enemy3_x, enemy3_y, &img_enemyPlane1, SRCPAINT);
			

		}
	}
	else
	{
		putimage(position_x-50, position_y-60, &img_planeExplode1, SRCAND);//显示爆炸
		putimage(position_x - 50, position_y - 60, &img_planeExplode2, SRCPAINT);

	}

	settextcolor(RED);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(Width * 0.8, High * 0.95, _T("得分:"));
	TCHAR s[5];
	_stprintf_s(s,_T( "%d"), score);
	outtextxy(Width * 0.9, High * 0.95,s);

	settextcolor(RED);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(Width * 0.2, High * 0.95, _T("生命:"));
	TCHAR s2[5];
	_stprintf_s(s2, _T("%d"), shengming);
	outtextxy(Width * 0.3, High * 0.95, s2);

	settextcolor(RED);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(Width * 0.45, High * 0.95, _T("关卡:"));
	TCHAR s3[5];
	_stprintf_s(s3,_T("%d"), guanka);
	outtextxy(Width * 0.6, High * 0.95, s3);
	

	FlushBatchDraw();
	Sleep(2);
}




#if 1

//子弹和敌机自由移动
void updateWithoutlnput()
{
	if (isExpolde <= 4)
	{
		//子弹的移动
		for (list<Bullet>::iterator it = bullt.begin(); it != bullt.end(); )
		{
			if (it->by > -25)
				it->by = it->by - 2;

			if (it->by <= -25)
			{
				it = bullt.erase(it);
			}
			else
				++it;
		}

		//第一个飞机的移动
		if (enemy_y < High - 25)
		{
			enemy_y = enemy_y + 0.5;
		}
		else
			enemy_y = 5;

		//boss机的移动
		if (temp == 1)
		{
			if (enemy2_y < High - 25)
			{
				enemy2_y = enemy2_y + 0.75;
			}
			else
			{
				enemy2_y = 5;
				enemy2_x = rand() % Width;
			}
		}

		//第二个飞机的移动
		if (guanka >= 2)
		{
			if (enemy3_y < High - 25)
			{
				enemy3_y = enemy3_y + 0.45;
			}
			else
			{
				enemy3_y = 5;
				enemy3_x = rand() % Width + 40;
			}
		}

		//循环检测子弹是否击中敌机
		for (list<Bullet>::iterator it = bullt.begin(); it != bullt.end(); )
		{

			bool bue = false;
			if (fabs(it->bx - enemy_x) + fabs(it->by - enemy_y) < 80)//子弹击中敌机
			{
				enemy_x = rand() % Width;
				enemy_y = -40;



				bue = true;

				score++;
			}

			if (fabs(it->bx - enemy2_x) + fabs(it->by - enemy2_y) < 80)//子弹击中敌机
			{
				enemy2_x = rand() % Width;
				enemy2_y = -40;

				bue = true;
				temp++;
				score++;
			}

			if (fabs(it->bx - enemy3_x) + fabs(it->by - enemy3_y) < 80)//子弹击中敌机
			{
				enemy3_x = rand() % Width;
				enemy3_y = -40;

				bue = true;
				score++;
			}

			if (!bue)
				it++;
			else
				it = bullt.erase(it);
		}

		//更改关卡
		if (score >= 10)
		{
			guanka = 2;
		}
		if (score >= 25)
		{
			guanka = 3;
		}

		//判断敌机是否撞到我们
		if (fabs(position_x - enemy_x) + fabs(position_y - enemy_y) < 150 ||
			fabs(position_x - enemy2_x) + fabs(position_y - enemy2_y) < 150 ||
			fabs(position_x - enemy3_x) + fabs(position_y - enemy3_y) < 150) //敌机击中我们
		{
			isExpolde++;
			if (isExpolde == 1)
			{
				startup2();
				shengming = 2;
			}
			if (isExpolde == 3)
			{
				startup2();
				shengming = 1;
			}

		}

	}

}

//飞机跟随鼠标移动
void updateWithlnput()
{
	
	if (isExpolde <= 4)
	{
		MOUSEMSG m;//定义鼠标消息
		while (MouseHit())//这个函数用于检测当前是否有鼠标消息
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_MOUSEMOVE)
			{
				//飞机的位置等于鼠标所在位置
				position_x = m.x;
				position_y = m.y;


			}
			else if(m.uMsg==WM_LBUTTONDOWN)
			{
				//按下鼠标左键，发
				bullet_x = position_x+18;
				bullet_y = position_y - 108;

				Bullet a;
				a.bx = bullet_x;
				a.by = bullet_y;


				bullt.push_back(a);
	
			}
		}
	}

	char input;
	if (_kbhit())//判断是否有输入
	{
		input = _getch();//根据用户的不同输入来移动，不必输入回车
		if (input == 27)//ESC键的ACSII码为27
		{
			gameStatus = 3;
		}
	}
}

#endif


//结束游戏处理
void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}



int main()
{
	
	

	startup();//数据初始化
	while (1)//游戏循环执行
	{
		show();//显示界面
		
		updateWithoutlnput();//与用户输入无关的更新
		updateWithlnput();//与用户输入有关的更新
	}

	gameover();

	//getchar();

	return 0;
}
