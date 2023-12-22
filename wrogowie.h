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
	sf::RectangleShape krztalt;//tej zmiennej nie usuwam poniewa¿ na niej bazowuj¹ funckje pushback dla wektorów wrogów i ziaren
	sf::Vector2f pozycja;
	sf::Vector2f *przesuniecie;

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void init();	
public:
	Wrog(int ilosc, sf::RenderWindow* okno);//wrogowie bêd¹ prostok¹tami
	Wrog() { ilosc = 1; 
	}
	~Wrog();
	void draw();
	void ruch();
	std::vector<sf::RectangleShape> wrogowie;
};
class Ziarno:public Wrog //zbierane przez gracza, zwiêkszaj¹ iloœæ punktów
{
	//za ka¿de ziarno bêdzie +1 punkt dla gracza
	void init();
public:
	Ziarno(int ilosc, sf::RenderWindow* okno);
	~Ziarno();
};

class WrogCS
{
	float obrot = 0;
	sf::ConvexShape gwiazda;//nie wiem czemu jak zrobi³em to na wskaŸnikach to wskaŸnik zwraca³ NULL
	sf::RenderWindow* window;
	sf::Vector2f przesuniecie;
public:
	WrogCS(sf::RenderWindow* okno); ~WrogCS();
	void init();
	void ruch();
	void draw();
	sf::FloatRect getBounds();
};