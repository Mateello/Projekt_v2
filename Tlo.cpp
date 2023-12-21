#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

std::mt19937 generateRandomEngine() {//generator losowej liczby
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen;
}

int getRandomNumber(std::mt19937& gen, int min, int max) {
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}
class Gwiazdozbior {
public:
    Gwiazdozbior(int liczbaGwiazd, int szerokoscOkna, int wysokoscOkna);
    ~Gwiazdozbior();
    void rysuj(sf::RenderWindow& okno);

private:
    std::vector<sf::CircleShape> gwiazdy;
    int szerokoscOkna;
    int wysokoscOkna;

    float losujPozycjeX(int szerokoscOkna);
    float losujPozycjeY(int wysokoscOkna);
};

Gwiazdozbior::Gwiazdozbior(int liczbaGwiazd, int szerokoscOkna, int wysokoscOkna)
    : szerokoscOkna(szerokoscOkna), wysokoscOkna(wysokoscOkna) {
    std::mt19937 gen = generateRandomEngine();

    for (int i = 0; i < liczbaGwiazd; ++i) {
        int promien = getRandomNumber(gen, 1, 10);
        int pozycjaX = getRandomNumber(gen, 0, szerokoscOkna);
        int pozycjaY = getRandomNumber(gen, 0, wysokoscOkna);
        sf::Color kolor = sf::Color(getRandomNumber(gen, 0, 255), getRandomNumber(gen, 0, 255), getRandomNumber(gen, 0, 255));
        sf::CircleShape gwiazda(promien);
        gwiazda.setPosition(pozycjaX, pozycjaY);
        gwiazda.setFillColor(kolor);
        gwiazdy.push_back(gwiazda);
    }
}
void Gwiazdozbior::rysuj(sf::RenderWindow& okno) {
    for (const auto& gwiazda : gwiazdy) {
        okno.draw(gwiazda);
    }
}
float Gwiazdozbior::losujPozycjeX(int szerokoscOkna)
{
    std::mt19937 gen = generateRandomEngine();
    int szerokosc = szerokoscOkna;
    return getRandomNumber(gen, 0, szerokosc);
}
float Gwiazdozbior::losujPozycjeY(int wysokoscOkna)
{
    std::mt19937 gen = generateRandomEngine();
    int wysokosc = wysokoscOkna;
    return getRandomNumber(gen, 0, wysokosc);
}