#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>
#include<cmath>

class Wrog
{
	int wierzcholki;//ilosc wierzcholkow wrog�w
protected:
	int ilosc;
	sf::RenderWindow *okno;
	sf::Vector2f wymiar_okna;
	float promien;
	sf::CircleShape krztalt;//tej zmiennej nie usuwam poniewa� na niej bazowuj� funckje pushback dla wektor�w wrog�w i ziaren

	float losPozycjeX(int szerokoscOkna);
	float losPozycjeY(int wysokoscOkna);

public:
	Wrog() {
		ilosc = 1; promien = 100; wierzcholki = 0;
	}
	Wrog(int liczbaWrogow,float r,int w, sf::RenderWindow& okno);
	~Wrog();
	sf::Vector2f pozycja;
	sf::FloatRect wrogOtoczka;//otoczka wrog�w i "ziaren"
	void rysuj(sf::RenderWindow& okno);
	std::vector<sf::CircleShape> wrogowie;//wektor wrog�w - pozwalaj�cy tworzy� wielu wrog�w
};
class Ziarna:public Wrog //zbierane przez gracza, zwi�kszaj� ilo�� punkt�w
{
	int wartosc;//warto�� - ilo�� punkt�w za zebranie ziarna
public:
	Ziarna(int liczbaziaren,float promien,int wartosc, sf::RenderWindow& okno);
	Ziarna() {
		ilosc = 3; promien = 30; wartosc = 1;//konstruktor domy�lny
	}
	~Ziarna();
	int getWartosc();//wydobywa nam warto�� punktow� danego ziarna
};