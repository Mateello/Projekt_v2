#pragma once
#include <SFML/Graphics.hpp>

//klasa dzia�aj�ca jako silnik gry
class Gra
{	
	//zmienne wska�nikowe odopowiadaj�ce za okna - wska�niki daltego, �e b�d� chcia� dynamicznie alokowa� te okna - usuwa� je i tworzy� wtedy kiedy potrzebuje
	/*sf::RenderWindow* menu;
	sf::RenderWindow* glowne;--------------na wszelki tak, �eby mie� jak by�o wcze�niej
	sf::RenderWindow* help;
	sf::RenderWindow* esc;*/

	sf::VideoMode videoMode;
	sf::RenderWindow *okno;
	std::string nazwa;

	sf::Event event;//z tego nie robi� zmiennej wska�nikowej i nie inicjalizuje go bo ma domy�ln� inicjalizacj�

	//prywatne metody
	void inicjalizujZmienne();
	void inicjalizujMenu();
	void inicjalizujGlowne();
	void inicjalizujHelp();
	void inicjalizujEsc();
public:
	Gra();//konstruktor
	~Gra();//destruktor

	//akcesory
	const bool getWindowIsOpen()const;//funckja odpowiadaj�ca za otwieranie okna

	//publiczne metody
	void pollEvents();

	void aktualizuj();
	void wyswietlaj();
};