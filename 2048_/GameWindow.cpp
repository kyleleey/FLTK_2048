#include "GameWindow.h"
#include <vector>
#include <FL/fl_ask.H>

bool flag = false;//判断是否有任何改变，true代表有，false代表无
bool checkifequal(int previousmap[4][4], int data_[4][4]);
bool canmove(int data_[4][4]);

Window::Window(int width, int height, const char * name)
	: Fl_Window(width, height, name)
{
	reset_btn = new Button(20, 20, 120, 40, "Reset(r)");
	clear_btn = new Button(150, 20, 120, 40, "Clear Max Score(c)");
	withdraw_btn = new Button(280, 20, 120, 40, "Regret(z)");
	quit_btn = new Button(410, 20, 120, 40, "Quit(q)");
	set_score_btn = new Button(280, 70, 250, 40, "Make current score to be Max score(m)");
	save_btn = new Button(280, 120, 120, 40,  "Save game(s)");
	reload_btn = new Button(410, 120, 120, 40, "Reload game(d)");

	for (int k = 0; k < 10; ++k)
	{
		old_score[k] = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				old_data[k][i][j] = 0;
				data[i][j] = 0;
			}
		}
	}
	add_number();
	FILE* fp = fopen("data.txt", "rt");
	if (fp == NULL)
	{
		fp = fopen("data.txt", "wt+");
		score = 0;
		fprintf(fp, "score:%d", max_score);
	}
	else
	{
		fscanf(fp, "score:%d", &max_score);
	}
	fflush(fp);
	fclose(fp);
}

int Window::handle(int type)
{
	int event_key;
	event_key = Fl::event_key();
	switch (type)
	{
	case  FL_PUSH:
		if (reset_btn->is_clicked())
		{
			reset();
		}
		if (clear_btn->is_clicked())
		{
			max_score = 0;
			FILE* fp = fopen("data.txt", "wt+");
			fprintf(fp, "score:%d", max_score);
			fflush(fp);
			fclose(fp);
			reset();
			redraw();
		}
		if (withdraw_btn->is_clicked())
		{
			withdraw();
			redraw();
		}
		if (quit_btn->is_clicked())
		{
			fl_alert("ByeBye");
			exit(0);
		}
		if (set_score_btn->is_clicked())
		{
			max_score = score;
			FILE* fp = fopen("data.txt", "wt+");
			fprintf(fp, "score:%d", max_score);
			fflush(fp);
			fclose(fp);
			redraw();
		}
		if (save_btn->is_clicked())
		{
			FILE* fp1 = fopen("game_save.txt", "wt+");
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					fprintf(fp1, "%d ", data[i][j]);
				}
			}
			fprintf(fp1, "%d ", score);
			fflush(fp1);
			fclose(fp1);
			redraw();
		}
		if (reload_btn->is_clicked())
		{
			FILE* fp1 = fopen("game_save.txt", "rt+");
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					fscanf(fp1, "%d", &data[i][j]);
				}
			}
			fscanf(fp1, "%d", &score);
			fflush(fp1);
			fclose(fp1);
			redraw();
		}
		break;
	case FL_KEYDOWN:
		if (event_key == 'r')
		{
			reset();
		}
		if (event_key == 'c')
		{
			max_score = 0;
			FILE* fp = fopen("data.txt", "wt+");
			fprintf(fp, "score:%d", score);
			fflush(fp);
			fclose(fp);
			redraw();
		}
		if (event_key == 'z')
		{
			withdraw();
			redraw();
		}
		if (event_key == 'q')
		{
			if (score >= max_score)
			{
				max_score = score;
			}
			FILE* fp = fopen("data.txt", "wt+");
			fprintf(fp, "score:%d", max_score);
			fflush(fp);
			fclose(fp);
			fl_alert("ByeBye");
			exit(0);
		}
		if (event_key == 'm')
		{
			max_score = score;
			FILE* fp = fopen("data.txt", "wt+");
			fprintf(fp, "score:%d", max_score);
			fflush(fp);
			fclose(fp);
			redraw();
		}
		if (event_key == 's')
		{
			FILE* fp1 = fopen("game_save.txt", "wt+");
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					fprintf(fp1, "%d ", data[i][j]);
				}
			}
			fprintf(fp1, "%d ", score);
			fflush(fp1);
			fclose(fp1);
			redraw();
		}
		if (event_key == 'd')
		{
			FILE* fp1 = fopen("game_save.txt", "rt+");
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					fscanf(fp1, "%d", &data[i][j]);
				}
			}
			fscanf(fp1, "%d", &score);
			fflush(fp1);
			fclose(fp1);
			redraw();
		}
		if (event_key == FL_Up)
		{
			save();
			up_move();
			int zerocount=0;
			if (flag == false) { 
				add_number(); 
				redraw(); 
			}
			flag = true;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (data[i][j] == 0) { zerocount += 1; }
				}
			}
			if(flag == true && zerocount == 0) {
				if (canmove(data)==false) {
					if (score >= max_score)
					{
						max_score = score;
					}
					FILE* fp = fopen("data.txt", "wt+");
					fprintf(fp, "score:%d", max_score);
					fflush(fp);
					fclose(fp);
					fl_alert("Game Over! Your score is %d", score);
					reset();
				}
			}
		}
		if (event_key == FL_Down)
		{
			save();
			down_move();
			int zerocount = 0;
			if (flag == false) {
				add_number();
				redraw();
			}
			flag = true;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (data[i][j] == 0) { zerocount += 1; }
				}
			}
			if (flag == true && zerocount == 0) {
				if (canmove(data) == false) {
					if (score >= max_score)
					{
						max_score = score;
					}
					FILE* fp = fopen("data.txt", "wt+");
					fprintf(fp, "score:%d", max_score);
					fflush(fp);
					fclose(fp);
					fl_alert("Game Over! Your score is %d", score);
					reset();
				}
			}
		}
		if (event_key == FL_Left)
		{
			save();
			left_move();
			int zerocount = 0;
			if (flag == false) {
				add_number();
				redraw();
			}
			flag = true;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (data[i][j] == 0) { zerocount += 1; }
				}
			}
			if (flag == true && zerocount == 0) {
				if (canmove(data) == false) {
					if (score >= max_score)
					{
						max_score = score;
					}
					FILE* fp = fopen("data.txt", "wt+");
					fprintf(fp, "score:%d", max_score);
					fflush(fp);
					fclose(fp);
					fl_alert("Game Over! Your score is %d", score);
					reset();
				}
			}
		}
		if (event_key == FL_Right)
		{
			save();
			right_move();
			int zerocount = 0;
			if (flag == false) {
				add_number();
				redraw();
			}
			flag = true;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (data[i][j] == 0) { zerocount += 1; }
				}
			}
			if (flag == true && zerocount == 0) {
				if (canmove(data) == false) {
					if (score >= max_score)
					{
						max_score = score;
					}
					FILE* fp = fopen("data.txt", "wt+");
					fprintf(fp, "score:%d", max_score);
					fflush(fp);
					fclose(fp);
					fl_alert("Game Over! Your score is %d", score);
					reset();
				}
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

void Window::draw()
{
	char buffer[100];
	//draw background
	fl_draw_box(FL_FLAT_BOX, 0, 0, 600, 700, fl_rgb_color(172, 155, 137));

	reset_btn->draw();
	clear_btn->draw();
	withdraw_btn->draw();
	quit_btn->draw();
	set_score_btn->draw();
	save_btn->draw();
	reload_btn->draw();

	fl_font(FL_TIMES, 30);
	fl_color(fl_rgb_color(96, 85, 67));

	sprintf_s(buffer, "Current Score:%d", score);

	fl_draw(buffer, 20, 120, 600, 50, FL_ALIGN_LEFT);

	sprintf_s(buffer, "Max Score:%d", max_score);
	fl_draw(buffer, 20, 70, 600, 50, FL_ALIGN_LEFT);

	fl_font(FL_TIMES | FL_BOLD, 45);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			_itoa_s(data[i][j], buffer, 10);
			if (data[i][j] == 0)
			{
				fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(195, 179, 164));
			}
			else
			{
				if(data[i][j]==2 || data[i][j] == 128 || data[i][j] == 8192){ fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(215, 215, 215)); }
				else if (data[i][j] == 4 || data[i][j] == 256 || data[i][j] == 16384) { fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(217, 218, 165)); }
				else if (data[i][j] == 8 || data[i][j] == 512 || data[i][j] == 32768) { fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(248, 197, 135)); }
				else if (data[i][j] == 16 || data[i][j] == 1024 || data[i][j] == 65536) { fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(254, 188, 129)); }
				else if (data[i][j] == 32 || data[i][j] == 2048 || data[i][j] == 131072) { fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(254, 121, 1)); }
				else if (data[i][j] == 64 || data[i][j] == 4096) { fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(252, 47, 3)); }
				else { fl_draw_box(FL_FLAT_BOX, 20 + j * 130, 180 + i * 130, 120, 120, fl_rgb_color(255, 255, 255)); }
				fl_color(fl_rgb_color(96, 85, 67));
				fl_draw(buffer, 20 + j * 130, 180 + i * 130, 120, 120, FL_ALIGN_CENTER);
			}

		}
	}
}

void Window::left_move()
{
	int previous_map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			previous_map[i][j] = data[i][j];
		}
	}
	//其他方向移动同理左移
	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> new_line;
		//找出非0的数字
		for (int j = 0; j < 4; ++j)
		{
			if (data[i][j] != 0)
			{
				new_line.push_back(data[i][j]);
				data[i][j] = 0;
			}
		}
		//合并
		for (int j = 1; j < new_line.size(); ++j)
		{
			std::vector<int>::iterator it = new_line.begin() + j;
			if (new_line[j - 1] == new_line[j])
			{
				new_line[j - 1] = 2 * new_line[j - 1];
				score += 2 * new_line[j];
				new_line.erase(it);
			}
		}
		//移动
		for (int j = 0; j < new_line.size(); ++j)
		{
			data[i][j] = new_line[j];
		}
	}
	flag = checkifequal(previous_map, data);
}

void Window::up_move()
{
	int previous_map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			previous_map[i][j] = data[i][j];
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> new_line;
		for (int j = 0; j < 4; ++j)
		{
			if (data[j][i] != 0)
			{
				new_line.push_back(data[j][i]);
				data[j][i] = 0;
			}
		}
		for (int j = 1; j < new_line.size(); ++j)
		{
			std::vector<int>::iterator it = new_line.begin() + j;
			if (new_line[j - 1] == new_line[j])
			{
				new_line[j - 1] = 2 * new_line[j - 1];
				score += 2 * new_line[j];
				new_line.erase(it);
			}
		}
		for (int j = 0; j < new_line.size(); ++j)
		{
			data[j][i] = new_line[j];
		}
	}
	flag = checkifequal(previous_map, data);
}

void Window::down_move()
{
	int previous_map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			previous_map[i][j] = data[i][j];
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> new_line;
		for (int j = 0; j < 4; ++j)
		{
			if (data[j][i] != 0)
			{
				new_line.push_back(data[j][i]);
				data[j][i] = 0;
			}
		}
		for (int j = 1; j < new_line.size(); ++j)
		{
			std::vector<int>::iterator it = new_line.begin() + j;
			if (new_line[j - 1] == new_line[j])
			{
				new_line[j - 1] = 2 * new_line[j - 1];
				score += 2 * new_line[j];
				new_line.erase(it);
			}
		}
		for (int j = 0; j < new_line.size(); ++j)
		{
			data[4 - new_line.size() + j][i] = new_line[j];
		}
	}
	flag = checkifequal(previous_map, data);
}

void Window::right_move()
{
	int previous_map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			previous_map[i][j] = data[i][j];
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> new_line;
		for (int j = 0; j < 4; ++j)
		{
			if (data[i][j] != 0)
			{
				new_line.push_back(data[i][j]);
				data[i][j] = 0;
			}
		}
		for (int j = 1; j < new_line.size(); ++j)
		{
			std::vector<int>::iterator it = new_line.begin() + j;
			if (new_line[j - 1] == new_line[j])
			{
				new_line[j - 1] = 2 * new_line[j - 1];
				score += 2 * new_line[j];
				new_line.erase(it);
			}
		}
		for (int j = 0; j < new_line.size(); ++j)
		{
			data[i][4 - new_line.size() + j] = new_line[j];
		}
	}
	flag = checkifequal(previous_map, data);
}

void Window::add_number()
{
	std::vector<Postion> positons;
	Postion p;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (data[i][j] == 0)
			{
				p.X = i;
				p.Y = j;
				positons.push_back(p);
			}
		}
	}
	if (positons.size() > 0)
	{
		int index = rand() % positons.size();
		Postion target = positons[index];
		if (rand() % 3 == 0)
			data[target.X][target.Y] = 4;
		else
			data[target.X][target.Y] = 2;

		redraw();
	}
	else
	{
		if (score >= max_score)
		{
			max_score = score;
		}
		FILE* fp = fopen("data.txt", "wt+");
		fprintf(fp, "score:%d", max_score);
		fflush(fp);
		fclose(fp);
		fl_alert("Game Over! Your score is %d",score);
		reset();

	}
}

void Window::reset()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			data[i][j] = 0;
		}
	}
	score = 0;
	add_number();
}

void Window::save()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			old_data[index][i][j] = data[i][j];
		}
	}
	old_score[index] = score;
	index = (index + 1) % 10;
}


void Window::withdraw()
{
	--index;

	if (index < 0)
		index = 9;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			data[i][j] = old_data[index][i][j];
		}
	}
	score = old_score[index];
}

bool checkifequal(int previousmap[4][4], int data_[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (previousmap[i][j] != data_[i][j]) { return false; }
		}
	}
	return true;
}

bool canmove(int data_[4][4]) {
	bool ret = false;
	//先对每一行进行判断
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (data_[i][j] == data_[i][j + 1]) { ret = true; return ret; }//判断一行内有没有相等
		}
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (data_[i][j] == data_[i + 1][j]) { ret = true; return ret; }//判断每一列内有没有相等
		}
	}
	return ret;
}