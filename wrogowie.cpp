#include "wrogowie.h"
//-------------------------------------------------------------- Klasa Wrog --------------------------------------------------------------
Wrog::Wrog(int ilosc,float *grid, sf::RenderWindow* okno){
	this->ilosc = ilosc; this->grid = grid; this->window = okno; init();
}
void Wrog::init(){
	for (int i = 0; i < this->ilosc; i++){
		przesuniecie = new sf::Vector2f[ilosc];
		krztalt.setSize(sf::Vector2f(*grid, *grid/2));
		krztalt.setFillColor(sf::Color::Red);//wrogowie b�d� mie� czerwony
		krztalt.setPosition(rand() % 29, rand() % 29);//losPozycjeY(window->getSize().y- krztalt.getGlobalBounds().top));//obecnie losowa pozycja 
		pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
		wrogowie.push_back(krztalt);
	}
}
Wrog::~Wrog(){
	delete window; delete[] przesuniecie;
}
float Wrog::losPozycjeX(int szerokoscOkna){
	int szerokosc = (szerokoscOkna-krztalt.getGlobalBounds().left);
	return rand() % szerokosc + 1;
}
float Wrog::losPozycjeY(int wysokoscOkna){
	int wysokosc = (wysokoscOkna - krztalt.getGlobalBounds().top);
	return rand() % wysokosc + 1;
}
void Wrog::draw(){
	for (const auto& krztalt : wrogowie) {
		window->draw(krztalt);
	}
}
void Wrog::ruch()
{
	float losV = rand()%5+3;
	for (int i = 0; i < wrogowie.size(); i++) {
		if (wrogowie[i].getPosition().x > (window->getSize().x - (i+1)*wrogowie[i].getSize().x))
			przesuniecie[i].x = -3.f;
		if (wrogowie[i].getPosition().x < (i+1)*wrogowie[i].getSize().x)
			przesuniecie[i].x = 2;
		if (wrogowie[i].getPosition().y > (window->getSize().y - (i+1)*wrogowie[i].getSize().y))
			przesuniecie[i].y = -2 * losV;
		if (wrogowie[i].getPosition().y < (i+1)*wrogowie[i].getSize().y)
			przesuniecie[i].y = 1 * losV;
		
		wrogowie[i].move(sf::Vector2f(przesuniecie[i]));
	}
}
sf::Vector2f Wrog::getVelocity(int i) {
	return przesuniecie[i];
}
void Wrog::setVelocity(int i,float x, float y) {
	przesuniecie[i].x = x; przesuniecie[i].y = y;
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
	ilosc = (*szerokosc) * (*wysokosc); 
	licznik = 0;
	for (int i = 0; i < this->ilosc; i++){
		krztalt.setSize(sf::Vector2f(*grid/2, *grid/2));
		krztalt.setRotation(45.f);
		krztalt.setFillColor(sf::Color::Magenta);//wrogowie b�d� mie� czerwony
		krztalt.setPosition(((*grid) * (i % (*szerokosc))) + krztalt.getSize().x, (*grid) * licznik);//obecnie losowa pozycja 
		if (i % (*szerokosc)== (*szerokosc)-1)
			licznik++;
		wrogowie.push_back(krztalt);
	}
}
//------------------------------------------------------------- Mapa -------------------------------------------------------------
Mapa::Mapa(int* wysokosc, int* szerokosc, float* grid, sf::RenderWindow* okno)//:Ziarno(wysokosc, szerokosc, grid,okno)
{//mo�e b�dzie trzeba doda� jako argument konstruktora inta - kt�ry bedzie wybiera� poziom 
	this->wysokosc = wysokosc; this->szerokosc = szerokosc; this->window = okno; this->grid = grid; test();
}
Mapa::~Mapa() {
	delete window; delete grid; delete wysokosc; delete szerokosc;
}
void Mapa::test() {
	ilosc = ((*wysokosc) * (*szerokosc));
	for (int i = 0; i < this->ilosc; i++) {
		krztalt.setSize(sf::Vector2f(*grid, *grid)); krztalt.setRotation(0.f);
		krztalt.setFillColor(sf::Color(33, 33, 222));
		krztalt.setOutlineColor(sf::Color::Black); krztalt.setOutlineThickness(1.f);
		krztalt.setPosition((*grid) * (i % (*szerokosc)), (*grid) * licznik);
		if (i % (*szerokosc) == (*szerokosc) - 1)
			licznik++;
		if((i<*szerokosc)||(i>ilosc-*szerokosc-1)||(i%(*szerokosc)<1) || (i % (*szerokosc) ==*szerokosc-1))
		wrogowie.push_back(krztalt);
	}
}
//------------------------------------------------------------- ConvexShape -------------------------------------------------------------
WrogCS::WrogCS(sf::RenderWindow* okno)
{
	this->window = okno; init();
}
WrogCS::~WrogCS()
{
	delete window;
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
	gwiazda.setPosition(sf::Vector2f((window->getSize().x + gwiazda.getGlobalBounds().left) / 2, -gwiazda.getGlobalBounds().top));
}
void WrogCS::ruch()
{
	float vCS = rand() % 5 + 1;//losowanie pr�dko�ci z przedzia�u 1 do 4
	gwiazda.setRotation(obrot += 7.5f);

	if (gwiazda.getPosition().x > (window->getSize().x + gwiazda.getGlobalBounds().left) / 2)
		przesuniecie.x = -2.f;
	if (gwiazda.getPosition().x < (window->getSize().x - gwiazda.getGlobalBounds().left) / 2)
		przesuniecie.x = 3.f;
	if (gwiazda.getPosition().y > (window->getSize().y - gwiazda.getGlobalBounds().top / 12))//liczba 12 dobrana eksperymentalnie
		przesuniecie.y = -1*vCS;
	if (gwiazda.getPosition().y < (window->getSize().y + gwiazda.getGlobalBounds().top) / 12)//liczba 12 dobrana eksperymentalnie
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