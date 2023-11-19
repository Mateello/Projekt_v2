#include <SFML/Graphics.hpp>
#include <iostream>

class Okno
{
	int selectedItemIndeks();//numer w³aœnie wybranego wiersza
	sf::Font czcionka;//zmienna odpowiadaj¹ca za czcionke
	sf::Text tekst[3];//tablica zawieraj¹ca teksty w danej lini - narazie 3
public:
	Okno(float szerokosc,float wysokosc);//konstruktor
	~Okno();

	/*virtual*/ void rysuj(sf::RenderWindow& window);//funkcja rysuj¹ca okno po przkazaniu jej przez wskaŸnik parametrów okna
	void wGore();//przesuwanie siê w gore
	void wDol();//przesuwanie siê w dol
};