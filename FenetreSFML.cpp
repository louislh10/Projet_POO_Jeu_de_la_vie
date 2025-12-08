#include "FenetreSFML.h"
#include <iostream>

FenetreSFML::FenetreSFML(Jeu& j, int tailleCase)
    : jeu(j), tailleCase(tailleCase),
    window(sf::VideoMode(static_cast<unsigned int>(j.getGrille().getLargeur()* tailleCase),
        static_cast<unsigned int>(j.getGrille().getHauteur()* tailleCase)),
        "Jeu de la Vie fenetreSFML") {
    if (j.getGrille().getLargeur() == 0 || j.getGrille().getHauteur() == 0) {
        throw std::runtime_error("Grille videimpossible d'afficher.");
    }
}

void FenetreSFML::afficher() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        jeu.mettreAJour();

        window.clear(sf::Color::Black);

        const Grille& g = jeu.getGrille();

        for (int i = 0; i < g.getHauteur(); ++i) {
            for (int j = 0; j < g.getLargeur(); ++j) {
                Cellule* c = g.getCellule(j, i);


                if (!c) {
                    std::cerr << "erreur cellule nul en j=" << j << ", i=" << i << std::endl;
                    continue;
                }

                sf::RectangleShape cell(sf::Vector2f(
                    static_cast<float>(tailleCase - 1), 
                    static_cast<float>(tailleCase - 1)
                ));

                cell.setPosition(
                    static_cast<float>(j * tailleCase),
                    static_cast<float>(i * tailleCase)
                );

               
                cell.setFillColor(c->estVivante() ? sf::Color::Cyan : sf::Color::Black);

                window.draw(cell);
            }
        }

        window.display();
        sf::sleep(sf::milliseconds(100));
    }
} 