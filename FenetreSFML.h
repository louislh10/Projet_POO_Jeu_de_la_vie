#pragma once
#ifndef FENETRESFML_H
#define FENETRESFML_H

#include <SFML/Graphics.hpp>
#include "Jeu.h"

class FenetreSFML {
private:
    Jeu& jeu;
    int tailleCase;
    sf::RenderWindow window;

public:
    FenetreSFML(Jeu& j, int tailleCase = 20);
    void afficher();
};

#endif