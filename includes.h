#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#define MAX_X           80
#define MAX_Y           24
#define PADDLE_LENGTH   (MAX_X/10)
#define PADDLE_MOVE     (PADDLE_LENGTH / 2)

#define MAX_NUMLINES    12
#define MAX_NUMCOLS     20

typedef struct Paddle{
    int xPos;
    int length;
}Paddle;


typedef enum { LEFT, RIGHT, X_NEUTRAL } xDirection;
typedef enum { UP, DOWN, Y_NEUTRAL} yDirection;



typedef struct Ball
{
	int xPos, yPos;
	xDirection dirX;
	yDirection dirY;
}Ball;
typedef struct Game
{
	Ball ball;
    Paddle paddle;
}Game;


typedef struct Brick
{
	int xStart, xEnd, y;
	int visible;
	int color;
}Brick;

typedef struct 
{
	enum StrikeV { STRIKE_VNONE, STRIKE_BOTTOM, STRIKE_TOP } StrikeV;
	enum StrikeH { STRIKE_HNONE, STRIKE_LEFT, STRIKE_RIGHT } StrikeH;
	Brick *brick;
}Strike;


void Paddle_Draw(Paddle *paddle);
void Paddle_Delete(Paddle *paddle);
void Paddle_Reset(Paddle *paddle);
void Paddle_Move(Paddle *paddle, xDirection direction);



int  Ball_CheckCollisionWithPaddle(Ball *ball, Paddle *paddle);
void Ball_MoveX(Ball *ball, xDirection dirX);
void Ball_MoveY(Ball *ball, yDirection dirY);
void Ball_Delete(Ball *ball);
void Ball_Draw(Ball *ball);
void Ball_Reset(Ball *ball);
void Ball_Move(Ball *ball);

void Brick_DrawBrick(Brick *brick);
void Brick_DrawAllBricks(void);
void Brick_ResetBricks(void);
void Brick_DeleteBrick(Brick *brick);
void Brick_DeleteAllBricks(void);
int Brick_CountBricks(void);
int Brick_CheckCollisionWithBall(Ball *ball, Strike *strike);
Game Game_New(void);
void Game_Loop(Game *game);


extern Brick Bricks[MAX_NUMLINES][MAX_NUMCOLS];
#endif