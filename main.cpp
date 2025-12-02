#include <iostream>
#include <thread>
#include <chrono>
#include "Jeu.h"
#include "RegleC.h"
#include "FenetreSFML.h"
#include "Cellule.h" // AJOUT : inclure le header complet de Cellule

using namespace std;

// Affichage console
void afficherConsole(const Jeu& jeu) {
    const Grille& g = jeu.getGrille();
    for (int y = 0; y < g.getHauteur(); ++y) {
        for (int x = 0; x < g.getLargeur(); ++x) {
            Cellule* c = g.getCellule(x, y);
            if (c != nullptr) {
                cout << (c->estVivante() ? '#' : '.'); // choix d'utilisé # a la place 1 et . a la place du 0 pour une meilleure visibilité en mode console
            }
            else {
                cout << '.'; 
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cout << " Jeu de la Vie de Louis Le Hel et Louis Fritz- John Conway \n";
    cout << "1 - Mode console\n";
    cout << "2 - Mode graphique avec la fenetre SFML\n";
    cout << "Votre choix : ";

    int choix;
    if (!(cin >> choix)) {
        cerr << "Entrée invalide.\n";
        return 1;
    }

    string fichier;
    cout << "Entrez le fichier de configuration (testfichier.txt) : ";
    if (!(cin >> fichier)) {
        cerr << "nom fichier invalide.\n";
        return 1;
    }

    // creation jeu
    Jeu jeu(1, 1, make_unique<RegleC>());

    try { 
        jeu.chargerDepuisFichier(fichier);
    }
    catch (const exception& e) { 
        cerr << "erreur : " << e.what() << endl;
        return 1;
    }

    cout << "\n Grille initiale de testfichier.txt :\n";
    afficherConsole(jeu);

    if (choix == 1) { // Mode console
        int max_iter;
        cout << "Entrez le nb iterations de votre choix : ";
        while (!(cin >> max_iter) || max_iter <= 0) {
            cerr << "Entree non valide..\n";
            cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // le buffer signifie qu'on vide le flux d'entrée pour éviter une boucle infinie
			cout << "Entrez le nb iterations de votre choix : ";
        }
        int iteration = 0;
        while (iteration < max_iter) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "Iteration numero : " << iteration << " \n";
            afficherConsole(jeu);

            jeu.mettreAJour();
            iteration++;

			string path = fichier.substr(0, fichier.length()-4) + "_out/iter" + to_string(iteration) + ".txt";
            jeu.sauvegarderDansFichier(path);

            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
    else if (choix == 2) {  // Mode graphique avec SFML
        FenetreSFML fenetre(jeu, 20);
        fenetre.afficher();
    }
    else {
        cout << "choix non valide.\n";
    }

    return 0;
}