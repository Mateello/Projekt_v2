//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include "wrogowie.h"
#include "gracz.h"
#include "okno.h"
void Help();
void Esc(sf::RenderWindow*okno);
int main()
{
	srand(time(NULL));
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	menu.setFramerateLimit(60);

	Interfejs glowne_menu(&menu); glowne_menu.setIntState(true); glowne_menu.setPosition(-100.f,0);
	glowne_menu.setString("Nowa gra","Wyniki","O grze","Wyjscie");//poziomy trudności zmieniają prędkość wrogów i mape

	Interfejs wybor_poziomu(&menu);// wybor_poziomu.setPosition(100.f, 0);
	wybor_poziomu.setString("Poziom 1", "Poziom 2", "Poziom 3", "Powrot");

	Interfejs tab_wynikow(&menu); //tab_wynikow.setPosition(50.f,50.f);
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
			if (event.type = sf::Event::Closed)
				menu.close();
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				Esc(&menu);
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
				Help();
		}
		menu.clear(sf::Color::Black);
		glowne_menu.rysuj();
		wybor_poziomu.rysuj();
		tab_wynikow.rysuj();
		o_grze.rysuj();
		//------------------------------------przy mapce 600x600 zastosować ścianki z kwadratów 30x30 ?????
		//docelowo ziarna wrzucić w tablicae - array, połozyć je na całej mapie równomiernie i przykryć ścianami/usunąć
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (glowne_menu.getIntState() == true)){
			switch (glowne_menu.getIntIndeks()) {
			case 1: {
				 wybor_poziomu.setIntState(true); glowne_menu.setIntState(false); }
				  break;
			case 2: {
				tab_wynikow.setIntState(true); glowne_menu.setIntState(false); }
				  break;
			case 3: {
				  glowne_menu.setIntState(false);  o_grze.setIntState(true); }
				  break;
			case 4: {
				Help(); glowne_menu.setIntState(false); }
				  break;
			}
		}
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (wybor_poziomu.getIntState() == true)) {
			switch (wybor_poziomu.getIntIndeks())
				{
				case 4: {
					wybor_poziomu.setIntState(false); glowne_menu.setIntState(true); }
					break;
				}
			}
		//WybInter(glowne_menu,wybor_poziomu,tab_wynikow,o_grze);
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (o_grze.getIntState() == true) && (o_grze.getIntIndeks() == 4)) {
			glowne_menu.setIntState(true); o_grze.setIntState(false);
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
void WybInter(Interfejs &wybrane, Interfejs& opcja_1, Interfejs& opcja_2, Interfejs& opcja_3 )//będzie zwracać indeks interfejsu który będzie do narysowania
{
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (wybrane.getIntState() == true) && (wybrane.getIntIndeks() == 4)) {
		opcja_3.setIntState(true); wybrane.setIntState(false);
		}
}
void Help(){
	float obr = 0;
	sf::Clock zegar;
	sf::RenderWindow pomoc(sf::VideoMode(400.f, 400.f), "Pomoc");
	sf::Font czcionka; sf::Text tekst;
	czcionka.loadFromFile("Righteous-Regular.ttf");
	tekst.setString("Pomoc"); tekst.setFillColor(sf::Color::Green); tekst.setCharacterSize(50);
	tekst.setPosition(sf::Vector2f(0.f,0.f)); tekst.setFont(czcionka);
	while (pomoc.isOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		sf::Event event;
		while (pomoc.pollEvent(event)){
			if (event.type = sf::Event::Closed){
				pomoc.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				pomoc.close();
			}
		}
		pomoc.clear();
		pomoc.draw(tekst);
		pomoc.display();
		if (zegar.getElapsedTime().asMilliseconds() > 10.0f){
			if ((tekst.getPosition().x < 200.f) && (tekst.getPosition().y < 200.f))
			{tekst.move(0.5f, 1.f); tekst.setRotation(5.f);}
			else
				tekst.move(0.f, 0.f);
			zegar.restart();
		}
	}
}
void Esc(sf::RenderWindow *okno){
	bool wyjdz=false, zostan=false;
	sf::Vector2f wymiar, zakres; zakres.x = 100.f; zakres.y = 80.f;
	sf::RenderWindow Esc(sf::VideoMode(400.f, 400.f), "Czy napewno");
	sf::RectangleShape linia(sf::Vector2f(100.f, 3.f));
	wymiar.x = Esc.getSize().x; wymiar.y = Esc.getSize().y;
	sf::Font czcionka; sf::Text pyt,tak,nie;
	czcionka.loadFromFile("Righteous-Regular.ttf");
	pyt.setString("Napewno chcesz wyjsc?"); pyt.setFillColor(sf::Color::Yellow); pyt.setCharacterSize(32);
	pyt.setPosition(wymiar.x/24,wymiar.y/8); pyt.setFont(czcionka);
	tak.setString("Tak"); tak.setCharacterSize(40); tak.setFont(czcionka); tak.setPosition(wymiar.x/8,wymiar.y/2);
	nie.setString("Nie"); nie.setCharacterSize(40); nie.setFont(czcionka); nie.setPosition((Esc.getSize().x - wymiar.x /4), wymiar.y / 2);

	while (Esc.isOpen())
	{
		sf::Event event;
		while (Esc.pollEvent(event)) {
			if (event.type = sf::Event::Closed) {
				Esc.close();
			}
		}
		Esc.clear();Esc.draw(pyt);
		if ((sf::Mouse::getPosition(Esc).x>tak.getPosition().x)&&(sf::Mouse::getPosition(Esc).x < tak.getPosition().x+zakres.y)&&
			(sf::Mouse::getPosition(Esc).y > tak.getPosition().y)&&(sf::Mouse::getPosition(Esc).y < tak.getPosition().y+zakres.y)){
			tak.setFillColor(sf::Color::Red); tak.setStyle(sf::Text::Underlined || sf::Text::Bold);
			linia.setPosition(nie.getPosition().x - 20.f, nie.getPosition().y + 25.f); wyjdz = true;
			Esc.draw(tak); Esc.draw(nie); Esc.draw(linia);
		}
		else if ((sf::Mouse::getPosition(Esc).x > nie.getPosition().x) && (sf::Mouse::getPosition(Esc).x < nie.getPosition().x + zakres.y) &&
			(sf::Mouse::getPosition(Esc).y > nie.getPosition().y) && (sf::Mouse::getPosition(Esc).y < nie.getPosition().y + zakres.y)){
			nie.setFillColor(sf::Color::Green); nie.setStyle(sf::Text::Underlined || sf::Text::Bold);
			linia.setPosition(tak.getPosition().x - 15.f, tak.getPosition().y + 25.f); zostan = true;
			Esc.draw(tak); Esc.draw(nie); Esc.draw(linia);
		}
		else{
			tak.setFillColor(sf::Color::White); tak.setStyle(sf::Text::Regular); 
			nie.setFillColor(sf::Color::White); nie.setStyle(sf::Text::Regular);
			Esc.draw(tak); Esc.draw(nie);
		}
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && (wyjdz == true))) {
			Esc.close();}//okno->close();}---------------------- ogólnie działa ale wywala instrukcje pinktu przerwania 
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && (zostan == true)))
		Esc.close();
		
		Esc.display();
	}
}