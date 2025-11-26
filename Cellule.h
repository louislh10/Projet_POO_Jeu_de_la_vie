
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

    // calcul de l'état futur (délégué à la Regle)
    void calculerEtatFutur(const Regle& regle, int nbVoisinsVivants);

    // applique l'état futur -> devient l'état actuel
    void appliquerEtatFutur();

    // accesseurs
    bool estVivante() const;
    bool getEtatFutur() const;
    void setEtatFutur(bool nouvelEtat);

    // doit être défini par les classes concrètes pour affichage
    virtual char afficher() const = 0;
};