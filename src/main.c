#include <game.h>

int main(void)
{
	screen_init();

	gint key;
	game_t game;

	do
	{

		mvaddstr(LINES/2, (COLS-strlen(MSG_EXIT))/2, MSG_EXIT);
		mvaddstr(LINES/2 - 1, (COLS-strlen(MSG_PLAY))/2, MSG_PLAY);

		key = getch();
		if(key == 'P' || key == 'p') {
			game_init(&game);
			game_start(&game);
			game_endup(&game);
			clear();
		}
	} while(key != 'Q' && key != 'q');

	screen_endup();

	return 0;
}
