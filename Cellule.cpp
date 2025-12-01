#include "Cellule.h"
#include "Regle.h"

Cellule::Cellule(bool etat) : etatActuel(etat), etatFutur(etat) {}

Cellule::~Cellule() = default;

void Cellule::calculerEtatFutur(const Regle& regle, int nbVoisinsVivants) { // permet de calculer l' etat futur de la cellule 
    etatFutur = regle.doitVivre(etatActuel, nbVoisinsVivants);
}

void Cellule::appliquerEtatFutur() {
    etatActuel = etatFutur;
}

bool Cellule::estVivante() const {
    return etatActuel;
}

bool Cellule::getEtatFutur() const {
    return etatFutur;
}

void Cellule::setEtatFutur(bool nouvelEtat) {
    etatFutur = nouvelEtat;
}