#pragma once
#include "Cellule.h"

class CelluleMorte : public Cellule {
public:
    CelluleMorte();
    CelluleMorte(bool etat);
    virtual ~CelluleMorte() = default;

    virtual void calculerEtatFutur(const Regle& regle, int nbVoisinsVivants) override;
    virtual char afficher() const override;
};
