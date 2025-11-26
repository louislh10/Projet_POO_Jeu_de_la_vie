#include "Cellule.h"
#include "Regle.h"

Cellule::Cellule(bool etat) : etatActuel(etat), etatFutur(etat) {}

Cellule::~Cellule() = default;

void Cellule::calculerEtatFutur(const Regle& regle, int nbVoisinsVivants) {
    // déléguer la logique à la règle
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