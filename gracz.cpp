#include "gracz.h"

Gracz::Gracz(float *grid, sf::RenderWindow* window){
	this->window = window; this->grid = grid; init();
}
Gracz::~Gracz(){
	delete grid; delete zawodnik; delete tekstura; delete window;
}
void Gracz::init(){
	alivePlayer = true; tekstura = new sf::Texture; zawodnik = new sf::Sprite;
	tekstura->loadFromFile("zgory-2.png"); zycie = 3;
	zawodnik->setTexture(*tekstura);zawodnik->setScale(sf::Vector2f((*grid)/ tekstura->getSize().x, (*grid)/tekstura->getSize().y ));
	setPosition();predkosc.x = *grid/8;predkosc.y = *grid/8; punkty = 0;
	punkt.loadFromFile("song089.wav"); punktS.setBuffer(punkt);
	wrog.loadFromFile("wybuch — kopia.wav"); wrogS.setBuffer(wrog);
}
sf::FloatRect Gracz::getBounds(){
	return zawodnik->getGlobalBounds();
}
void Gracz::draw(){
	this->window->draw(*zawodnik);
}
void Gracz::update() {
	predkosc.x = *grid / 8; predkosc.y = *grid / 8;
	pozycja.x = zawodnik->getPosition().x; pozycja.y = zawodnik->getPosition().y;
	//kolizje z oknem/otoczk¹ gry
	if (zawodnik->getGlobalBounds().left < *grid) {
		zawodnik->setPosition((*grid), zawodnik->getGlobalBounds().top);
	}
	else if (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width > window->getSize().x - (*grid)) {//œciana z prawej
		zawodnik->setPosition(window->getSize().x - zawodnik->getGlobalBounds().width - (*grid), zawodnik->getGlobalBounds().top);
	}
	if (zawodnik->getGlobalBounds().top < *grid) {//œciana z góry
		zawodnik->setPosition(zawodnik->getGlobalBounds().left, (*grid));
	}
	else if (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > window->getSize().y - (*grid)) {//œciana z do³u
		zawodnik->setPosition(zawodnik->getGlobalBounds().left, window->getSize().y - zawodnik->getGlobalBounds().height - (*grid));
	}

	//poruszanie graczem
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		zawodnik->move(-predkosc.x, 0.f);
		tekstura->loadFromFile("lewo-2.png");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		zawodnik->move(predkosc.x, 0.f);
		tekstura->loadFromFile("prawo-2.png");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		zawodnik->move(0.f, -predkosc.y);
		tekstura->loadFromFile("wgore-2.png");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		zawodnik->move(0.f, predkosc.y);
		tekstura->loadFromFile("wdol-2.png");
	}

	if ((alivePlayer != false))// || (wygrana == true))//koniec odliczania czasu
	t_stop = clock();

	if (zycie == 0)
		alivePlayer = false;
}
int Gracz::getPunkty(){
	return punkty;
}
void Gracz::initTimer() {
	t_start = clock();//rozpoczynam odliczanie czasu
}
void Gracz::stopTimer() {
	t_stop = clock();// clock();//rozpoczynam odliczanie czasu
}
int Gracz::getCzas(){//pobieram iloœæ cykli procesora od narysowania gracza i aktualizuje a¿ do jego œmierci
	float czas = (t_stop - t_start) / CLOCKS_PER_SEC; return czas;
}//jako ¿e typ t_clock pobiera iloœæ cykli procesora w Hz, musimy to podzieliæ przez sta³¹ dla danego urz¹dzenia
bool Gracz::getPlayerState(){
	return alivePlayer;
}
void Gracz::resetLive() {
	alivePlayer = true;
}
void Gracz::resetScores() {
	punkty = 0;
}
void Gracz::setPosition(float x,float y) {
	zawodnik->setPosition(x, y);
}
void Gracz::setPosition() {
	zawodnik->setPosition((window->getSize().x - zawodnik->getGlobalBounds().width) / 2, (window->getSize().y - zawodnik->getGlobalBounds().height) / 2);
}
void Gracz::wall_collision(std::vector< sf::RectangleShape >& sciany) {
	for (int i = 0; i < sciany.size(); i++) {
		if (sciany[i].getGlobalBounds().intersects(zawodnik->getGlobalBounds())) {
			if ((zawodnik->getGlobalBounds().left < sciany[i].getGlobalBounds().left)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width < sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().top < sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > sciany[i].getGlobalBounds().top))
			{
				zawodnik->setPosition(sciany[i].getGlobalBounds().left - zawodnik->getGlobalBounds().width, zawodnik->getGlobalBounds().top);//kolizja z prawej
				predkosc.x = 0;
			}
			else if ((zawodnik->getGlobalBounds().left > sciany[i].getGlobalBounds().left)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width > sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().top < sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > sciany[i].getGlobalBounds().top))
			{
				zawodnik->setPosition(sciany[i].getGlobalBounds().left + zawodnik->getGlobalBounds().width, zawodnik->getGlobalBounds().top);//kolizja z lewej
				predkosc.x = 0;
			}
			else if ((zawodnik->getGlobalBounds().top > sciany[i].getGlobalBounds().top)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height > sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().left < sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width > sciany[i].getGlobalBounds().left))
			{
				zawodnik->setPosition(zawodnik->getGlobalBounds().left, sciany[i].getGlobalBounds().top + zawodnik->getGlobalBounds().height);//kolizja z góry
				predkosc.y = 0;
			}
			else if ((zawodnik->getGlobalBounds().top < sciany[i].getGlobalBounds().top)
				&& (zawodnik->getGlobalBounds().top + zawodnik->getGlobalBounds().height < sciany[i].getGlobalBounds().top + sciany[i].getGlobalBounds().height)
				&& (zawodnik->getGlobalBounds().left < sciany[i].getGlobalBounds().left + sciany[i].getGlobalBounds().width)
				&& (zawodnik->getGlobalBounds().left + zawodnik->getGlobalBounds().width > sciany[i].getGlobalBounds().left))
			{
				zawodnik->setPosition(zawodnik->getGlobalBounds().left, sciany[i].getGlobalBounds().top - zawodnik->getGlobalBounds().height);
				predkosc.y = 0;
			}
		}
	}
}
bool Gracz::enemy_collision(std::vector< sf::RectangleShape >& wrog) {
	for (int i = 0; i < wrog.size(); i++) {
		if (wrog[i].getGlobalBounds().intersects(zawodnik->getGlobalBounds())) {
			wrogS.play(); return true;//wrogS.setVolume(50);
		}
	}
}
void Gracz::scores_collision(std::vector< sf::RectangleShape >& pkt) {
	for (int i = 0; i < pkt.size(); i++) {
		if (pkt[i].getGlobalBounds().intersects(zawodnik->getGlobalBounds())) {
			pkt.erase(pkt.begin() + i); punkty++;
			punktS.play();punktS.setVolume(5);
		}
	}
	if (pkt.size() == 0) {
		wygrana = true; alivePlayer = false;
	}
}
bool Gracz::ConSh_collision(sf::FloatRect bounds) {
	if (bounds.intersects(zawodnik->getGlobalBounds())){
		wrogS.play();return true;
	}
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