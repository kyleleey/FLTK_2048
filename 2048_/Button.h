#pragma once
class Button
{
public:
	Button(int x,int y,int width,int height,const char* content);//���캯��
	bool is_clicked();//����Ƿ��ڰ����ķ�Χ�ڱ����
	void draw();//��fl_draw_box����Ϊ�������ư���
private:
	int x, y, width, height;//ÿһ�����������λ�á�����
	char text[100];//�������������ݣ���char����洢
};

