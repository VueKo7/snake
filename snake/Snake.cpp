#include "Snake.h"



void snake_INIT(Snake_body* head) {

	head->next_body = NULL; //la testa punta a NULL
	head->prev_body = NULL; //la testa punta a NULL

	head->style = sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	head->style.setFillColor(sf::Color(0, 128, 0));
	head->style.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	head->live = true;
	head->directionX = 1;
	head->directionY = 0;
}



void _add_bodyPart(Snake_body* head, sf::RectangleShape style)
{
	Snake_body* tmp_head; //lista di supporto per non alterare la head

	//percorro la lista fino in fondo
	for (tmp_head = head; tmp_head->next_body != NULL; tmp_head = tmp_head->next_body);

	//creo il nuovo elemento da accodare
	Snake_body* new_bodyPart = new Snake_body;
	new_bodyPart->style = style;
	new_bodyPart->style.setFillColor(sf::Color::Green);

	new_bodyPart->style.setPosition(head->style.getPosition().x + head->style.getSize().x * - head->directionX,
								head->style.getPosition().y + head->style.getSize().y * -head->directionY);
	
	new_bodyPart->next_body = NULL;
	new_bodyPart->prev_body = tmp_head;

	
	//accodo alla lista il nuovo elemento
	tmp_head->next_body = new_bodyPart;
}



void handleInput(Snake_body* head)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if(head->directionY != 1) {
			head->directionY = -1;
			head->directionX = 0;
		}
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if(head->directionX != 1) {
			head->directionY = 0;
			head->directionX = -1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if(head->directionY != -1) {
			head->directionY = 1;
			head->directionX = 0;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if(head->directionX != -1) {
			head->directionY = 0;
			head->directionX = 1;
		}
	}
}





void movement(Snake_body* head) {

	Snake_body* tmp_head;
	for (tmp_head = head->next_body; tmp_head->next_body != NULL; tmp_head = tmp_head->next_body);

	while (tmp_head->prev_body != NULL) {
		tmp_head->style.setPosition(tmp_head->prev_body->style.getPosition());

		tmp_head = tmp_head->prev_body;
	}
	
	head->style.move(sf::Vector2f(head->directionX * head->style.getSize().x, head->directionY * head->style.getSize().y));	
}






void checkCollision(Snake_body* head) {

	sf::Vector2f pos = head->style.getPosition();

	int nextStepX = (head->style.getSize().x * head->directionX);
	int nextStepY = (head->style.getSize().y * head->directionY);
	if ((pos.x + nextStepX >= SCREEN_WIDTH || pos.x + nextStepX <= -TILE_SIZE) || (pos.y + nextStepY >= SCREEN_HEIGHT || pos.y + nextStepY <= -TILE_SIZE)) {
		head->live = false;
	}
	else { //controllo che non si mangi la coda
		Snake_body* tmp_head = head;
		while (tmp_head->next_body != NULL) {
			if ((head->style.getPosition().x + head->directionX * TILE_SIZE == tmp_head->style.getPosition().x) && (head->style.getPosition().y + head->directionY * TILE_SIZE == tmp_head->style.getPosition().y))
				head->live = false;
			tmp_head = tmp_head->next_body;
		}
	}
}



void update(Snake_body* head) {

	handleInput(head);
	checkCollision(head);
	movement(head);
}

