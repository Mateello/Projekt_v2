#include "okno.h"

Interfejs::Interfejs(float *grid,sf::RenderWindow* okno){
	this->grid = grid; this->okno = okno; init();
}
Interfejs::~Interfejs(){
	delete grid; delete narysowany; delete wybor; delete okno; delete czcionka; 
	delete t1; delete t2; delete t3; delete t4; delete tlo;
}
void Interfejs::init(){
	sf::Color t³o(38, 115, 101);
	wym_obr.x = (*grid)*5; wym_obr.y = (*grid)*4/3; otoczkat.x = wym_obr.x - ((*grid)*2/3); otoczkat.y = wym_obr.y - ((*grid)/2);
	tlo = new sf::RectangleShape; wybor = new int; narysowany = new bool;
	tlo->setFillColor(t³o);
	tlo->setPosition(0.f,0.f); tlo->setSize(sf::Vector2f(okno->getSize().x, okno->getSize().y));
	czcionka = new sf::Font; czcionka->loadFromFile("Agbalumo-Regular.ttf");
	t1 = new sf::Text; t1->setFont(*czcionka); t1->setCharacterSize(*grid); t1->setString("Pierwszy");
	t1->setPosition(sf::Vector2f(okno->getSize().x / 2 - 2 * (*grid), okno->getSize().y / 6)); t1->setFillColor(sf::Color::White);
	t2 = new sf::Text; t2->setFont(*czcionka); t2->setCharacterSize(*grid); t2->setString("Drugi");
	t2->setPosition(sf::Vector2f(okno->getSize().x/2 - 2 * (*grid), okno->getSize().y / 3)); t2->setFillColor(sf::Color::White);
	t3 = new sf::Text; t3->setFont(*czcionka); t3->setCharacterSize(*grid); t3->setString("Trzeci");
	t3->setPosition(sf::Vector2f(okno->getSize().x/2 - 2 * (*grid), okno->getSize().y / 2)); t3->setFillColor(sf::Color::White);
	t4 = new sf::Text; t4->setFont(*czcionka); t4->setCharacterSize(*grid); t4->setString("Czwarty");
	t4->setPosition(sf::Vector2f(okno->getSize().x/2 - 2 * (*grid), okno->getSize().y / 3 *2)); t4->setFillColor(sf::Color::White);
}
void Interfejs::rysuj()//zmiana koloru napisów, przy którym jest myszka
{
	if (*narysowany == true)
	{
		okno->draw(*tlo);
		if ((mousePos.x > t1->getPosition().x && (mousePos.x < (t1->getPosition().x + otoczkat.x)) &&
			(mousePos.y > t1->getPosition().y) && (mousePos.y < (t1->getPosition().y + otoczkat.y)))) {
	
			okno->draw(*t1); t1->setFillColor(napisy); setIntIndeks(1);
		}
		else {
			okno->draw(*t1); t1->setFillColor(sf::Color::White);
		}
		if ((mousePos.x > t2->getPosition().x && (mousePos.x < (t2->getPosition().x + otoczkat.x)) &&
			(mousePos.y > t2->getPosition().y) && (mousePos.y < (t2->getPosition().y + otoczkat.y)))) {

			okno->draw(*t2); t2->setFillColor(napisy); setIntIndeks(2);
		}
		else {
			okno->draw(*t2); t2->setFillColor(sf::Color::White);
		}
		if ((mousePos.x > t3->getPosition().x && (mousePos.x < (t3->getPosition().x + otoczkat.x)) &&
			(mousePos.y > t3->getPosition().y) && (mousePos.y < (t3->getPosition().y + otoczkat.y)))) {

			okno->draw(*t3); t3->setFillColor(napisy); setIntIndeks(3);
		}
		else {
			okno->draw(*t3); t3->setFillColor(sf::Color::White);
		}
		if ((mousePos.x > t4->getPosition().x && (mousePos.x < (t4->getPosition().x + otoczkat.x)) &&
			(mousePos.y > t4->getPosition().y) && (mousePos.y < (t4->getPosition().y + otoczkat.y)))) {

			okno->draw(*t4); t4->setFillColor(napisy); setIntIndeks(4);
		}
		else {
			okno->draw(*t4); t4->setFillColor(sf::Color::White);
		}
	}
	else
		setIntIndeks(NULL);
}
void Interfejs::rysuj(bool obw){//rysowanie interfejsów, których zadaniem jest wyœwietlanie danych
	if (*narysowany == true)
	{
		okno->draw(*tlo); okno->draw(*t1);
		if ((mousePos.x > t4->getPosition().x && (mousePos.x < (t4->getPosition().x + otoczkat.x)) &&
			(mousePos.y > t4->getPosition().y) && (mousePos.y < (t4->getPosition().y + otoczkat.y)))) {

			okno->draw(*t4); setIntIndeks(4); t4->setFillColor(napisy);
		}
		else {
			okno->draw(*t4); t4->setFillColor(sf::Color::White);
		}
	}
	else
		setIntIndeks(NULL);
}
void Interfejs::setCharSize(int size){
	t1->setCharacterSize(size); t2->setCharacterSize(size); t3->setCharacterSize(size); t4->setCharacterSize(size);
}
void Interfejs::setString(std::string napis1, std::string napis2, std::string napis3, std::string napis4)//podmienianie napisów z odmyœlnych na ustawione;
{
	t1->setString(napis1); t2->setString(napis2); t3->setString(napis3); t4->setString(napis4);
}
void Interfejs::setPosition(float przesuniecie_x, float przesuniecie_y){
	t1->setPosition(t1->getPosition().x+ przesuniecie_x, t1->getPosition().y + przesuniecie_y);
	t2->setPosition(t2->getPosition().x + przesuniecie_x, t2->getPosition().y + przesuniecie_y);
	t3->setPosition(t3->getPosition().x + przesuniecie_x, t3->getPosition().y + przesuniecie_y);
	t4->setPosition(t4->getPosition().x + przesuniecie_x, t4->getPosition().y + przesuniecie_y);
}
void Interfejs::setIntIndeks(int n){
	*wybor = n;
}
int Interfejs::getIntIndeks(){
	return *wybor;
}
void Interfejs::setIntState(bool s){
	*narysowany = s;
}
bool Interfejs::getIntState(){
	return *narysowany;
}