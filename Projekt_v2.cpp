//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>//string stream, do wyświetlania czasu gry, punktów, nazwy gracza
#include<fstream>
#include "wrogowie.h"
#include "gracz.h"
#include "okno.h"

std::stringstream infoGracza(int pkt,int czas);
void Help();
void Esc(sf::RenderWindow *okno);
void animacja(sf::Text* koniec, float* grid, sf::Vector2u size);
int main(){
	srand(time(NULL));
	float gridSizeF=30.f;//zmienna przechowująca zmienną "siatki" gry od niej będą zależeć wielkość okna, mapy itd
	unsigned gridSizeU=static_cast<unsigned>(gridSizeF);//ta sama wartość zmiennej ale jako typ unsinged - napewno dodatni
	sf::RenderWindow menu(sf::VideoMode(gridSizeF*30, gridSizeF * 25), "PacMan");
	menu.setFramerateLimit(60);

	int map_height = (int)menu.getSize().y / gridSizeF;//mapa będzie kwadratowa dlatego tylko jeden wymiar
	int map_width = (int)menu.getSize().x / gridSizeF;

	Interfejs glowne_menu(&gridSizeF,&menu); glowne_menu.setIntState(true); glowne_menu.setPosition(-3*gridSizeF,0);
	glowne_menu.setString("Nowa gra", "Wyniki", "O grze", "Wyjscie");

	Interfejs wybor_poziomu(&gridSizeF ,&menu);
	wybor_poziomu.setString("Poziom 1", "Poziom 2", "Poziom 3", "Powrot");

	Interfejs tab_wynikow(&gridSizeF, &menu); tab_wynikow.setCharSize(gridSizeU * 2 / 3);
	tab_wynikow.setString(" ", " ", " ", " Powrot "); tab_wynikow.setPosition(-7 * gridSizeF, -2 * gridSizeF);

	Interfejs o_grze(&gridSizeF ,&menu); bool obw = false; o_grze.setCharSize(gridSizeU * 2 / 3);
	o_grze.setString(
	" Gra zostala stworzona jako podobienstwo PACMAN'a.\n Zasady sa takie same jak w PacMan'ie.\nUnikaj wrogow,zbieraj punkty."
		"\nCzas jest ograniczony, na skonczenie gry jest 5 minut"," ", " ", " Powrot ");
	o_grze.setPosition(-7*gridSizeF,-2*gridSizeF);

	sf::Clock zegar;//tworzymy obiekt mierzący czas

	bool gra = false;
	
	Dane* dane; dane = new Dane;
	
	Gracz p1(&gridSizeF,&menu);//obiekt typu gracz, argumentem jest okno w którym jest rysowany
	Wrog w_1(4,&gridSizeF,&menu);
	//----------------------------------------- liczbe która jest poziomem trudności zrobić jako wskaźnik --------------------
	Ziarno pkt(&map_height, &map_width,&gridSizeF,&menu);
	Mapa mapka(0,&map_height, &map_width, &gridSizeF, &menu);//0 to testowy
	Mapa poziom1(1,&map_height, &map_width, &gridSizeF, &menu);
	Mapa poziom2(2,&map_height, &map_width, &gridSizeF, &menu);
	Mapa poziom3(3,&map_height, &map_width, &gridSizeF, &menu);
	int poziom = 0;
	WrogCS ConSh(&menu);
	std::string odczytaj;
	sf::Text napisy,*koniec, odczytane;
	koniec = new sf::Text;
	sf::Font czcionka; czcionka.loadFromFile("Arial.ttf"); napisy.setFont(czcionka);
	napisy.setCharacterSize(gridSizeU*2/3); napisy.setFillColor(sf::Color::Cyan); napisy.setPosition(0, 0);
	koniec->setFont(czcionka); koniec->setCharacterSize(2*gridSizeU); koniec->setStyle(sf::Text::Underlined); 
	koniec->setPosition(koniec->getGlobalBounds().width, menu.getSize().y /2-2*gridSizeF);
	odczytane.setCharacterSize(20); odczytane.setFont(czcionka); odczytane.setPosition(150, 50); odczytane.setFillColor(sf::Color::Black);
	//PĘTLA GRY
	while (menu.isOpen())//jeśli gra (silnik gry) będzie działać, okna będą wyświetlane
	{
		glowne_menu.mousePos = sf::Mouse::getPosition(menu); wybor_poziomu.mousePos = sf::Mouse::getPosition(menu);
		tab_wynikow.mousePos = sf::Mouse::getPosition(menu); o_grze.mousePos = sf::Mouse::getPosition(menu);
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
		tab_wynikow.rysuj(false);
		o_grze.rysuj(false);
		std::ifstream odczyt("tab.txt");
		if (odczyt.good() == false)
			std::cout << "nie znaleziono pliku";
		else {
			while (getline(odczyt, odczytaj))
				odczytane.setString(odczytaj);
		}
		if(tab_wynikow.getIntState()==true)
			menu.draw(odczytane);
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (glowne_menu.getIntState() == true)) {
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
				glowne_menu.setIntState(false); exit(0); }//menu.close();}//działa ale zakomentowane jest żeby wyjatek nie wyskakiwał
				  break;
			}
		}
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (wybor_poziomu.getIntState() == true)) {
			switch (wybor_poziomu.getIntIndeks()) {
			case 1:w_1.setPoziom(1); gra = true; poziom = 1; break;
			case 2:w_1.setPoziom(2); gra = true; poziom = 2; break;
			case 3:w_1.setPoziom(3); gra = true; poziom = 3; break;
			case 4: {
				wybor_poziomu.setIntState(false); glowne_menu.setIntState(true); }
				  break;
			}
		}
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (tab_wynikow.getIntState() == true) && (tab_wynikow.getIntIndeks() == 4)) {
			glowne_menu.setIntState(true); tab_wynikow.setIntState(false);
		}
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (o_grze.getIntState() == true) && (o_grze.getIntIndeks() == 4)) {
			glowne_menu.setIntState(true); o_grze.setIntState(false);
		}
		if (gra == true) {
			menu.clear(sf::Color::Black);
			//aktualnie wyświetlane napisy
			napisy.setString(infoGracza(p1.getPunkty(), p1.getCzas()).str());
			//kolizje
			switch (poziom) {
			case 0:p1.wall_collision(mapka.wrogowie); break;
			case 1:p1.wall_collision(poziom1.wrogowie); break;
			case 2:p1.wall_collision(poziom2.wrogowie); break;
			case 3:p1.wall_collision(poziom3.wrogowie); break;
			}
			p1.enemy_collision(w_1.wrogowie);
			p1.scores_collision(pkt.wrogowie);
			p1.ConSh_collision(ConSh.getBounds());
			switch (poziom) {
			case 0:mapka.setPoints(pkt.wrogowie); break;
			case 1:poziom1.setPoints(pkt.wrogowie); break;
			case 2:poziom2.setPoints(pkt.wrogowie); break;
			case 3:poziom3.setPoints(pkt.wrogowie); break;
			}
			p1.update();
			if ((p1.getPlayerState() != false) && (p1.Win() == true)) {//koniec gry - gracz wygrywa
				koniec->setString("Wygrales!"); koniec->setFillColor(sf::Color::Green);
				menu.draw(*koniec);
			}
			else if (p1.getPlayerState() != false) {
				switch (poziom) {
				case 0:mapka.draw(); break;
				case 1:poziom1.draw(); break;
				case 2:poziom2.draw(); break;
				case 3:poziom3.draw(); break;
				}
				p1.draw(); w_1.draw(); pkt.draw(); ConSh.draw();
			}//rysowanie gracza (oraz elemetnów gry),jeśli gracz "żyje"

			else if ((p1.getPlayerState() == false))
			{//gra się kończy po śmierci gracza
				koniec->setString("YOU'RE DEAD!"); koniec->setFillColor(sf::Color(255, 0, 0, 128));
				menu.draw(*koniec);
			}

			menu.draw(napisy);

			if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {//nieregularny wróg porusza się i obraca 
				ConSh.ruch();
				w_1.ruch();
				if ((p1.Win() == true) || (p1.getPlayerState() == false))
					animacja(koniec, &gridSizeF, menu.getSize());
				zegar.restart();
			}
		}
		menu.display();
		if ((p1.getPlayerState() == false) || (p1.Win() == true)) {
			dane->nazwa = " "; dane->punkty = p1.getPunkty(); dane->czas = p1.getCzas(); dane->poziom = poziom;
			std::ofstream wpis("tab.txt");
			wpis << "Nazwa: " << dane->nazwa <<"\tPoziom: "<<dane->poziom << "\tPkt: " << dane->punkty << "\tT: " << dane->czas << "s" << "\n";
			wpis.close();	
		}
	}
	delete koniec; delete dane;
	return 0;
}
std::stringstream infoGracza(int pkt, int czas) {std::stringstream ss;
	if (czas < 10) {
		ss << "Czas: " << "00:0" << czas <<"\t" << "Punkty: " << pkt ; }
	else if (czas < 60) {
		ss << "Czas: " << "00:" << czas << "\t" << "Punkty: " << pkt;}
	else if ((czas > 59)&&(czas % 60<10)) {
		ss << "Czas: " << czas / 60 % 60 << ":0" << czas % 60 << "\t" << "Punkty: " << pkt;}
	else {
		ss << "Czas: " << czas / 60 % 60 << ":" << czas % 60 << "\t"  << "Punkty: " << pkt;}
	return ss;
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
			Esc.close(); exit(0);//teraz działa jak marzenie
		}//okno->close();}//---------------------- ogólnie działa ale wywala instrukcje pinktu przerwania 
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && (zostan == true)))
		Esc.close();
		
		Esc.display();
	}
}
void animacja(sf::Text* koniec, float *grid,sf::Vector2u size) {
	sf::Vector2f wymiar =sf::Vector2f(size);
	if ((koniec->getPosition().x < wymiar.x))// && (koniec->getPosition().y < size.y - 2 * koniec->getGlobalBounds().top)) {
		koniec->move(5.f, 0.f);
	else 
		koniec->setPosition(-koniec->getGlobalBounds().width, wymiar.y/2-2*(*grid));
}