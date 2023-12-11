#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>
#include "wrogowie.h"

class Gracz
{
	int punkty;
	sf::Vector2f window;
	sf::Texture tekstura;
	sf::Sprite Zawodnik;
public:
	Gracz() {//konstruktor domyślny
		punkty = 0; pozycja.x = 0; pozycja.y = 0;
	}
	Gracz(sf::RenderWindow& okno);
	sf::Sprite getGracz();
	sf::FloatRect NastepnaPoz;//zmienna przechowująca wartość następnej pozycji
	sf::FloatRect ZawOtoczka;//zmienna przechowująca wartości getGlobalBounds
	sf::Vector2f predkosc;
	sf::Vector2f pozycja;
	void update();
	void getPunkty(int &pkt);
	void setPunkty(int pkt);
	void kolizja();
};