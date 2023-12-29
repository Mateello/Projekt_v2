#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cmath>

class Wrog{
	int poziom;//poziom trudnoœci
protected:
	int ilosc;
	sf::RenderWindow *window;
	sf::RectangleShape krztalt;//tej zmiennej nie usuwam poniewa¿ na niej bazowuj¹ funckje pushback dla wektorów wrogów i ziaren
	sf::Vector2f pozycja;
	float *grid;
	void init();	
public:
	Wrog(int poziom,int ilosc,float *grid, sf::RenderWindow* okno);//wrogowie bêd¹ prostok¹tami
	Wrog() { ilosc = 1; 
	}
	sf::Vector2f* przesuniecie;
	~Wrog();
	void draw();
	void ruch();
	std::vector<sf::RectangleShape> wrogowie;
	void setVelocity(int i,float x, float y);
};
class Ziarno:public Wrog //zbierane przez gracza, zwiêkszaj¹ iloœæ punktów
{
	//za ka¿de ziarno bêdzie +1 punkt dla gracza
protected:
	void init();
	int * wysokosc, * szerokosc;//s¹ to inty bo okreœlaj¹ iloœæ œcian
	int licznik;//licznik rzêdów
public:
	Ziarno(int* wysokosc,int *szerokosc, float *grid, sf::RenderWindow* okno);
	Ziarno() { ilosc = 1; }
	~Ziarno();
};
class Mapa :public Ziarno{
	void test();//w przysz³oœci zrobiæ 3 funkcje tego typu które maj¹ ró¿ne ustawienia map?
	int poziom;
public:
	Mapa(int poziom,int* wysokosc, int* szerokosc, float* grid, sf::RenderWindow* okno);
	~Mapa();
	void setPoints(std::vector< sf::RectangleShape >& pkt);//usuwanie punktów pokrywaj¹cych siê z œcianami
};
//---------------------------------------------------------------------------ConvexShape------------------------------------------------
class WrogCS
{
	float obrot = 0;
	sf::ConvexShape gwiazda;//nie wiem czemu jak zrobi³em to na wskaŸnikach to wskaŸnik zwraca³ NULL
	sf::RenderWindow* window;
	sf::Vector2f przesuniecie;
public:
	WrogCS(sf::RenderWindow* okno); ~WrogCS();
	void init();
	void ruch();
	void draw();
	sf::FloatRect getBounds();
};