#include "pch.h"
#include "CppUnitTest.h"

#include <vector>
#include <fstream>

#include "../Jeu.h"
#include "../RegleC.h"
#include "../Cellule.h" 
#include "../Grille.h"
#include "../CelluleMorte.h" 
#include "../CelluleVivante.h"
#include "../Regle.h"
#include <memory>
#include "../Jeu.cpp"
#include "../RegleC.cpp"
#include "../Cellule.cpp" 
#include "../Grille.cpp"
#include "../CelluleMorte.cpp" 
#include "../CelluleVivante.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetPOOJeudelavietest
{
  
    TEST_CLASS(TestGrilleSimple)
    {
    public:
        TEST_METHOD(Test_Block_Reste_Stable)
        {
            //grille initale 
            std::vector<std::vector<int>> debut = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            };

            // bloc censé rester pareil
            std::vector<std::vector<int>> attendu = debut;

            int h = static_cast<int>(debut.size());
            int w = static_cast<int>(debut[0].size());

            Grille g(w, h);
            g.initialiserDepuisMatrice(debut);

            RegleC regle;

            // 5 iter
            for (int i = 0; i < 5; i++) {
                g.appliquerRegle(regle);
            }

            
            std::vector<std::vector<int>> resultat = g.convertirEnMatrice();

            
            Assert::AreEqual(attendu.size(), resultat.size());

            for (size_t i = 0; i < attendu.size(); i++) {
                Assert::AreEqual(attendu[i].size(), resultat[i].size());
                for (size_t j = 0; j < attendu[i].size(); j++) {
                    Assert::AreEqual(attendu[i][j], resultat[i][j]);
                }
            }
        }
    };

    //test de sauvegarde dans un fichier
    TEST_CLASS(TestSauvegardeFichier)
    {
    public:
        TEST_METHOD(Test_Sauvegarde_Apres_5_Iterations)
        {
            std::string fichierEntree = "testfichier.txt";
            std::string fichierSortie = "testfichier_out/iter_5.txt";

           
            Jeu jeu(1, 1, std::make_unique<RegleC>());

            
            try {
                jeu.chargerDepuisFichier(fichierEntree);
            }
            catch (const std::exception& e) {
                std::string msg = "Erreur lecture: ";
                msg += e.what();
                Assert::Fail(std::wstring(msg.begin(), msg.end()).c_str());
            }
            for (int i = 0; i < 5; i++) {
                jeu.mettreAJour();
            }
            try {
                jeu.sauvegarderDansFichier(fichierSortie);
            }
            catch (const std::exception& e) {
                std::string msg = "Erreur sauvegarde: ";
                msg += e.what();
                Assert::Fail(std::wstring(msg.begin(), msg.end()).c_str());
            }

           //fichier contient bien qqch ?
            std::ifstream fichier(fichierSortie);
            Assert::IsTrue(fichier.is_open(), L"Le fichier n'a pas été créé");

            //verif pas vide
            std::string ligne;
            bool pasVide = false;
            while (std::getline(fichier, ligne)) {
                if (!ligne.empty()) {
                    pasVide = true;
                    break;
                }
            }

            Assert::IsTrue(pasVide, L"Le fichier est vide");
            fichier.close();
        }
    };
