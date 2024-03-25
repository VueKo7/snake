#pragma once
#include "main.h"


struct Snake_body {

	int directionX;
	int directionY;

	bool live;

	//body itself
	sf::RectangleShape style;

	//if snake eats then add a new body_part
	Snake_body* next_body;
	Snake_body* prev_body;
};



void _add_bodyPart(Snake_body* head, sf::RectangleShape style);
void handleInput(Snake_body* head);
void update(Snake_body* head);
void checkCollision(Snake_body* head);
void movement(Snake_body* head);
void snake_INIT(Snake_body* head);
