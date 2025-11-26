
#include "Grille.h"
#include "CelluleVivante.h"
#include "CelluleMorte.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

// Constructeur
Grille::Grille(int l, int h) : largeur(l), hauteur(h) {
    cellules.resize(hauteur);
    for (int y = 0; y < hauteur; ++y) {
        cellules[y].resize(largeur);
        for (int x = 0; x < largeur; ++x) {
            cellules[y][x] = std::make_unique<CelluleMorte>();
        }
    }
}

// Définir le destructeur dans le .cpp pour que Cellule soit complet ici
Grille::~Grille() = default;

// Libérer toutes les cellules (réinitialiser les unique_ptr)
void Grille::libererCellules() {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            cellules[y][x].reset();
        }
    }
}

// Accesseurs
int Grille::getLargeur() const { return largeur; }
int Grille::getHauteur() const { return hauteur; }

void Grille::setCelluleVivante(int x, int y) {
    if (!dansBornes(x, y)) {
        std::cerr << "Erreur setCelluleVivante : indices hors bornes (" << x << ", " << y << ")\n";
        return;
    }
    cellules[y][x] = std::make_unique<CelluleVivante>();
}

void Grille::setCelluleMorte(int x, int y) {
    if (!dansBornes(x, y)) {
        std::cerr << "Erreur setCelluleMorte : indices hors bornes (" << x << ", " << y << ")\n";
        return;
    }
    cellules[y][x] = std::make_unique<CelluleMorte>();
}

bool Grille::estVivante(int x, int y) const {
    if (!dansBornes(x, y)) return false;
    const auto& ptr = cellules[y][x];
    return ptr ? ptr->estVivante() : false;
}

Cellule* Grille::getCellule(int x, int y) const {
    if (!dansBornes(x, y)) return nullptr;
    return cellules[y][x].get();
}

bool Grille::dansBornes(int x, int y) const {
    return x >= 0 && x < largeur && y >= 0 && y < hauteur;
}

int Grille::compterVoisinsVivants(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (dansBornes(nx, ny) && cellules[ny][nx]) {
                if (cellules[ny][nx]->estVivante()) count++;
            }
        }
    }
    return count;
}

void Grille::appliquerRegle(const Regle& regle) {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[y][x]) {
                int nbVoisins = compterVoisinsVivants(x, y);
                cellules[y][x]->calculerEtatFutur(regle, nbVoisins);
            }
        }
    }

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (!cellules[y][x]) continue;
            bool etatActuel = cellules[y][x]->estVivante();
            bool etatFutur = cellules[y][x]->getEtatFutur();
            if (etatActuel != etatFutur) {
                if (etatFutur)
                    cellules[y][x] = std::make_unique<CelluleVivante>();
                else
                    cellules[y][x] = std::make_unique<CelluleMorte>();
            }
            cellules[y][x]->appliquerEtatFutur();
        }
    }
}


void Grille::chargerDepuisFichier(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier " + filename);
    }

    int h, l;
    file >> h >> l;
    if (h <= 0 || l <= 0) throw std::runtime_error("Dimensions invalides dans le fichier");

    libererCellules();

    // Redimensionner sans copier des vecteurs contenant des unique_ptr
    largeur = l;
    hauteur = h;
    cellules.clear();
    cellules.resize(hauteur);
    for (int y = 0; y < hauteur; ++y) {
        cellules[y].resize(largeur); // default-construct unique_ptr (null)
    }

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int val = 0;
            if (!(file >> val)) val = 0;
            if (val == 1) cellules[y][x] = std::make_unique<CelluleVivante>();
            else cellules[y][x] = std::make_unique<CelluleMorte>();
        }
    }

    file.close();
    std::cout << "Grille chargée : largeur = " << largeur << ", hauteur = " << hauteur << std::endl;
}