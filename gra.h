#pragma once
#include <SFML/Graphics.hpp>

//klasa dzia³aj¹ca jako silnik gry
class Gra
{	
	//zmienne wskaŸnikowe odopowiadaj¹ce za okna - wskaŸniki daltego, ¿e bêdê chcia³ dynamicznie alokowaæ te okna - usuwaæ je i tworzyæ wtedy kiedy potrzebuje
	/*sf::RenderWindow* menu;
	sf::RenderWindow* glowne;--------------na wszelki tak, ¿eby mieæ jak by³o wczeœniej
	sf::RenderWindow* help;
	sf::RenderWindow* esc;*/

	sf::VideoMode videoMode;
	sf::RenderWindow *okno;
	std::string nazwa;

	sf::Event event;//z tego nie robiê zmiennej wskaŸnikowej i nie inicjalizuje go bo ma domyœln¹ inicjalizacjê

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
	const bool getWindowIsOpen()const;//funckja odpowiadaj¹ca za otwieranie okna

	//publiczne metody
	void pollEvents();

	void aktualizuj();
	void wyswietlaj();
};