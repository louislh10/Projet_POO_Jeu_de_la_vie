#pragma once
#include "Regle.h"

class RegleC : public Regle {
public:
    virtual ~RegleC() = default;
    virtual bool doitVivre(bool estVivante, int nbVoisinsVivants) const override;
};