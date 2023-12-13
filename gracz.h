#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>

class Gracz
{
	sf::RenderWindow *window;
	sf::Texture *tekstura;
	sf::Sprite *zawodnik;
	sf::Vector2f predkosc;
	sf::Vector2f pozycja;
public:
	Gracz(sf::RenderWindow *okno);
	~Gracz();
	void update();
	void init();
	void draw();//zmienna odpowowiadająca za to czy gracz "żyje" czy nie
	sf::FloatRect getBounds();
};