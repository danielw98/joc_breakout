#include<curses.h>
#include <stdlib.h>
#include"includes.h"

int Ball_CheckCollisionWithPaddle(Ball *ball, Paddle *paddle)
{
	if (ball->xPos >= paddle->xPos && ball->xPos <= (paddle->xPos + paddle->length)) 
		return true;
	return false;
}
void Ball_MoveX(Ball *ball, xDirection dirX)
{
	ball->dirX = dirX;
}

void Ball_MoveY(Ball *ball, yDirection dirY)
{
	if (dirY == DOWN && ball->dirX == X_NEUTRAL)
		ball->dirX = rand() % 2;
	ball->dirY = dirY;
}

void Ball_Delete(Ball *ball)
{
	move(ball->yPos, ball->xPos);
	addch(' ');
	refresh();
}

void Ball_Draw(Ball *ball)
{
	move(ball->yPos, ball->xPos);
	attron(A_BOLD | COLOR_PAIR(2));
    addch('*');
	attroff(A_BOLD | COLOR_PAIR(2));
	refresh();
}
void Ball_Reset(Ball *ball)
{
	ball->xPos = MAX_X / 2;
	ball->yPos = MAX_Y - 4;
	ball->dirX = X_NEUTRAL;
	ball->dirY = DOWN;
}

void Ball_Move(Ball *ball)
{
	Ball_Delete(ball);
	
	switch (ball->dirX){
	case RIGHT:{
		if(ball->xPos + 1 <= MAX_X - 1)
		 	ball->xPos++;
		else
			ball->xPos = MAX_X - 1;
		break;
	}
	case LEFT:{
		if(ball->xPos - 1 >= 0)
		 	ball->xPos--;
		else
			ball->xPos = 0;
		break;
	}
	default:
		break;
	}
	switch (ball->dirY){
	case DOWN:{
		if(ball->yPos + 1 < MAX_Y - 1)
			ball->yPos++;
		else
			ball->yPos = MAX_Y - 2;	
		break;
	}
	case UP:{
		if(ball->yPos - 1 > 0)
			ball->yPos--;
		else
			ball->yPos = 1;
		break;
	}
	default:
		break;
	}
	
	Ball_Draw(ball);
}