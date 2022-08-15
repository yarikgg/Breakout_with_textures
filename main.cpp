#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Breakout");

	sf::RectangleShape player;
	player.setSize(sf::Vector2f(100, 50));
	player.setFillColor(sf::Color::Green);
	player.setOrigin(100 / 2, 50 / 2);
	player.setPosition(320, 400);

	sf::CircleShape ball(20);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(20, 0);
	ball.setPosition(320, 300);

	std::vector<sf::Sprite> blocks;
	sf::Texture t;
	t.loadFromFile("bricks.png");

	std::vector<int> is_destroy;

	for (int i = 1; i <= 15; ++i) {
		is_destroy.push_back(0);
	}

	float ball_directionx = 0;
	float ball_directiony = -0.1f;

	for (int i = 1; i <= 5; ++i) { // spawn the blocks
		sf::Sprite block;
		block.setTexture(t);
		block.setOrigin(88, 25);

		block.setPosition(120 * i, 20);

		blocks.push_back(block);
	}

	for (int i = 1; i <= 5; ++i) {
		sf::Sprite block;
		block.setTexture(t);
		block.setOrigin(88, 25);

		block.setPosition(120 * i, 90);

		blocks.push_back(block);
	}

	for (int i = 1; i <= 5; ++i) {
		sf::Sprite block;
		block.setTexture(t);
		block.setOrigin(88, 25);

		block.setPosition(120 * i, 160);

		blocks.push_back(block);
	}

	int i = 0;

	float old_pos = sf::Mouse::getPosition(window).x;
	float new_pos = sf::Mouse::getPosition(window).x;

	while (window.isOpen()) { // main loop

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
		}

		window.clear();
		new_pos = sf::Mouse::getPosition(window).x;

		if (new_pos > old_pos && ball.getGlobalBounds().intersects(player.getGlobalBounds())) { // ball_direction
			ball_directionx = 0.1;
		}
		else if (new_pos < old_pos && ball.getGlobalBounds().intersects(player.getGlobalBounds())) {
			ball_directionx = -0.1;
		}

		player.setPosition(sf::Mouse::getPosition(window).x, 400);
		window.draw(player);
		window.draw(ball);
		ball.move(ball_directionx, ball_directiony);
		for (sf::Sprite block : blocks) { // destroy block
			if (i >= 15) {
				i = 0;
			}
			if (is_destroy[i] == 0 && ball.getGlobalBounds().intersects(block.getGlobalBounds())) {
				is_destroy[i] = 1;
				ball_directiony = -ball_directiony;
				ball_directionx = -ball_directionx;
			}
			if (is_destroy[i] == 1) {
				block.setPosition(-1000, -1000);
			}
			else {
				window.draw(block);
			}
			++i;

		}

		if (ball.getGlobalBounds().intersects(player.getGlobalBounds())) {
			ball_directiony = -0.1;
		}

		if (ball.getPosition().y <= 0) { // the reflection of ball
			ball_directiony = 0.1;
		}
		if (ball.getPosition().x <= 0) {
			ball_directionx = -ball_directionx;
		}
		if (ball.getPosition().x >= 640) {
			ball_directionx = -ball_directionx;
		}
		if (ball.getPosition().y >= 640) {
			return 0;
		}

		old_pos = sf::Mouse::getPosition(window).x;

		window.display();
	}

	return EXIT_SUCCESS;
}