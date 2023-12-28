#include "Mapa.h"
Mapa::Mapa(float* grid, int* szerokosc, int* wysokosc, sf::RenderWindow* okno) {
	this->grid = grid; this->szerokosc = szerokosc; this->wysokosc = wysokosc; this->okno = okno;
}
Mapa::~Mapa() {
	delete szerokosc; delete wysokosc; delete okno; delete grid;
}
void Mapa::init(){
	for (int i = 0; i < *szerokosc; i++) {
		for (int j = 0; j < *wysokosc; j++) {
			sciana.setSize(sf::Vector2f(*grid, *grid)); sciana.setFillColor(sf::Color(33, 33, 222));
			sciana.setOutlineColor(sf::Color::Black); sciana.setOutlineThickness(1.f); sciana.setPosition((*grid)*i, (*grid) * j);
			poziom[i].push_back(sciana);
		}
	}
}
void Mapa::draw(){
	/**for (int i = 0; i < *szerokosc; i++) {
		for (int j = 0; j < *wysokosc; j++) {
			okno->draw(sciana);
		}
	}*/
	for (int i = 0; i < poziom.size();i++) {
		for (int j = 0; j < poziom.size(); j++) {
			okno->draw(sciana); std::cout << "dziala?";
		}
		std::cout << "\n";
	}
}