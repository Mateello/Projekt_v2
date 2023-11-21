#include <SFML/Graphics.hpp>
#include<iostream>

class Gracz
{
	sf::Vector2f pozycja;
	sf::Vector2f rozmiar_okna;
	sf::Vector2f window;
	sf::Texture Pacman_t;
	sf::Sprite Pacman;
public:
	Gracz(float x_in, float y_in, float okno_x, float okno_y);
	sf::Sprite getGracz();
};