#include "common.h"

pos_t *pos_new(gint y, gint x)
{
	pos_t *n = g_new(pos_t, 1);
	n->y = y;
	n->x = x;
	return n;
}

gint pos_cmp(pos_t *p1, pos_t *p2)
{
	if(p1->y == p2->y && p1->x == p2->x)
		return 0;

	return -1;
}
