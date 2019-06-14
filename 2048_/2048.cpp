#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "GameWindow.h"

#pragma comment(lib,"fltkd.lib")

int  main()
{
	Window  *window;
	Fl_Box  *box;
	window = new  Window(550, 700, "2048");
	window->end();
	window->show();
	return  Fl::run();
}
