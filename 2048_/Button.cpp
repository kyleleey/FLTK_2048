#include "Button.h"
#include <string.h>
#include <FL/fl_draw.H>

Button::Button(int x, int y, int width, int height, const char * content)
	:x(x),y(y),width(width),height(height)
{
	strcpy_s(text, content);
}

bool Button::is_clicked()
{
	int mouse_x = Fl::event_x();
	int mouse_y = Fl::event_y();
	if (mouse_x > x && mouse_x < x + width &&
		mouse_y > y && mouse_y < y + height)
	{
		return true;
	}
	return false;
}

void Button::draw()
{
	fl_draw_box(FL_FLAT_BOX, x, y, width, height, fl_rgb_color(195, 179, 164));
	fl_font(FL_TIMES, 15);
	fl_color(fl_rgb_color(96, 85, 67));
	fl_draw(text, x, y, width, height, FL_ALIGN_CENTER);
}
