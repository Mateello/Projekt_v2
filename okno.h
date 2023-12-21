#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
//#include "Tlo.cpp"

class Interfejs
{
protected:
	sf::Vector2f otoczkat,odl_bound;
	sf::RectangleShape* tlo, *t_bounds ;
	sf::Text* t1, * t2 , * t3, * t4;
	sf::Font* czcionka; 
	sf::RenderWindow* okno;
	void init();
public:
	Interfejs(sf::RenderWindow* okno);
	~Interfejs();
	void rysuj();
	void setString(std::string napis1, std::string napis2, std::string napis3, std::string napis4);
	int wybor;//zmienna zawierająca numer opcji wybranej przez gracza -> do switcha w głównym
	bool narysowany;//zmienna przechowująca informacje czy interfejs jest właśnie widoczny dla gracza
	sf::Vector2i mousePos;//pozycja myszy
};