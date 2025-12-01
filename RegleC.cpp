#include "RegleC.h"

// Règle de Conway : 
// - une cellule vivante survit si elle a 2 ou 3 voisins vivants
// - une cellule morte devient vivante si elle a exactement 3 voisins vivants
bool RegleC::doitVivre(bool estVivante, int nbVoisinsVivants) const {
    if (estVivante) {
        return (nbVoisinsVivants == 2 || nbVoisinsVivants == 3);
    }
    else {
        return (nbVoisinsVivants == 3);
    }
}