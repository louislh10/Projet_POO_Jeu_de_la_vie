#include "CelluleMorte.h"

CelluleMorte::CelluleMorte() : Cellule(false) {}

char CelluleMorte::afficher() const {
    return '.';
}