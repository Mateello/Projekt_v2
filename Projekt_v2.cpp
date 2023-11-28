//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include "gracz.h" //osobny folder z klasą i jej metodami - lda przejrzystości kodu
#include "wrogowie.h"//osobny plik z klasą z wrogami
//#include"okno.h" --- będzie odkomentowane jak naprawię
//#include "gra.h" - próba zrobienia osobnego folderu z "silnikiem" gry

int main() 
{
	//INICJALIZACJA SILNIKA GRY (KLASY Gra)
	//Gra gra;//obiekt klasy Gra

	//OKNA - OBIEKTY -------------------------------------------------------------DOCELOWO WSZYSTKO ZWIĄZANE Z OKNAMI ZOSTANIE PRZERZUCONE DO INNYCH PLIKÓW
	sf::RenderWindow menu(sf::VideoMode(600.f,600.f),"Menu");
	//Menu MenuGlowne(menu.getSize().x, menu.getSize().y);
	sf::Font czcionka;
	sf::Text tekst[3];

	if (!czcionka.loadFromFile("Righteous-Regular.ttf"))//ładowanie czcionki z pliku
	{
		std::cout << "Nie udalo sie zaladowac czcionki!" << "\n";//napis wyskakujący w oknie konsoli gdy nie załadujemy czcionki
	}

	tekst[0].setFont(czcionka);
	tekst[0].setFillColor(sf::Color::White);
	tekst[0].setString("Graj");
	tekst[0].setCharacterSize(60);
	tekst[0].setPosition(200, 100);//pozycja linijki tekstu

	tekst[1].setFont(czcionka);
	tekst[1].setFillColor(sf::Color::White);
	tekst[1].setString("Pomoc");
	tekst[1].setCharacterSize(40);
	tekst[1].setPosition(200, 250);

	tekst[2].setFont(czcionka);
	tekst[2].setFillColor(sf::Color::White);
	tekst[2].setString("Wyjscie");
	tekst[2].setCharacterSize(40);
	tekst[2].setPosition(200, 400);

	sf::Clock zegar;//tworzymy obiekt mierzący czas
	float obrot = 0.f;

	Gracz P1(100, 100, 250, 250);

	/*sf::Font czcionka;
	sf::Text tekst[3];*/

	//WROGOWIE - DOCELOWO ZROBIĆ Z TEGO OSOBNĄ KLASĘ
	/*sf::CircleShape wrog_1(100.f);
	sf::CircleShape wrog_2(100.f, 3);
	sf::RectangleShape wrog_3(sf::Vector2f(100.f, 100.f));*/
	float width = menu.getSize().x;
	float height = menu.getSize().y;

	wrog *w_1= new wrog(50,0, width, height);
	wrog *w_2=new wrog(50, 3, width, height);
	wrog *w_3=new wrog(50, 4, width, height);
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
			/*if (event.type = sf::Event::KeyReleased)
			{
				if ((event.key.code == sf::Keyboard::Up)|| (event.key.code == sf::Keyboard::W))//jeśli na klawiaturze nacisnę strzałkę w górę lub W wywołuje metodę "wGore"
				{
					MenuGlowne.wGore();
				}
				if ((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S))//jeśli na klawiaturze nacisnę strzałkę w dół lub S wywołuje metodę "wDol"
				{
					MenuGlowne.wDol();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					sf::RenderWindow glowne(sf::VideoMode(800.f, 800.f), "Projekt - PACMAN");
					sf::RenderWindow help(sf::VideoMode(800.f, 800.f), "Pomoc");

				}
			}*/
			
		}
		menu.clear(sf::Color::Black);
		//MenuGlowne.rysuj(menu);//obiekt MenuGlowne rysuje okno menu - a dokładniej na nim to co jest zawarte w obiekcie
		//menu.draw(wrog_4);
		w_1->rysuj(menu);
		w_2->rysuj(menu);
		w_3->rysuj(menu);
		//menu.draw(P1.getGracz());
		for (int i = 0; i < 3/*maksymalna ilość wierszy*/; i++)
		{
			//menu.draw(tekst[i]);//rysowanie po koleji linijek tekstu
		}
		menu.display();
		if (zegar.getElapsedTime().asMilliseconds() > 10.0f)//-----------------nieregularny wróg porusza się i obraca 
		{
			wrog_4.setRotation(obrot+=5.f);

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
	delete w_1;delete w_2;delete w_3;
	return 0;
}