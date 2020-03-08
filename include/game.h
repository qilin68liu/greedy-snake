#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "print.h"

#define MSG_EXIT "Press q or Q to exit"
#define MSG_PLAY "Press p or P to play"

typedef struct _game_t {
	gint height;
	gint interval;
	gint width;
	gint starty;
	gint startx;
	gchar *body_ch;
	gchar *food_ch;
	gboolean pause;
	snake_t *snake;
	food_t *food;
	WINDOW *win;
} game_t;

void screen_init();
void screen_endup();

void game_init(game_t *g);
void game_endup(game_t *g);
void game_start(game_t *g);

#endif
