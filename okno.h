#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
	int MenuWybrane;//numer w�a�nie wybranego wiersza
	sf::Font czcionka;//zmienna odpowiadaj�ca za czcionke
	sf::Text tekst[3];//tablica zawieraj�ca teksty w danej lini - narazie 3
public:
	Menu(float szerokosc,float wysokosc);//konstruktor
	~Menu();

	/*virtual*/ void rysuj(sf::RenderWindow& window);//funkcja rysuj�ca okno po przkazaniu jej przez wska�nik parametr�w okna
	void wGore();//przesuwanie si� w gore
	void wDol();//przesuwanie si� w dol
	int MenuNacisniete() {
		return MenuWybrane;
	}
};