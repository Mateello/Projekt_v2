//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>//string stream, do wyświetlania czasu gry, punktów, nazwy gracza
#include<fstream>
#include "wrogowie.h"
#include "gracz.h"
#include "okno.h"

std::stringstream infoGracza(int pkt,int czas, int poziom,int zycie, std::string nazwa);
void Help();
void Esc();
void animacja(sf::Text* koniec, float* grid, sf::Vector2u size);
void Wyjscie(sf::Text *wyjscie, float* grid, sf::Vector2i* m_poz);

int main() {
	srand(time(NULL));

	float gridSizeF = 30.f;//zmienna przechowująca zmienną "siatki" gry od niej będą zależeć wielkość okna, mapy itd
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);//ta sama wartość zmiennej ale jako typ unsinged -> dla pewności posiadania dodatniej wartości
	
	sf::RenderWindow window(sf::VideoMode(gridSizeF * 30, gridSizeF * 25), "PacMan");
	window.setFramerateLimit(60);

	int map_height = (int)window.getSize().y / gridSizeF;
	int map_width = (int)window.getSize().x / gridSizeF;

	Interfejs glowne_menu(&gridSizeF, &window); 
	glowne_menu.setIntState(true); 
	glowne_menu.setPosition(-3 * gridSizeF, 0);
	glowne_menu.setString("Nowa gra", "Wyniki", "O grze", "Wyjscie");

	Interfejs wybor_poziomu(&gridSizeF, &window);
	wybor_poziomu.setString("Poziom 1", "Poziom 2", "Poziom 3", "Powrot");

	Interfejs tab_wynikow(&gridSizeF, &window); 
	tab_wynikow.setCharSize(gridSizeU * 2 / 3);
	tab_wynikow.setString(" ", " ", " ", " Powrot ");
	tab_wynikow.setPosition(-7 * gridSizeF, 5 * gridSizeF);
	//setPosition jest względne do pozycji ustalonej w klasie Interfejs

	Interfejs o_grze(&gridSizeF, &window); bool obw = false; o_grze.setCharSize(gridSizeU * 2 / 3);
	o_grze.setString(
		" Gra zostala stworzona jako podobienstwo PACMAN'a.\n\n Zasady sa takie same jak w PacMan'ie.\n\nUnikaj wrogow,zbieraj punkty."
		, " ", " ", " Powrot ");
	o_grze.setPosition(-7 * gridSizeF, -2 * gridSizeF);

	sf::Clock zegar;//Obiekt mierzący czas

	bool gra = false;
	int poziom = 0, indeks = 0, licznik = 0;//pomocnicze zmienne //int rozgrywki = 0;

	Dane* dane; dane = new Dane;

	Gracz p1(&gridSizeF, &window);//obiekt typu gracz, argumentem jest okno w którym jest rysowany
	Wrog w_1(4, &gridSizeF, &window);
	//----------------------------------------- liczbe która jest poziomem trudności zrobić jako wskaźnik --------------------
	Ziarno pkt(&map_height, &map_width, &gridSizeF, &window);

	Mapa mapka(0, &map_height, &map_width, &gridSizeF, &window);//0 to testowy
	Mapa poziom1(1, &map_height, &map_width, &gridSizeF, &window);
	Mapa poziom2(2, &map_height, &map_width, &gridSizeF, &window);
	Mapa poziom3(3, &map_height, &map_width, &gridSizeF, &window);

	WrogCS ConSh(&gridSizeF, &window);

	std::string linia;//zmienna przechowująca łańcuchy znaków lini odczytanej z pliku

	sf::Text napisy, * koniec, odczytane, nazwa, wynik, * wyjscie, * powrot_menu;//machnąć tu wskaźniki--------------------------------

	koniec = new sf::Text;
	wyjscie = new sf::Text;
	powrot_menu = new sf::Text;

	std::vector<sf::Text> lista, odwrocona_lista;//wektory przechowujące dane odczytane z pliku

	sf::String playerName; playerName.clear();//Łańcuch znaków wpisany przez użytkownika

	sf::Vector2i mysz_poz;// mysz_poz = new sf::Vector2i;

	sf::Font czcionka; czcionka.loadFromFile("Arial.ttf"); 
	napisy.setFont(czcionka);
	napisy.setCharacterSize(gridSizeU * 2 / 3);
	napisy.setFillColor(sf::Color::Magenta);
	napisy.setPosition(0, 0);

	wynik.setCharacterSize(gridSizeU * 2 / 3); 
	wynik.setFont(czcionka);
	wynik.setString("Twoj wynik: "); 
	wynik.setPosition(0, -gridSizeF);

	koniec->setFont(czcionka); 
	koniec->setCharacterSize(2 * gridSizeU);
	koniec->setStyle(sf::Text::Underlined);
	koniec->setPosition(koniec->getGlobalBounds().width, window.getSize().y / 2 - 2 * gridSizeF);

	wyjscie->setFont(czcionka); 
	wyjscie->setCharacterSize(gridSizeU);
	wyjscie->setString("Wyjscie");
	wyjscie->setPosition((window.getSize().x-wyjscie->getGlobalBounds().width)/2, window.getSize().y / 2 +5* wyjscie->getGlobalBounds().height);

	powrot_menu->setFont(czcionka); 
	powrot_menu->setCharacterSize(gridSizeU);
	powrot_menu->setPosition(20 * gridSizeU, 18 * gridSizeU); 
	powrot_menu->setString("Wyjscie");

	odczytane.setCharacterSize(20); 
	odczytane.setFont(czcionka); 
	odczytane.setPosition(2 * gridSizeF, 1 * gridSizeF);
	odczytane.setFillColor(sf::Color::White);

	nazwa.setFont(czcionka);
	nazwa.setCharacterSize(gridSizeU);
	nazwa.setFillColor(sf::Color::White);
	nazwa.setPosition(3 * gridSizeU, 6 * gridSizeU);

	//PĘTLA GRY
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::TextEntered) && (wybor_poziomu.getIntState() == true) && (gra != true)) {
				playerName += event.text.unicode;
				nazwa.setString(playerName);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				Esc();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
				Help();
		}
		if (gra == false) {//wszystkie elementy rysowane związane z interfejsami itp
			//zmnienne aktualizujące pozycję myszki
			glowne_menu.mousePos = sf::Mouse::getPosition(window);
			wybor_poziomu.mousePos = sf::Mouse::getPosition(window);
			tab_wynikow.mousePos = sf::Mouse::getPosition(window);
			o_grze.mousePos = sf::Mouse::getPosition(window);
			// ^^^ zmnienne aktualizujące pozycję myszki ^^^

			window.clear(sf::Color::Black);
			glowne_menu.rysuj();
			wybor_poziomu.rysuj();
			tab_wynikow.rysuj(false);
			o_grze.rysuj(false);

			if (wybor_poziomu.getIntState() == true)
				window.draw(nazwa);

			p1.setName(nazwa.getString());//ustalanie nazwy gracza na wpisaną przez użytkownika

			std::ifstream odczyt;
			odczyt.open("tab.txt", std::ios::in);
			if (odczyt.good() == true) {
				while (getline(odczyt, linia))//(plik z którego odczytujemy, zmienna przechowująca odczytaną linie
				{
					odczytane.setString(linia);
					lista.push_back(odczytane);//przerzucam do wektora pełną linie z pliku
				}
			}
			odczyt.close();

			if (tab_wynikow.getIntState() == true)//rysowanie danych odczytanych z pliku następuje tylko przy wyświetlaniu odpowiedniego interfejsu
			{
				for (int i = 0; i < 20; i++) {
					//przerzucenie danych z końca listy na początek odwróconej listy - 20 to ilość lini mieszczących się w oknie z wypisanymi danymi z pliku
					if (odwrocona_lista.size() < 20) {
						odwrocona_lista.push_back(lista.back());
						lista.pop_back();
					}
					odczytane = odwrocona_lista[i];//tekst przyjmuje wartość z wektora
					odczytane.setPosition(odczytane.getPosition().x, odczytane.getPosition().y + gridSizeF * i);
					if (odczytane.getPosition().y < window.getSize().y - 4 * gridSizeF)
						window.draw(odczytane);//rysowanie odczytanych wartości
				}
			}
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
					glowne_menu.setIntState(false); exit(0); }//menu.close();} jest exit(0) ponieważ zamykanie okna kończyło się błędem
					  break;
				}
			}
			if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (wybor_poziomu.getIntState() == true)) {
				if (playerName.isEmpty()) {//warunek blokujący możliwość wybrania poziomu bez podania nazwy użytkownika
					nazwa.setString("Wpisz nazwe: ");
					if (wybor_poziomu.getIntIndeks() == 4) {
						wybor_poziomu.setIntState(false); glowne_menu.setIntState(true);
					}
				}
				else {
					switch (wybor_poziomu.getIntIndeks()) {
					case 1:w_1.setPoziom(1); gra = true; poziom = 1; break;
					case 2:w_1.setPoziom(2); gra = true; poziom = 2; break;
					case 3:w_1.setPoziom(3); gra = true; poziom = 3; break;
					case 4: {
						wybor_poziomu.setIntState(false); glowne_menu.setIntState(true); }
						  break;
					}
					p1.initTimer();
				}
			}
			if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (tab_wynikow.getIntState() == true) && (tab_wynikow.getIntIndeks() == 4)) {
				glowne_menu.setIntState(true); tab_wynikow.setIntState(false);
			}
			if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (o_grze.getIntState() == true) && (o_grze.getIntIndeks() == 4)) {
				glowne_menu.setIntState(true); o_grze.setIntState(false);
			}
		}
		else{//if(p1.getPlayerState()==true) {//warunek blokujący wyświetlanie się interfejsów i gry w tym samym czasie
			window.clear(sf::Color(20, 20, 20));
			//akutalizowane dane gracza
			napisy.setString(infoGracza(p1.getPunkty(), p1.getCzas(), poziom,p1.zycie, p1.getName()).str());
			//kolizje
			switch (poziom) {//kolizje gracza ze ścianami na każym poziomie trudnośći
			case 0:p1.wall_collision(mapka.wrogowie); break;
			case 1:p1.wall_collision(poziom1.wrogowie); break;
			case 2:p1.wall_collision(poziom2.wrogowie); break;
			case 3:p1.wall_collision(poziom3.wrogowie); break;
			}

			ConSh.setPoz(poziom);//ustawienie poziomu trudności Convex shape'a
			p1.scores_collision(pkt.wrogowie);//"zjadanie" punktów

			switch (poziom) {
			case 0:mapka.setPoints(pkt.wrogowie); break;//kolizje mapy z punktami - jeśli ściana i punkt się stykają punkt jest usuwany
			case 1:poziom1.setPoints(pkt.wrogowie); break;
			case 2:poziom2.setPoints(pkt.wrogowie); break;
			case 3:poziom3.setPoints(pkt.wrogowie); break;
			}

			p1.update();

			mysz_poz = sf::Mouse::getPosition(window);

			if ((p1.zycie >0) && (p1.Win() == true)) {//koniec gry - gracz wygrywa
				koniec->setString("Wygrales!"); 
				koniec->setFillColor(sf::Color::Green);

				napisy.setPosition(2 * gridSizeF, 5 * gridSizeF); 
				napisy.setScale(1.5, 1.5); 
				napisy.setFillColor(sf::Color::Green);

				wynik.setPosition(napisy.getPosition().x, napisy.getPosition().y - gridSizeU);
				wynik.setFillColor(napisy.getFillColor()); 
				wynik.setScale(napisy.getScale());

				window.draw(wynik);
				window.draw(napisy);
				window.draw(*koniec);
				window.draw(*wyjscie);
				
				Wyjscie(wyjscie, &gridSizeF, &mysz_poz);
			}

			else if (p1.getPlayerState() != false) {//warunek trwania gry - gracz żyje i rysowanie elementów gry
				switch (poziom) {
				case 0:mapka.draw(); break;
				case 1:poziom1.draw(); break;
				case 2:poziom2.draw(); break;
				case 3:poziom3.draw(); break;
				}
				p1.draw(); w_1.draw(); pkt.draw(); ConSh.draw();
			}//rysowanie gracza (oraz elemetnów gry),jeśli gracz "żyje"

			else if ((p1.getPlayerState() == false)&&(p1.Win() == false)) {//gra się kończy po śmierci gracza
				koniec->setString("YOU'RE DEAD!"); 
				koniec->setFillColor(sf::Color(255, 0, 0, 128));
				
				napisy.setPosition(2.f * gridSizeF, 5 * gridSizeF);
				napisy.setScale(1.5, 1.5); 
				napisy.setFillColor(sf::Color::Red);
				
				wynik.setPosition(napisy.getPosition().x, napisy.getPosition().y - gridSizeU);
				wynik.setFillColor(napisy.getFillColor()); 
				wynik.setScale(napisy.getScale());

				window.draw(wynik);
				window.draw(napisy);
				window.draw(*koniec);
				window.draw(*wyjscie);

				Wyjscie(wyjscie, &gridSizeF, &mysz_poz);
			}
			if ((p1.zycie!=0)&&((p1.enemy_collision(w_1.wrogowie)==true)||(p1.ConSh_collision(ConSh.getBounds())))) {
				//reset pozycji po stracie jednego życia
				ConSh.setStartPosition();
				w_1.setStartPosition();
				p1.setPosition();
				p1.zycie--;
			}

			if ((p1.getPlayerState() == true)&&(p1.Win() == false)) {
				napisy.setPosition(0, 0);
				napisy.setScale(1, 1);
				napisy.setFillColor(sf::Color::Magenta);
				window.draw(napisy);//rysowanie aktualizowanych danych gracza
			}
			if (koniec->getPosition().x > window.getSize().x)
				++licznik;
			if (licznik == 4)
				exit(0);
			if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {//nieregularny wróg porusza się i obraca 
				ConSh.ruch();
				w_1.ruch();
				if ((p1.Win() == true) || (p1.getPlayerState() == false)) {
					animacja(koniec, &gridSizeF, window.getSize());//animowany napis

				}
				zegar.restart();
			}
		}
		window.display();
		if (((p1.getPlayerState() == false) || (p1.Win() == true)) && (dane->nazwa != p1.getName())) {
			//zapis do pliku danych z gry - pkt,nazwa,poziom,czas gry po przegranej lub wygranej
			dane->nazwa = p1.getName(); 
			dane->punkty = p1.getPunkty();
			dane->czas = p1.getCzas();
			dane->poziom = poziom;
			dane->zycie = p1.zycie;

			std::ofstream wpis; wpis.open("tab.txt", std::ios::out | std::ios::app);
			wpis << "\nNazwa: " << dane->nazwa << "\tPoziom: " << dane->poziom<<"\tZycie: "<<dane->zycie << "\tPkt: " << dane->punkty << "\t\tCzas gry: ";
			if (dane->czas < 10) {
				wpis << "00:0" << dane->czas;
			}
			else if (dane->czas < 60) {
				wpis << "00:" << dane->czas;
			}
			else if ((dane->czas > 59) && (dane->czas % 60 < 10)) {
				wpis << dane->czas << ":0 " << dane->czas / 60 % 60;
			}
			else {
				wpis << dane->czas << ": " << dane->czas / 60 % 60;
			}
			if (dane->zycie != 0)
				wpis << "\tWygrana!";
			else
				wpis << "\tPrzegrana";

			wpis.close();
		}
	}
	delete koniec; delete dane; delete wyjscie; delete powrot_menu;
	return 0;
}
std::stringstream infoGracza(int pkt, int czas,int poziom,int zycie,std::string nazwa) {//funkcja odpowiadająca za przekazanie danych do strumienia "stringów"
	std::stringstream ss;
		ss << "Gracz: " << nazwa <<"\tPoziom: "<<poziom<<"\tZycie: "<<zycie<<"\t";
	if (czas < 10) {
		ss << "Czas: " << "00:0" << czas ; }
	else if (czas < 60) {
		ss << "Czas: " << "00:" << czas;}
	else if ((czas > 59)&&(czas % 60<10)) {
		ss << "Czas: " << czas / 60 % 60 << ":0" << czas % 60 ;}
	else {
		ss << "Czas: " << czas / 60 % 60 << ":" << czas % 60 ;}

	ss << "\tPunkty: " << pkt;;
	return ss;
}
void Help(){//okno pomocy
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
void Esc(){//okno przy naciśnięciu klawisza ESC
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
		koniec->move(7.5f, 0.f);
	else 
		koniec->setPosition(-koniec->getGlobalBounds().width, wymiar.y/2-2*(*grid));
}
void Wyjscie(sf::Text* wyjscie, float* grid,sf::Vector2i *m_poz) {
	sf::Vector2f pozcyja = sf::Vector2f(*m_poz);
	if ((pozcyja.x > wyjscie->getPosition().x)
		&& (pozcyja.x < wyjscie->getPosition().x + wyjscie->getGlobalBounds().width)
		&& (pozcyja.y > wyjscie->getPosition().y)
		&& (pozcyja.y < wyjscie->getPosition().y + wyjscie->getGlobalBounds().height)) {
		wyjscie->setFillColor(sf::Color::Red); wyjscie->setStyle(sf::Text::Underlined);
	}
	else {
		wyjscie->setFillColor(sf::Color::White); wyjscie->setStyle(sf::Text::Regular);
	}
	if ((wyjscie->getFillColor() == sf::Color::Red)&&(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		exit(0);
}