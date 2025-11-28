#include "Jeu.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace fs = std::filesystem;

Jeu::Jeu(int lignes, int colonnes, std::unique_ptr<Regle> r)
    : grille(lignes, colonnes), regle(std::move(r)) {
}

void Jeu::chargerDepuisFichier(const std::string& chemin) {
    // Déléguer au membre grille pour qu'il réutilise ses ressources
    grille.chargerDepuisFichier(chemin);
}

void Jeu::sauvegarderDansFichier(const std::string& _chemin) const {

	fs::path chemin(_chemin);

    if (!chemin.parent_path().empty() && !fs::exists(chemin.parent_path())) {
        fs::create_directories(chemin.parent_path());

    }
    
    std::ofstream file(chemin);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + _chemin);
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