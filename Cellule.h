#pragma once

// forward declaration pour éviter inclusion cyclique
class Regle;

class Cellule {
protected:
    bool etatActuel;
    bool etatFutur;

public:
    Cellule(bool etat = false);
    virtual ~Cellule() = default;

    // calculer l'état futur en délégant au calcul de la règle
    virtual void calculerEtatFutur(const Regle& regle, int nbVoisinsVivants) = 0;

    // applique l'état futur -> devient l'état actuel
    void appliquerEtatFutur();

    // accesseurs
    bool estVivante() const;
    void setEtatFutur(bool nouvelEtat);
    bool getEtatFutur() const;

    // retourne un caractère pour affichage console ('#' = vivante, '.' = morte)
    virtual char afficher() const = 0;
};
