#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>
#include<cmath>

class Wrog
{
protected:
	int ilosc;
	sf::RenderWindow *window;
	sf::Vector2f wymiar;
	sf::RectangleShape krztalt;//tej zmiennej nie usuwam poniewa� na niej bazowuj� funckje pushback dla wektor�w wrog�w i ziaren
	sf::Vector2f pozycja;
	std::vector<sf::RectangleShape> wrogowie;

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void init();
public:
	Wrog(int ilosc, sf::Vector2f wymiar, sf::RenderWindow *okno);//wrogowie b�d� prostok�tami
	~Wrog();
	void draw();//wektor wrog�w - pozwalaj�cy tworzy� wielu wrog�w
};
class Ziarna:public Wrog //zbierane przez gracza, zwi�kszaj� ilo�� punkt�w
{
	int wartosc=1;//warto�� - ilo�� punkt�w za zebranie ziarna
public:
	Ziarna(int ilosc, sf::Vector2f wymiar, sf::RenderWindow *okno);
	~Ziarna();
	void init();
};