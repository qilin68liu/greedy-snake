#include "snake.h"

#define DEFAULT_LEN 3

snake_t *snake_new(gint y, gint x)
{
	snake_t *s = g_new(snake_t, 1);

	s->length = DEFAULT_LEN;
	s->direct = UP;
	s->body = g_queue_new();

	for(gint i = 0; i < DEFAULT_LEN; i++) {
		g_queue_push_tail(s->body, (gpointer)pos_new(y++, x));
	}

	return s;
}

void snake_free(snake_t *s)
{
	g_queue_free_full(s->body, g_free);
	g_free(s);
}

void snake_move(snake_t *s, move_info_t *i)
{
	pos_t *n = g_queue_pop_tail(s->body);
	pos_t *h = g_queue_peek_head(s->body);

	i->del = *n;
	switch(s->direct) {
		case UP:
			n->y = h->y - 1;
			n->x = h->x;
			break;
		case DOWN:
			n->y = h->y + 1;
			n->x = h->x;
			break;
		case LEFT:
			n->y = h->y;
			n->x = h->x - 1;
			break;
		case RIGHT:
			n->y = h->y;
			n->x = h->x + 1;
			break;
	}
	i->add = *n;
	g_queue_push_head(s->body, n);
}

void snake_eat(snake_t *s, food_t *f)
{
	pos_t *t = s->body->tail->data;
	pos_t *pt = s->body->tail->prev->data;

	// vertical
	if(t->x == pt->x) {
		f->x = t->x;
		f->y = t->y > pt->y ? t->y + 1 : t->y - 1;
	}

	// horizontal
	if(t->y == pt->y) {
		f->y = t->y;
		f->x = t->x > pt->x ? t->x + 1 : t->x - 1;
	}

	g_queue_push_tail(s->body, (pos_t *)f);
	s->length++;
}

food_t *food_new(gint y, gint x)
{
	food_t *f = g_new(food_t, 1);
	f->y = y;
	f->x = x;

	return f;
}
