#include "gracz.h"

Gracz::Gracz(sf::RenderWindow *window)
{
	this->window = window; init();
}
Gracz::~Gracz()
{
	delete zawodnik; delete tekstura; delete window;
}
void Gracz::init()
{
	deadPlayer = true; punkty = 0;
	tekstura = new sf::Texture;
	tekstura->loadFromFile("pokeball.png");//ze wzglêdu na problem z pacman.png - na razie porzyczê pokeball'a
	zawodnik = new sf::Sprite;
	zawodnik->setTexture(*tekstura);zawodnik->setScale(sf::Vector2f(0.5f, 0.5f));
	zawodnik->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	predkosc.x = 5.f;//niestety na razie dobrae w taki sposób
	predkosc.y = 5.f; 
	bounds = zawodnik->getGlobalBounds();
}
sf::FloatRect Gracz::getBounds()
{
	return zawodnik->getGlobalBounds();
}
void Gracz::draw()
{
	this->window->draw(*zawodnik);
}
void Gracz::update()
{
	pozycja.x = zawodnik->getPosition().x; pozycja.y = zawodnik->getPosition().y;
	//kolizje z œcianami
	if (zawodnik->getGlobalBounds().left < 0.f){//œciana z lewej
		zawodnik->setPosition(0.f, zawodnik->getGlobalBounds().top);
	}
	else if (zawodnik->getGlobalBounds().left+ zawodnik->getGlobalBounds().width > window->getSize().x){//œciana z prawej
		zawodnik->setPosition(window->getSize().x - zawodnik->getGlobalBounds().width, zawodnik->getGlobalBounds().top);
	}
	if (zawodnik->getGlobalBounds().top < 0.f){//œciana z góry
		zawodnik->setPosition(zawodnik->getGlobalBounds().left, 0.f);
	}
	else if (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > window->getSize().y){//œciana z do³u
		zawodnik->setPosition(zawodnik->getGlobalBounds().left, window->getSize().y - zawodnik->getGlobalBounds().height);
	}

	//poruszanie graczem
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		zawodnik->move(-predkosc.x,0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		zawodnik->move(predkosc.x, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		zawodnik->move(0.f, -predkosc.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		zawodnik->move(0.f, predkosc.y);
	}
}
bool Gracz::kolizje(std::vector<sf::RectangleShape> W)
{
	for (int i = 0; i < W.size(); i++)//std::vector<sf::RectangleShape>::iterator i = wrogowie.begin(); i != wrogowie.end();i++
	{
		if (W[i].getGlobalBounds().intersects(zawodnik->getGlobalBounds()))
			return false;
		else
			return true;
	}
}