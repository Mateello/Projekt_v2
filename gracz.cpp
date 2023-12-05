#include "gracz.h"

Gracz::Gracz(float x_in, float y_in, float okno_x, float okno_y)
{
	Pacman_t.loadFromFile("pokeball.png");//ze wzglêdu na problem z pacman.png - na razie porzyczê pokeball'a
	Pacman.setTexture(Pacman_t);
	Pacman.setPosition(250,250);
	window.x = okno_x; window.y = okno_y;
	przesuniecie = 5.f;
}
sf::Sprite Gracz::getGracz()
{
	return Pacman;
}
void Gracz::update()
{
	//kolizje z œcianami

	if (Pacman.getGlobalBounds().left < 0.f){//œciana z lewej
		Pacman.setPosition(0.f, Pacman.getGlobalBounds().top);
	}
	else if (Pacman.getGlobalBounds().left+Pacman.getGlobalBounds().width > window.x){//œciana z prawej
		Pacman.setPosition(window.x- Pacman.getGlobalBounds().width, Pacman.getGlobalBounds().top);
	}
	if (Pacman.getGlobalBounds().top < 0.f){//œciana z góry
		Pacman.setPosition(Pacman.getGlobalBounds().left, 0.f);
	}
	else if (Pacman.getGlobalBounds().top + Pacman.getGlobalBounds().height > window.y){//œciana z do³u
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