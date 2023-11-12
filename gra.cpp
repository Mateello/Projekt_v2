#include"gra.h"

//****************************************************************KONSTRUKTOR I DESTRUKTOR******************************************************************
Gra::Gra()//konstruktor
{
	//wywo³anie metod inicjalizuj¹cych zmienne i okna - kolejnoœæ taka poniewa¿ w metodzie inicjalizujZmienne() ustawi³em wskaŸniki na wartoœæ NULL
	this->inicjalizujZmienne();
	this->inicjalizujMenu();//domyœlnie wartoœæ wskaŸnika *okno inicjalizuje okno menu, bo jest pierwsz¹ inicjalizowan¹ funkcj¹
	void inicjalizujGlowne();
	void inicjalizujHelp();
	void inicjalizujEsc();
}
Gra::~Gra()//destruktor
{
	delete this->okno;//usuwam daynamicznie zaalokowane okna
}
//*****************************************************************METODY PUBLICZNE KLASY GRA*****************************************************************
void Gra::pollEvents()//zwracanie wydarzeñ
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
void Gra::aktualizuj()//wyrzuciæ spowrotem pêtle pollEvents do Maina???
{
	this->pollEvents();
}
void Gra::wyswietlaj()
{
	this->okno->clear();

	//tu bêdzie rysowane wszystko

	this->okno->display();
}
//*****************************************************************METODY PRYWATNE KLASY GRA*****************************************************************
void Gra::inicjalizujZmienne()//inicjalizowanie zmiennych prywatnych klasy gra - silnika gry, tak ¿eby mo¿naby³o ich u¿ywaæ
{
	this->okno = nullptr;//nullpointer - wska¿niki wskazuj¹ na wartoœæ NULL
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
//*******************************AKCESORY-ma dostep do sk³adowych obiektu, mo¿e je wyœwietlaæ ale nie zmienia ich wartoœci**********************************
const bool Gra::getWindowIsOpen()const//metoda dzia³aj¹ca jak pêtla while(okno.isOpen)
{
	return this->okno->isOpen();//na chwile obecn¹ tak to zostawie----------------------------------------------------------------------------------DO POPRAWY
}