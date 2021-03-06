#ifndef GAME_H_
#define GAME_H_
#include "food.h"
#include "snake.h"
#include "pen.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
 
#define SPACE    32
#define ESC      27
#define UP       65
#define DOWN     66
#define RIGHT    67
#define LEFT     68

class Game{
public:
	//game start function
	//initialize every thing
	//need to be implemented
	void start();
	
private:
	void gameStart();
	void handler();
	char get_key();
	int end();
	int getKey();
	void drawBox();
	void drawSnake();
	void snakeMove();
	void updateFood();
	Pen pen;
	Food food;
	Snake snake;
    char fkey;
    int speed;
    int score;
};


#endif