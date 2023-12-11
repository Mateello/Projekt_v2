﻿//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<vector>
#include "gracz.h" //osobny folder z klasą i jej metodami - lda przejrzystości kodu
//#include"okno.h" --- będzie odkomentowane jak naprawię
//#include "gra.h" - próba zrobienia osobnego folderu z "silnikiem" gry
int main()
{
	srand(time(NULL));//dla odmiany taki generator liczb pseudolosowych
	//INICJALIZACJA SILNIKA GRY (KLASY Gra)
	//Gra gra;//obiekt klasy Gra

	//OKNA - OBIEKTY -------------------------------------------------------------DOCELOWO WSZYSTKO ZWIĄZANE Z OKNAMI ZOSTANIE PRZERZUCONE DO INNYCH PLIKÓW
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	//Menu MenuGlowne(menu.getSize().x, menu.getSize().y);

	sf::Clock zegar;//tworzymy obiekt mierzący czas
	float obrot = 0.f;
	float width = menu.getSize().x;//szerokość okna
	float height = menu.getSize().y;//wysokość okna

	Gracz p1(menu);

	Wrog *w_1=new Wrog(3,15, 4,menu);//ilość, rozmiar,ilość wierzchołków, okno

	Ziarna *male = new Ziarna(5, 5, 15, menu);//dynamiczna alkoacja ziaren, ilość,średnica,wartość punktowa, okno w którym rysujemy
	Ziarna sr(3,10,5,menu);
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

	wrog_4.setPosition(sf::Vector2f((width + wrog_4.getGlobalBounds().left)/2, - wrog_4.getGlobalBounds().top));
	sf::Vector2f przesuniecie;
	sf::Vector2f pozycjaw4;
	wrog_4.setFillColor(sf::Color::Red);

	bool deadPlayer=true;//zmienna odpowowiadająca za to czy gracz "żyje" czy nie
	//PĘTLA GRY
	while (menu.isOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		sf::Event event;
		while (menu.pollEvent(event))
		{
			if (event.type = sf::Event::Closed)
			{
				menu.close();
			}
		}
		p1.update();
		menu.clear(sf::Color::Black);
		male->rysuj(menu); //sr.rysuj(menu); duze.rysuj(menu);//rysowanie zairen menu.rysuj(sr);
		w_1->rysuj(menu);menu.draw(wrog_4);//rysowanie wrogów
		if(deadPlayer!=false)
		menu.draw(p1.getGracz());//rysowanie gracza

		menu.display();

		if (zegar.getElapsedTime().asMilliseconds() > 10.0f)//-----------------nieregularny wróg porusza się i obraca 
		{
			float V_w4 = rand() % 3;//prędkość niereguralnego wroga - pseudolosowa
			wrog_4.setRotation(obrot += 7.5f);
			pozycjaw4.x = wrog_4.getPosition().x; pozycjaw4.y = wrog_4.getPosition().y;

			//Kolizje------------------------------------
			if (wrog_4.getGlobalBounds().intersects(p1.getBounds()))//nie działa - getGlobalbounds zwraca 0 0
			deadPlayer = false;

			if (pozycjaw4.x > (width + wrog_4.getGlobalBounds().left)/2)
			przesuniecie.x = -2.f;
			if (pozycjaw4.x < (width - wrog_4.getGlobalBounds().left)/2)
			przesuniecie.x = 3.f;
			if (pozycjaw4.y > (height - wrog_4.getGlobalBounds().top/12))//liczba 12 dobrana eksperymentalnie
			przesuniecie.y = -1*V_w4;
			if(pozycjaw4.y < (height + wrog_4.getGlobalBounds().top)/12)//liczba 12 dobrana eksperymentalnie
			przesuniecie.y = V_w4;

			wrog_4.move(sf::Vector2f(przesuniecie));

			zegar.restart();
		}
	}
	delete male; delete w_1;
	return 0;
}