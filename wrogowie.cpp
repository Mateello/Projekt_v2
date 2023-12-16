#include "wrogowie.h"

std::mt19937 generateRandomEngine() //generator losowej liczby
{
	std::random_device rd;
	std::mt19937 gen(rd());
	return gen;
}
int getRandomNumber(std::mt19937& gen, int min, int max)
{
	std::uniform_int_distribution<> distribution(min, max);
	return distribution(gen);
}
//-------------------------------------------------------------- Klasa Wrog --------------------------------------------------------------
Wrog::Wrog(sf::RenderWindow *okno)
{
	this->wymiar = wymiar; this->window = okno; init();
}
void Wrog::init()
{
	krztalt.setSize(sf::Vector2f(30.f, 15.f));
	krztalt.setFillColor(sf::Color::Red);//wrogowie bêd¹ mieæ czerwony
	//krztalt.setPosition(losPozycjeX(window->getSize().x), losPozycjeY(window->getSize().y));//obecnie losowa pozycja 
	pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
}
Wrog::~Wrog()
{
	delete window;
}
float Wrog::losPozycjeX(int szerokoscOkna)
{
	std::mt19937 gen = generateRandomEngine();
	int szerokosc = (szerokoscOkna-krztalt.getGlobalBounds().left);
	float x;

	x = getRandomNumber(gen, 0, szerokosc);

	return x;
}
float Wrog::losPozycjeY(int wysokoscOkna)
{
	std::mt19937 gen = generateRandomEngine();
	int wysokosc = (wysokoscOkna - krztalt.getGlobalBounds().top);
	float y;

	y = getRandomNumber(gen, 0, wysokosc);

	return y;
}
void Wrog::draw()
{
	window->draw(krztalt);
}
//------------------------------------------------------------- Punkty -------------------------------------------------------------
Ziarno::Ziarno(sf::RenderWindow *okno):Wrog(okno)//---powielalo mi iloœæ punktów
{	
	init();
}
Ziarno::~Ziarno()
{
	;
}
void Ziarno::init()
{
	krztalt.setSize(sf::Vector2f(15.f, 15.f));
	krztalt.setRotation(45.f);
	krztalt.setFillColor(sf::Color::Magenta);//wrogowie bêd¹ mieæ czerwony
	//krztalt.setPosition(losPozycjeX(window->getSize().x), losPozycjeY(window->getSize().y));//obecnie losowa pozycja 
	pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
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
	std::mt19937 gen = generateRandomEngine();//inicjonowanie generatora liczb losowych
	float vCS = getRandomNumber(gen, 1, 5);//losowanie prêdkoœci z przedzia³u 1 do 4
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