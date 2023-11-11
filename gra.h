#pragma once
#include <SFML/Graphics.hpp>

//klasa dzia�aj�ca jako silnik gry
class Gra
{

	//zmienne wska�nikowe odopowiadaj�ce za okna - wska�niki daltego, �e b�d� chcia� dynamicznie alokowa� te okna - usuwa� je i tworzy� wtedy kiedy potrzebuje
	sf::RenderWindow* menu;
	sf::RenderWindow* glowne;
	sf::RenderWindow* help;
	sf::RenderWindow* esc;

	sf::Event event;//z tego nie robi� zmiennej wska�nikowej i nie inicjalizuje go bo ma domy�ln� inicjalizacj�

	//prywatne metody
	void inicjalizujZmienne();
	void inicjalizujOkna();
public:
	Gra();//konstruktor
	~Gra();//destruktor

	//publiczne metody
	void aktualizuj();
	void wyswietlaj();
};