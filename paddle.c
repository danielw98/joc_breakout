#include<curses.h>
#include"includes.h"
void Paddle_Draw(Paddle *paddle)
{
	int i;
	move(MAX_Y - 1, paddle->xPos);
    attron(A_BOLD | COLOR_PAIR(1));
	addch('<');
	for (i = 1 ; i < paddle->length - 1; i++)
		addch('#');
	addch('>');
    attroff(A_BOLD | COLOR_PAIR(1));
	refresh();
}

void Paddle_Delete(Paddle *paddle)
{
    int i;
    move(getmaxy(stdscr)-1, paddle->xPos);
    for(i = 0; i < paddle->length; i++)
        addch(' ');
    refresh();
}

void Paddle_Reset(Paddle *paddle)
{
    paddle->length = PADDLE_LENGTH;
    paddle->xPos   = (MAX_X-PADDLE_LENGTH)/2;
}
void Paddle_Move(Paddle *paddle, xDirection direction)
{
    Paddle_Delete(paddle);
    if (direction == LEFT)
	{
		if (PADDLE_MOVE <= paddle->xPos) 
            paddle->xPos -= PADDLE_MOVE;
		else 
            paddle->xPos = 0;
	}
	else
	{
		if (MAX_X - paddle->xPos - paddle->length >= PADDLE_MOVE) 
            paddle->xPos += PADDLE_MOVE;
		else 
            paddle->xPos = MAX_X  - paddle->length;
	}

    Paddle_Draw(paddle);
}