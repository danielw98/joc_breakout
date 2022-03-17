#include<curses.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "includes.h"



Game Game_New(void)
{
    Game game;
    Paddle_Reset(&game.paddle);
    Paddle_Draw(&game.paddle);
    Ball_Reset(&game.ball);
    Ball_Draw(&game.ball);
    return game;
}

int Score = 0;
int Lives = 3;
int Level = 1;
void DeleteStats(void)
{
	int i;
	move(0, 2);
	for (i = 0; i < MAX_X - 1; i++)
		addch(' ');
}
void DrawStats(void)
{
	DeleteStats();
	move(0, 2);
	attron(COLOR_PAIR(7));
	printw("Lives: %d\t\t\t", Lives);
	printw("Score: %d\t\t\t", Score);
	printw("Level: %d", Level);
	attroff(COLOR_PAIR(7));

	attrset(COLOR_PAIR(1));
	refresh();
}

void DrawMessage(char *message)
{
	move(MAX_Y / 2, (MAX_X - strlen(message)) / 2);
	addstr(message);
	refresh();
}
void DeleteMessage(void)
{
	int i;
	move(MAX_Y / 2, 0);

	for (i = 0; i < MAX_X - 1; i++)
		addch(' ');
	refresh();
}
void Game_Over(Ball *ball, Paddle *paddle)
{
	char message[255];
	Brick_DeleteAllBricks();
	Ball_Delete(ball);
	Paddle_Delete(paddle);
	DeleteStats();
	sprintf(message,"Game Over. Score is %d. Press any key to exit.", Score);
	DrawMessage(message);
	timeout(-1);
	getch();
    endwin();
    exit(0);
}


void Game_Launch(void)
{
	int key;

	DrawMessage("Press SPACE to start. Press P to pause.");

	while (1){
		key = getch();
		if(key == ' ' || key == 27)
			break;
	}

	DeleteMessage();

	if (key == 27)
	{
		endwin();
		exit(0);
	}
}

void Game_Loop(Game *game)
{ 
	Ball *ball = &game->ball;
	Paddle *paddle = &game->paddle;
	Strike strike;
	int key = 0;
	int ticks = 0;
	int paddleMovedLastTick;
	xDirection paddleDirection;

    Brick_ResetBricks();
    Brick_DrawAllBricks();
    DrawStats();
	Game_Launch();
	while (1) 
	{
		key = getch();
		if(key == 27)
			break;
		if(key == 'P' || key == 'p')
		{
			while(1){
				key = getch();
				if(key == 'P' || key == 'p')
					break;
			}
		}
		if (ticks == 5)
		{
			Score += 2;
			DrawStats();
			ticks = 0;
		}
		ticks++;

		if (ball->yPos == 1)
		{ 
			Ball_MoveY(ball, DOWN);
		}
		else if (ball->yPos >= MAX_Y - 2)
		{
			if (!Ball_CheckCollisionWithPaddle(ball, paddle))
			{
				Ball_Delete(ball);
				ball->yPos = MAX_Y - 1;
				Ball_Draw(ball);

				if (Lives == 1)
				{
					Game_Over(ball, paddle);
				}
				else
				{
					--Lives;
					DrawStats();

					Game_Launch();

					Ball_Delete(ball);
					Paddle_Delete(paddle);

					Ball_Reset(ball);
					Paddle_Reset(paddle);

					Paddle_Draw(paddle);
					Ball_Draw(ball);

					Brick_DrawAllBricks();
				}
			}
			else
			{
				Ball_MoveY(ball, UP);
				if (paddleMovedLastTick)
				{ 
					ball->dirX = paddleDirection;
				}
				else
				{ 
					int paddle_third  = (paddle->length / 3);
					if (ball->xPos <= paddle->xPos + paddle_third)
					{
						ball->dirX = LEFT;
					}
					else if (ball->xPos > paddle->xPos + paddle_third && ball->xPos <= paddle->xPos + (paddle_third * 2))
					{
						int up = rand() % 2;
						if (up)
							ball->dirX = X_NEUTRAL;
					}
					else
					{
						ball->dirX = RIGHT;
					}
				}
			}
		}
		paddleMovedLastTick = false;

		if (ball->xPos >= MAX_X - 1)
		{
			ball->xPos = MAX_X - 1;
			Ball_MoveX(ball, LEFT);
		}
		else if (ball->xPos <= 0)
		{
			ball->xPos = 0;
			Ball_MoveX(ball, RIGHT);
		}

		if (Brick_CheckCollisionWithBall(ball, &strike))
		{

				switch (strike.StrikeV)
				{
				case STRIKE_TOP:
					ball->dirY = UP;
					break;
				case STRIKE_BOTTOM:
					ball->dirY = DOWN;
					break;
				default:
					break;
				}

				switch (strike.StrikeH)
				{
				case STRIKE_LEFT:
					ball->dirX = LEFT;
					break;
				case STRIKE_RIGHT:
					ball->dirX = RIGHT;
					break;
				default:
				{
					if (ball->dirX != X_NEUTRAL)
						break;
					else
					{
						int dir = rand() % 2;
						ball->dirX = (xDirection)dir;
					}
					break;
				}
				}

			Brick_DeleteBrick(strike.brick);
			Score += 100;
			DrawStats();

			if (!Brick_CountBricks())
			{ 
					char WonBuf[256];
					snprintf(WonBuf, sizeof WonBuf, "You Won! Score is %d! Press any key to exit...", Score);
					DrawMessage(WonBuf);
					Ball_Delete(ball);
					timeout(-1);
					getch();
					Game_Over(ball,paddle);
			}
		}

		switch (key)
		{
		case KEY_LEFT:
			Paddle_Move(paddle, LEFT);
			paddleMovedLastTick = true;
			paddleDirection = LEFT;
			break;
		case KEY_RIGHT:
			Paddle_Move(paddle, RIGHT);
			paddleMovedLastTick = true;
			paddleDirection = RIGHT;
			break;
        }

		Ball_Move(ball);
	}
}

void init_colors(void)
{
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(6,COLOR_YELLOW,COLOR_BLACK);
    init_pair(7,COLOR_BLACK,COLOR_WHITE);
}
int main()
{
    initscr();
    keypad(stdscr,TRUE);
    curs_set(0);
    noecho();
    timeout(200);
    if (COLS < MAX_X || LINES < MAX_Y)
	{
		endwin();
		fprintf(stderr, "Minimum resolution: %dx%d\n", MAX_X, MAX_Y);
		exit(1);
		
	}
    init_colors();
    
    Game game = Game_New();
    Game_Loop(&game);
	endwin();
    return 0;
}