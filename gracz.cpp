#include "gracz.h"

Gracz::Gracz(float x_in, float y_in, float okno_x, float okno_y)
{
	Pacman_t.loadFromFile("pokeball.png");//ze wzgl�du na problem z pacman.png - na razie porzycz� pokeball'a
	Pacman.setTexture(Pacman_t);
	window.x = okno_x; window.y = okno_y;
}
sf::Sprite Gracz::getGracz()
{
	return Pacman;
}
void Gracz::update()
{

}