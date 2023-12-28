#include "Mapa.h"
Mapa::Mapa(float* grid, int* szerokosc, int* wysokosc, sf::RenderWindow* okno) {
	this->grid = grid; this->szerokosc = szerokosc; this->wysokosc = wysokosc; this->okno = okno;
}
Mapa::~Mapa() {
	delete szerokosc; delete wysokosc; delete okno; delete grid;
}
void Mapa::init(){
	ilosc = (*szerokosc) * (*wysokosc); licznik = 0;
	for (int i = 0; i < ilosc; i++) {
		sciana.setSize(sf::Vector2f(*grid, *grid)); sciana.setFillColor(sf::Color(33, 33, 222));
		sciana.setOutlineColor(sf::Color::Black); sciana.setOutlineThickness(1.f);
		sciana.setPosition((*grid) * (i % (*szerokosc)), (*grid) * licznik);
		if (i % (*szerokosc) == (*szerokosc) - 1)
			licznik++;
		poziom.push_back(sciana);
	}
}
void Mapa::draw(){
	for (const auto& sciana : poziom) {
		okno->draw(sciana);
	}
}