#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>

class Gracz
{
	int punkty;
	sf::Vector2f pozycja;
	sf::Vector2f window;
	sf::Texture Pacman_t;
	sf::Sprite Pacman;
	float przesuniecie;
public:
	Gracz(sf::RenderWindow& okno);
	sf::Sprite getGracz();
	void update();
	void getPunkty(int &pkt);
	void setPunkty(int pkt);
	void getPozycja(sf::Sprite Gracz);
};