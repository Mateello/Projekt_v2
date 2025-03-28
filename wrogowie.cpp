#include "wrogowie.h"
#include<random>
//------------------------------------------ generator liczb losowych ------------------------------------------
std::mt19937 generateRandomEngine() {
	std::random_device rd;
	std::mt19937 gen(rd());
	return gen;
}
int getRandomNumber(std::mt19937& gen, int min, int max) {
	std::uniform_int_distribution<> distribution(min, max);
	return distribution(gen);
}
//-------------------------------------------------------------- Klasa Wrog --------------------------------------------------------------
Wrog::Wrog(int ilosc,float *grid, sf::RenderWindow* okno){
	this->poziom = poziom; this->ilosc = ilosc; this->grid = grid; this->window = okno; init();
}
void Wrog::init(){
	for (int i = 0; i < this->ilosc; i++) {
		std::mt19937 gen = generateRandomEngine();
		przesuniecie = new sf::Vector2f[ilosc];
		krztalt.setSize(sf::Vector2f(*grid, *grid / 2));
		krztalt.setFillColor(sf::Color::Red);//wrogowie b�d� mie� czerwony
		switch (i % 4) {//pozycja wrog�w w rogach mapy
		case 0:krztalt.setPosition(0,0);//getRandomNumber(gen, *grid, 2 * (*grid)-1), getRandomNumber(gen, (*grid), 2 * (*grid)-1));
			break;
		case 1:krztalt.setPosition(window->getSize().x,0);
			break;
		case 2:krztalt.setPosition(window->getSize().x, window->getSize().y);
			getRandomNumber(gen, window->getSize().y, window->getSize().y );
			break;
		case 3:krztalt.setPosition(0, window->getSize().y);
			break;
		}
		pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
		wrogowie.push_back(krztalt);
	}
}
Wrog::~Wrog(){
	delete window; delete[] przesuniecie;
}
void Wrog::draw(){
	for (const auto& krztalt : wrogowie) {
		window->draw(krztalt);
	}
}
void Wrog::ruch(){
	float losV = (rand()%5+3)+poziom*2;
	for (int i = 0; i < wrogowie.size(); i++) {
		if (wrogowie[i].getPosition().x > (window->getSize().x-(*grid)- wrogowie[i].getGlobalBounds().width))
			przesuniecie[i].x = -2.f* poziom;
		else if (wrogowie[i].getPosition().x< (*grid))//+wrogowie[i].getGlobalBounds().width)
			przesuniecie[i].x = 2.f* poziom;
		if (wrogowie[i].getPosition().y > (window->getSize().y - (*grid) - wrogowie[i].getGlobalBounds().height))
			przesuniecie[i].y = -1.f*losV;
		else if (wrogowie[i].getPosition().y <(*grid))
			przesuniecie[i].y = 1.f*losV;
		
		wrogowie[i].move(sf::Vector2f(przesuniecie[i]));
	}
}
void Wrog::setPoziom(int p) {
	poziom = p;
}
void Wrog::setStartPosition() {
	for (int i = 0; i < this->ilosc; i++) {
		switch (i % 4) {//pozycja wrog�w w rogach mapy
		case 0:wrogowie[i].setPosition(*grid, *grid);
			break;
		case 1:wrogowie[i].setPosition(window->getSize().x - (*grid), (*grid));
			break;
		case 2:wrogowie[i].setPosition(window->getSize().x - (*grid), window->getSize().y - (*grid));
			break;
		case 3:wrogowie[i].setPosition(*grid, window->getSize().y - (*grid));
			break;
		}
	}
}
//------------------------------------------------------------- Punkty -------------------------------------------------------------
Ziarno::Ziarno(int* wysokosc, int* szerokosc, float *grid, sf::RenderWindow* okno)//:Wrog(okno)//---powielalo mi ilo�� punkt�w
{	
	this->wysokosc = wysokosc; this->szerokosc = szerokosc; this->window = okno; this->grid = grid; init();
}
Ziarno::~Ziarno(){
	delete window; delete grid; delete wysokosc; delete szerokosc;
}
void Ziarno::init(){
	ilosc =//40;
		(*szerokosc)* (*wysokosc);//ilo�� mo�liwych punkt�w do zdobycia zale�y od szeroko�ci i wysoko�ci okna (ilo�ci siatek)
	licznik = 0;
	for (int i = 0; i < this->ilosc; i++){
		krztalt.setSize(sf::Vector2f(*grid/2, *grid/2));
		krztalt.setRotation(45.f);
		krztalt.setFillColor(sf::Color(203, 197, 135));
		krztalt.setPosition(((*grid) * (i % (*szerokosc))) + krztalt.getSize().x, ((*grid) * licznik)+4.f);
		if (i % (*szerokosc)== (*szerokosc)-1)
			licznik++;
		wrogowie.push_back(krztalt);
	}
}
//------------------------------------------------------------- Mapa -------------------------------------------------------------
Mapa::Mapa(int poziom,int* wysokosc, int* szerokosc, float* grid, sf::RenderWindow* okno)
{
	this->poziom = poziom; this->wysokosc = wysokosc; this->szerokosc = szerokosc; this->window = okno; this->grid = grid; init();
}
Mapa::~Mapa() {
	delete window; delete grid; delete wysokosc; delete szerokosc;
}
void Mapa::init() {
	ilosc = ((*wysokosc) * (*szerokosc));
	for (int i = 0; i < this->ilosc; i++) {
		krztalt.setSize(sf::Vector2f(*grid, *grid)); krztalt.setRotation(0.f);
		krztalt.setFillColor(sf::Color(33, 33, 222));
		krztalt.setOutlineColor(sf::Color::Black); krztalt.setOutlineThickness(1.f);
		krztalt.setPosition((*grid) * (i % (*szerokosc)), (*grid) * licznik);
		if (i % (*szerokosc) == (*szerokosc) - 1)
			licznik++;
		if ((i < *szerokosc) || (i > ilosc - *szerokosc - 1) || (i % (*szerokosc) < 1) || (i % (*szerokosc) == *szerokosc - 1))
			wrogowie.push_back(krztalt);
		else if((poziom != 0) && (i % (10-poziom) == 0)) {
			wrogowie.push_back(krztalt);
		}
	}
}
void Mapa::setPoints(std::vector< sf::RectangleShape >& pkt) {
	for (int i = 0; i < wrogowie.size(); i++) {
		for (int j = 0; j < pkt.size(); j++) {

			if (pkt[j].getGlobalBounds().intersects(wrogowie[i].getGlobalBounds())) {
				pkt.erase(pkt.begin() + j);
			}
		}
	}
}
//------------------------------------------------------------- ConvexShape -------------------------------------------------------------
WrogCS::WrogCS(float *grid,sf::RenderWindow* okno)
{
	this->grid = grid; this->window = okno; init();
}
WrogCS::~WrogCS()
{
	delete window; delete grid;
}
void WrogCS::init() {
	
	gwiazda.setPointCount(8);
	gwiazda.setPoint(0, sf::Vector2f(0.f, 0.f));
	gwiazda.setPoint(1, sf::Vector2f(10.f, -30.f));
	gwiazda.setPoint(2, sf::Vector2f(20.f, 0.f));
	gwiazda.setPoint(3, sf::Vector2f(50.f, 10.f));
	gwiazda.setPoint(4, sf::Vector2f(20.f, 20.f));
	gwiazda.setPoint(5, sf::Vector2f(10.f, 50.f));
	gwiazda.setPoint(6, sf::Vector2f(0.f, 20.f));
	gwiazda.setPoint(7, sf::Vector2f(-30.f, 10.f));

	gwiazda.setFillColor(sf::Color::Red);
	setStartPosition();
	gwiazda.setScale((*grid)/30.f, (*grid) / 30.f);
}
void WrogCS::ruch()
{
	float vCS = rand() % (5 + poziom)+1;//losowanie pr�dko�ci z przedzia�u
	gwiazda.setRotation(obrot += 7.5f);

	if (gwiazda.getPosition().x > (window->getSize().x + gwiazda.getGlobalBounds().left) / 2)
		przesuniecie.x = -2.f;
	if (gwiazda.getPosition().x < (window->getSize().x - gwiazda.getGlobalBounds().left) / 2)
		przesuniecie.x = 3.f;
	if (gwiazda.getPosition().y > (window->getSize().y - gwiazda.getGlobalBounds().top / 12))
		przesuniecie.y = -1*vCS;
	if (gwiazda.getPosition().y < (window->getSize().y + gwiazda.getGlobalBounds().top) / 12)
		przesuniecie.y = 1*vCS;

	gwiazda.move(sf::Vector2f(przesuniecie));
}
void WrogCS::draw()
{
	this->window->draw(gwiazda);
}
sf::FloatRect WrogCS::getBounds()
{
	return gwiazda.getGlobalBounds();
}
void WrogCS::setPoz(int poz) {
	poziom = poz;
}
void WrogCS::setStartPosition() {
	gwiazda.setPosition(sf::Vector2f((window->getSize().x - gwiazda.getGlobalBounds().width) / 2, -gwiazda.getGlobalBounds().height));
}