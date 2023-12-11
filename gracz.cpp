#include "gracz.h"

Gracz::Gracz(sf::RenderWindow& okno)
{
	punkty = 0;
	ZawOtoczka = Zawodnik.getGlobalBounds();

	window.x = okno.getSize().x; window.y = okno.getSize().y;
	tekstura.loadFromFile("pokeball.png");//ze wzglêdu na problem z pacman.png - na razie porzyczê pokeball'a
	Zawodnik.setTexture(tekstura);
	Zawodnik.setScale(sf::Vector2f(0.5f,0.5f));
	Zawodnik.setPosition(window.x / 2, window.y/2 );
	predkosc.x = 0.3f;//niestety na razie dobrae w taki sposób
	predkosc.y = 0.3f;

	std::cout << Zawodnik.getLocalBounds().left;//czemu getGlobalBounds daje 0 ??? ------------------------------
}
sf::Sprite Gracz::getGracz()//funckja zwraca nam sprite'a
{
	return this->Zawodnik;
}
void Gracz::getPunkty(int &pkt)//dostajemy iloœæ punktów danego gracza
{
	pkt = this->punkty;
}
void Gracz::setPunkty(int pkt)//zmiana iloœci punktów gracza
{
	this->punkty+=pkt;
}
void Gracz::kolizja()
{	
	Wrog w; Gracz p;
	/*float dx = (p.pozycja.x + (p.ZawOtoczka.width / 2) - (w.pozycja.x + (w.wrogOtoczka.width / 2))); --------- wersja 2
	float dy = (p.pozycja.y + (p.ZawOtoczka.height / 2) - (w.pozycja.y + (w.wrogOtoczka.height / 2)));
	//dx - szerokoœæ miêdzy œrodkami kó³, dy - wysokoœæ miêdzy œrodkami kó³
	float odleglosc = sqrt((dx * dx) + (dy * dy));//twierdzenie pitagorasa - sprawdzimy odleg³œæ miêdzy okrêgami
	if (odleglosc <= (p.ZawOtoczka.width / 2 + w.wrogOtoczka.width / 2))
	{
		std::cout << "Dzia³a!";
	}*/
	for ( auto& i: w.wrogowie)
	{p.NastepnaPoz = p.ZawOtoczka;
		p.NastepnaPoz.left += p.predkosc.x;
		p.NastepnaPoz.top += p.predkosc.y;
	}
}
void Gracz::update()
{
	kolizja();
	pozycja.x = Zawodnik.getPosition().x; pozycja.y = Zawodnik.getPosition().y;
	//kolizje z œcianami
	if (Zawodnik.getGlobalBounds().left < 0.f){//œciana z lewej
		Zawodnik.setPosition(0.f, Zawodnik.getGlobalBounds().top);
	}
	else if (Zawodnik.getGlobalBounds().left+ Zawodnik.getGlobalBounds().width > window.x){//œciana z prawej
		Zawodnik.setPosition(window.x- Zawodnik.getGlobalBounds().width, Zawodnik.getGlobalBounds().top);
	}
	if (Zawodnik.getGlobalBounds().top < 0.f){//œciana z góry
		Zawodnik.setPosition(Zawodnik.getGlobalBounds().left, 0.f);
	}
	else if (Zawodnik.getGlobalBounds().top + Zawodnik.getGlobalBounds().height > window.y){//œciana z do³u
		Zawodnik.setPosition(Zawodnik.getGlobalBounds().left, window.y- Zawodnik.getGlobalBounds().height);
	}

	//poruszanie graczem
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Zawodnik.move(-predkosc.x,0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Zawodnik.move(predkosc.x, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Zawodnik.move(0.f, -predkosc.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Zawodnik.move(0.f, predkosc.y);
	}
}