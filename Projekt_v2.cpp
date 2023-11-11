#include <SFML/Graphics.hpp>
#include <gra.h>
int main() 
{
	//OKNA - DOCELOWO ZROBIĆ Z TEGO KLASE
	sf::RenderWindow menu(sf::VideoMode(600.f, 600.f), "Menu");
	sf::RenderWindow glowne(sf::VideoMode(400.f, 400.f), "Projekt-PACMAN");
	sf::RenderWindow help(sf::VideoMode(200.f, 200.f), "Pomoc");
	sf::RenderWindow esc(sf::VideoMode(200.f, 200.f), "Opuszczanie gry");

	glowne.close();//trzeba uważać bo te okna i tak się na chwile pokażą
	help.close();
	esc.close();

	//WROGOWIE - DOCELOWO ZROBIĆ Z TEGO KLASE
	sf::CircleShape wrog_1(100.f);
	sf::CircleShape wrog_2(100.f, 3);
	sf::RectangleShape wrog_3(sf::Vector2f(150.f, 100.f));
	sf::ConvexShape wrog_4;
	wrog_4.setPointCount(5);
	wrog_4.setPoint(0, sf::Vector2f(0.f, 0.f));
	wrog_4.setPoint(1, sf::Vector2f(30.f, 10.f));
	wrog_4.setPoint(2, sf::Vector2f(30.f, 50.f));
	wrog_4.setPoint(3, sf::Vector2f(20.f, 50.f));
	wrog_4.setPoint(4, sf::Vector2f(0.f, 70.f));

	sf::Color wr_kl (sf::Color::Red);//kolor wrogów
	wrog_1.setFillColor(wr_kl); wrog_2.setFillColor(wr_kl); wrog_3.setFillColor(wr_kl); wrog_4.setFillColor(wr_kl);
	sf::Color wr_outline(sf::Color::Yellow);//kolor otoczki
	wrog_1.setOutlineColor(wr_outline); wrog_2.setOutlineColor(wr_outline); wrog_3.setOutlineColor(wr_outline); wrog_4.setOutlineColor(wr_outline);
	wrog_1.setOutlineThickness(-5.f); wrog_2.setOutlineThickness(-5.f); wrog_3.setOutlineThickness(-5.f); wrog_4.setOutlineThickness(-5.f);

	//PĘTLA GRY
	while (menu.isOpen())
	{
		sf::Event event;
		while (menu.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				menu.close();
		}
		menu.clear();
		menu.draw(wrog_4);
		menu.display();
	}
	return 0;
}