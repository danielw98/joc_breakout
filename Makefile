build:
	gcc -Wall -o breakout main.c paddle.c ball.c bricks.c -lncurses
clean:
	-rm breakout 2> /dev/null
