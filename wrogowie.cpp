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
wrog::wrog(float r, int w, float szerokoscOkna, float wysokoscOkna)
{
	promien = r; wierzcholki = w;
	wymiar_okna.x = szerokoscOkna; wymiar_okna.y = wysokoscOkna;
	std::mt19937 gen = generateRandomEngine();
	//sf::Color kolor = sf::Color(getRandomNumber(gen,0,255), getRandomNumber(gen, 0, 255), getRandomNumber(gen, 0, 255));
	sf::Color kolor = sf::Color(128,128,128);
	sf::CircleShape krztalt(promien, wierzcholki); 
	krztalt.setFillColor(kolor);
}
wrog::~wrog()
{

}
sf::CircleShape wrog::getWrog()
{
	return krztalt;
}
float wrog::losPozycjeX(int szerokoscOkna)
{
	std::mt19937 gen = generateRandomEngine();
	int szerokosc = szerokoscOkna;
	float x;

	x = getRandomNumber(gen, 0, szerokosc);

	return x;
}
float wrog::losPozycjeY(int wysokoscOkna)
{
	std::mt19937 gen = generateRandomEngine();
	int wysokosc = wysokoscOkna;
	float y;

	y = getRandomNumber(gen, 0, wysokosc);

	return y;
}
void wrog::rysuj(sf::RenderWindow& okno)
{
	okno.draw(getWrog());
}