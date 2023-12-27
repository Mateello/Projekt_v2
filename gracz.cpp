#include "gracz.h"

Gracz::Gracz(float grid, sf::RenderWindow* window){
	this->window = window; this->grid = grid; init();
}
Gracz::~Gracz(){
	t_stop = clock(); delete tekst; delete czcionka; delete name; delete zawodnik; delete tekstura; delete window;
}
void Gracz::init(){
	t_start = clock();//rozpoczynam odliczanie czasu -- obecnie odliczanie zacznie si� od inicjalizacji gracza ---------------------------- DO POPRAWY
	deadPlayer = true; name = new sf::String; czcionka = new sf::Font; tekst = new sf::Text;tekstura = new sf::Texture; zawodnik = new sf::Sprite;
	tekstura->loadFromFile("pokeball.png");//ze wzgl�du na problem z pacman.png - na razie porzycz� pokeball'a
	zawodnik->setTexture(*tekstura);zawodnik->setScale(sf::Vector2f(0.5f, 0.5f));
	zawodnik->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	czcionka->loadFromFile("Arial.ttf"); tekst->setString(*name);
	predkosc.x = 5.f;predkosc.y = 5.f;//niestety na razie dobrae w taki spos�b
	bounds = zawodnik->getGlobalBounds(); punkty = 0;
}
sf::FloatRect Gracz::getBounds(){
	return zawodnik->getGlobalBounds();
}
void Gracz::draw(){
	this->window->draw(*zawodnik);
}
void Gracz::update(){
	pozycja.x = zawodnik->getPosition().x; pozycja.y = zawodnik->getPosition().y;
	//kolizje z �cianami
	if (zawodnik->getGlobalBounds().left < 0.f){//�ciana z lewej
		zawodnik->setPosition(0.f, zawodnik->getGlobalBounds().top);
	}
	else if (zawodnik->getGlobalBounds().left+ zawodnik->getGlobalBounds().width > window->getSize().x){//�ciana z prawej
		zawodnik->setPosition(window->getSize().x - zawodnik->getGlobalBounds().width, zawodnik->getGlobalBounds().top);
	}
	if (zawodnik->getGlobalBounds().top < 0.f){//�ciana z g�ry
		zawodnik->setPosition(zawodnik->getGlobalBounds().left, 0.f);
	}
	else if (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > window->getSize().y){//�ciana z do�u
		zawodnik->setPosition(zawodnik->getGlobalBounds().left, window->getSize().y - zawodnik->getGlobalBounds().height);
	}

	//poruszanie graczem
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		zawodnik->move(-predkosc.x,0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		zawodnik->move(predkosc.x, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		zawodnik->move(0.f, -predkosc.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		zawodnik->move(0.f, predkosc.y);
	}
	if(deadPlayer!=false)
	t_stop = clock();
}
void Gracz::addPunkty() {
	punkty++;
}
int Gracz::getPunkty(){
	return punkty;
}
float Gracz::getCzas(){//pobieram ilo�� cykli procesora od narysowania gracza i aktualizuje a� do jego �mierci
	float czas = (t_stop - t_start) / CLOCKS_PER_SEC; return czas;
}//jako �e typ t_clock pobiera ilo�� cykli procesora w Hz, musimy to podzieli� przez sta�� dla danego urz�dzenia