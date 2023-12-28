#include <SFML/Graphics.hpp>
#include <iostream>

class Mapa {
	int *wysokosc, *szerokosc;//s� to inty bo okre�laj� ilo�� �cian
	float* grid;
	sf::RenderWindow* okno;
	sf::RectangleShape sciana;
	std::vector<std::vector<sf::RectangleShape>> poziom;//dwuwymiarowy wektor przechowuj�cy zmienne �ciany
	void init();
public:
	Mapa(float* grid,int *wysokosc, int *szerokosc, sf::RenderWindow* okno);
	~Mapa();
	void draw();
};