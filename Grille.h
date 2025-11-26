
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Cellule.h"   // <- assure le type complet pour tous les TU qui incluent Grille.h
class Regle;

class Grille {
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<std::unique_ptr<Cellule>>> cellules;

public:
    Grille(int largeur, int hauteur);
    ~Grille(); // défini dans Grille.cpp, afin que Cellule soit complet à la destruction

    void libererCellules();

    int getLargeur() const;
    int getHauteur() const;

    void setCelluleVivante(int x, int y);
    void setCelluleMorte(int x, int y);
    bool estVivante(int x, int y) const;

    int compterVoisinsVivants(int x, int y) const;
    void appliquerRegle(const Regle& regle);

    Cellule* getCellule(int x, int y) const;
    bool dansBornes(int x, int y) const;

    void chargerDepuisFichier(const std::string& filename);
};