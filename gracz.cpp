#include "gracz.h"
#include "wrogowie.h"

Gracz::Gracz(sf::RenderWindow& okno)
{
	punkty = 0;
	Pacman_t.loadFromFile("pokeball.png");//ze wzgl�du na problem z pacman.png - na razie porzycz� pokeball'a
	Pacman.setTexture(Pacman_t);
	Pacman.setPosition(250,250);
	window.x = okno.getSize().x; window.y = okno.getSize().y;
	przesuniecie = 5.f;
}
sf::Sprite Gracz::getGracz()
{
	return Pacman;
}
void Gracz::getPunkty(int &pkt)//dostajemy ilo�� punkt�w danego gracza
{
	pkt = punkty;
}
void Gracz::setPunkty(int pkt)//zmiana ilo�ci punkt�w gracza
{
	punkty+=pkt;
}
void Gracz::getPozycja(sf::Sprite Gracz)
{

}
void Gracz::update()
{
	//kolizje z �cianami

	if (Pacman.getGlobalBounds().left < 0.f){//�ciana z lewej
		Pacman.setPosition(0.f, Pacman.getGlobalBounds().top);
	}
	else if (Pacman.getGlobalBounds().left+Pacman.getGlobalBounds().width > window.x){//�ciana z prawej
		Pacman.setPosition(window.x- Pacman.getGlobalBounds().width, Pacman.getGlobalBounds().top);
	}
	if (Pacman.getGlobalBounds().top < 0.f){//�ciana z g�ry
		Pacman.setPosition(Pacman.getGlobalBounds().left, 0.f);
	}
	else if (Pacman.getGlobalBounds().top + Pacman.getGlobalBounds().height > window.y){//�ciana z do�u
		Pacman.setPosition(Pacman.getGlobalBounds().left, window.y- Pacman.getGlobalBounds().height);
	}

	//poruszanie graczem
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Pacman.move(-przesuniecie,0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Pacman.move(przesuniecie, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Pacman.move(0.f, -przesuniecie);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Pacman.move(0.f, przesuniecie);
	}
}