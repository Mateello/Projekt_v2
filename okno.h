#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
//#include "Tlo.cpp"

class Interfejs
{
protected:
	sf::Vector2f otoczkat;
	sf::RectangleShape* tlo, *t_bounds ;
	sf::Text* t1, * t2 , * t3, * t4;
	sf::Font* czcionka; 
	sf::RenderWindow* okno;
	int *wybor;//zmienna zawieraj¹ca numer opcji wybranej przez gracza -> do switcha w g³ównym
	bool *narysowany;//zmienna przechowuj¹ca informacje czy interfejs jest w³aœnie widoczny dla gracza
	void init();
public:
	Interfejs(sf::RenderWindow* okno);
	~Interfejs();
	void rysuj();
	void rysuj(bool obw);
	void setIntIndeks(int n);
	int getIntIndeks();
	void setIntState(bool s);//ustawianie stanu interfejsu -> true - narysowany; false - nienarysowany
	bool getIntState();
	void setCharSize(int size);
	void setString(std::string napis1, std::string napis2, std::string napis3, std::string napis4);
	void setPosition(float przesuniecie_x, float przesuniecie_y);
	int podtrzymanie;
	sf::Vector2i mousePos;//pozycja myszy
};