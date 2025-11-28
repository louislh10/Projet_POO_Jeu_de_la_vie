#include <iostream>
#include <thread>
#include <chrono>
#include "Jeu.h"
#include "RegleConway.h"
#include "FenetreSFML.h"
#include "Cellule.h" // AJOUT : inclure le header complet de Cellule

using namespace std;

// Affichage console
void afficherConsole(const Jeu& jeu) {
    const Grille& g = jeu.getGrille();
    for (int y = 0; y < g.getHauteur(); ++y) {
        for (int x = 0; x < g.getLargeur(); ++x) {
            Cellule* c = g.getCellule(x, y);
            // Vérification de nullité pour éviter le crash lors du déréférencement
            if (c != nullptr) {
                cout << (c->estVivante() ? '#' : '.');
            }
            else {
                cout << '.'; // cellule invalide affichée comme morte
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cout << "=== Jeu de la Vie - Conway ===\n";
    cout << "1 - Mode console\n";
    cout << "2 - Mode graphique (SFML)\n";
    cout << "Votre choix : ";

    int choix;
    if (!(cin >> choix)) {
        cerr << "Entrée invalide.\n";
        return 1;
    }

    string fichier;
    cout << "Entrez le fichier de configuration (ex: testfichier.txt) : ";
    if (!(cin >> fichier)) {
        cerr << "Nom de fichier invalide.\n";
        return 1;
    }

    // Création du jeu avec la règle de Conway
    Jeu jeu(1, 1, make_unique<RegleConway>());

    try {
        jeu.chargerDepuisFichier(fichier);
    }
    catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }

    cout << "\nGrille initiale :\n";
    afficherConsole(jeu);

    if (choix == 1) {
        // Mode console
        int max_iter;
        cout << "Entrez le nb iter : ";
        while (!(cin >> max_iter) || max_iter <= 0) {
            cerr << "Entrée invalide. Veuillez entrer un nombre positif.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        int iteration = 0;
        while (iteration < max_iter) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "=== Iteration " << iteration << " ===\n";
            afficherConsole(jeu);

            jeu.mettreAJour();
            iteration++;

			string path = fichier.substr(0, fichier.length()-4) + "_out/iter" + to_string(iteration) + ".txt";
            jeu.sauvegarderDansFichier(path);

            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
    else if (choix == 2) {
        // Mode graphique SFML
        FenetreSFML fenetre(jeu, 20);
        fenetre.afficher();
    }
    else {
        cout << "Choix invalide.\n";
    }

    return 0;
}