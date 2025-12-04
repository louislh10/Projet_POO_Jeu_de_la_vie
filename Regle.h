#pragma once

class Regle {
public:
    virtual ~Regle() = default;
    // retourne true si la cellule doit être vivante au tour suivant
    virtual bool doitVivre(bool estVivante, int nbVoisinsVivants) const = 0; 
};