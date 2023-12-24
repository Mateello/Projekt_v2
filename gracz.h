#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>

class Gracz{
	sf::RenderWindow *window;
	sf::Texture *tekstura;
	sf::Sprite *zawodnik;
	sf::Vector2f predkosc;
	sf::Vector2f pozycja;
	sf::String *name;
	sf::Font* czcionka;
	sf::Text* tekst;
public:
	bool deadPlayer;//zmienna odpowowiadaj¹ca za to czy gracz "¿yje" czy nie
	Gracz(sf::RenderWindow *okno);
	~Gracz();
	void update();
	void init();
	void draw();
	sf::String setName(sf::Event e);
	sf::FloatRect getBounds();
	sf::FloatRect bounds;
};
//-------------------------------------------------------------- Zapis do pliku ----------------------------------------------------
struct Dane{
	int punkty,id;
	clock_t start, stop;//zmienne przechowuj¹ce moment rozpoczêcia i zakoñczenia rozgrywki
	double czas_gry;
	char nazwa[20];
};