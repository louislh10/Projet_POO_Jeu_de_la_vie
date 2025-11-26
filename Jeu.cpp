#include "Jeu.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

Jeu::Jeu(int lignes, int colonnes, std::unique_ptr<Regle> r)
    : grille(lignes, colonnes), regle(std::move(r)) {
}

void Jeu::chargerDepuisFichier(const std::string& chemin) {
    // Déléguer au membre grille pour qu'il réutilise ses ressources
    grille.chargerDepuisFichier(chemin);
}

void Jeu::sauvegarderDansFichier(const std::string& chemin) const {
    std::ofstream file(chemin);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + chemin);
    }

    // ✅ CORRECTION : Format correct = hauteur largeur
    file << grille.getHauteur() << " " << grille.getLargeur() << "\n";

    // ✅ CORRECTION : Boucle sur hauteur puis largeur
    for (int i = 0; i < grille.getHauteur(); ++i) {
        for (int j = 0; j < grille.getLargeur(); ++j) {
            Cellule* c = grille.getCellule(j, i);
            file << (c->estVivante() ? 1 : 0) << " ";
        }
        file << "\n";
    }

    file.close();
}

void Jeu::mettreAJour() {
    grille.appliquerRegle(*regle);
}