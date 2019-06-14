#pragma once
class Button
{
public:
	Button(int x,int y,int width,int height,const char* content);//构造函数
	bool is_clicked();//检测是否在按键的范围内被点击
	void draw();//以fl_draw_box函数为基础绘制按键
private:
	int x, y, width, height;//每一个按键对象的位置、长宽
	char text[100];//按键的文字内容，用char数组存储
};

