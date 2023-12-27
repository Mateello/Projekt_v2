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
	float grid, czas_gry;
	clock_t t_start, t_stop;//zmienne przechowuj¹ce iloœæ cykli procesora od narysowania do usuniecia gracza
	int punkty;
public:
	bool deadPlayer,narysowany;//zmienna odpowowiadaj¹ca za to czy gracz "¿yje" czy nie
	Gracz(float grid,sf::RenderWindow *okno);
	~Gracz();
	void update();
	void init();
	void draw();
	void addPunkty();
	int getPunkty();
	float getCzas();
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