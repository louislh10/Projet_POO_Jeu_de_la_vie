#pragma once
#include "Regle.h"

class RegleConway : public Regle {
public:
    virtual ~RegleConway() = default;
    virtual bool doitVivre(bool estVivante, int nbVoisinsVivants) const override;
};