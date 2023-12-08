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
Wrog::Wrog(float r, int w, sf::RenderWindow& okno)
{
	promien = r; wierzcholki = w;
	//wymiar_okna.x = szerokoscOkna; wymiar_okna.y = wysokoscOkna;
	wymiar_okna.x=okno.getSize().x;; wymiar_okna.y= okno.getSize().y;
	std::mt19937 gen = generateRandomEngine();
	sf::Color kolor = sf::Color(getRandomNumber(gen,0,255), getRandomNumber(gen, 0, 255), getRandomNumber(gen, 0, 255));
	krztalt.setRadius(promien);
	krztalt.setPointCount(wierzcholki);
	krztalt.setFillColor(kolor);
	krztalt.setPosition(losPozycjeX(wymiar_okna.x)-krztalt.getGlobalBounds().left, losPozycjeY(wymiar_okna.y - krztalt.getGlobalBounds().top));//obecnie losowa pozycja 
}
Wrog::~Wrog()
{
	;
}
sf::CircleShape Wrog::getWrog()
{
	return krztalt;
}
float Wrog::losPozycjeX(int szerokoscOkna)
{
	std::mt19937 gen = generateRandomEngine();
	int szerokosc = szerokoscOkna;
	float x;

	x = getRandomNumber(gen, 0, szerokosc);

	return x;
}
float Wrog::losPozycjeY(int wysokoscOkna)
{
	std::mt19937 gen = generateRandomEngine();
	int wysokosc = wysokoscOkna;
	float y;

	y = getRandomNumber(gen, 0, wysokosc);

	return y;
}
void Wrog::rysuj(sf::RenderWindow& okno)
{
	okno.draw(getWrog());
}
//------------------------------------------------------------- Punkty -------------------------------
Ziarna::Ziarna(float promien, int wartosc, sf::RenderWindow& okno)//domyslny konstruktor-najwiêksze ziarno - najmniej pkt
{
	this->wartosc = wartosc; this->promien = promien;
	wymiar_okna.x = okno.getSize().x;; wymiar_okna.y = okno.getSize().y;
	std::mt19937 gen = generateRandomEngine();
	krztalt.setRadius(promien);
	krztalt.setPosition(losPozycjeX(wymiar_okna.x) - krztalt.getGlobalBounds().left, losPozycjeY(wymiar_okna.y - krztalt.getGlobalBounds().top));
}
Ziarna::~Ziarna()
{
	;
}
int Ziarna::getWartosc()
{
	return wartosc;
}