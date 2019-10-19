#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#include<graphics.h>
#include<easyx.h>

//引用Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

#define High 600 // 游戏画面尺寸
#define Width 512

/*
	1.初始画游戏界面 
		void startMenu()
	2.显示画面
	 void show();
	3.
*/

IMAGE img_bk;//背景图片
int gameStatus = 0;//游戏状态,0为初始菜单界面,1为正常游戏,2为结束游戏状态,3为游戏暂停
void startMenu();//初始菜单界面
void pauseMenu();//游戏暂停后菜单界面，一般按ESC键后启动该界面
void startup();//数据初始化
void show();//显示界面

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
			//exit(0);
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
	initgraph(Width, High);
	//获取窗口句柄
	HWND hwnd = GetHWnd();
	//设置窗口标题文字
	SetWindowText(hwnd, _T("数据结构小游戏开发-飞机打针"));

	loadimage(&img_bk, _T("./res/images/background.jpg"));




	BeginBatchDraw();

	while (gameStatus == 0)
		startMenu();//初始菜单界面
			
}

//显示界面
void show()
{
	while (gameStatus == 3)
		pauseMenu();//游戏暂停后菜单界面,一般按ESC键后启动该界面

	putimage(0, 0, &img_bk);//显示背景


}

int main()
{
	startup();//数据初始化
	while (1)//游戏循环执行
	{
		show();//显示界面
	}

	

	return 0;
}
