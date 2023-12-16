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
	sf::RectangleShape krztalt;//tej zmiennej nie usuwam poniewa¿ na niej bazowuj¹ funckje pushback dla wektorów wrogów i ziaren
	sf::Vector2f pozycja;

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void init();
public:
	Wrog(sf::RenderWindow *okno);//wrogowie bêd¹ prostok¹tami
	~Wrog();
	void draw();//wektor wrogów - pozwalaj¹cy tworzyæ wielu wrogów
};
class Ziarno:public Wrog //zbierane przez gracza, zwiêkszaj¹ iloœæ punktów
{
	int wartosc=1;//wartoœæ - iloœæ punktów za zebranie ziarna
public:
	Ziarno(sf::RenderWindow *okno);
	~Ziarno();
	void init();
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