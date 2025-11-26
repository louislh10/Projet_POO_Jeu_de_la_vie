
#pragma once
#include "Cellule.h"

class CelluleMorte : public Cellule {
public:
    CelluleMorte();
    virtual ~CelluleMorte() = default;

    virtual char afficher() const override;
};