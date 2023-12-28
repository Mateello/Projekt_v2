#include <SFML/Graphics.hpp>
#include <iostream>

class Mapa {
	int *wysokosc, *szerokosc,ilosc,licznik;//s¹ to inty bo okreœlaj¹ iloœæ œcian
	float* grid;
	sf::RenderWindow* okno;
	sf::RectangleShape sciana;
	std::vector<sf::RectangleShape> poziom;//dwuwymiarowy wektor przechowuj¹cy zmienne œciany
	void init();
public:
	Mapa(float* grid,int *wysokosc, int *szerokosc, sf::RenderWindow* okno);
	~Mapa();
	void draw();
};