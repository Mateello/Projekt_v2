//ARiSS 3 Sem, s194336 Projekt - "PACMAN"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>//string stream, do wyświetlania czasu gry, punktów, nazwy gracza
#include<array>
#include "wrogowie.h"
#include "gracz.h"
#include "okno.h"

int kolizje_w(std::vector<sf::RectangleShape> &w, sf::FloatRect b);//kolizje z wrogami
int kolizje_pkt(std::vector<sf::RectangleShape> &p, sf::FloatRect b);//kolizje z punktami
void kolizje_walls(std::vector<sf::RectangleShape>& sciany,std::vector<sf::RectangleShape> &wrog, sf::FloatRect b);//kolizje gracza i wrogów z ścianami
std::stringstream infoGracza(int pkt,int czas);
void Help();
void Esc(sf::RenderWindow*okno);
int main(){
	srand(time(NULL));
	float gridSizeF=30.f,obr=0;//zmienna przechowująca zmienną "siatki" gry od niej będą zależeć wielkość okna, mapy itd
	unsigned gridSizeU=static_cast<unsigned>(gridSizeF);//ta sama wartość zmiennej ale jako typ unsinged - napewno dodatni
	sf::RenderWindow menu(sf::VideoMode(gridSizeF*30, gridSizeF * 25), "PacMan");
	menu.setFramerateLimit(60);

	int map_height = (int)menu.getSize().y / gridSizeF;//mapa będzie kwadratowa dlatego tylko jeden wymiar
	int map_width = (int)menu.getSize().x / gridSizeF;

	Interfejs glowne_menu(&menu); glowne_menu.setIntState(true); glowne_menu.setPosition(-3*gridSizeF,0);
	glowne_menu.setString("Nowa gra","Wyniki","O grze","Wyjscie");//poziomy trudności zmieniają prędkość wrogów i mape

	Interfejs wybor_poziomu(&menu);
	wybor_poziomu.setString("Poziom 1", "Poziom 2", "Poziom 3", "Powrot");

	Interfejs tab_wynikow(&menu);
	tab_wynikow.setString(" 1 ", " 2 ", " 3 ", " Powrot ");

	Interfejs o_grze(&menu); bool obw = false; o_grze.setCharSize(20);
	o_grze.setString(" Gra zostala stworzona na podstawie PACMAN'a ", " Fajna jest dobrze dziala ", " Gra na 5 ", " Powrot ");
	o_grze.setPosition(-7*gridSizeF,-2*gridSizeF);

	sf::Clock zegar;//tworzymy obiekt mierzący czas

	std::vector<Dane> zapis;//wektro który będzie przechowywał i zapisywał do pliku dane o grze - czas,nazwe,indeks,punkty
	
	Gracz p1(&gridSizeF,&menu);//obiekt typu gracz, argumentem jest okno w którym jest rysowany
	Wrog w_1(3,&gridSizeF,&menu);
	Ziarno pkt(&map_height, &map_width,&gridSizeF,&menu);
	Mapa test(&map_height, &map_width, &gridSizeF, &menu);
	WrogCS ConSh(&menu);
	int ilosc = pkt.wrogowie.size();//początkowa ilość punktów (i maksymalna) ------------------------------------------------------------

	sf::Text napisy,koniec; sf::Font czcionka; czcionka.loadFromFile("Arial.ttf"); napisy.setFont(czcionka);
	napisy.setCharacterSize(20); napisy.setFillColor(sf::Color::Cyan); napisy.setPosition(gridSizeF, gridSizeF);
	koniec.setFont(czcionka); koniec.setCharacterSize(50); koniec.setStyle(sf::Text::Underlined); koniec.setFillColor(sf::Color(255, 0, 0, 128));
	koniec.setPosition(0, 0); koniec.setString("YOU'RE DEAD");

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
		//glowne_menu.rysuj();
		//wybor_poziomu.rysuj(); 
		//tab_wynikow.rysuj(); 
		//o_grze.rysuj(); 
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
				glowne_menu.setIntState(false); }// menu.close(); }//działa ale zakomentowane jest żeby wyjatek nie wyskakiwał
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
		if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)) == true) && (o_grze.getIntState() == true) && (o_grze.getIntIndeks() == 4)){
			glowne_menu.setIntState(true); o_grze.setIntState(false);}
		//aktualnie wyświetlane napisy
		napisy.setString(infoGracza(p1.getPunkty(), p1.getCzas()).str());
		//kolizje
		if (kolizje_w(w_1.wrogowie, p1.getBounds()) != -1)
			;// p1.killPlayer();
		p1.update();
		

		if ((p1.getPlayerState() != false) && (kolizje_pkt(pkt.wrogowie, p1.getBounds())==false)) {
			koniec.setString("Wygrales!"); koniec.setFillColor(sf::Color::Green); menu.draw(koniec);
		}
		else if (p1.getPlayerState() != false) {
			p1.draw(); w_1.draw(); pkt.draw(); ConSh.draw();
			if (kolizje_pkt(pkt.wrogowie, p1.getBounds()) >0)
				p1.setPunkty(ilosc, pkt.wrogowie.size());
		}//rysowanie gracza (oraz elemetnów gry),jeśli gracz "żyje"
		else if ((p1.getPlayerState() == 0))
			menu.draw(koniec);
		test.draw();
		menu.draw(napisy);
		menu.display();
		//-----------------nieregularny wróg porusza się i obraca 
		if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {
			if (ConSh.getBounds().intersects(p1.getBounds()))//Kolizja z convexShapem 
				;// p1.killPlayer();
			ConSh.ruch();
			w_1.ruch();
			if ((koniec.getPosition().x < menu.getSize().x) &&
				(koniec.getPosition().y < (menu.getSize().y -2* koniec.getGlobalBounds().top)))
				koniec.move(0.5f, 1.f), koniec.setRotation(obr+=2.f);
			else
				koniec.move(0.f, 0.f), koniec.setScale(2,2);
			zegar.restart();}
	}
	return 0;
}
int kolizje_w(std::vector<sf::RectangleShape> &w,sf::FloatRect b){
	int kolizja = -1;
	for (int i = 0; i < w.size(); i++) {
		if (w[i].getGlobalBounds().intersects(b))
			kolizja = i;}
	return kolizja;
}
int kolizje_pkt( std::vector<sf::RectangleShape> &p, sf::FloatRect b) {
	for (int i = 0; i < p.size(); i++) {
		if (p[i].getGlobalBounds().intersects(b)) {
			p.erase(p.begin() + i); return 1;}
	}
	if (p.size() == 0) {
		 return 0;}
}
void kolizje_walls(std::vector<sf::RectangleShape>& sciany, std::vector<sf::RectangleShape>& wrog, sf::FloatRect b) {

}
std::stringstream infoGracza(int pkt, int czas) {std::stringstream ss;

	if (czas < 10) {
		ss << "Punkty: " << pkt << "\n" << "Czas: " << "00:0" << czas;}
	else if (czas < 60) {
		ss << "Punkty: " << pkt << "\n" << "Czas: "<<"00:" << czas;}
	else if ((czas > 59)&&(czas % 60<10)) {
		ss << "Punkty: " << pkt << "\n" << "Czas: " << czas / 60 % 60 << ":0" << czas % 60;}
	else {
		ss << "Punkty: " << pkt << "\n" << "Czas: " << czas / 60 % 60 << ":" << czas % 60;}
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
			Esc.close();
		}//, okno->close();}//---------------------- ogólnie działa ale wywala instrukcje pinktu przerwania 
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && (zostan == true)))
		Esc.close();
		
		Esc.display();
	}
}