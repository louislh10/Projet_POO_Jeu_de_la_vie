
#pragma once
#include <memory>

class Regle;

class Cellule {
protected: 
    bool etatActuel;
    bool etatFutur;

public:
    explicit Cellule(bool etat = false);
    virtual ~Cellule();

    // calcul de letat futur
    void calculerEtatFutur(const Regle& regle, int nbVoisinsVivants);

    
    void appliquerEtatFutur();

   
    bool estVivante() const;
    bool getEtatFutur() const;
    void setEtatFutur(bool nouvelEtat);

    
    virtual char afficher() const = 0;
};