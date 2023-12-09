#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>

class Wrog
{
	int wierzcholki;//ilosc wierzcholkow wrogów
protected:
	int ilosc;
	sf::RenderWindow *okno;
	sf::Vector2f wymiar_okna;
	float promien;
	sf::CircleShape krztalt;//tej zmiennej nie usuwam poniewa¿ na niej bazowuj¹ funckje pushback dla wektorów wrogów i ziaren

	std::vector<sf::CircleShape> wrogowie;

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);

public:
	Wrog() {
		ilosc = 1; promien = 100; wierzcholki = 0;
	}
	Wrog(int liczbaWrogow,float r,int w, sf::RenderWindow& okno);
	~Wrog();

	void rysuj(sf::RenderWindow& okno);
};
class Ziarna:public Wrog //zbierane przez gracza, zwiêkszaj¹ iloœæ punktów
{
	int wartosc;//wartoœæ - iloœæ punktów za zebranie ziarna
	std::vector<sf::CircleShape> ziarna;//wektor ziaren - dziêki niemu moge tworzyæ wiele obiektów
public:
	Ziarna(int liczbaziaren,float promien,int wartosc, sf::RenderWindow& okno);
	Ziarna() {
		ilosc = 3; promien = 30; wartosc = 1;//konstruktor domyœlny
	}
	~Ziarna();
	int getWartosc();//wydobywa nam wartoœæ punktow¹ danego ziarna
	void rysuj(sf::RenderWindow& okno);//przeci¹¿anie nazwy metody 
};