#include "wrogowie.h"
//-------------------------------------------------------------- Klasa Wrog --------------------------------------------------------------
Wrog::Wrog(int ilosc, sf::RenderWindow* okno)
{
	this->ilosc = ilosc;
	this->window = okno; init();
}
void Wrog::init()
{
	for (int i = 0; i < this->ilosc; i++)
	{
		krztalt.setSize(sf::Vector2f(30.f, 15.f));
		krztalt.setFillColor(sf::Color::Red);//wrogowie bêd¹ mieæ czerwony
		krztalt.setPosition(losPozycjeX(window->getSize().x-krztalt.getGlobalBounds().left), losPozycjeY(window->getSize().y- krztalt.getGlobalBounds().top));//obecnie losowa pozycja 
		pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
		wrogowie.push_back(krztalt);
	}
}
Wrog::~Wrog()
{
	delete window;
}
float Wrog::losPozycjeX(int szerokoscOkna)
{
	int szerokosc = (szerokoscOkna-krztalt.getGlobalBounds().left);
	return rand() % szerokosc + 1;
}
float Wrog::losPozycjeY(int wysokoscOkna)
{
	int wysokosc = (wysokoscOkna - krztalt.getGlobalBounds().top);
	return rand() % wysokosc + 1;
}
void Wrog::draw()
{
	for (const auto& krztalt : wrogowie) {
		window->draw(krztalt);
	}
}
//------------------------------------------------------------- Punkty -------------------------------------------------------------
Ziarno::Ziarno(int ilosc, sf::RenderWindow* okno)//:Wrog(okno)//---powielalo mi iloœæ punktów
{	
	this->window = okno; init();
}
Ziarno::~Ziarno()
{
	delete window;
}
void Ziarno::init()
{
	for (int i = 0; i < this->ilosc+3; i++){
		krztalt.setSize(sf::Vector2f(15.f, 15.f));
		krztalt.setRotation(45.f);
		krztalt.setFillColor(sf::Color::Magenta);//wrogowie bêd¹ mieæ czerwony
		krztalt.setPosition(losPozycjeX(window->getSize().x), losPozycjeY(window->getSize().y));//obecnie losowa pozycja 
		pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
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
	float vCS = rand() % 4 + 1;//losowanie prêdkoœci z przedzia³u 1 do 4
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