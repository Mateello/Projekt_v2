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

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void init();
public:
	Wrog(sf::RenderWindow *okno);//wrogowie b�d� prostok�tami
	~Wrog();
	void draw();//wektor wrog�w - pozwalaj�cy tworzy� wielu wrog�w
};
class Ziarno:public Wrog //zbierane przez gracza, zwi�kszaj� ilo�� punkt�w
{
	int wartosc=1;//warto�� - ilo�� punkt�w za zebranie ziarna
public:
	Ziarno(sf::RenderWindow *okno);
	~Ziarno();
	void init();
};

class WrogCS
{
	float obrot = 0;
	sf::ConvexShape gwiazda;//nie wiem czemu jak zrobi�em to na wska�nikach to wska�nik zwraca� NULL
	sf::RenderWindow* window;
	sf::Vector2f przesuniecie;
public:
	WrogCS(sf::RenderWindow* okno); ~WrogCS();
	void init();
	void ruch();
	void draw();
	sf::FloatRect getBounds();
};