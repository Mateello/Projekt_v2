#include <SFML/Graphics.hpp>
#include "gra.h"

int main() 
{
	//INICJALIZACJA SILNIKA GRY (KLASY Gra)
	Gra gra;//obiekt klasy Gra

	//WROGOWIE - DOCELOWO ZROBIĆ Z TEGO KLASE
	sf::CircleShape wrog_1(100.f);
	sf::CircleShape wrog_2(100.f, 3);
	sf::RectangleShape wrog_3(sf::Vector2f(150.f, 100.f));
	sf::ConvexShape wrog_4;
	wrog_4.setPointCount(5);
	wrog_4.setPoint(0, sf::Vector2f(0.f, 0.f));
	wrog_4.setPoint(1, sf::Vector2f(30.f, 10.f));
	wrog_4.setPoint(2, sf::Vector2f(30.f, 50.f));
	wrog_4.setPoint(3, sf::Vector2f(20.f, 50.f));
	wrog_4.setPoint(4, sf::Vector2f(0.f, 70.f));

	sf::Color wr_kl (sf::Color::Red);//kolor wrogów
	wrog_1.setFillColor(wr_kl); wrog_2.setFillColor(wr_kl); wrog_3.setFillColor(wr_kl); wrog_4.setFillColor(wr_kl);
	sf::Color wr_outline(sf::Color::Yellow);//kolor otoczki
	wrog_1.setOutlineColor(wr_outline); wrog_2.setOutlineColor(wr_outline); wrog_3.setOutlineColor(wr_outline); wrog_4.setOutlineColor(wr_outline);
	wrog_1.setOutlineThickness(-5.f); wrog_2.setOutlineThickness(-5.f); wrog_3.setOutlineThickness(-5.f); wrog_4.setOutlineThickness(-5.f);

	//PĘTLA GRY
	while (gra.getWindowIsOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		//aktualizowanie stanu gry
		gra.aktualizuj();

		//wyświetlanie zawartości
		gra.wyswietlaj();
	}
	return 0;
}