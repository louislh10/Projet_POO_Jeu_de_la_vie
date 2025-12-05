#include "CelluleVivante.h"

CelluleVivante::CelluleVivante() : Cellule(true) {}
CelluleVivante::CelluleVivante(bool etat) : Cellule(etat) {}

char CelluleVivante::afficher() const {

    return '#';


}