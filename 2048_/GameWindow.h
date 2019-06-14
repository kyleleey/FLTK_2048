#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include "Button.h"

struct Postion//�����������������ʱʹ�õĽṹ
{
	int X;
	int Y;
};

class Window : public Fl_Window//�̳���Fl_Window��
{
public:
	Window(int width, int height, const char* name);//���캯��

	void left_move();//���ƺ���
	void up_move();//���ƺ���
	void down_move();//���ƺ���
	void right_move();//���ƺ���
	void add_number();//�ڿհ״����������
	void reset();//���¿�ʼ
	void save();//��������ڴ�����ڻ���Ĵ洢������������ʵ����Ϸ�洢����
	void withdraw();//���ء������塱����
	//���º���Ϊ���ػ���ĺ����������Ϻ���ʹ�ùؼ���override��ȷ������
	void draw() override;//���ƺ�����
	int handle(int event) override;//��׽���ͼ��̶����ĺ���

protected:
	//���Զ����Button����ΪGameWindow������ݳ�Ա
	Button* reset_btn;//���¿�ʼ����
	Button* withdraw_btn;//�����塱����
	Button* clear_btn;//��߷����㰴��
	Button* quit_btn;//�˳���Ϸ����
	Button* set_score_btn;//�����ڵ÷�����Ϊ��߷�
	Button* save_btn;//��Ϸ����
	Button* reload_btn;//��������֮ǰ���̵���Ϸ
	int old_data[10][4][4];//���ڴ洢��ȥʮ�������̣�Ϊ��ʵ�ֻ��幦��
	int index = 0; //����old_data���±�
	int data[4][4];//�洢4*4���̵�����
	int max_score = 0;//��߷�
	int score = 0;//��ǰ�÷�
	int old_score[10];//ÿһ�β���ǰʮ�εĵ÷�
};
