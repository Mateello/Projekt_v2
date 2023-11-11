#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	sf::RenderWindow glowne(sf::VideoMode(400.f, 400.f), "Projekt-PACMAN");
	sf::RenderWindow help(sf::VideoMode(200.f, 200.f), "Pomoc");
	sf::RenderWindow Esc(sf::VideoMode(200.f, 200.f), "Opuszczanie gry");

	sf::CircleShape wrog_1(100.f);
	sf::CircleShape wrog_2(100.f, 3);

	sf::RectangleShape wrog_3(sf::Vector2f(150.f, 100.f));
	sf::ConvexShape wrog_4;
	wrog_4.setPointCount(5);
	wrog_4.setPoint(0, sf::Vector2f(0.f, 0.f));
	wrog_4.setPoint(1, sf::Vector2f(30.f, 10.f));
	wrog_4.setPoint(2, sf::Vector2f(30.f, 50.f));
	wrog_4.setPoint(3, sf::Vector2f(20.f, 50.f));
	wrog_4.setPoint(4, sf::Vector2f(0.f, 70.f));

	while (glowne.isOpen())
	{
		sf::Event event;
		while (glowne.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				glowne.close();
		}
		glowne.clear();
		glowne.draw(wrog_4);
		glowne.display();
	}
	return 0;
}