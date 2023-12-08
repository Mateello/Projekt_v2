//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<vector>
#include "gracz.h" //osobny folder z klasą i jej metodami - lda przejrzystości kodu
#include "wrogowie.h"//osobny plik z klasą z wrogami
//#include"okno.h" --- będzie odkomentowane jak naprawię
//#include "gra.h" - próba zrobienia osobnego folderu z "silnikiem" gry

int main()
{
	srand(time(NULL));//dla odmiany taki generator liczb pseudolosowych

	//INICJALIZACJA SILNIKA GRY (KLASY Gra)
	//Gra gra;//obiekt klasy Gra

	//OKNA - OBIEKTY -------------------------------------------------------------DOCELOWO WSZYSTKO ZWIĄZANE Z OKNAMI ZOSTANIE PRZERZUCONE DO INNYCH PLIKÓW
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	menu.setFramerateLimit(60);
	//Menu MenuGlowne(menu.getSize().x, menu.getSize().y);

	sf::Clock zegar;//tworzymy obiekt mierzący czas
	float obrot = 0.f;
	float width = menu.getSize().x;//szerokość okna
	float height = menu.getSize().y;//wysokość okna
	float rozmiar_wrogow = 15;

	Gracz P1(menu);

	Wrog* w_1; w_1 = new Wrog(rozmiar_wrogow, 3,menu);//coś nie działa - nie rysuje się wróg
	Wrog* w_2; w_2 = new Wrog(rozmiar_wrogow, 4,menu);

	Ziarna ziarenka(50,15,menu);

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

	wrog_4.setPosition(sf::Vector2f(width/2,50.f));

	sf::Vector2f pozycja;
	pozycja.x = wrog_4.getPosition().x; pozycja.y = wrog_4.getPosition().y;
	sf::Vector2f przesuniecie; 

	sf::Color wr_kl (sf::Color::Red);//kolor wrogów
	wrog_4.setFillColor(wr_kl);

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
		P1.update();
		menu.clear(sf::Color::Black);
		menu.draw(wrog_4);
		ziarenka.rysuj(menu);
		w_1->rysuj(menu);
		w_2->rysuj(menu);
		menu.draw(P1.getGracz());
		menu.display();
		if (zegar.getElapsedTime().asMilliseconds() > 10.0f)//-----------------nieregularny wróg porusza się i obraca 
		{
			float V_w4 = rand()%7+3;//prędkość niereguralnego wroga - pseudolosowa
			wrog_4.setRotation(obrot+=7.5f);

			pozycja = wrog_4.getPosition();

			if (pozycja.x > width/2+100.f)
			przesuniecie.x = -2.f;
			if (pozycja.x < width / 2 - 100.f)
			przesuniecie.x = 3.f;
			if (pozycja.y > height-50.f)
			przesuniecie.y = -1*V_w4;
			if(pozycja.y <60.f)
			przesuniecie.y = V_w4;

			wrog_4.move(sf::Vector2f(przesuniecie));

			zegar.restart();
		}
	}
	delete w_1; delete w_2;
	return 0;
}