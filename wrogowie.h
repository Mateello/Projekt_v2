#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cmath>

class Wrog{
	int poziom;//poziom trudno�ci
protected:
	int ilosc;
	sf::RenderWindow *window;
	sf::RectangleShape krztalt;//tej zmiennej nie usuwam poniewa� na niej bazowuj� funckje pushback dla wektor�w wrog�w i ziaren
	sf::Vector2f pozycja;
	float *grid;
	void init();	
public:
	Wrog(int poziom,int ilosc,float *grid, sf::RenderWindow* okno);//wrogowie b�d� prostok�tami
	Wrog() { ilosc = 1; 
	}
	sf::Vector2f* przesuniecie;
	~Wrog();
	void draw();
	void ruch();
	std::vector<sf::RectangleShape> wrogowie;
	void setVelocity(int i,float x, float y);
};
class Ziarno:public Wrog //zbierane przez gracza, zwi�kszaj� ilo�� punkt�w
{
	//za ka�de ziarno b�dzie +1 punkt dla gracza
protected:
	void init();
	int * wysokosc, * szerokosc;//s� to inty bo okre�laj� ilo�� �cian
	int licznik;//licznik rz�d�w
public:
	Ziarno(int* wysokosc,int *szerokosc, float *grid, sf::RenderWindow* okno);
	Ziarno() { ilosc = 1; }
	~Ziarno();
};
class Mapa :public Ziarno{
	void test();//w przysz�o�ci zrobi� 3 funkcje tego typu kt�re maj� r�ne ustawienia map?
	int poziom;
public:
	Mapa(int poziom,int* wysokosc, int* szerokosc, float* grid, sf::RenderWindow* okno);
	~Mapa();
	void setPoints(std::vector< sf::RectangleShape >& pkt);//usuwanie punkt�w pokrywaj�cych si� z �cianami
};
//---------------------------------------------------------------------------ConvexShape------------------------------------------------
class WrogCS
{
	float obrot = 0;
	sf::ConvexShape gwiazda;//nie wiem czemu jak zrobi�em to na wska�nikach to wska�nik zwraca� NULL
	sf::RenderWindow* window;
	sf::Vector2f przesuniecie;
public:
	WrogCS(sf::RenderWindow* okno); ~WrogCS();
	void init();
	void ruch();
	void draw();
	sf::FloatRect getBounds();
};