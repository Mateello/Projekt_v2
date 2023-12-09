#include <SFML/Graphics.hpp>
#include<iostream>
#include <random>

class Wrog
{
	int wierzcholki;//ilosc wierzcholkow wrog�w
protected:
	int ilosc;
	sf::RenderWindow *okno;
	sf::Vector2f wymiar_okna;
	float promien;
	sf::CircleShape krztalt;//tej zmiennej nie usuwam poniewa� na niej bazowuj� funckje pushback dla wektor�w wrog�w i ziaren

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
class Ziarna:public Wrog //zbierane przez gracza, zwi�kszaj� ilo�� punkt�w
{
	int wartosc;//warto�� - ilo�� punkt�w za zebranie ziarna
	std::vector<sf::CircleShape> ziarna;//wektor ziaren - dzi�ki niemu moge tworzy� wiele obiekt�w
public:
	Ziarna(int liczbaziaren,float promien,int wartosc, sf::RenderWindow& okno);
	Ziarna() {
		ilosc = 3; promien = 30; wartosc = 1;//konstruktor domy�lny
	}
	~Ziarna();
	int getWartosc();//wydobywa nam warto�� punktow� danego ziarna
	void rysuj(sf::RenderWindow& okno);//przeci��anie nazwy metody 
};