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
Wrog::Wrog(int ilosc,sf::Vector2f wymiar, sf::RenderWindow *okno)
{
	this->wymiar = wymiar; this->ilosc = ilosc; this->window = okno; init();
}
void Wrog::init()
{
	for (int i = 0; i < this->ilosc; i++)
	{
		krztalt.setSize(wymiar);
		krztalt.setFillColor(sf::Color::Red);//wrogowie bêd¹ mieæ czerwony
		krztalt.setPosition(losPozycjeX(window->getSize().x), losPozycjeY(window->getSize().y));//obecnie losowa pozycja 
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
	for (const auto& krztalt : wrogowie) {
		window->draw(krztalt);
	}
}
//------------------------------------------------------------- Punkty -------------------------------
Ziarna::Ziarna(int ilosc, sf::Vector2f wymiar, sf::RenderWindow *okno) :Wrog(ilosc, wymiar, okno)
{
	//this->ilosc = (ilosc / 2)-1;//na razie bêdzie tak, poniewa¿ pojawia siê dwókrotnie wiêksza iloœæ ziaren
	init();
	/*for (int i = 0; i < ilosc; i++) {
		krztalt.setFillColor(sf::Color::Magenta);
		wrogowie.push_back(krztalt);
	}*/
}
Ziarna::~Ziarna()
{
	;
}
void Ziarna::init()
{
	for (int i = 0; i < this->ilosc; i++)
	{
		krztalt.setSize(wymiar);
		krztalt.setRotation(45.f);
		krztalt.setFillColor(sf::Color::Magenta);//wrogowie bêd¹ mieæ czerwony
		krztalt.setPosition(losPozycjeX(window->getSize().x), losPozycjeY(window->getSize().y));//obecnie losowa pozycja 
		pozycja.x = krztalt.getPosition().x; pozycja.y = krztalt.getPosition().y;
		wrogowie.push_back(krztalt);
	}
}