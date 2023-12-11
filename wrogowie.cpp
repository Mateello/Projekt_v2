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
Wrog::Wrog(int liczbaWrogow, float r, int w, sf::RenderWindow& okno)
{
	promien = r; wierzcholki = w; ilosc = liczbaWrogow;
	//wymiar_okna.x = szerokoscOkna; wymiar_okna.y = wysokoscOkna;
	wymiar_okna.x=okno.getSize().x;; wymiar_okna.y= okno.getSize().y;
	std::mt19937 gen = generateRandomEngine();
	//sf::Color kolor = sf::Color(getRandomNumber(gen,0,255), getRandomNumber(gen, 0, 255), getRandomNumber(gen, 0, 255));
	for (int i = 0; i < ilosc; i++)
	{
		wrogOtoczka=krztalt.getGlobalBounds();//ustalanie "otoczki" wroga
		krztalt.setRadius(promien);
		krztalt.setPointCount(wierzcholki);
		krztalt.setFillColor(sf::Color::Red);//wrogowie bêd¹ mieæ czerwony
		krztalt.setPosition(losPozycjeX(wymiar_okna.x), losPozycjeY(wymiar_okna.y));//obecnie losowa pozycja 
		wrogowie.push_back(krztalt);
		pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
	}
}
Wrog::~Wrog()
{
	delete okno;
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
void Wrog::rysuj(sf::RenderWindow& okno)
{
	//okno.draw(krztalt);
	for (const auto& krztalt : wrogowie) {
		okno.draw(krztalt);
	}
}
//------------------------------------------------------------- Punkty -------------------------------
Ziarna::Ziarna(int liczbaziaren, float promien, int wartosc, sf::RenderWindow& okno)//domyslny konstruktor-najwiêksze ziarno - najmniej pkt
{
	this->wartosc = wartosc; this->promien = promien; ilosc = liczbaziaren;
	wymiar_okna.x = okno.getSize().x;; wymiar_okna.y = okno.getSize().y;
	std::mt19937 gen = generateRandomEngine();
	for (int i=0;i< ilosc;i++)
	{
		wrogOtoczka = krztalt.getGlobalBounds();//ustalanie "otoczki" wroga
		sf::Color kolor = sf::Color(getRandomNumber(gen, 0, 255), getRandomNumber(gen, 0, 255), getRandomNumber(gen, 0, 255));
		krztalt.setFillColor(kolor);
		krztalt.setRadius(promien);
		krztalt.setPosition(losPozycjeX(wymiar_okna.x), losPozycjeY(wymiar_okna.y));
		wrogowie.push_back(krztalt);
	}
}
Ziarna::~Ziarna()
{
	;
}	
int Ziarna::getWartosc()
{
	return wartosc;
}