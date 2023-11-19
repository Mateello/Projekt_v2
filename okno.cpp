#include "okno.h"
#include <iostream>

Okno::Okno(float szerokosc, float wysokosc)//konstruktor
{
	if (!czcionka.loadFromFile("Righteous-Regular.ttf"))//³adowanie czcionki z pliku
	{
		std::cout << "Nie udalo sie zaladowac czcionki!" << "\n";//napis wyskakuj¹cy w oknie konsoli gdy nie za³adujemy czcionki
	}

	tekst[0].setFont(czcionka);
	tekst[0].setFillColor(sf::Color(255,255,255));
	tekst[0].setString("Graj");
	tekst[0].setPosition(sf::Vector2f(szerokosc/3, wysokosc/4/*(masymalna iloœæ wierszy +1)*1 */));//pozycja linijki tekstu

	tekst[1].setFont(czcionka);
	tekst[1].setFillColor(sf::Color(255, 0, 0));
	tekst[1].setString("Opcje");
	tekst[1].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / 2.7/*(masymalna iloœæ wierszy +1)*2*/));//pozycja linijki tekstu

	tekst[2].setFont(czcionka);
	tekst[2].setFillColor(sf::Color(0, 255, 0));
	tekst[2].setString("Wyjscie");
	tekst[2].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / 2/*(masymalna iloœæ wierszy +1)*3*/));//pozycja linijki tekstu
}
Okno::~Okno()//destruktor
{

}
void Okno::rysuj(sf::RenderWindow& window)
{
	for (int i = 0; i < 3/*maksymalna iloœæ wierszy*/; i++)
	{
		window.draw(tekst[i]);//rysowanie po koleji linijek tekstu
	}
}