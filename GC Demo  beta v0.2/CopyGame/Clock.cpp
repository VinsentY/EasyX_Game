#include "Clock.h"

void Clock::move() {
	move_x_min = x + (r - 10) * sin(angle);
	move_y_min = y - (r - 10) * cos(angle);
	move_x_hour = x + (r - 20) * sin(angle / 12);
	move_y_hour = y - (r - 20) * cos(angle / 12);

	setfillcolor(BLACK);
	solidcircle(x, y, r);
	setfillcolor(WHITE);
	solidcircle(x, y, r - 5);
	setcolor(BLACK);

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
	line(x, y, move_x_min, move_y_min);
	line(move_x_min, move_y_min, move_x_min - 10 * cos(angle - 45), move_y_min - 10 * sin(angle - 45));
	line(move_x_min, move_y_min, move_x_min - 10 * sin(angle - 45), move_y_min + 10 * cos(angle - 45));


	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	line(x, y, move_x_hour, move_y_hour);
	line(move_x_hour, move_y_hour, move_x_hour - 10 * cos(angle / 12 - 45), move_y_hour - 10 * sin(angle / 12 - 45));
	line(move_x_hour, move_y_hour, move_x_hour - 10 * sin(angle / 12 - 45), move_y_hour + 10 * cos(angle / 12 - 45));

	angle = angle + PI / 180;
	setfillcolor(BLACK);
}
