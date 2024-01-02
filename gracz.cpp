#include "gracz.h"

Gracz::Gracz(float *grid, sf::RenderWindow* window){
	this->window = window; this->grid = grid; init();
}
Gracz::~Gracz(){
	delete grid; delete zawodnik; delete tekstura; delete window;
}
void Gracz::init(){
	t_start = clock();//rozpoczynam odliczanie czasu
	alivePlayer = true; tekstura = new sf::Texture; zawodnik = new sf::Sprite;
	tekstura->loadFromFile("pacman.png");
	zawodnik->setTexture(*tekstura);zawodnik->setScale(sf::Vector2f((*grid)/ tekstura->getSize().x, (*grid)/tekstura->getSize().y ));
	zawodnik->setPosition((window->getSize().x-zawodnik->getGlobalBounds().width) / 2, (window->getSize().y - zawodnik->getGlobalBounds().height) / 2);
	predkosc.x = *grid/8;predkosc.y = *grid/8; punkty = 0;
}
sf::FloatRect Gracz::getBounds(){
	return zawodnik->getGlobalBounds();
}
void Gracz::draw(){
	this->window->draw(*zawodnik);
}
void Gracz::update(){
	pozycja.x = zawodnik->getPosition().x; pozycja.y = zawodnik->getPosition().y;
	//kolizje z œcianami
	if (zawodnik->getGlobalBounds().left < 0.f) {//œciana z lewej
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
		zawodnik->move(-predkosc.x, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		zawodnik->move(predkosc.x, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		zawodnik->move(0.f, -predkosc.y); 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		zawodnik->move(0.f, predkosc.y); 

	if (alivePlayer != false)//koniec odliczania czasu
	t_stop = clock();

}
int Gracz::getPunkty(){
	return punkty;
}
int Gracz::getCzas(){//pobieram iloœæ cykli procesora od narysowania gracza i aktualizuje a¿ do jego œmierci
	float czas = (int)(t_stop - t_start) / CLOCKS_PER_SEC; return czas;
}//jako ¿e typ t_clock pobiera iloœæ cykli procesora w Hz, musimy to podzieliæ przez sta³¹ dla danego urz¹dzenia
bool Gracz::getPlayerState(){
	return alivePlayer;
}
void Gracz::setPosition(float x,float y) {
	zawodnik->setPosition(x, y);
}
void Gracz::wall_collision(std::vector< sf::RectangleShape >& sciany) {
	for (int i = 0; i < sciany.size(); i++) {
		if (sciany[i].getGlobalBounds().intersects(zawodnik->getGlobalBounds())) {
			if ((zawodnik->getGlobalBounds().left < sciany[i].getGlobalBounds().left)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width < sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().top < sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > sciany[i].getGlobalBounds().top))
				zawodnik->setPosition(sciany[i].getGlobalBounds().left - zawodnik->getGlobalBounds().width, zawodnik->getGlobalBounds().top);//kolizja z prawej

			else if ((zawodnik->getGlobalBounds().left > sciany[i].getGlobalBounds().left)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width > sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().top < sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > sciany[i].getGlobalBounds().top))
				zawodnik->setPosition(sciany[i].getGlobalBounds().left + zawodnik->getGlobalBounds().width, zawodnik->getGlobalBounds().top);//kolizja z lewej

			if ((zawodnik->getGlobalBounds().top > sciany[i].getGlobalBounds().top)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().left < sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width > sciany[i].getGlobalBounds().left))
				zawodnik->setPosition(zawodnik->getGlobalBounds().left, sciany[i].getGlobalBounds().top + zawodnik->getGlobalBounds().height );//kolizja z góry

			if ((zawodnik->getGlobalBounds().top < sciany[i].getGlobalBounds().top)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height < sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().left < sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width > sciany[i].getGlobalBounds().left))
				zawodnik->setPosition(zawodnik->getGlobalBounds().left, sciany[i].getGlobalBounds().top - zawodnik->getGlobalBounds().height);
		}
	}
}
void Gracz::enemy_collision(std::vector< sf::RectangleShape >& wrog) {
	for (int i = 0; i < wrog.size(); i++) {
		if (wrog[i].getGlobalBounds().intersects(zawodnik->getGlobalBounds()))
			alivePlayer = false;
	}
}
void Gracz::scores_collision(std::vector< sf::RectangleShape >& pkt) {
	for (int i = 0; i < pkt.size(); i++) {
		if (pkt[i].getGlobalBounds().intersects(zawodnik->getGlobalBounds())) {
			pkt.erase(pkt.begin() + i); punkty++;
		}
	}
	if (pkt.size() == 0)
		wygrana = true;
}
void Gracz::ConSh_collision(sf::FloatRect bounds) {
	if (bounds.intersects(zawodnik->getGlobalBounds()))
		alivePlayer = false;
}
bool Gracz::Win() {
	return wygrana;
}
void Gracz::setName(std::string s) {
	this->nazwa = s;
}
std::string Gracz::getName() {
	return nazwa;
}