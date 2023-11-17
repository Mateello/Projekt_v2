//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
//#include "gra.h" - próba zrobienia osobnego folderu z "silnikiem" gry 
//#include"okno.h" - później będzie podłączone

int main() 
{
	//INICJALIZACJA SILNIKA GRY (KLASY Gra)
	//Gra gra;//obiekt klasy Gra

	//OKNA - OBIEKTY -------------------------------------------------------------DOCELOWO WSZYSTKO ZWIĄZANE Z OKNAMI ZOSTANIE PRZERZUCONE DO INNYCH PLIKÓW
	sf::VideoMode menu_wymiary = sf::VideoMode(600.f,600.f);
	sf::RenderWindow menu(menu_wymiary, "Menu");
	float szerokosc = menu_wymiary.width;
	float wysokosc = menu_wymiary.height;

	sf::Clock zegar;//tworzymy obiekt mierzący czas
	float obrot = 0.f;

	sf::Font czcionka;
	sf::Text tekst[3];

	if (!czcionka.loadFromFile("Righteous-Regular.ttf"))//ładowanie czcionki z pliku
	{
		std::cout << "Nie udalo sie zaladowac czcionki!" << "\n";//napis wyskakujący w oknie konsoli gdy nie załadujemy czcionki
	}

	tekst[0].setFont(czcionka);
	tekst[0].setFillColor(sf::Color(255, 255, 255));
	tekst[0].setString("Graj");
	tekst[0].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / 4/*(masymalna ilość wierszy +1)*1 */));//pozycja linijki tekstu

	tekst[1].setFont(czcionka);
	tekst[1].setFillColor(sf::Color(255, 0, 0));
	tekst[1].setString("Opcje");
	tekst[1].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / 2.7/*(masymalna ilość wierszy +1)*2*/));//pozycja linijki tekstu

	tekst[2].setFont(czcionka);
	tekst[2].setFillColor(sf::Color(0, 255, 0));
	tekst[2].setString("Wyjscie");
	tekst[2].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / 2/*(masymalna ilość wierszy +1)*3*/));//pozycja linijki tekstu

	//WROGOWIE - DOCELOWO ZROBIĆ Z TEGO OSOBNĄ KLASĘ
	sf::CircleShape wrog_1(100.f);
	sf::CircleShape wrog_2(100.f, 3);
	sf::RectangleShape wrog_3(sf::Vector2f(100.f, 100.f));
	sf::ConvexShape wrog_4;

	wrog_4.setPointCount(8);
	wrog_4.setPoint(0, sf::Vector2f(0.f, 0.f));
	wrog_4.setPoint(1, sf::Vector2f(10.f, -30.f));
	wrog_4.setPoint(2, sf::Vector2f(20.f, 0.f));
	wrog_4.setPoint(3, sf::Vector2f(50.f, 10.f));
	wrog_4.setPoint(4, sf::Vector2f(20.f, 20.f));
	wrog_4.setPoint(5, sf::Vector2f(10.f, 50.f));
	wrog_4.setPoint(6, sf::Vector2f(0.f, 20.f));
	wrog_4.setPoint(7, sf::Vector2f(-30.f, 10.f));

	wrog_4.setPosition(sf::Vector2f(50.f,50.f));

	sf::Vector2f pozycja;
	pozycja.x = wrog_4.getPosition().x; pozycja.y = wrog_4.getPosition().y;
	sf::Vector2f przesuniecie; 

	sf::Color wr_kl (sf::Color::Red);//kolor wrogów
	wrog_1.setFillColor(wr_kl); wrog_2.setFillColor(wr_kl); wrog_3.setFillColor(wr_kl); wrog_4.setFillColor(wr_kl);
	sf::Color wr_outline(sf::Color(00, 0, 255));//kolor otoczki
	wrog_1.setOutlineColor(wr_outline); wrog_2.setOutlineColor(wr_outline); wrog_3.setOutlineColor(wr_outline);
	wrog_1.setOutlineThickness(-5.f); wrog_2.setOutlineThickness(-5.f); wrog_3.setOutlineThickness(-5.f);

	//PĘTLA GRY
	while (menu.isOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		sf::Event event;
		while (menu.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				menu.close();
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					menu.close();
			}
		}
		menu.clear();
		menu.draw(wrog_4);

		for (int i = 0; i < 3/*maksymalna ilość wierszy*/; i++)
		{
			menu.draw(tekst[i]);//rysowanie po koleji linijek tekstu
		}
		menu.display();
		if (zegar.getElapsedTime().asMilliseconds() > 10.0f)//-----------------nieregularny wróg porusza się i obraca 
		{
			wrog_4.setRotation(obrot+=2.5f);

			pozycja = wrog_4.getPosition();

			if (pozycja.x > 500.f)
			przesuniecie.x = -2.f;
			if (pozycja.x <100.f)
			przesuniecie.x = 3.f;
			if (pozycja.y > 500.f)
			przesuniecie.y = -1.5f;
			if(pozycja.y <100.f)
			przesuniecie.y = 2.5f;

			wrog_4.move(sf::Vector2f(przesuniecie));

			zegar.restart();
		}
	}
	return 0;
}