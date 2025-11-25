#pragma once
#include "Cellule.h"

class CelluleVivante : public Cellule {
public:
    CelluleVivante();                  // construit une cellule vivante
    CelluleVivante(bool etat);         // constructeur générique
    virtual ~CelluleVivante() = default;

    virtual void calculerEtatFutur(const Regle& regle, int nbVoisinsVivants) override;
    virtual char afficher() const override;
};
