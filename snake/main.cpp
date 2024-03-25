#include "Snake.h"
#include "main.h"

void render(sf::RenderWindow& window, Snake_body* head, sf::RectangleShape apple);
void update(Snake_body* head, sf::RectangleShape& apple);
void placeApple(sf::RectangleShape& apple);


int main()
{
	Snake_body* head = new Snake_body;
	snake_INIT(head); //inizializzo la testa del serpente


	//la linked list si comporterà come il corpo
	_add_bodyPart(head, sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE)));
	

	//creo la finestra e imposto il limite di frameRate
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "snake!");
	window.setFramerateLimit(FRAME);


	sf::RectangleShape apple(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	apple.setFillColor(sf::Color::Red);
	apple.setPosition(head->style.getPosition().x + 100, head->style.getPosition().y + 100);
	srand(time(NULL));



	//GAMELOOP
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		update(head, apple);
		render(window, head, apple);

		if (!head->live)
			break;
	}

	return 0;
}


void update(Snake_body* head, sf::RectangleShape& apple)
{
	//AGGIORNAMENTO SNAKE
	update(head);

	//AGGIORNAMENTO APPLE
	if (head->style.getGlobalBounds().intersects(apple.getGlobalBounds())) {
		placeApple(apple);
		_add_bodyPart(head, sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE)));
	}
}





void render(sf::RenderWindow& window, Snake_body* head, sf::RectangleShape apple)
{
	window.clear();
	
	sf::VertexArray lines(sf::Lines, 2);
	int tileSize = head->style.getSize().x;
	for (int i = 0; i < SCREEN_WIDTH / tileSize; i++) {

		lines[0].position = sf::Vector2f(i * tileSize, 0);
		lines[1].position = sf::Vector2f(i * tileSize, SCREEN_HEIGHT);

		window.draw(lines);
	}
	for (int i = 0; i < SCREEN_HEIGHT / tileSize; i++) {

		lines[0].position = sf::Vector2f(0, i * tileSize);
		lines[1].position = sf::Vector2f(SCREEN_WIDTH, i * tileSize);

		window.draw(lines);
	}
	

	
	window.draw(apple);

	Snake_body* tmp_head = head;
	while (tmp_head != NULL) {
		window.draw(tmp_head->style);
		tmp_head = tmp_head->next_body;
	}

	window.display();
}



void placeApple(sf::RectangleShape& apple) {
	int width = (SCREEN_WIDTH / TILE_SIZE);
	int height = (SCREEN_HEIGHT / TILE_SIZE);
	int x = rand() % width;
	int y = rand() % height;
	apple.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
}