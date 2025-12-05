#ifndef JEU_H
#define JEU_H

#include <string>
#include <memory>
#include "Grille.h"
#include "Regle.h"

class Jeu {
private:
    Grille grille;
    std::unique_ptr<Regle> regle;

public:
    Jeu(int lignes, int colonnes, std::unique_ptr<Regle> r);

    void chargerDepuisFichier(const std::string& chemin);
    void sauvegarderDansFichier(const std::string& chemin) const;
    void mettreAJour();

    const Grille& getGrille() const { return grille; }
};

#endif //fichier inclu une fois