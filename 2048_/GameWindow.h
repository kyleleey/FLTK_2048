#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include "Button.h"

struct Postion//用于随机生成新数字时使用的结构
{
	int X;
	int Y;
};

class Window : public Fl_Window//继承自Fl_Window类
{
public:
	Window(int width, int height, const char* name);//构造函数

	void left_move();//左移函数
	void up_move();//上移函数
	void down_move();//下移函数
	void right_move();//右移函数
	void add_number();//在空白处添加新数字
	void reset();//重新开始
	void save();//这个是用于储存便于悔棋的存储函数，并不是实现游戏存储功能
	void withdraw();//撤回、“悔棋”函数
	//以下函数为重载基类的函数，查资料后发现使用关键字override来确保重载
	void draw() override;//绘制函数，
	int handle(int event) override;//捕捉鼠标和键盘动作的函数

protected:
	//将自定义的Button类作为GameWindow类的数据成员
	Button* reset_btn;//重新开始按键
	Button* withdraw_btn;//“悔棋”按键
	Button* clear_btn;//最高分清零按键
	Button* quit_btn;//退出游戏按键
	Button* set_score_btn;//将当期得分设置为最高分
	Button* save_btn;//游戏存盘
	Button* reload_btn;//重新载入之前存盘的游戏
	int old_data[10][4][4];//用于存储过去十步的棋盘，为了实现悔棋功能
	int index = 0; //用于old_data的下标
	int data[4][4];//存储4*4棋盘的数字
	int max_score = 0;//最高分
	int score = 0;//当前得分
	int old_score[10];//每一次操作前十次的得分
};
