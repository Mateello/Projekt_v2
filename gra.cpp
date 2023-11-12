#include"gra.h"

//****************************************************************KONSTRUKTOR I DESTRUKTOR******************************************************************
Gra::Gra()//konstruktor
{
	//wywo�anie metod inicjalizuj�cych zmienne i okna - kolejno�� taka poniewa� w metodzie inicjalizujZmienne() ustawi�em wska�niki na warto�� NULL
	this->inicjalizujZmienne();
	this->inicjalizujMenu();//domy�lnie warto�� wska�nika *okno inicjalizuje okno menu, bo jest pierwsz� inicjalizowan� funkcj�
	void inicjalizujGlowne();
	void inicjalizujHelp();
	void inicjalizujEsc();
}
Gra::~Gra()//destruktor
{
	delete this->okno;//usuwam daynamicznie zaalokowane okna
}
//*****************************************************************METODY PUBLICZNE KLASY GRA*****************************************************************
void Gra::pollEvents()//zwracanie wydarze�
{
	while (this->okno->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->okno->close();
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->okno->close();
		}
	}
}
void Gra::aktualizuj()//wyrzuci� spowrotem p�tle pollEvents do Maina???
{
	this->pollEvents();
}
void Gra::wyswietlaj()
{
	this->okno->clear();

	//tu b�dzie rysowane wszystko

	this->okno->display();
}
//*****************************************************************METODY PRYWATNE KLASY GRA*****************************************************************
void Gra::inicjalizujZmienne()//inicjalizowanie zmiennych prywatnych klasy gra - silnika gry, tak �eby mo�naby�o ich u�ywa�
{
	this->okno = nullptr;//nullpointer - wska�niki wskazuj� na warto�� NULL
}
void Gra::inicjalizujMenu()
{
	this->videoMode.height = 600;
	this->videoMode.width = 600;
	this->nazwa = "Menu";
	this->okno = new sf::RenderWindow(this->videoMode, nazwa);
}
void Gra::inicjalizujGlowne()
{
	this->videoMode.height = 400;
	this->videoMode.width = 400;
	this->nazwa = "Projekt-PACMAN";
	this->okno = new sf::RenderWindow(this->videoMode, nazwa);
}
void Gra::inicjalizujHelp()
{
	this->videoMode.height = 200;
	this->videoMode.width = 200;
	this->nazwa = "Pomoc";
	this->okno = new sf::RenderWindow(this->videoMode, nazwa);
}
void Gra::inicjalizujEsc()
{
	this->videoMode.height = 200;
	this->videoMode.width = 200;
	this->nazwa = "Opuszczanie gry";
	this->okno = new sf::RenderWindow(this->videoMode, nazwa);
}
//*******************************AKCESORY-ma dostep do sk�adowych obiektu, mo�e je wy�wietla� ale nie zmienia ich warto�ci**********************************
const bool Gra::getWindowIsOpen()const//metoda dzia�aj�ca jak p�tla while(okno.isOpen)
{
	return this->okno->isOpen();//na chwile obecn� tak to zostawie----------------------------------------------------------------------------------DO POPRAWY
}