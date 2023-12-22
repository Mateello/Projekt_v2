#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>
#include<ctime>
#include<cmath>
#include"gracz.h"

class Wrog
{
protected:
	int ilosc;
	sf::RenderWindow *window;
	sf::RectangleShape krztalt;//tej zmiennej nie usuwam poniewa� na niej bazowuj� funckje pushback dla wektor�w wrog�w i ziaren
	sf::Vector2f pozycja;
	sf::Vector2f *przesuniecie;

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void init();	
public:
	Wrog(int ilosc, sf::RenderWindow* okno);//wrogowie b�d� prostok�tami
	Wrog() { ilosc = 1; 
	}
	~Wrog();
	void draw();
	void ruch();
	std::vector<sf::RectangleShape> wrogowie;
};
class Ziarno:public Wrog //zbierane przez gracza, zwi�kszaj� ilo�� punkt�w
{
	//za ka�de ziarno b�dzie +1 punkt dla gracza
	void init();
public:
	Ziarno(int ilosc, sf::RenderWindow* okno);
	~Ziarno();
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