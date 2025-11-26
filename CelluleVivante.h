
#pragma once
#include "Cellule.h"

class CelluleVivante : public Cellule {
public:
    CelluleVivante();
    explicit CelluleVivante(bool etat);
    virtual ~CelluleVivante() = default;

    virtual char afficher() const override;
};