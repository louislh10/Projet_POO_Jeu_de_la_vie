#pragma once

class Regle {
public:
    virtual ~Regle() = default;
  
    virtual bool doitVivre(bool estVivante, int nbVoisinsVivants) const = 0; 
};