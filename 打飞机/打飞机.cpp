#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#include<graphics.h>
#include<easyx.h>

//引用Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

#define High 579 // 游戏画面尺寸
#define Width 1024



/*
	1.初始画游戏界面 
		void startMenu()
	2.显示画面
*/

IMAGE img_bk;//背景图片


void startMenu()
{
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.3, High * 0.2,"1 新游戏");
	
}

int main()
{
    
}
