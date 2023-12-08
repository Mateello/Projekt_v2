#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>

class Wrog
{
	int wierzcholki;//ilosc wierzcholkow wrog�w
protected:
	sf::RenderWindow *okno;
	sf::Vector2f wymiar_okna;
	float promien;
	sf::CircleShape krztalt;

public:
	Wrog() {
		promien = 100; wierzcholki = 0;
	}
	Wrog(float r,int w, sf::RenderWindow& okno);
	~Wrog();

	sf::CircleShape getWrog();
	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void rysuj(sf::RenderWindow& okno);
};
class Ziarna:public Wrog //zbierane przez gracza, zwi�kszaj� ilo�� punkt�w
{
	int wartosc;//warto�� - ilo�� punkt�w za zebranie ziarna
public:
	Ziarna(float promien,int wartosc, sf::RenderWindow& okno);
	Ziarna() {
		promien = 30; wartosc = 1;
	}
	~Ziarna();
	int getWartosc();
};