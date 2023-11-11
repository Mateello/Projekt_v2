#include"gra.h"
//METODY PUBLICZNE KLASY GRA
void Gra::aktualizuj()
{

}
void Gra::wyswietlaj()
{

}
//METODY PRYWATNE KLASY GRA
void Gra::inicjalizujZmienne()//inicjalizowanie zmiennych prywatnych klasy gra - silnika gry, tak ¿eby mo¿naby³o ich u¿ywaæ
{
	this->menu = nullptr;//nullpointer - wska¿niki wskazuj¹ na wartoœæ NULL
	this->glowne = nullptr;
	this->help= nullptr;
	this->esc = nullptr;
}
void Gra::inicjalizujOkna()
{
	this->menu=new sf::RenderWindow(sf::VideoMode(600.f, 600.f), "Menu");//dynamicznie zaalokowane okno
	this->glowne = new sf::RenderWindow (sf::VideoMode(400.f, 400.f), "Projekt-PACMAN");
	this->help = new sf::RenderWindow (sf::VideoMode(200.f, 200.f), "Pomoc");
	this->esc = new sf::RenderWindow (sf::VideoMode(200.f, 200.f), "Opuszczanie gry");
}

Gra::Gra()//konstruktor
{
	this->inicjalizujZmienne();
	this->inicjalizujOkna();
}
Gra::~Gra()//destruktor
{
	delete this->menu;//usuwam daynamicznie zaalokowane okna
	delete this->glowne;
	delete this->help;
	delete this->esc;
}