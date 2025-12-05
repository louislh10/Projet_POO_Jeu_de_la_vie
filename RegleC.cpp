#include "RegleC.h"


bool RegleC::doitVivre(bool estVivante, int nbVoisinsVivants) const {
    if (estVivante) {
        return (nbVoisinsVivants == 2 || nbVoisinsVivants == 3); 
    }
    else {
        return (nbVoisinsVivants == 3); 
    }
}

//rappel regles: une cellule vivante avec 2 ou 3 voisins vivants survit sinon
//une cellule morte avec 3 voisins vivants devient vivante