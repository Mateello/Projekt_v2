//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include "wrogowie.h"
#include "gracz.h"
#include "okno.h"
void GameOver();
int main()
{
	srand(time(NULL));
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	menu.setFramerateLimit(60);

	Interfejs glowne_menu(&menu);
	glowne_menu.setString("Nowa gra","Wyniki","O grze","Wyjscie");//poziomy trudności zmieniają prędkość wrogów i mape

	Interfejs wybor_poziomu(&menu);
	wybor_poziomu.setString("Poziom 1", "Poziom 2", "Poziom 3", "Powrot");

	Interfejs tab_wynikow(&menu);
	tab_wynikow.setString(" 1 ", " 2 ", " 3 ", " Powrot ");

	Interfejs o_grze(&menu); bool obw = false; o_grze.setCharSize(20);
	o_grze.setString(" Gra zostala stworzona na podstawie PACMAN'a. ", " Fajna jest dobrze dziala ", " Gra na 5 ", " Powrot ");
	o_grze.setPosition(-200.f,-50.f);

	sf::Clock zegar;//tworzymy obiekt mierzący czas

	std::vector<Dane> zapis;//wektro który będzie przechowywał i zapisywał do pliku dane o grze - czas,nazwe,indeks,punkty

	Gracz p1(&menu);//obiekt typu gracz, argumentem jest okno w którym jest rysowany
	Wrog w_1(3,&menu);
	int kolizja = -1;
	Ziarno pkt(4,&menu);
	WrogCS ConSh(&menu);

	//PĘTLA GRY
	while (menu.isOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		glowne_menu.mousePos = sf::Mouse::getPosition(menu);wybor_poziomu.mousePos = sf::Mouse::getPosition(menu);
		tab_wynikow.mousePos = sf::Mouse::getPosition(menu);o_grze.mousePos = sf::Mouse::getPosition(menu);
		//zmnienne aktualizujące pozycję myszki
		sf::Event event;
		while (menu.pollEvent(event))
		{
			if (event.type = sf::Event::Closed){
				menu.close();
			}
			if (event.type == sf::Event::TextEntered)
			{
				p1.setName(event);
			}
		}
		menu.clear(sf::Color::Black);
		glowne_menu.setIntState(true); glowne_menu.rysuj();

		//------------------------------------przy mapce 600x600 zastosować ścianki z kwadratów 30x30 ?????
		//docelowo ziarna wrzucić w tablicae - array, połozyć je na całej mapie równomiernie i przykryć ścianami/usunąć
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (glowne_menu.getIntState() == true))
		glowne_menu.podtrzymanie = glowne_menu.getIntIndeks();
		switch (glowne_menu.podtrzymanie) {
		case 1: {
			wybor_poziomu.setIntState(true); wybor_poziomu.rysuj(); glowne_menu.setIntState(false); }
			  break;
		case 2: {
			tab_wynikow.setIntState(true); tab_wynikow.rysuj(); glowne_menu.setIntState(false); }
			  break;
		case 3:{
			o_grze.setIntState(true); o_grze.rysuj(); glowne_menu.setIntState(false);}
			break;
		case 4: {
			GameOver(); glowne_menu.setIntState(false); }
			break;
		}

		//kolizje
		/**for (int i = 0; i < w_1.wrogowie.size(); i++) {
			if (w_1.wrogowie[i].getGlobalBounds().intersects(p1.getBounds()))
				kolizja = i;
		}
		if (kolizja != -1)//byłoby zero ale wektory są zapisywane od 0
			p1.deadPlayer = false;

		for (int i = 0; i < pkt.wrogowie.size(); i++) {
			if (pkt.wrogowie[i].getGlobalBounds().intersects(p1.getBounds())) {
				pkt.wrogowie.erase(pkt.wrogowie.begin() + i);
			}
			if (pkt.wrogowie.size() == 0)
				std::cout << "Wygrana!";
		}*/

		/**p1.update();

		if (p1.deadPlayer != false)
			p1.draw();//rysowanie gracza,jeśli "żyje"
		else{
			menu.close();
			GameOver();
		}*/
		//w_1.draw(); pkt.draw(); ConSh.draw();//rysowanie wroga typu ConvexShape

		menu.display();
		//-----------------nieregularny wróg porusza się i obraca 
		/**if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {
			if (ConSh.getBounds().intersects(p1.getBounds()))//Kolizja z convexShapem ]
			p1.deadPlayer = false;
			ConSh.ruch();
			w_1.ruch();
			zegar.restart();}*/
	}
	return 0;
}
int WybInter(int wyb, bool narysowane)//uzupelnić argumenty wywołania funkcji----------------------------------------------
//będzie zwracać indeks interfejsu który będzie do narysowania
{
	if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (narysowane == true))
		return wyb;
}
void GameOver(){
	float obr = 0;
	sf::Clock zegar;
	sf::RenderWindow gameover(sf::VideoMode(400.f, 400.f), "Koniec Gry!");
	sf::Font czcionka; sf::Text tekst;
	czcionka.loadFromFile("Righteous-Regular.ttf");
	tekst.setString("Koniec gry!"); tekst.setFillColor(sf::Color::Red); tekst.setCharacterSize(50);
	tekst.setPosition(sf::Vector2f(0.f,0.f)); tekst.setFont(czcionka);
	tekst.setStyle(sf::Text::Bold | sf::Text::Underlined);
	while (gameover.isOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		sf::Event event;
		while (gameover.pollEvent(event)){
			if (event.type = sf::Event::Closed){
				gameover.close();
			}
		}
		gameover.clear();
		gameover.draw(tekst);
		gameover.display();
		if (zegar.getElapsedTime().asMilliseconds() > 10.0f){
			if ((tekst.getPosition().x < 200.f) && (tekst.getPosition().y < 200.f))
			{tekst.move(0.5f, 1.f); tekst.setRotation(5.f);}
			else
				tekst.move(0.f, 0.f);
			zegar.restart();
		}
	}
}