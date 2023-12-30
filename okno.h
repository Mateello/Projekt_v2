#include <SFML/Graphics.hpp>
#include <iostream>

class Interfejs
{
protected:
	sf::Vector2f otoczkat,wym_obr;//otoczka to prostok�t w kt�rym musi znale�� si� kursor by wybra� opcje, wym to wymiar rysowanego prostok�tu
	sf::RectangleShape* tlo, *t_bounds ;
	sf::Text* t1, * t2 , * t3, * t4;
	sf::Font* czcionka; 
	sf::RenderWindow* okno;
	int *wybor;//zmienna zawieraj�ca numer opcji wybranej przez gracza -> do switcha w g��wnym
	bool *narysowany;//zmienna przechowuj�ca informacje czy interfejs jest w�a�nie widoczny dla gracza
	float* grid;
	void init();
public:
	Interfejs(float *grid,sf::RenderWindow* okno);
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
	sf::Vector2i mousePos;//pozycja myszy
};