#ifndef SNAKE_H
#define SNAKE_H

#include "common.h"

typedef struct _snake_t {
	gint length;
	direct_t direct;
	GQueue *body;
} snake_t;

typedef pos_t food_t;

snake_t *snake_new(gint y, gint x);
void snake_free(snake_t *s);
void snake_move(snake_t *s, move_info_t *i);
void snake_eat(snake_t *s, food_t *f);

food_t *food_new(gint y, gint x);

#endif
