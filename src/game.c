#include "game.h"

static food_t *rand_food(game_t *g);
static gboolean snake_is_alive(game_t *g);
static gboolean snake_meet_food(snake_t *s, food_t *f);

void screen_init()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
}

void screen_endup()
{
	endwin();
}

void game_init(game_t *g)
{
	g->height = 20;
	g->interval = 1000000;
	g->width = 21;
	g->starty = (LINES - g->height - 2) / 2;
	g->startx = (COLS - g->width * 2 - 3) / 2;
	g->body_ch = "*";
	g->food_ch = "*";
	g->pause = TRUE;
	g->snake = snake_new(g->height / 2, g->width / 2 + 1);
	g->food = rand_food(g);
	g->win = newwin(g->height + 2, g->width * 2 + 1, g->starty, g->startx);
	wborder(g->win, '|','|','-','-','+','+','+','+');
	wrefresh(g->win);

	print_param_t param = { g->win, g->starty, g->startx, g->body_ch };
	print_snake(g->snake, &param);

	param.msg = g->food_ch;
	print_food(g->food, &param);

	game_info_t game_info = { g->snake->length, g->interval };
	print_game_info(&game_info, &param);
}

void game_endup(game_t *g)
{
	delwin(g->win);
	snake_eat(g->snake, g->food);
	snake_free(g->snake);
}

void game_start(game_t *g)
{
	game_info_t game_info = { g->snake->length, g->interval };
	print_param_t param = { g->win, g->starty, g->startx, g->body_ch };

	gint key;
	while(1)
	{
		if((key = getch()) != ERR)
		{
			switch(key)
			{
				case 'w':
				case 'W':
				case KEY_UP:
					if(g->snake->direct != DOWN)
						g->snake->direct = UP;
					break;
				case 's':
				case 'S':
				case KEY_DOWN:
					if(g->snake->direct != UP)
						g->snake->direct = DOWN;
					break;
				case 'a':
				case 'A':
				case KEY_LEFT:
					if(g->snake->direct != RIGHT)
						g->snake->direct = LEFT;
					break;
				case 'd':
				case 'D':
				case KEY_RIGHT:
					if(g->snake->direct != LEFT)
						g->snake->direct = RIGHT;
					break;
				case ' ':
					if(g->pause == FALSE)
						g->pause = TRUE;
					else
						g->pause = FALSE;
					break;
				case 'q':
				case 'Q':
					return;
				default:
					break;
			}
		}

		if(g->pause) {
			g_usleep(50000);
			continue;
		}

		move_info_t info;
		snake_move(g->snake, &info);

		param.msg = g->body_ch;
		print_move(&info, &param);

		// Check whether snake is alive;
		if(!snake_is_alive(g))
			return;

		//check whether snake meet the food
		if(snake_meet_food(g->snake, g->food))
		{
			snake_eat(g->snake, g->food);
			g->food = rand_food(g);

			gint tmp_int = 1000000 - (g->snake->length - 3) * 20000;
			g->interval = tmp_int >= 200000 ? tmp_int : 200000;

			param.msg = g->food_ch;
			print_food(g->food, &param);

			game_info.length = g->snake->length;
			game_info.interval = g->interval;
			print_game_info(&game_info, &param);
		}

		g_usleep(g->interval);
	}
}

static food_t *rand_food(game_t *g)
{
	pos_t pos;
	GRand *rand = g_rand_new();

	do {
		pos.y = g_rand_int_range(rand, 1, g->height + 1);
		pos.x = g_rand_int_range(rand, 1, g->width + 1);
	} while (g_queue_find_custom(g->snake->body, &pos, (GCompareFunc)pos_cmp));

	g_rand_free(rand);
	return food_new(pos.y, pos.x);
}

static gboolean snake_meet_food(snake_t *s, food_t *f)
{
	pos_t *h = g_queue_peek_head(s->body);
	return !pos_cmp(h, (pos_t *)f);
}

static gboolean snake_is_alive(game_t *g)
{
	pos_t *h = g_queue_pop_head(g->snake->body);
	gboolean ret = TRUE;

	if(h->y <= 0 || h->y > g->height)
		ret = FALSE;
	if(h->x <= 0 || h->x > g->width)
		ret = FALSE;

	// Check whether snake bites itself
	if(g_queue_find_custom(g->snake->body, h, (GCompareFunc)pos_cmp))
		ret = FALSE;

	g_queue_push_head(g->snake->body, h);
	return ret;
}
