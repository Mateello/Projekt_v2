#pragma once
#include <SFML/Graphics.hpp>

//klasa dzia³aj¹ca jako silnik gry
class Gra
{

	//zmienne wskaŸnikowe odopowiadaj¹ce za okna - wskaŸniki daltego, ¿e bêdê chcia³ dynamicznie alokowaæ te okna - usuwaæ je i tworzyæ wtedy kiedy potrzebuje
	sf::RenderWindow* menu;
	sf::RenderWindow* glowne;
	sf::RenderWindow* help;
	sf::RenderWindow* esc;

	sf::Event event;//z tego nie robiê zmiennej wskaŸnikowej i nie inicjalizuje go bo ma domyœln¹ inicjalizacjê

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