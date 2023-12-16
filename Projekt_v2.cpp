//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include "wrogowie.h"
#include "gracz.h"
int main()
{
	//OKNA - Interfejsy OBIEKTY -------------------------------------------------------------DOCELOWO WSZYSTKO ZWIĄZANE Z OKNAMI ZOSTANIE PRZERZUCONE DO INNYCH PLIKÓW
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	menu.setFramerateLimit(60);

	sf::Clock zegar;//tworzymy obiekt mierzący czas

	Gracz p1(&menu);//obiekt typu gracz, argumentem jest okno w którym jest rysowany

	int max_ilosc_wrogow;
	std::vector<Wrog> wrogowie;//wektor z klasy Wrog 

	WrogCS ConSh(&menu);

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
		ConSh.draw();//rysowanie wroga typu ConvexShape

		if (p1.deadPlayer != false){
			p1.draw();//rysowanie gracza,jeśli "żyje"
		}
		if (p1.deadPlayer == true)

		//p1.deadPlayer=p1.kolizje(w_1.wrogowie);//to samo wychodzi 
		/**p1.deadPlayer = w_1.kolizje(p1.getBounds());
		if (pkt.kolizje(p1.getBounds())==false)
		p1.punkty++;*/

		menu.display();

		if (zegar.getElapsedTime().asMilliseconds() > 10.0f)//-----------------nieregularny wróg porusza się i obraca 
		{
			if (ConSh.getBounds().intersects(p1.getBounds()))//Kolizja z convexShapem
			p1.deadPlayer = false;

			ConSh.ruch();
			zegar.restart();
		}
	}
	return 0;
}