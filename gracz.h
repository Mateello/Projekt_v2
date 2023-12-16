#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>

class Gracz{
	sf::RenderWindow *window;
	sf::Texture *tekstura;
	sf::Sprite *zawodnik;
	sf::Vector2f predkosc;
	sf::Vector2f pozycja;
public:
	bool deadPlayer;//zmienna odpowowiadaj¹ca za to czy gracz "¿yje" czy nie
	Gracz(sf::RenderWindow *okno);
	~Gracz();
	void update();
	void init();
	void draw();
	sf::FloatRect getBounds();
	sf::FloatRect bounds;
	int punkty;
	bool kolizje(std::vector<sf::RectangleShape> W);
};