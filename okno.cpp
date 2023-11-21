#include "okno.h"

Menu::Menu(float szerokosc, float wysokosc)//konstruktor
{
	if (!czcionka.loadFromFile("Righteous-Regular.ttf"))//³adowanie czcionki z pliku
	{
		std::cout << "Nie udalo sie zaladowac czcionki!" << "\n";//napis wyskakuj¹cy w oknie konsoli gdy nie za³adujemy czcionki
	}

	tekst[0].setFont(czcionka);
	tekst[0].setFillColor(sf::Color::White);
	tekst[0].setString("Graj");
	tekst[0].setCharacterSize(60);
	tekst[0].setPosition(200,100);//pozycja linijki tekstu

	tekst[1].setFont(czcionka);
	tekst[1].setFillColor(sf::Color::White);
	tekst[1].setString("Pomoc"); 
	tekst[1].setCharacterSize(40);
	tekst[1].setPosition(200, 250);

	tekst[2].setFont(czcionka);
	tekst[2].setFillColor(sf::Color::White);
	tekst[2].setString("Wyjscie"); 
	tekst[2].setCharacterSize(40);
	tekst[2].setPosition(200, 400);

	MenuWybrane=-1;
}
Menu::~Menu()//destruktor
{

}
void Menu::rysuj(sf::RenderWindow& window)
{
	for (int i = 0; i < 3/*maksymalna iloœæ wierszy*/; i++)
	{
		window.draw(tekst[i]);//rysowanie po koleji linijek tekstu
	}
}
void Menu::wGore()
{
	if (MenuWybrane - 1 >= 0)//0 - pierwsza komórka tablicy tekst[]
	{
		tekst[MenuWybrane].setFillColor(sf::Color::Blue);//podœwietlanie wybranej linijki na niebiesko

		MenuWybrane--;
		if (MenuWybrane == -1)
		{
			MenuWybrane=2;//nastawiam wartoœæ zmienniej odpowiadaj¹cej za podœwietlanie/wybór opcji na maksymalny indeks tablicy -1
		}
		tekst[MenuWybrane].setFillColor(sf::Color::Blue);//podœwietlenie ostatniej opcji do wyboru
	}
}
void Menu::wDol()
{
	if (MenuWybrane + 1 <= 3)//to 3 to wielkoœæ tablicy tekst[]
	{
		tekst[MenuWybrane].setFillColor(sf::Color::Blue);

		MenuWybrane--;

		if (MenuWybrane == 3)
		{
			MenuWybrane == 0;
		}
		tekst[MenuWybrane].setFillColor(sf::Color::Blue);
	}
}
/* ------------------ ¯eby nie straciæ tego
int wybrane = MenuGlowne.MenuNacisniete();
					if (wybrane == 0)
					{
						while (glowne.isOpen())
						{
							sf::Event event_2;//zmienna Event odpowiadaj¹ca za okno g³ówne gry
							while (glowne.pollEvent(event_2))
							{
								if (event_2.type = sf::Event::Closed)
								{
									glowne.close();
								}
								if (event.type = sf::Event::KeyPressed)
								{
									if (event_2.key.code == sf::Keyboard::Escape)
									{
										glowne.close();//sf::RenderWindow wyjscie(sf::VideoMode(400.f, 400.f), "Wyjscie"); ---- NA POTEM
									}
								}
							}
							help.close();
							glowne.clear(sf::Color::Yellow);
							glowne.draw(P1.getGracz());
							glowne.display();
						}
					}
					if (wybrane == 1)
					{
						while (help.isOpen())
						{
							sf::Event event_3;//zmienna Event odpowiadaj¹ca za okno pomoc
							while (help.pollEvent(event_3))
							{
								if (event_3.type = sf::Event::Closed)
								{
									help.close();
								}
								if (event.type = sf::Event::KeyPressed)
								{
									if (event_3.key.code == sf::Keyboard::Escape)
									{
										help.close();//sf::RenderWindow wyjscie(sf::VideoMode(400.f, 400.f), "Wyjscie"); ---- NA POTEM
									}
								}
							}
							glowne.close();
							help.clear(sf::Color::Yellow);
							help.draw(P1.getGracz());
							help.display();
						}
					}
					if (wybrane == 2)
					{
						menu.close();
					}
					*/