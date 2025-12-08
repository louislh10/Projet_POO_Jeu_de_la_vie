#include "Jeu.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <direct.h>  //pour mkdir 
#include <sys/stat.h>

Jeu::Jeu(int lignes, int colonnes, std::unique_ptr<Regle> r)
    : grille(lignes, colonnes), regle(std::move(r)) {
}

void Jeu::chargerDepuisFichier(const std::string& chemin) {
    grille.chargerDepuisFichier(chemin);
}

void Jeu::sauvegarderDansFichier(const std::string& chemin) const {
    size_t pos = chemin.find_last_of("/\\"); 
    if (pos != std::string::npos) {
        std::string dossier = chemin.substr(0, pos);

        // verif dossier existe deja ou pas
        struct stat info;
        if (stat(dossier.c_str(), &info) != 0) {
            // Le dossier existe pas on creer
#ifdef _WIN32
            int result = _mkdir(dossier.c_str());
            (void)result;//ignoré le resulat pcq le compilateur met un warn
#else
            mkdir(dossier.c_str(),0755); //(si madame gaudon utilise linux)
#endif 
        }
    }

    std::ofstream file(chemin);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + chemin);
    }

    
    file << grille.getHauteur() << " " << grille.getLargeur() << "\n";



    for (int i = 0; i < grille.getHauteur(); ++i) {
        for (int j = 0; j < grille.getLargeur(); ++j) {
            Cellule* c = grille.getCellule(j, i);
            if (c && c->estVivante()) {
                file << "1 ";
            }
            else {
                file << "0 ";
            }
        }
        file << "\n";
    }

    file.close();
}

void Jeu::mettreAJour() {
    grille.appliquerRegle(*regle);
}