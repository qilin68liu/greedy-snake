#include "print.h"
#include "game.h"

void print_pos(pos_t *n, print_param_t *p)
{
	mvwprintw(p->win, Y(n->y), X(n->x), p->msg);
	//wrefresh(p->win);
}

void print_snake(snake_t *s, print_param_t *p)
{
	g_queue_foreach(s->body, (GFunc)print_pos, p);
	wrefresh(p->win);
}

void print_move(move_info_t *i, print_param_t *p)
{
	mvwprintw(p->win, Y(i->del.y), X(i->del.x), " ");
	mvwprintw(p->win, Y(i->add.y), X(i->add.x), p->msg);
	wrefresh(p->win);
}

void print_food(food_t *f, print_param_t *p)
{
	mvwprintw(p->win, Y(f->y), X(f->x), p->msg);
	wrefresh(p->win);
}

void print_game_info(game_info_t *i, print_param_t *p)
{
	move(p->starty - 1, p->startx);
	printw("Length: %d, Interval: %d", i->length, i->interval);
	refresh();
}
