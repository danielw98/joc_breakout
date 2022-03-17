#include"includes.h"
#include<string.h>
#include<curses.h>
int BricksPerLine = 10; 
int BrickNumLines = 5;
int HeightFromPaddle = 3;

Brick Bricks[MAX_NUMLINES][MAX_NUMCOLS];


int Brick_Exists(int xPos, int yPos)
{
	int i, j;
	Brick *brick;
	
	for (i = 0; i < MAX_NUMLINES; i++)
	{
		for (j = 0; j < MAX_NUMCOLS; j++)
		{
			brick = &Bricks[i][j];
			
			if (brick->visible && xPos >= brick->xStart && xPos <= brick->xEnd && yPos == brick->y)
				return true;
			
		}
	}
	
	return false;
}

void Brick_DrawBrick(Brick *brick)
{
	int i;
	if (!brick->visible) 
        return;
	
	move(brick->y, brick->xStart);
	
	attron(COLOR_PAIR(brick->color));
	addch('[');
	for (i = 1; i < brick->xEnd - brick->xStart - 1; i++)
		addch('=');
	addch(']');
	attroff(COLOR_PAIR(brick->color));

	
	refresh();
}

/*
    Intrare: void
    Iesire: void
    Rol: itereaza peste matricea de caramizi 
    si le deseneaza pe cele vizibile
*/
void Brick_DrawAllBricks(void)
{
	int i,j;
	for (i = 0 ; i < BrickNumLines; i++)
		for (j = 0; j < BricksPerLine; j++)
            if(Bricks[i][j].visible)
                Brick_DrawBrick(&Bricks[i][j]);

}

/*
    Intrare: void
    Iesire: void
    Rol: initializeaza matricea de caramizi
    cu valorile corespunzatoare pentru a fi
    afisata prima data la consola
*/
void Brick_ResetBricks(void)
{ 
	int Width = MAX_X / BricksPerLine;
	const int StartY = HeightFromPaddle;
	int i, j;
	Brick *brick = NULL;
	
	memset(Bricks, 0, sizeof(Bricks));
	
    while(Width * BricksPerLine > MAX_X){
        --Width;
	}

	for (i = 0; i < BrickNumLines; i++)
	{
		for (j = 0; j < BricksPerLine; j++)
		{
			brick = &Bricks[i][j];
			brick->xStart = Width * j;
			brick->xEnd = brick->xStart + Width;
			brick->y = StartY + i;
			brick->visible = true;
			brick->color = i + 2;
			
		}
	}
}

/*
    Intrare:  pointer catre o caramida
    Iesire: void
    Rol: sterge de pe consola caramida
    trimisa ca parametru, inlocuind toate
    caracterele ei cu caracterul ' '
*/
void Brick_DeleteBrick(Brick *brick)
{
	int i;
	move(brick->y, brick->xStart);
	for (i = 0; i < brick->xEnd - brick->xStart; i++)
		addch(' ');
	brick->visible = false;
	refresh();
}

void Brick_DeleteAllBricks()
{
	int i, j;
	for (i = 0; i < BrickNumLines; i++)
		for (j = 0; j < BricksPerLine; j++)
			if (Bricks[i][j].visible)
				Brick_DeleteBrick(&Bricks[i][j]);

}
int Brick_CountBricks(void)
{
	int i, j;
	int count;
	
	for (i = 0; i < BrickNumLines; i++)
		for (j = 0; j < BricksPerLine; j++)
			if (Bricks[i][j].visible)
				count++;
	
	return count;
}


int Brick_CheckCollisionWithBall(Ball *ball, Strike *strike)
{
	int i = 0, j = 0;
	
	for (i = 0; i < BrickNumLines; ++i)
	{
		for (j = 0; j < BricksPerLine; ++j)
		{
			if (Bricks[i][j].visible &&
				ball->xPos >= Bricks[i][j].xStart - 1 && ball->xPos <= Bricks[i][j].xEnd + 1 &&
				ball->yPos <= Bricks[i][j].y + 1 && ball->yPos >= Bricks[i][j].y - 1)
			{
				if (ball->yPos == Bricks[i][j].y - 1) 
				{
					strike->StrikeV = STRIKE_TOP;
				}
				else if (ball->yPos == Bricks[i][j].y + 1)
				{
					strike->StrikeV  = STRIKE_BOTTOM;
				}
				else
				{
					strike->StrikeV = STRIKE_VNONE;
				}
				
				if (ball->xPos == Bricks[i][j].xStart - 1) 
				{
					strike->StrikeH = STRIKE_LEFT;
				}
				else if (ball->xPos == Bricks[i][j].xEnd + 1)
				{
					strike->StrikeH = STRIKE_RIGHT;
				}
				else
				{
					strike->StrikeH = STRIKE_HNONE;
				}
				
				strike->brick = &Bricks[i][j];
				
				return true;
			}
		}
	}
	
	return false;
}
