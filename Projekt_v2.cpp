//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
//#include "gra.h" - próba zrobienia osobnego folderu z "silnikiem" gry 
#include"okno.h"//podłączenie pliku nagłówkowego odpowiadającego za klasy i metody związane z oknami

int main() 
{
	//INICJALIZACJA SILNIKA GRY (KLASY Gra)
	//Gra gra;//obiekt klasy Gra

	//OKNA - OBIEKTY 
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");

	Okno window(600,600,"nie wiem");

	//WROGOWIE - DOCELOWO ZROBIĆ Z TEGO OSOBNĄ KLASĘ
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

	//OKNA - NA RAZIE OBECNIE PO ZA OSOBNYM FOLDEREM I KLASĄ ------------------------------------ profilaktycznie zostawiam
	/*sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	sf::RenderWindow glowne(sf::VideoMode(400.f, 400.f), "Projekt - PACMAN");
	sf::RenderWindow help(sf::VideoMode(200.f, 200.f), "Help");
	sf::RenderWindow esc(sf::VideoMode(200.f, 200.f), "Opuszczanie gry"); 
	glowne.close(); 
	help.close(); 
	esc.close();*/ 

	//PĘTLA GRY
	while (menu.isOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		sf::Event event;
		while (menu.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close(menu);
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close(menu);
			}
		}
		window.clear(menu);
		window.rysuj(menu);
		window.display(menu);//na obecną chwilę nie udało się załadować czcionki! ----------------------- failed to create the font face !!!!!!!!!!!!!!!!!!!!!!!
	}
	return 0;
}