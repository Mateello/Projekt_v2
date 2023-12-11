#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>
#include<cmath>

class Wrog
{
	int wierzcholki;//ilosc wierzcholkow wrogów
protected:
	int ilosc;
	sf::RenderWindow *okno;
	sf::Vector2f wymiar_okna;
	float promien;
	sf::CircleShape krztalt;//tej zmiennej nie usuwam poniewa¿ na niej bazowuj¹ funckje pushback dla wektorów wrogów i ziaren

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);

public:
	Wrog() {
		ilosc = 1; promien = 100; wierzcholki = 0;
	}
	Wrog(int liczbaWrogow,float r,int w, sf::RenderWindow& okno);
	~Wrog();
	sf::Vector2f pozycja;
	sf::FloatRect wrogOtoczka;//otoczka wrogów i "ziaren"
	void rysuj(sf::RenderWindow& okno);
	std::vector<sf::CircleShape> wrogowie;//wektor wrogów - pozwalaj¹cy tworzyæ wielu wrogów
};
class Ziarna:public Wrog //zbierane przez gracza, zwiêkszaj¹ iloœæ punktów
{
	int wartosc;//wartoœæ - iloœæ punktów za zebranie ziarna
public:
	Ziarna(int liczbaziaren,float promien,int wartosc, sf::RenderWindow& okno);
	Ziarna() {
		ilosc = 3; promien = 30; wartosc = 1;//konstruktor domyœlny
	}
	~Ziarna();
	int getWartosc();//wydobywa nam wartoœæ punktow¹ danego ziarna
};