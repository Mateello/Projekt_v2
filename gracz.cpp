#include "gracz.h"

Gracz::Gracz(sf::RenderWindow *window)
{
	this->window = window; init();
}
Gracz::~Gracz()
{
	delete tekst; delete czcionka; delete name; delete zawodnik; delete tekstura; delete window;
}
void Gracz::init()
{
	deadPlayer = true; name = new sf::String; czcionka = new sf::Font; tekst = new sf::Text;tekstura = new sf::Texture; zawodnik = new sf::Sprite;
	tekstura->loadFromFile("pokeball.png");//ze wzglêdu na problem z pacman.png - na razie porzyczê pokeball'a
	zawodnik->setTexture(*tekstura);zawodnik->setScale(sf::Vector2f(0.5f, 0.5f));
	zawodnik->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	czcionka->loadFromFile("Arial.ttf"); tekst->setString(*name);
	predkosc.x = 5.f;predkosc.y = 5.f;//niestety na razie dobrae w taki sposób
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
sf::String Gracz::setName(sf::Event e)//przed tym bêdzie if który wywo³a funckjê czyli - if(wpisujemy text) to wywo³a siê ta funkcja
{
	if (e.text.unicode < 128)
	{
		*name += e.text.unicode;
	}
	return *name;
}