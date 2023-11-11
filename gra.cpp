#include"gra.h"
//*****************************************************************METODY PUBLICZNE KLASY GRA*****************************************************************
void Gra::pollEvents()//zwracanie wydarzeñ
{
	while (this->menu->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->menu->close();
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->menu->close();
		}
	}
}
void Gra::aktualizuj()
{
	this->pollEvents();
}
void Gra::wyswietlaj()
{
	this->menu->clear();
	this->glowne->clear();
	this->help->clear();
	this->esc->clear();

	//tu bêdzie rysowane wszystko

	this->menu->display();
	this->glowne->display();
	this->help->display();
	this->esc->display();
}
//*****************************************************************METODY PRYWATNE KLASY GRA*****************************************************************
void Gra::inicjalizujZmienne()//inicjalizowanie zmiennych prywatnych klasy gra - silnika gry, tak ¿eby mo¿naby³o ich u¿ywaæ
{
	this->menu = nullptr;//nullpointer - wska¿niki wskazuj¹ na wartoœæ NULL
	this->glowne = nullptr;
	this->help= nullptr;
	this->esc = nullptr;
}
void Gra::inicjalizujOkna()
{
	this->menu=new sf::RenderWindow(sf::VideoMode(600.f, 600.f), "Menu");//dynamicznie zaalokowane okno
	this->glowne = new sf::RenderWindow (sf::VideoMode(400.f, 400.f), "Projekt-PACMAN");
	this->help = new sf::RenderWindow (sf::VideoMode(200.f, 200.f), "Pomoc");
	this->esc = new sf::RenderWindow (sf::VideoMode(200.f, 200.f), "Opuszczanie gry");
}

//*******************************AKCESORY-ma dostep do sk³adowych obiektu, mo¿e je wyœwietlaæ ale nie zmienia ich wartoœci**********************************
const bool Gra::getWindowIsOpen()const//metoda dzia³aj¹ca jak pêtla while(okno.isOpen)
{
	return this->menu->isOpen();//na chwile obecn¹ tak to zostawie----------------------------------------------------------------------------------DO POPRAWY
	return this->glowne->isOpen();
	return this->help->isOpen();
	return this->esc->isOpen();
}
//****************************************************************KONSTRUKTOR I DESTRUKTOR******************************************************************
Gra::Gra()//konstruktor
{
	//wywo³anie metod inicjalizuj¹cych zmienne i okna - kolejnoœæ taka poniewa¿ w metodzie inicjalizujZmienne() ustawi³em wskaŸniki na wartoœæ NULL
	this->inicjalizujZmienne();
	this->inicjalizujOkna();
}
Gra::~Gra()//destruktor
{
	delete this->menu;//usuwam daynamicznie zaalokowane okna
	delete this->glowne;
	delete this->help;
	delete this->esc;
}