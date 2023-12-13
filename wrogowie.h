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
	std::vector<sf::RectangleShape> wrogowie;

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);
	void init();
public:
	Wrog(int ilosc, sf::Vector2f wymiar, sf::RenderWindow *okno);//wrogowie bêd¹ prostok¹tami
	~Wrog();
	void draw();//wektor wrogów - pozwalaj¹cy tworzyæ wielu wrogów
};
class Ziarna:public Wrog //zbierane przez gracza, zwiêkszaj¹ iloœæ punktów
{
	int wartosc=1;//wartoœæ - iloœæ punktów za zebranie ziarna
public:
	Ziarna(int ilosc, sf::Vector2f wymiar, sf::RenderWindow *okno);
	~Ziarna();
	void init();
};