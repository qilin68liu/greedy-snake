#ifndef PRINT_H
#define PRINT_H

#include "common.h"
#include "snake.h"

#define X(x) ((x) * 2 - 1)
#define Y(y) (y)

typedef struct _game_t game_t;

void print_pos(pos_t *n, print_param_t *p);
void print_snake(snake_t *s, print_param_t *p);
void print_move(move_info_t *f, print_param_t *p);
void print_food(food_t *f, print_param_t *p);
void print_game_info(game_t *g, print_param_t *p);

#endif
