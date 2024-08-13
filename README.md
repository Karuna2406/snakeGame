# snakeGame
Snake Game Using ncurses in C++

A simple implementation of the classic Snake game using the ncurses library for terminal-based graphics. This project demonstrates basic ncurses functionalities including screen initialization, input handling, and rendering.

## Features
- Snake movement and growth
- Collision detection with walls and itself
- Random food placement
- Basic user input handling with arrow keys

## Dependencies
- ncurses library

## Setup

1. **Install Dependencies**

   Install the `libncurses5-dev` and `libncursesw5-dev` packages:

   ```bash
   sudo apt-get install libncurses5-dev libncursesw5-dev

# compile the program 
g++ -o snake_game snake_game.cpp -lncurses
# run the game
./snake_game

## Usage
Use the arrow keys to control the snake.
The goal is to eat the food (X) that appears randomly on the screen.
Avoid collisions with the walls or the snake’s own body.
