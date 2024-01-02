#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>

class Gracz{
	sf::RenderWindow *window;
	sf::Texture *tekstura;
	sf::Sprite *zawodnik;
	sf::Vector2f predkosc, pozycja;
	std::string nazwa;
	float *grid, czas_gry;
	clock_t t_start, t_stop;//zmienne przechowujące ilość cykli procesora od narysowania do usuniecia gracza
	int punkty;
	bool alivePlayer,wygrana;//zmienna odpowowiadająca za to czy gracz "żyje" czy nie
public:
	Gracz(float *grid,sf::RenderWindow *okno);
	~Gracz();
	void update();
	void init();
	void draw();
	void setPosition(float x, float y);
	void wall_collision(std::vector< sf::RectangleShape > &sciany);//kolizje ze scianami
	void enemy_collision(std::vector< sf::RectangleShape >&wrog);//kolizje z wrogami
	void scores_collision(std::vector< sf::RectangleShape >&pkt);//kolizje z punktami
	void ConSh_collision(sf::FloatRect bounds);
	int getPunkty();
	int getCzas();
	bool Win();
	bool getPlayerState();
	void setName(std::string s);
	std::string getName();
	sf::FloatRect getBounds();
};
//-------------------------------------------------------------- Zapis do pliku ----------------------------------------------------
struct Dane{
	int punkty,czas,poziom;
	std::string nazwa;
};