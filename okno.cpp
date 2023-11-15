#include "okno.h"
#include <iostream>

Okno::Okno(float szerokosc, float wysokosc, std::string name)//konstruktor
{
	if (!czcionka.loadFromFile("Righteous - Regular.ttf"))//�adowanie czcionki z pliku
	{
		std::cout << "Nie udalo sie zaladowac czcionki!" << "\n";//napis wyskakuj�cy w oknie konsoli gdy nie za�adujemy czcionki
	}

	tekst[0].setFont(czcionka);
	tekst[0].setFillColor(sf::Color::White);
	tekst[0].setString("Graj");
	tekst[0].setPosition(sf::Vector2f(szerokosc/2, wysokosc/4/*(masymalna ilo�� wierszy +1)*1 */));//pozycja linijki tekstu

	tekst[1].setFont(czcionka);
	tekst[1].setFillColor(sf::Color::Green);
	tekst[1].setString("Opcje");
	tekst[1].setPosition(sf::Vector2f(szerokosc / 2, wysokosc / 2/*(masymalna ilo�� wierszy +1)*2*/));//pozycja linijki tekstu

	tekst[2].setFont(czcionka);
	tekst[2].setFillColor(sf::Color::Blue);
	tekst[2].setString("Wyjscie");
	tekst[2].setPosition(sf::Vector2f(szerokosc / 2, wysokosc / 3/*(masymalna ilo�� wierszy +1)*3*/));//pozycja linijki tekstu
}
Okno::~Okno()//destruktor
{

}
void Okno::rysuj(sf::RenderWindow& window)
{
	for (int i = 0; i < 3/*maksymalna ilo�� wierszy*/; i++)
	{
		window.draw(tekst[i]);//rysowanie po koleji linijek tekstu
	}
}
void Okno::clear(sf::RenderWindow& window){
	window.clear();
}
void Okno::display(sf::RenderWindow& window){
	window.display();
}
void Okno::close(sf::RenderWindow& window)
{
	window.close();
}