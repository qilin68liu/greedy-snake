#ifndef COMMON_H
#define COMMON_H

#include <glib.h>
#include <ncurses.h>

typedef struct _pos_t {
	gint y;
	gint x;
} pos_t;

typedef enum _direct_t {
	UP,
	DOWN,
	LEFT,
	RIGHT
} direct_t;

typedef struct _print_param {
	WINDOW *win;
	gchar ch;
} print_param_t;

typedef struct _move_info {
	pos_t del;
	pos_t add;
} move_info_t;

pos_t *pos_new(gint y, gint x);
gint pos_cmp(pos_t *p1, pos_t *p2);

#endif
