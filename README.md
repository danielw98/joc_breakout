# Breakout Game

Welcome to this Breakout clone! It's built with ncurses, making it a cool, terminal-based game. If you're into old-school arcade games or just want to see what you can do with ncurses, you're in the right place.

## Demo Animation

![Breakout Animation](https://github.com/danielw98/joc_breakout/blob/main/joc_breakout.gif?raw=true)

## How It Works

- **Move the Paddle**: Use left and right arrow keys. It's all about timing and angles.
- **Break Bricks**: Clear each level by breaking all the bricks. Each brick might take one or more hits to break, depending on the level.
- **Keep the Ball Moving**: Don't let the ball pass your paddle, or you'll lose a life. Lose all lives, and it's game over.

## Getting Started

First, make sure you've got ncurses installed on your system. Then, clone this repo, compile the game, and run it. Here are the commands you'll likely need:

```bash
git clone https://github.com/danielw98/joc_breakout
cd joc_breakout
make
./breakout
```

## Dive Into the Code

The game's pretty straightforward but feel free to poke around the code. main.c kicks things off, ball.c controls our ball's behavior, paddle.c is all about moving that paddle, and bricks.c manages those bricks you're aiming to destroy.

## Contribute

Got an idea for an improvement? See a bug? Jump in and help out! Fork the repo, make your changes, and submit a pull request. All contributions are welcome.

## License

This project is under an MIT license. Feel free to use, modify, and distribute as you see fit. Check out the LICENSE file for all the details.