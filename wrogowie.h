#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>

class wrog
{
	float xVel = 1, yVel = 1;
	sf::Vector2f wymiar_okna;
	float promien;
	int wierzcholki;//ilosc wierzcholkow wrogów
	sf::CircleShape krztalt;

public:
	wrog(float r,int w, float szerokoscOkna, float wysokoscOkna);
	~wrog();

	sf::CircleShape getWrog();
	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void rysuj(sf::RenderWindow &okno);
};